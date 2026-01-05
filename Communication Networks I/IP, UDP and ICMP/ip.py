'''
    ip.py
    
    Funciones necesarias para implementar el nivel IP
    Autor: Javier Ramos <javier.ramos@uam.es>
    2022 EPS-UAM
'''
from ethernet import *
from arp import *
from fcntl import ioctl
import subprocess
from time import sleep
SIOCGIFMTU = 0x8921
SIOCGIFNETMASK = 0x891b
#Diccionario de protocolos. Las claves con los valores numéricos de protocolos de nivel superior a IP
#por ejemplo (1, 6 o 17) y los valores son los nombres de las funciones de callback a ejecutar.
protocols={}
#Tamaño mínimo de la cabecera IP
IP_MIN_HLEN = 20
#Tamaño máximo de la cabecera IP
IP_MAX_HLEN = 60
def chksum(msg):
    '''
        Nombre: chksum
        Descripción: Esta función calcula el checksum IP sobre unos datos de entrada dados (msg)
        Argumentos:
            -msg: array de bytes con el contenido sobre el que se calculará el checksum
        Retorno: Entero de 16 bits con el resultado del checksum en ORDEN DE RED
    '''
    s = 0
    y = 0xa29f    
    for i in range(0, len(msg), 2):
        if (i+1) < len(msg):
            a = msg[i] 
            b = msg[i+1]
            s = s + (a+(b << 8))
        elif (i+1)==len(msg):
            s += msg[i]
        else:
            raise 'Error calculando el checksum'
    y = y & 0x00ff
    s = s + (s >> 16)
    s = ~s & 0xffff

    return s

def getMTU(interface):
    '''
        Nombre: getMTU
        Descripción: Esta función obteiene la MTU para un interfaz dada
        Argumentos:
            -interface: cadena con el nombre la interfaz sobre la que consultar la MTU
        Retorno: Entero con el valor de la MTU para la interfaz especificada
    '''
    s = socket.socket(socket.AF_PACKET, socket.SOCK_RAW)
    ifr = struct.pack('16sH', interface.encode("utf-8"), 0)
    mtu = struct.unpack('16sH', ioctl(s,SIOCGIFMTU, ifr))[1]
   
    s.close()
   
    return mtu
   
def getNetmask(interface):
    '''
        Nombre: getNetmask
        Descripción: Esta función obteiene la máscara de red asignada a una interfaz 
        Argumentos:
            -interface: cadena con el nombre la interfaz sobre la que consultar la máscara
        Retorno: Entero de 32 bits con el valor de la máscara de red
    '''
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    ip = fcntl.ioctl(
        s.fileno(),
       SIOCGIFNETMASK,
        struct.pack('256s', (interface[:15].encode('utf-8')))
    )[20:24]
    s.close()
    return struct.unpack('!I',ip)[0]


def getDefaultGW(interface):
    '''
        Nombre: getDefaultGW
        Descripción: Esta función obteiene el gateway por defecto para una interfaz dada
        Argumentos:
            -interface: cadena con el nombre la interfaz sobre la que consultar el gateway
        Retorno: Entero de 32 bits con la IP del gateway
    '''
    p = subprocess.Popen(['ip r | grep default | awk \'{print $3}\''], stdout=subprocess.PIPE, shell=True)
    dfw = p.stdout.read().decode('utf-8')
    print(dfw)
    return struct.unpack('!I',socket.inet_aton(dfw))[0]



