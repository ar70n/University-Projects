#################################################################
## Asignatura: Estructura de Computadores.
## Grado II. 2º curso.
## Fichero: calculaSumaMult_1a.asm
## Descripción: Programa que calcula la suma de dos operandos y posteriormente multiplica por 2, todo a través de una función
## Fichero de apoyo: Práctica: 3. Ejercicio: 1a
#################################################################

.text 0x0000

	la s0, X
	lw a1, 0(s0)
	lw a2, 4(s0)

main:		
	#Se guarda en s0 la dirección del símbolo X. A partir de ahí también se puede acceder fácilmente a Y y R
	la s0, X 
	
	#Lectura de X y guardado en un registro... utilice uno de los registros específicos
	lw a1, 0(s0)
	#Lectura de Y y guardado en un registro... utilice uno de los registros específicos
	lw a2, 4(s0)
	#Llamada a función
	jal calculaSumaMult
	#Guardado del retorno en la variable R de memoria
	sw a0, 8(s0)
	#Bucle infinito
	


		 
		 
	
	#Suma de los dos parámetros
calculaSumaMult: add a0,a1,a2
	#Multiplica por dos ... utilice para el resultado final uno de los registros específicos
	slli a0, a0, 1
	#Retorno a main
	jr ra
	
	

.data
X: 10
Y: 4
R:

