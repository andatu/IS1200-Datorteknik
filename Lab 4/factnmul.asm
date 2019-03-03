.text
addi $a0, $0, 5      # a0 = n
add $v0, $a0, $0
addi $a2, $0, 1

loop:
beq $a0, $a2, end
nop
addi $a0, $a0, -1
mul $v0, $v0, $a0
beq $0, $0, loop
nop
end:
beq $0, $0, end
nop