def process_IP_datagram(us,header,data,srcMac):
    '''
        Nombre: process_IP_datagram
        Descripción: Esta función procesa datagramas IP recibidos.
            Se ejecuta una vez por cada trama Ethernet recibida con Ethertype 0x0800
            Esta función debe realizar, al menos, las siguientes tareas:
                -Extraer los campos de la cabecera IP (includa la longitud de la cabecera)
                -Calcular el checksum y comprobar que es correcto                    
                -Analizar los bits de de MF y el offset. Si el offset tiene un valor != 0 dejar de procesar el datagrama (no vamos a reensamblar)
                -Loggear (usando logging.debug) el valor de los siguientes campos:
                    -Longitud de la cabecera IP
                    -IPID
                    -TTL
                    -Valor de las banderas DF y MF
                    -Valor de offset
                    -IP origen y destino
                    -Protocolo
                -Comprobar si tenemos registrada una función de callback de nivel superior consultando el diccionario protocols y usando como
                clave el valor del campo protocolo del datagrama IP.
                    -En caso de que haya una función de nivel superior registrada, debe llamarse a dicha funciñón 
                    pasando los datos (payload) contenidos en el datagrama IP.
        
        Argumentos:
            -us: Datos de usuario pasados desde la llamada de pcap_loop. En nuestro caso será None
            -header: cabecera pcap_pktheader
            -data: array de bytes con el contenido del datagrama IP
            -srcMac: MAC origen de la trama Ethernet que se ha recibido
        Retorno: Ninguno
    '''

    #print("process ip datagram llamado")

    version = getBits(data[0],0,4)
    ihl = getBits(data[0],4,8)*4 # 1 byte : 0
    type = data[1] # 1 byte : 1
    length = data[2:4] # 2 bytes : 2-3
    identification = struct.unpack('!H', data[4:6])[0] # 2 bytes : 4-5

    flags = getBits(data[6],0,3) 
    offset_ms = getBits(data[6],3,8) # parte del offset en byte 6
    offset_ls = data[7]  # parte del offset en byte 7
    offset = ((offset_ms << 8) | offset_ls) * 8 # 2 bytes : 6-7
    
    ttl =  data[8] # 1 byte : 8
    protocol = data[9] # 1 byte : 9
    checksum = struct.unpack('H', data[10:12])[0] # 2 bytes : 10-11
    ip_origen = socket.inet_ntoa(struct.unpack('!4s', data[12:16])[0])
    ip_destino = socket.inet_ntoa(struct.unpack('!4s', data[16:20])[0])

    opciones = data[20:] # Tamaño variable : 20...

    calculated_checksum = chksum(data[0:10] + struct.pack('H', 0x0000) + data[12:])

    if (checksum != calculated_checksum): #or offset != 0x00 or getBits(flags, 7, 8) != 0x00):
        #print(f"\nChecksum incorrecto:\nChecksum del programa{calculated_checksum}--Checksum que nos llega{checksum}")
        #print(f"\nFlags: {flags}, MF: {getBits(flags,7,8)}, Offset: {offset}")
        return
    print("\n")
    logging.debug(f"Length:{ihl}")
    logging.debug(f"ToS:{type}")    
    logging.debug(f"IPID:{identification}")
    logging.debug(f"TTL:{ttl}")
    logging.debug(f"DF:{getBits(flags,6,7)}")
    logging.debug(f"MF:{getBits(flags,7,8)}")
    logging.debug(f"Offset:{offset}")
    logging.debug(f"IP origen:{ip_origen}")
    logging.debug(f"IP destino:{ip_destino}")
    logging.debug(f"Protocol:{protocol}")

    if (offset != 0x00):
        return
    
    #print("processing ip datagram with protocol: ", protocol)

    if (protocol in protocols):
        callback = protocols[protocol]
        callback(us, header, data[ihl:], struct.unpack('!I', data[12:16])[0])
    else:
        print("No protocol registered for ", protocol)


def registerIPProtocol(callback,protocol):
    '''
        Nombre: registerIPProtocol
        Descripción: Esta función recibirá el nombre de una función y su valor de protocolo IP asociado y añadirá en la tabla 
            (diccionario) de protocolos de nivel superior dicha asociación. 
            Este mecanismo nos permite saber a qué función de nivel superior debemos llamar al recibir un datagrama IP  con un 
            determinado valor del campo protocolo (por ejemplo TCP o UDP).
            Por ejemplo, podemos registrar una función llamada process_UDP_datagram asociada al valor de protocolo 17 y otra 
            llamada process_ICMP_message asocaida al valor de protocolo 1. 
        Argumentos:
            -callback_fun: función de callback a ejecutar cuando se reciba el protocolo especificado. 
                La función que se pase como argumento debe tener el siguiente prototipo: funcion(us,header,data,srcIp):
                Dónde:
                    -us: son los datos de usuarios pasados por pcap_loop (en nuestro caso este valor será siempre None)
                    -header: estructura pcap_pkthdr que contiene los campos len, caplen y ts.
                    -data: payload del datagrama IP. Es decir, la cabecera IP NUNCA se pasa hacia arriba.
                    -srcIP: dirección IP que ha enviado el datagrama actual.
                La función no retornará nada. Si un datagrama se quiere descartar basta con hacer un return sin valor y dejará de procesarse.
            -protocol: valor del campo protocolo de IP para el cuál se quiere registrar una función de callback.
        Retorno: Ninguno 
    '''

    #print("registering ip protocol ", protocol)
    protocols[protocol] = callback
    #print(protocols)
    


def initIP(interface,opts=None):
    global myIP, MTU, netmask, defaultGW,ipOpts, IPID
    '''
        Nombre: initIP
        Descripción: Esta función inicializará el nivel IP. Esta función debe realizar, al menos, las siguientes tareas:
            -Llamar a initARP para inicializar el nivel ARP
            -Obtener (llamando a las funciones correspondientes) y almacenar en variables globales los siguientes datos:
                -IP propia
                -MTU
                -Máscara de red (netmask)
                -Gateway por defecto
            -Almacenar el valor de opts en la variable global ipOpts
            -Registrar a nivel Ethernet (llamando a registerCallback) la función process_IP_datagram con el Ethertype 0x0800
            -Inicializar el valor de IPID con el número de pareja
        Argumentos:
            -interface: cadena de texto con el nombre de la interfaz sobre la que inicializar ip
            -opts: array de bytes con las opciones a nivel IP a incluir en los datagramas o None si no hay opciones a añadir
        Retorno: True o False en función de si se ha inicializado el nivel o no
    '''

    if initARP(interface) != 0:
        return False

    myIP = getIP(interface)
    MTU = getMTU(interface)
    #MTU = 658
    netmask = getNetmask(interface)
    defaultGW = getDefaultGW(interface)

    ipOpts = opts
    IPID = 9

    #print("IP inicializado, protocolo %d registrado" % 0x0800)
    registerEthCallback(process_IP_datagram, 0x0800)

    return True


