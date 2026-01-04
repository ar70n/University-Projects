#################################################################
## Asignatura: Estructura de Computadores.
## Grado II. 2� curso.
## Fichero: Vectores.asm
## Descripci�n: Programa que...
## Fichero de apoyo: Pr�ctica: 3. Ejercicio: 2
#################################################################


.text

main:	
	#Se guarda en s0 la direcci�n del s�mbolo N
	la s0, N
	
		
	#Lee la variable N
	lw s1, 0(s0)
		
	#Inicializa el bucle for
	addi s5, zero, 0 #la i
	add t2, zero, s1
	
	
	#Se guarda en .. la direcci�n base del array A
	la s2, A
	
	#Se guarda en .. la direcci�n base del array B
	la s3, B
	
	#Se guarda en .. la direcci�n base del array C
	la s4, C
	
	#Comprobaci�n del bucle
bucle:	bge s5,t2, fin

	
	# C�lculo offset de los vectores
	slli s6, s5, 2
	
	# C�lculo de la direcci�n A(i)
	add s7,s2,s6 
	
	#Lectura de A(i)
	lw s8, (s7)
	
	# C�lculo de la direcci�n B(i)
	add s10, s3, s6
	
	#Lectura de B(i)
	lw s9, (s10)
	
	#Multiplicaci�n por 4 de B(i)
	slli s9, s9, 2
	
	#Suma 
	add s8, s8,s9
	
	# C�lculo de la direcci�n C(i)
	add s11, s4, s6
	
	#Escritura en C(i)
	sw s8(s11)
	
	#Operaci�n del bucle
	addi s5,s5,1
	
	#Salto a la comparaci�n
	j bucle
	
	#Bucle infinito
fin: j fin	

.data # Comienzo de seccion de memoria de datos
A: 2,2,4,6,5,6,7,8,9,10
B: -1,-5,4,10,1,-2,5,10,-10,0
C: .space 40 #.space reserva el espacio determinado en bytes.
N: 10

