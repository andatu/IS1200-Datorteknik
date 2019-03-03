
delay:
	and	$t1, $t1, $0			# i=0
	andi	$t2, $t2, 4711			# konstant
whileloop: 
	slti	$t0, $a0, 1			
	bne	$t0, $0, donewhileloop		# while ms>0
	subi	$a0, $a0, 1			# ms--
forloop:
	slt	$t3, $t1, $t2			
	beq	$t3, $0, doneforloop		# i<konstanten
	nop
	addi	$t1, $t1, 1			# i++
	j	forloop
doneforloop:
	j	whileloop
donewhileloop:
	jr	$ra