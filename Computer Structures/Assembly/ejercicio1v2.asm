.text 0x0000

	la s0, X
	lw s1, 0(s0)
	lw s2, 4(s0)
	addi sp, sp -4
	sw s1, 0(sp)
	addi sp, sp -4
	sw s2, 0(sp)
	
	

main: jal calculaSumaMult
	lw a0, 0(sp)
	addi sp,sp,4
	sw a0, 8(s0)
parar: j parar

calculaSumaMult: lw s2, 0(sp) 
		 addi sp,sp, 4
		 lw s1, 0(sp) 
		 addi sp,sp, 4

		 add a0,s1,s2
		 slli a0, a0, 1
		 addi sp, sp -4
		 sw a0, 0(sp)
		 jr ra


.data 0x2000
X: 0X000A
Y: 0x0004
R:
