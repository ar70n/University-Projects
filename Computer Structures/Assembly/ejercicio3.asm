.text 0x0000

	la s0, A
	lw s1, 0(s0)
	lw s2, 4(s0)
	
	addi sp, sp -4
	sw s1, 0(sp)
	addi sp, sp -4
	sw s2, 0(sp)
	
	

main: jal funcion1
	lw a0, 0(sp)
	addi sp,sp,4
	
	sw a0, 8(s0)
	
	
parar: j parar

funcion1: 
		 lw s2, 0(sp) 
		 addi sp,sp, 4
		 lw s1, 0(sp) 
		 addi sp,sp, 4

		slli s1,s1, 2
		slli s2,s2, 1
		
		sub a0,s1,s2
		
		#Metemos ra y k en la pila
		addi sp,sp, -4
		sw ra, 0(sp)
		
		addi sp,sp, -4
		sw a0, 0(sp)
		
		
		jal compl_a_2
		
		lw a0, 0(sp)
		addi sp, sp, 4
		
		lw ra, 0(sp)
		addi sp, sp, 4
		
		slli a0,a0,1
		
		addi sp, sp, -4
		sw a0,(sp)
		
		jr ra

compl_a_2: 
		
		lw a0,0(sp)
		addi sp,sp, 4
		
		sub a0, zero ,a0
		 
		addi sp, sp, -4
		sw a0, 0(sp)
		
		jr ra

.data 0x2000
A: 0X000A
B: 0x0006
R:
