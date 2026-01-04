#################################################################
## Asignatura: Estructura de Computadores.
## Grado II. 2º curso.
## Fichero: Tutorial.asm
## Descripción: Ejemplo de un programa en ensamblador
## Fichero de apoyo: Práctica: 3.
#################################################################

#############################
# Equivalente en C
# if (a < b) 
#	c = b;
# else
#	c = a;
# while (1);
#############################

.text 				# Comienzo de seccion de codigo de usuario
main:	la s0, a
	lw s1, 0(s0)  		# Cargar en registro s1 la variable a.
	lw s2, 4(s0) 		# Cargar en registro s2 la variable b
	bge s1, s2, falso 	# Si a>=b, nos vamos al else
	addi s4, s2, 0 		# Rama principal del if, s4 hace de variable c
	j finCondicion 		# Salto al final del bucle para que no se ejecute el else
falso:	addi s4, s1, 0 		# Rama del else

finCondicion: sw s4, 8(s0) 	# Guardar en memoria el valor del registro s4

bucle: j bucle
	
	
.data  				# Comienzo de seccion de datos de usuario
a: 20  				# Variable a, ocupa una palabra.
b: 10  				# Variable b
c: 0  				# Variable c


