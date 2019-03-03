# a0 = n
# v0 = result
# v1 = product
# a1 = i
# a2 = i2

.text
	addi $a0, $0, 3	 	# n = 3
	addi $v0, $0, 1 	# result = 1
	addi $a1, $0, 0		# i = 1
loop1:
	beq $a1, $a0, done	# if i = n end program
	addi $v1, $0, 0		# Product = 0
	addi $a2, $0, 0		# i2 = 1
mul:
	beq $a2, $v0, loop2	# End loop if i2 == result
	add $v1, $v1, $a1	# Product += i
	addi $a2, $a2, 1	# i2++
	beq $0, $0, mul		# Loop
loop2:
	add $v0, $v0, $v1 	# Result += product
	addi $a1, $a1, 1 	# i++
	beq $0, $0, loop1
done:	beq $0, $0, done	# Endless loop