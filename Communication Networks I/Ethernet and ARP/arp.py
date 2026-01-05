'''
    arp.py
    Implementación del protocolo ARP y funciones auxiliares que permiten realizar resoluciones de direcciones IP.
    Autor: Javier Ramos <javier.ramos@uam.es>
    2019 EPS-UAM
'''



from ethernet import *
import logging
import socket
import struct
import fcntl
import time
from threading import Lock
from expiringdict import ExpiringDict

#Semáforo global 
globalLock =Lock()
#Dirección de difusión (Broadcast)
broadcastAddr = bytes([0xFF]*6)
#Cabecera ARP común a peticiones y respuestas. Específica para la combinación Ethernet/IP
ARPHeader = bytes([0x00,0x01,0x08,0x00,0x06,0x04])
#longitud (en bytes) de la cabecera común ARP
ARP_HLEN = 6

#Variable que alamacenará que dirección IP se está intentando resolver
requestedIP = None
#Variable que alamacenará que dirección MAC resuelta o None si no se ha podido obtener
resolvedMAC = None
#Variable que alamacenará True mientras estemos esperando una respuesta ARP
awaitingResponse = False

#Variable para proteger la caché
cacheLock = Lock()
#Caché de ARP. Es un diccionario similar al estándar de Python solo que eliminará las entradas a los 10 segundos
cache = ExpiringDict(max_len=100, max_age_seconds=10)



def getIP(interface:str) -> int:
    '''
        Nombre: getIP
        Descripción: Esta función obtiene la dirección IP asociada a una interfaz. Esta funció NO debe ser modificada
        Argumentos:
            -interface: nombre de la interfaz
        Retorno: Entero de 32 bits con la dirección IP de la interfaz
    '''

    #print("\033[93m\n[DEBUG]: === getIP === \033[0m")
    
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    ip = fcntl.ioctl(
        s.fileno(),
        0x8915,  # SIOCGIFADDR
        struct.pack('256s', (interface[:15].encode('utf-8')))
    )[20:24]
    s.close()
    return struct.unpack('!I',ip)[0]

def printCache()->None:
    '''
        Nombre: printCache
        Descripción: Esta función imprime la caché ARP
        Argumentos: Ninguno
        Retorno: Ninguno
    '''

    #print("[DEBUG]: === printCache === ")

    print('{:>12}\t\t{:>12}'.format('IP','MAC'))
    with cacheLock:
        cache_copy = {k: v for k, v in cache.items()}
        
        for k in cache_copy:
            if k in cache_copy:
                print ('{:>12}\t\t{:>12}'.format(socket.inet_ntoa(struct.pack('!I',k)),':'.join(['{:02X}'.format(b) for b in cache_copy[k]])))



def processARPRequest(data:bytes,MAC:bytes)->None:
    '''
        Nombre: processARPRequest
        Decripción: Esta función procesa una petición ARP. Esta función debe realizar, al menos, las siguientes tareas:
            -Extraer la MAC origen contenida en la petición ARP
            -Si la MAC origen de la trama ARP no es la misma que la recibida del nivel Ethernet retornar
            -Extraer la IP origen contenida en la petición ARP
            -Extraer la IP destino contenida en la petición ARP
            -Comprobar si la IP destino de la petición ARP es la propia IP:
                -Si no es la propia IP retornar
                -Si es la propia IP:
                    -Construir una respuesta ARP llamando a createARPReply (descripción más adelante)
                    -Enviar la respuesta ARP usando el nivel Ethernet (sendEthernetFrame)
        Argumentos:
            -data: bytearray con el contenido de la trama ARP (después de la cabecera común)
            -MAC: dirección MAC origen extraída por el nivel Ethernet
        Retorno: Ninguno
    '''

    #Extraer la MAC destino
    #print("\033[93m\n[DEBUG]: === processARPRequest === \033[0m")
    #print(f"[DEBUG][processARPRequest]: MAC origen pasada como parámetro: [{MAC}]")

    MAC_origen_paquete = data[8:14]   
    
    #print(f"[DEBUG][processARPRequest]: MAC origen extraída del paquete: [{MAC_origen_paquete}]") 

    #No se pide en el enunciado pero vamos a actualizar la caché con la MAC origen y la IP origen
    IP_origen = struct.unpack("!I", data[14:18])[0]
    with cacheLock:
        cache[IP_origen] = MAC_origen_paquete


    if (MAC != MAC_origen_paquete):
        #print(f"[DEBUG][processARPRequest]: {"\033[31m"} ERROR {"\033[0m"}. La MAC origen pasada como parámetro NO COINCIDE con la del paquete: [{MAC}] != [{MAC_origen_paquete}]")
        #print("\n")
        return
    
    IP_origen = struct.unpack("!I", data[14:18])[0]
    IP_destino = struct.unpack("!I", data[24:28])[0]

    #IP_origen = data[14:18]
    #IP_destino = data[24:28]

    #print(f"data[13:17]: { data[13:17]}, data[14:18]: {data[14:18]}, data[15:19]: {data[15:19]}")

   #print("[DEBUG][processARPRequest]: IP_origen:",IP_origen ,"--", hexlify(data[14:18]))
   #print("[DEBUG][processARPRequest]: IP_destino:", IP_destino,"--", hexlify(data[24:28]))

    if IP_destino == myIP:
        reply = createARPReply(IP_origen, MAC)
        #print("[DEBUG][processARPRequest]: ARPReply: ", reply)
        sendEthernetFrame(reply, len(reply), 0x0806, MAC_origen_paquete) #0x0806 ethertype ARP

    

    return
    


