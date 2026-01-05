'''
    ethmsg.py
    Implementación del protocolo de mensajeria basica para emision de mensajes en tiempo real sobre ethernet.
    Autor: Manuel Ruiz <manuel.ruiz.fernandez@uam.es>
    2024 EPS-UAM
'''

from ethernet import *
import logging
import socket
import struct
import fcntl
import time
from threading import Lock
from expiringdict import ExpiringDict

ETHTYPE = 0x3003
#Dirección de difusión (Broadcast)
broadcast = bytes([0xFF]*6)




def process_ethMsg_frame(us:ctypes.c_void_p,header:pcap_pkthdr,data:bytes,srcMac:bytes) -> None:
    '''
        Nombre: process_EthMsg_frame
        Descripción: Esta función procesa las tramas mensajes sobre ethernet. 
            Se ejecutará por cada trama Ethenet que se reciba con Ethertype ETHTYPE (si ha sido registrada en initEth). 
                - Imprimir el contenido de los datos indicando la direccion MAC del remitente, la dirección IP de destino (en notación decimal a.b.c.d), asi como el tiempo de recepcion del mensaje, según el siguiente formato:
					[<segundos.microsegundos>] <MAC> -> <IP>: <mensaje> 
                - En caso de que no exista retornar
            
        Argumentos:
            -us: Datos de usuario pasados desde la llamada de pcap_loop. En nuestro caso será None
            -header: cabecera pcap_pktheader
            -data: array de bytes con el contenido de la trama ethMsg
            -srcMac: MAC origen de la trama Ethernet que se ha recibido
        Retorno: Ninguno
    '''

    #print("\033[94m\n[DEBUG]: === process_ethMsg_frame === \033[0m") 
    #print("[DEBUG]: data: ", data)
    
    '''
    ethertype = struct.unpack('!H', data[12:14])[0]
    print(f"Ethertype: {ethertype}")
    if ethertype != ETHTYPE:
        return
    '''
    
    ip = struct.unpack('!I', data[0:4])[0]
    print(f"\n\n[{header.ts.tv_sec}.{header.ts.tv_usec}] {':'.join(['{:02X}'.format(b) for b in srcMac])} -> {socket.inet_ntoa(struct.pack('!I',ip))}: {data[4:].decode()}\n")

    return

def initEthMsg(interface:str) -> int:
    '''
        Nombre: initEthMsg
        Descripción: Esta función construirá inicializará el nivel ethMsg. Esta función debe realizar, al menos, las siguientes tareas:
            -Registrar la función del callback process_ethMsg_frame con el Ethertype ETHTYPE
        Argumentos:   
			interfaz
    '''

    #print("\033[94m\n[DEBUG]: === initEthMsg === \033[0m") 

    registerEthCallback(process_ethMsg_frame,ETHTYPE)
    return 0

def sendEthMsg(ip:int, message:bytes) -> bytes:
    '''
        Nombre: sendEthMsg
        Descripción: Esta función mandara un mensaje en broacast 
            
            Esta función debe realizar, al menos, las siguientes tareas:
                - Crear una trama Ehernet con el mensaje remitido
                - Enviar un mensaje en broadcast
		Argumentos:
			ip: Direccion IP a la que remitir el mensaje. Enviar como una palabra de 32 bits en orden de red.
			message: datos con el mensaje a remitir.
                
        Retorno: 
			Numero de Bytes transmitidos en el mensaje.
			None en caso de que no haya podido emitir el mensaje
    '''

    #print("\033[94m\n[DEBUG]: === sendEthMsg === \033[0m") 

    eth_frame = ip.to_bytes(4, byteorder='big') + message.encode()
    
    #print("[DEBUG]: ethmsg_frame: ", eth_frame)
    
    if(sendEthernetFrame(eth_frame,len(eth_frame) ,ETHTYPE, broadcast)==-1):
        return None
    return len(eth_frame)
