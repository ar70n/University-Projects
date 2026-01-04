######################################################################
## Fichero: ProgramaMips.asm
## Descripción: Programa de prueba para el Micro RISC-V
## Asignatura: E.C. 2º grado
## Grupo de Prácticas: 
## Grupo de Teoría: 
## Práctica: 4
## Ejercicio: 1
######################################################################

.text # Comienzo de seccion de codigo de usuario
main:	la x1, datoA # Carga x2000 en x1
	addi x2, x0, 4 # Carga 4 en x2
	ori x3, x0, 15 # Carga x0F en x3
	andi x4, x3, 4 # Carga 4 en x4
	addi x5, x4, -20 # Carga -16 (0xFFFFFFF0) guarda en x5
	slti x6, x0, 0x7FF # Carga 1 en x6
	slti x6, x0, -1 # Carga 0 en x6
	slt x7, x5, x2 # Carga 1 en x7
	
	lw x8, (x1) # Carga datoA en x8. Carga 10
	lw x9, 4(x1) # Carga datoA+4 (datoB) en x9. Carga 9
	lw x10, 8(x1) # Carga datoC en x9. Carga 9
	sub x11, x7, x8 # x11=x7-x8. Carga -9
	
	beq x2, x5, nosalta
	beq x9, x10, salta

nosalta: add x11, x0, x0 # No se debe ejecutar (pondría un 0 en x11)
salta:	addi x12, x11, 2 # Suma con inmediato negativo. Carga -7 en x12
	add x13, x0, x2 # Carga 4 en x13
	sw x13, 12(x1) # Guarda x13 en resultado. Guarda 4
	lw x14, 12(x1) # Carga resultado en x14. Carga 4
	xori x15, x2, -1 # Carga 0xFFFFFFFB en x15
	xor x2, x14, x14 # Carga 0x00000000 en x2
	and x15, x15, x0 # Carga 0 en x15
	or x16, x3, x4 # Carga 0x0000000F en x16
	xori x17, x16, 0x13 # Carga 0x0000001C en x17
	jal fun # Salta a fun
	addi x18, x0, 0x74
	jr x18
fun:	jr ra # Retorna	
fin:	j fin	
	

.data
datoA:  10
datoB:  9 
datoC:  9 
resultado: .space 4