def processARPReply(data:bytes,MAC:bytes)->None:
    '''
        Nombre: processARPReply
        Decripción: Esta función procesa una respuesta ARP. Esta función debe realizar, al menos, las siguientes tareas:
            -Extraer la MAC origen contenida en la petición ARP
            -Si la MAC origen de la trama ARP no es la misma que la recibida del nivel Ethernet retornar
            -Extraer la IP origen contenida en la petición ARP
            -Extraer la MAC destino contenida en la petición ARP
            -Extraer la IP destino contenida en la petición ARP
            -Comprobar si la IP destino de la petición ARP es la propia IP:
                -Si no es la propia IP retornar
                -Si es la propia IP:
                    -Comprobar si la IP origen se corresponde con la solicitada (requestedIP). Si no se corresponde retornar
                    -Copiar la MAC origen a la variable global resolvedMAC
                    -Añadir a la caché ARP la asociación MAC/IP.
                    -Cambiar el valor de la variable awaitingResponse a False
                    -Cambiar el valor de la variable requestedIP a None
        Las variables globales (requestedIP, awaitingResponse y resolvedMAC) son accedidas concurrentemente por la función ARPResolution y deben ser protegidas mediante un Lock.
        Argumentos:
            -data: bytearray con el contenido de la trama ARP (después de la cabecera común)
            -MAC: dirección MAC origen extraída por el nivel Ethernet
        Retorno: Ninguno
    '''
    global requestedIP,resolvedMAC,awaitingResponse,cache

    #print("\033[93m\n[DEBUG]: === processARPReply === \033[0m")
    
    MAC_origen_paquete = data[8:14]

    #print("\n")

    if (MAC!=MAC_origen_paquete):
        return
    
    IP_origen = struct.unpack("!I", data[14:18])[0]
    IP_destino = struct.unpack("!I", data[24:28])[0]
    #MAC_destino_paquete = struct.unpack("!H", data[18:24])[0]

    with globalLock:
        if(myIP != IP_destino):
            return

        if (IP_origen != requestedIP):
            return
        
        resolvedMAC = MAC_origen_paquete        
        
        with cacheLock:
            cache[requestedIP] = resolvedMAC
        
        #print(f"[DEBUG][processARPReply]: cache({resolvedMAC}) <= {requestedIP}")
        awaitingResponse = False
        requestedIP = None
    return
    

def createARPRequest(ip:int) -> bytes:
    '''
        Nombre: createARPRequest
        Descripción: Esta función construye una petición ARP y devuelve la trama con el contenido.
        Argumentos: 
            -ip: dirección a resolver 
        Retorno: Bytes con el contenido de la trama de petición ARP
    '''
    
    global myMAC,myIP

    #print("\033[93m\n[DEBUG]: === createARPRequest === \033[0m") 

    frame = bytes()
    frame += ARPHeader
    frame += struct.pack('!H',0x0001) #Opcode 0x0001 para petición
    frame += myMAC
    frame += struct.pack('!I', myIP) #ip origen
    
    #print("[DEBUG][createARPRequest]: unpacked packed ip: (myIP): ", struct.unpack('!I', struct.pack('!I', myIP)))

    frame += bytes([0x00]*6) #Dirección MAC destino
    frame += struct.pack('!I', ip) #Dirección IP destino
    
    #print("[DEBUG][createARPRequest]: frame: ", frame)

    return frame

    
def createARPReply(IP:int ,MAC:bytes) -> bytes:
    '''
        Nombre: createARPReply
        Descripción: Esta función construye una respuesta ARP y devuelve la trama con el contenido.
        Argumentos: 
            -IP: dirección IP a la que contestar
            -MAC: dirección MAC a la que contestar
        Retorno: Bytes con el contenido de la trama de petición ARP
    '''
    global myMAC,myIP

    #print("\033[93m\n[DEBUG]: === createARPReply === \033[0m") 

    frame = bytes()
    frame += ARPHeader
    frame += struct.pack('!H',0x0002) #Opcode 0x0002 para respuesta
    frame += myMAC
    frame += struct.pack('!I',myIP)
    frame += MAC
    frame += struct.pack('!I',IP)

    #print("[DEBUG][createARPReply]: ip a la que contestar: ", IP)
    #print("[DEBUG][createARPReply]: frame: ", frame)    

    return frame