def sendIPDatagram(dstIP, data, protocol):
    global IPID
    '''
        Nombre: sendIPDatagram
        Descripción: Esta función construye un datagrama IP y lo envía. En caso de que los datos a enviar sean muy grandes la función
        debe generar y enviar el número de fragmentos IP que sean necesarios.
        Esta función debe realizar, al menos, las siguientes tareas:
            -Determinar si se debe fragmentar o no y calcular el número de fragmentos
            -Para cada datagrama o fragmento:
                -Construir la cabecera IP con los valores que corresponda.Incluir opciones en caso de que ipOpts sea distinto de None
                -Calcular el checksum sobre la cabecera y añadirlo a la cabecera
                -Añadir los datos a la cabecera IP
                -En el caso de que sea un fragmento ajustar los valores de los campos MF y offset de manera adecuada
                -Enviar el datagrama o fragmento llamando a sendEthernetFrame. Para determinar la dirección MAC de destino
                al enviar los datagramas se debe hacer unso de la máscara de red:                  
            -Para cada datagrama (no fragmento):
                -Incrementar la variable IPID en 1.
        Argumentos:
            -dstIP: entero de 32 bits con la IP destino del datagrama 
            -data: array de bytes con los datos a incluir como payload en el datagrama
            -protocol: valor numérico del campo IP protocolo que indica el protocolo de nivel superior de los datos
            contenidos en el payload. Por ejemplo 1, 6 o 17.
        Retorno: True o False en función de si se ha enviado el datagrama correctamente o no
          
    '''

    opt_size = len(ipOpts) if ipOpts != None else 0
    header_size = IP_MIN_HLEN + opt_size
    fragment_data_size = None    
    fragment_total_size = None
    last_fragment_total_size = None

    if len(data) + header_size < MTU:
        num_fragments = 1
        fragment_data_size = len(data)
        fragment_total_size = len(data) + header_size
        last_fragment_data_size = len(data)
        last_fragment_total_size = last_fragment_data_size + header_size

    else:
        fragment_data_size = MTU - header_size
        while( fragment_data_size % 8 != 0): #ajustamos el tamaño del fragmento para que sea múltiplo de 8
            fragment_data_size -= 1

        fragment_total_size = fragment_data_size + header_size
            
        num_fragments = len(data) // fragment_data_size

        if(num_fragments * fragment_total_size < len(data)):
            num_fragments += 1

        last_fragment_data_size = len(data) % fragment_data_size
        last_fragment_total_size = last_fragment_data_size + header_size
        
    for i in range(num_fragments):
        last = i == (num_fragments - 1)

        ip_header = bytes()
        ip_header += struct.pack('!B', 0x40 | (header_size // 4)) #version y ihl
        ip_header += struct.pack('!B', 0x01) #type of service (siempre 1)

        total_size = fragment_total_size if not last else last_fragment_total_size
        ip_header += struct.pack('!H', total_size)  # longitud total (long cabecera + long payload (fragmento))

        ip_header+= struct.pack('!H', IPID) #identificacion
        
        flags_offset = (0x0000 if last else 0x2000) | (i * fragment_data_size // 8)
        ip_header += struct.pack('!H', flags_offset)  # flags y offset    

        ip_header+= struct.pack('!B', 65) #time to live   
        ip_header+= struct.pack('!B', protocol) #protocolo
        ip_header+= struct.pack('H' ,0x0000) #header checksum
        ip_header+= struct.pack('!I', myIP) #ip origen
        ip_header+= struct.pack('!I', dstIP)  #ip destino

        #Printear todos los campos en orden
        # print(f"\nFragmento {i+1} de {num_fragments}")
        # print(f"Version: {getBits(ip_header[0],0,4)}") 
        # print(f"IHL: {getBits(ip_header[0],4,8)}") #1 byte : 0
        # print(f"Type of service: {ip_header[1]}")  # 1byte : 1
        # print(f"Total size: {total_size}") # 2bytes : 2-3
        # print(f"Identification: {IPID}") # 2bytes : 4-5
        # print(f"Flags: {getBits(ip_header[6],0,3)}")
        # print(f"Offset que queremos enviar: {i * fragment_data_size}")
        # print(f"Offset: {(getBits(ip_header[6],3,8) + ip_header[7]) * 8}") # 2bytes : 6-7
        # print(f"TTL: {ip_header[8]}")  # 1byte : 8
        # print(f"Protocol: {ip_header[9]}") # 1byte : 9
        # print(f"IP origen: {ip_header[12:16]}") # 4bytes : 12-15
        # print(f"IP destino: {ip_header[16:20]}") # 4bytes : 16-19
        # print(f"Options: {ip_header[20:20+opt_size]}")  # Tamaño variable : 20...
        
        if(ipOpts != None):
            ip_header += ipOpts
        
        if not last:
            fragment_data = data[i * fragment_data_size : (i+1) * fragment_data_size]
        else:
            fragment_data = data[i * fragment_data_size :]

        ip_header = ip_header[:10] + struct.pack('H', chksum(ip_header+fragment_data)) + ip_header[12:] #checksum
        frame = ip_header + fragment_data

        #print(f"Checksum: {struct.unpack('!H', ip_header[10:12])[0]}") # 2bytes : 10-11     

        if ((dstIP & netmask)==(myIP&netmask)):
            dstMac = ARPResolution(dstIP)
        else:
            dstMac = ARPResolution(defaultGW)

        #print("Sending ip datagram:", frame)
            
        sendEthernetFrame(frame, struct.unpack('!H', ip_header[2:4])[0],  0x0800,dstMac)
        sleep(0.1)
    IPID += 1
    return True


# start inclusive
# end exclusive
# example : getBits (-1101---, 1, 5) =  00001101
def getBits(b:bytes, start, end) -> bytes:
    displacement = 8 - end
    diff = end - start
    mask = (1 << diff) - 1
    return (b >> displacement) & mask