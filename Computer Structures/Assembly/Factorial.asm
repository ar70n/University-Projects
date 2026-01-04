.text 0x0000
	la s0, N
	lw s1, 0 (s0)
	add s3, s1, zero
	addi s2, s1, -1
	beq s1, zero, fin
L1: 	jal func
	addi s2, s2, -1
	beq s2, zero, fin
	j L1
fin: 	sw s3, 4(s0)
parar: 	j parar
func: 	and s6, s6, zero
	add s7, s2, zero
L2: 	add s6, s3, s6
	addi s7, s7, -1
	beq s7, zero, L3
	j L2
L3: 	add s3, s6, s0
	jr ra
.data 0x2000
N: 0x0003
F: 0x0000



