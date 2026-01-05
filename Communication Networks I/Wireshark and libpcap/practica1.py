'''
    practica1.py
    Muestra el tiempo de llegada de los primeros 50 paquetes a la interfaz especificada
    como argumento y los vuelca a traza nueva con tiempo actual

    Autor: Javier Ramos <javier.ramos@uam.es>
    2020 EPS-UAM
'''

from rc1_pcap import *
import sys
import binascii
import signal
import argparse
from argparse import RawTextHelpFormatter
import time
import logging
import os

ETH_FRAME_MAX = 1514
PROMISC = 1
NO_PROMISC = 0
TO_MS = 10
num_paquete = 0
minT = 0
maxT = 0
TIME_OFFSET = 30*60


def signal_handler(nsignal,frame):
	logging.info('Control C pulsado')
	if handle:
		pcap_breakloop(handle)
		

def procesa_paquete(us,header,data):
	global num_paquete, pdumperNOIP, pdumperIP
	global minT, maxT
	logging.info('Nuevo paquete de {} bytes capturado en el timestamp UNIX {}.{}'.format(header.len,header.ts.tv_sec,header.ts.tv_sec))
	num_paquete += 1

	if num_paquete==1:
		minT=header.ts.tv_sec+header.ts.tv_usec/1000000
	maxT=header.ts.tv_sec+header.ts.tv_usec/1000000

	# Mostramos los primeros nbytes del paquete
	if args.nbytes>0:
		
		logging.info(f'Primeros {min(args.nbytes,len(data))} bytes del paquete:')
		i=0
		while i<args.nbytes and i<len(data):
			if i%16==0:
				print()
			print('{:02x}'.format(data[i]).upper(),end=' ')	
			i+=1 
		print('\n')

	# Volcamos el paquete a fichero si capturamos en vivo solo
	if args.interface:
		if (data[12]!=0x08 or data[13]!=0x00):
			pcap_dump(pdumperNOIP,header,data)
		else:
			pcap_dump(pdumperIP,header,data)

	
if __name__ == "__main__":
	global pdumperNOIP, pdumperIP,args,handle
	parser = argparse.ArgumentParser(description='Captura tráfico de una interfaz ( o lee de fichero) y muestra la longitud y timestamp de los paquetes',
	formatter_class=RawTextHelpFormatter)
	parser.add_argument('--file', dest='tracefile', default=False,help='Fichero pcap a abrir')
	parser.add_argument('--itf', dest='interface', default=False,help='Interfaz a abrir')
	parser.add_argument('--nbytes', dest='nbytes', type=int, default=ETH_FRAME_MAX,help='Número de bytes a mostrar por paquete')
	parser.add_argument('--debug', dest='debug', default=False, action='store_true',help='Activar Debug messages')
	parser.add_argument('--npkts', dest='npkts',type=int ,default=-1,help='Número de paquetes a capturar')
	
	args = parser.parse_args()

	if args.debug:
		logging.basicConfig(level = logging.DEBUG, format = '[%(asctime)s %(levelname)s]\t%(message)s')
	else:
		logging.basicConfig(level = logging.INFO, format = '[%(asctime)s %(levelname)s]\t%(message)s')

	if args.tracefile is False and args.interface is False:
		logging.error('No se ha especificado interfaz ni fichero')
		parser.print_help()
		sys.exit(-1)
	elif args.nbytes<0 or args.npkts<-1:
		logging.error('nbytes y npkts deben ser mayores o iguales que 0')
		parser.print_help()
		sys.exit(-1)

	signal.signal(signal.SIGINT, signal_handler)

	
	errbuf = bytearray()

	# Si caputramos en vivo abrimos ficheros de volcado
	if args.interface:
		try:
			handle = pcap_open_live(args.interface,ETH_FRAME_MAX, NO_PROMISC, TO_MS, errbuf)
		except:
			logging.error(f'Error al abrir la interfaz \'{args.interface}\': {errbuf}')
			sys.exit(-1)
			
		descr1 = pcap_open_dead(DLT_EN10MB, ETH_FRAME_MAX)
		descr2 = pcap_open_dead(DLT_EN10MB, ETH_FRAME_MAX)

		actual_time = time.time()
		pdumperNOIP = pcap_dump_open(descr1, f"capturaNOIP.{args.interface}.{actual_time}.pcap")
		pdumperIP = pcap_dump_open(descr2, f"captura.{args.interface}.{actual_time}.pcap")
	
	# Si abrimos archivo ponemos handle offline
	elif args.tracefile:
		handle = pcap_open_offline(args.tracefile, errbuf)
		
		if len(errbuf)>3:
			logging.error(f'Ha habido un problema abriendo el archivo \'{args.tracefile}\': {errbuf}')
			parser.print_help()
			sys.exit(-1)
		
	# Procesamos los paquetes
	ret = pcap_loop(handle,args.npkts ,procesa_paquete,None)
	if ret == -1:
		logging.error('Error al capturar un paquete')
	elif ret == -2:
		logging.debug('pcap_breakloop() llamado')
	elif ret == 0:
		logging.debug('No mas paquetes o limite superado')
	logging.info('{} paquetes procesados'.format(num_paquete))
	logging.info('Tiempo transcurrido desde la captura del primer paquete al último: {}s'.format(maxT-minT))

	# Cerramos los ficheros de volcado si estamos en modo live
	if args.interface:
		pcap_close(descr1)
		pcap_close(descr2)

		pcap_dump_close(pdumperNOIP)
		pcap_dump_close(pdumperIP)


	pcap_close(handle)



