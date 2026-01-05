.data 

array:	.word 10,6,7,8,9,3,2,1,5,4
.space 16
array_copy: .space 40
.text 

	# array adress := s0
	# n := s1
	# i := s2
	# j := s3
	# min_index := s4
	# min_value := s5


	# Carga en s0 la dirección del array
	lui  s0, %hi(array) #Parte alta
	nop
	nop
	
	
	addi s0, s0, %lo(array) #Parte baja
	
	
	addi s1, zero, 40 # n = 10 * 4
	addi s2, zero, 0 # i = 0 * 4
	
	# Carga en s4 la dirección de la copia
	lui  s4, %hi(array_copy) #Parte alta
	nop
	nop
	
	
	addi s4, s4, %lo(array_copy) #Parte baja
	
#Bucle for de inicialización (copia el array original en array_copy)
for_init:
	
	
	bge s2, s1, start # if i >= n ==> fin
	
	nop
	nop
	nop

	
	add t1, s0, s2 # t1 := array + i
	
	nop
	nop
	
	
	
	lw s3, (t1) # s3 := mem[dir_array]
	
	add s5, s4,s2 # s5 := array_copy + i
	
	nop
	nop
	
	
	sw s3, (s5) # mem[array_copy + i] := mem[array + i]
	
	addi s2,s2,4 # i += 1 * 4
	
	
	
	j for_init
	
	nop
	nop
	nop
	
	
	
		
start:
	add s0, s4, zero # s0 = array_copy
	addi s1, zero, 40  # n = 10 * 4
	addi s2, zero, 0 # i = 0 * 4
	
	nop
for_ext_part1:
	
	nop
	
	
	bge s2, s1, done # if i >= n  ==> fin
	
	nop
	nop
	nop
	
	addi s4, s2, 0 # min_index = i
	
	nop
	nop
	
		
	add t1, s0, s4 # t1 := = array + min_index
	
	nop
	nop
	
	
	lw s5, (t1) # min_value = mem[array + min_index]
	
	addi s3, s2, 4 # j = i + 1 * 4
	
	
	nop
	nop
for_int:
	
	
	
	bge s3, s1, for_ext_part2  #if j >= n ==> break

	
	
	
		
	add t3, s0, s3 # t3 := array + j
	
	nop
	nop
	
	
	lw s6, (t3) # s6 := mem[array + j]
	
	nop
	nop
	
	
	
	bge s6,s5,if_greater # if mem[array + j] >= min_value ==> if_greater
	
	nop
	nop
	nop
	
	addi s4,s3,0 # min_index := j	
	addi s5, s6, 0 # min_value := mem[array + j]
	
	
	
if_greater:
	addi s3,s3,4 # j += 1 * 4;
	
	
	
	j for_int
	
	
	
	
		
	
for_ext_part2:
	
	# aux=array[i]
	add t1, s0, s2 # t1 := array + i
	
	nop
	nop
	
	
	
	lw s7, (t1) # aux := mem[array + i]
	
	
	
	
	sw s5, (t1) # mem[array + i] := min_value
	
	
	add t3, s0, s4 # t3 := array + min_index
	
	nop
	nop
	
	
	sw s7, (t3) # mem[array + min_index] := aux
	 
	addi s2,s2, 4 # i += 1 * 4
	
	
	
	j for_ext_part1
	
	
	
	
done:

