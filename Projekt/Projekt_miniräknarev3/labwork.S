  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #
 .data
 .text
 .align 2
.global hexasc
hexasc:

	andi $t1, $a0, 0xF	# Andar a0 med 00001111 f�r att f� 4 bitar
	addi $v0, $t1, 0x30	# Andar t1 med 0x30 f�r att komma till 0 i ASCII

	slti $t2, $v0, 0x3a	# kollar om v0 �r mindre �n "st�rre �n 9 i ASCII"

	bne $t2,$0, klar	# om t2=1 s� hoppar den till klar, annars n�sta rad
	nop
	addi $v0, $v0, 0x7	# om t2=0 �kas v0 med 7
klar:	jr $ra
	nop

.global time2string
time2string:
	PUSH $ra
	PUSH $s0
	PUSH $s1

	addi $t9, $0, 0		# t0 = NULL-byte
	add $s0, $a0, $0	# Sparar undan adressen till s0
	andi $a0, $a1, 0xffff	# F�r ut de 4 sista bytsen till s1
	sb $t9, 5($s0)		# NULL-byte in till s0

	PUSH $a0
	jal hexasc		#call hexasc
	nop
	POP $a0
	sb $v0, 4($s0)

	srl $a0, $a0, 4
	PUSH $a0
	jal hexasc		#call hexasc
	nop
	POP $a0
	sb $v0, 3($s0)

	addi $t8, $0, 0x3a
	sb $t8, 2($s0)

	srl $a0, $a0, 4
	PUSH $a0
	jal hexasc		#call hexasc
	nop			# fr�ga 3.4
	POP $a0
	sb $v0, 1($s0)

	srl $a0, $a0, 4
	PUSH $a0
	jal hexasc		#call hexasc
	nop
	POP $a0
	sb $v0, 0($s0)

	add $s1, $0, $a1
	addi $t8, $0, 0x58
	and $s1, $s1, 0xFF
	bne $s1, $0, functionX
	nop
	sb $t8, 5($s0)
	sb $t9, 6($s0)

functionX:

	POP $s1
	POP $s0
	POP $ra
	jr $ra
	nop

.global delay
delay:
	and	$t1, $t1, $zero			# i=0
	ori	$t2, $t2, 0xffff
	andi	$t2, $t2, 0xf0ff			# konstant
	sll	$t2, $t2, 6
whileloop:
	slti	$t0, $a0, 1
	bne	$t0, $0, donewhileloop		# while ms>0
	nop
	addi	$a0, $a0, -1			# ms--
forloop:
	slt	$t3, $t1, $t2
	beq	$t3, $0, doneforloop		# i<konstanten
	nop
	addi	$t1, $t1, 1			# i++
	j	forloop
	nop
doneforloop:
	j	whileloop
	nop
donewhileloop:
	jr	$ra
	nop

  .global enable_interrupt
  enable_interrupt:
    ei
    jr $ra
    nop
