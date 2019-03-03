.text
addi $a0, $0, 3      # a0 = n
add $v0, $0, $a0     # result=n
add $a1, $0, $0      # sparar resultatet fr�n loopen
add $a2, $0, $a0    # counter f�r multiplikation
addi $a3, $0, 1      # i1 = 1 
 

loop:
beq $a0, $a3, end    # i1=n? 
nop
addi $a2, $a2, -1    # counter -1
add $v1, $0, 1       # i2 =1
add $a1, $0, $v0     # L�gger in v�rdet som ska multipliceras

addi $a3, $a3, 1     # i1 ++1

mul:
beq $a2, $v1, loop   # om a2 = v1, g�r ur mul och tillbaka till loop
nop
add $v0, $v0, $a1    # v0 + v0 + a0
addi $v1, $v1, 1     # v1 = 1, och sen ++ i mul-loop
beq $0, $0, mul      # unconditional jump
nop


end:
beq $0, $0, end      # endless loop
nop