def process_arp_frame(us:ctypes.c_void_p,header:pcap_pkthdr,data:bytes,srcMac:bytes) -> None:
    '''
        Nombre: process_arp_frame
        Descripción: Esta función procesa las tramas ARP. 
            Se ejecutará por cada trama Ethenet que se reciba con Ethertype 0x0806 (si ha sido registrada en initARP). 
            Esta función debe realizar, al menos, las siguientes tareas:
                -Extraer la cabecera común de ARP (6 primeros bytes) y comprobar que es correcta
                -Extraer el campo opcode
                -Si opcode es 0x0001 (Request) llamar a processARPRequest (ver descripción más adelante)
                -Si opcode es 0x0002 (Reply) llamar a processARPReply (ver descripción más adelante)
                -Si es otro opcode retornar de la función
                -En caso de que no exista retornar
        Argumentos:
            -us: Datos de usuario pasados desde la llamada de pcap_loop. En nuestro caso será None
            -header: cabecera pcap_pktheader
            -data: array de bytes con el contenido de la trama ARP
            -srcMac: MAC origen de la trama Ethernet que se ha recibido
        Retorno: Ninguno
    '''

    #print("\033[93m\n[DEBUG]: === process_arp_frame === \033[0m") 

    opcode = struct.unpack('!H', data[6:8])[0]
    if data[0:6] != ARPHeader:
        return
    if opcode == 0x0001:
        #print("[DEBUG][process_arp_frame]: opcode 0x0001")
        processARPRequest(data,srcMac)
    elif opcode == 0x0002:
        processARPReply(data,srcMac)
    
    return
    


def initARP(interface:str) -> int:
    '''
        Nombre: initARP
        Descripción: Esta función construirá inicializará el nivel ARP. Esta función debe realizar, al menos, las siguientes tareas:
            -Registrar la función del callback process_arp_frame con el Ethertype 0x0806
            -Obtener y almacenar la dirección MAC e IP asociadas a la interfaz especificada
            -Realizar una petición ARP gratuita y comprobar si la IP propia ya está asignada. En caso positivo se debe devolver error.
            -Marcar la variable de nivel ARP inicializado a True
    '''
    global myIP,myMAC,arpInitialized

    #print("\033[93m\n[DEBUG]: === initARP === \033[0m") 

    registerEthCallback(process_arp_frame,0x0806)
    myIP = getIP(interface)
    myMAC = getHwAddr(interface)

    #print(f"[DEBUG][initARP]: my IP: {socket.inet_ntoa(struct.pack('!I',myIP))}")
    #print(f"[DEBUG][initARP]: my MAC: {':'.join(['{:02X}'.format(b) for b in myMAC])}")

    if (ARPResolution(myIP) != None):
        return -1

    with cacheLock:        
        cache[myIP] = myMAC        
        #print(f"[DEBUG][initARP]: cache({myIP}) <= {myMAC}")

    arpInitialized = True
    
    return 0

def ARPResolution(ip:int) -> bytes:
    '''
        Nombre: ARPResolution
        Descripción: Esta función intenta realizar una resolución ARP para una IP dada y devuelve la dirección MAC asociada a dicha IP 
            o None en caso de que no haya recibido respuesta. Esta función debe realizar, al menos, las siguientes tareas:
                -Comprobar si la IP solicitada existe en la caché:
                -Si está en caché devolver la información de la caché
                -Si no está en la caché:
                    -Construir una petición ARP llamando a la función createARPRequest (descripción más adelante)
                    -Enviar dicha petición
                    -Comprobar si se ha recibido respuesta o no:
                        -Si no se ha recibido respuesta reenviar la petición hasta un máximo de 3 veces. Si no se recibe respuesta devolver None
                        -Si se ha recibido respuesta devolver la dirección MAC
            Esta función necesitará comunicarse con el la función de recepción (para comprobar si hay respuesta y la respuesta en sí) mediante 3 variables globales:
                -awaitingResponse: indica si está True que se espera respuesta. Si está a False quiere decir que se ha recibido respuesta
                -requestedIP: contiene la IP por la que se está preguntando
                -resolvedMAC: contiene la dirección MAC resuelta (en caso de que awaitingResponse) sea False.
            Como estas variables globales se leen y escriben concurrentemente deben ser protegidas con un Lock
    '''
    global requestedIP,awaitingResponse,resolvedMAC
    i=0

    #print("\033[93m\n[DEBUG]: === ARPResolution === \033[0m") 
    with cacheLock:
        if (ip in cache):
            #print(f"[DEBUG][ARPResolution] ip {ip} in cache") 
            return cache[ip]
    
    #print(f"[DEBUG][ARPResolution] ip {ip} NOT in cache. Waiting for lock")

    with globalLock:
        awaitingResponse = True
        requestedIP = ip
        resolvedMAC = None

    #print("[DEBUG][ARPResolution] creating request") 

    request = createARPRequest(ip)

    while i < 3:
        with globalLock:
            if not awaitingResponse:
                break
        if sendEthernetFrame(request, len(request), 0x0806, broadcastAddr) != 0:
            return None
        time.sleep(0.1)
        i += 1

    #debug print
    #print("[DEBUG][ARPResolution] resolvedMac: ", resolvedMAC)

    with globalLock:
        if not awaitingResponse and resolvedMAC != None:
            return resolvedMAC
        
    return None


