  # hexmain.asm
  # Written 2015-09-04 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

	.text
main:
	li	$a0,16		# change this to test different values

	jal	hexasc		# call hexasc
	nop			# delay slot filler (just in case)	

	move	$a0,$v0		# copy return value to argument register

	li	$v0,11		# syscall with v0 = 11 will print out
	syscall			# one byte from a0 to the Run I/O window

	
stop:	j	stop		# stop after one run
	nop			# delay slot filler (just in case)

  # You can write your own code for hexasc here
  #
hexasc:
	
	andi $t1, $a0, 0xF	# Andar a0 med 00001111 för att få 4 bitar
	addi $v0, $t1, 0x30	# Andar t1 med 0x30 för att komma till 0 i ASCII
	
	slti $t2, $v0, 0x3a	# kollar om v0 är mindre än "större än 9 i ASCII"
	
	bne $t2,$0, klar	# om t2=1 så hoppar den till klar, annars nästa rad
	addi $v0, $v0, 0x7	# om t2=0 ökas v0 med 7
		
				
klar: jr $ra
	
	
	
	

