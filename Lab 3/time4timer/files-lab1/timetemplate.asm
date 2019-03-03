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

delay:
	jr $ra
	nop

time2string:
	add $s3, $a0, $0
	andi $a0, $a1, 0xFFFF	# Får ut de 4 sista bytsen till t0
	

	jal hexasc	#call hexasc
	move $s1, $v0
	srl $a0, $a0, 4
	
	jal hexasc
	sll $v0, $v0, 8
	add $s1,$s1, $v0
	lb $s2, 0x3A
	sll $s2, $s2, 16
	add $s1, $s1, $s2
	srl $a0, $a0, 4
	
	jal hexasc
	sll $v0, $v0, 24
	add $s1, $s1, $v0	
	srl $a0, $a0, 4
	
	jal hexasc
	sll $v0, $v0, 32
	add $s1, $s1, $v0
	sll $s1, $s1, 8
	add $a0, $s3, $0
	
	addi $sp, $a0, 0
	PUSH	($s1)
	jr $rs
	
	
	

	
	
	
