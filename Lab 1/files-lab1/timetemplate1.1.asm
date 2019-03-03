  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

	.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii "text more text lots of text\0"
	.text
main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall
	nop
	# wait a little
	li	$a0,2
	jal	delay
	nop
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xf	# check lowest digit
	sltiu	$t2,$t1,0xa	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop

  # you can write your code for subroutine "hexasc" below this line
  #
hexasc:
	
	andi $t1, $a0, 0xF	# Andar a0 med 00001111 för att få 4 bitar
	addi $v0, $t1, 0x30	# Andar t1 med 0x30 för att komma till 0 i ASCII
	
	slti $t2, $v0, 0x3a	# kollar om v0 är mindre än "större än 9 i ASCII"
	
	bne $t2,$0, delay	# om t2=1 så hoppar den till klar, annars nästa rad
	addi $v0, $v0, 0x7	# om t2=0 ökas v0 med 7



time2string:
	PUSH ($ra)
	PUSH ($s0)
	PUSH ($s1)	

	addi $t9, $0, 0		# t0 = NULL-byte
	add $s0, $a0, $0	# Sparar undan adressen till s0
	andi $a0, $a1, 0xFFFF	# Får ut de 4 sista bytsen till s1
	sb $t9, 5($s0)		# NULL-byte in till s0
	
	PUSH ($a0)
	jal hexasc		#call hexasc
	POP ($a0)
	sb $v0, 4($s0)	
					
	srl $a0, $a0, 4
	PUSH ($a0)
	jal hexasc		#call hexasc
	POP ($a0)
	sb $v0, 3($s0)

	addi $t8, $0, 0x3A 	
	sb $t8, 2($s0)
	
	srl $a0, $a0, 4
	PUSH ($a0)
	jal hexasc		#call hexasc
	POP ($a0)
	sb $v0, 1($s0)

	srl $a0, $a0, 4
	PUSH ($a0)
	jal hexasc		#call hexasc
	POP ($a0)
	sb $v0, 0($s0)	

	POP ($s1)
	POP ($s0)
	POP ($ra)	


delay:
	jr $ra
	nop
	
	

	
	
	
