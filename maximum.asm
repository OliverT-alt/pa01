# maximum.asm program
# CS 64, Z.Matni
#
# Get 3 integer inputs from the user (std.in)
# Reveal the maximum absolute value (e.g., entering -3, 2, 1 will give the answer
# See assignment description for details

#Data Area (i.e. memory setup directive)
.data
# TODO: Complete these incomplete declarations / initializations
prompt: .asciiz "Enter number:\n"
result: .asciiz "Maximum: "
newline: .asciiz "\n"

#Text Area (i.e. instructions/code directive)
.text
main:
# TODO: Write your code here
# You can have other labels expressed here, if you need to
    # Read first number
    la $a0, prompt
    li $v0, 4
    syscall
    li $v0, 5
    syscall
    move $t0, $v0

    # Read second number
    la $a0, prompt
    li $v0, 4
    syscall
    li $v0, 5
    syscall
    move $t1, $v0

    # Read third number
    la $a0, prompt
    li $v0, 4
    syscall
    li $v0, 5
    syscall
    move $t2, $v0

    bgez $t0, abs1
    sub $t3, $zero, $t0
    j next1
abs1:
    move $t3, $t0
next1:
    bgez $t1, abs2
    sub $t4, $zero, $t1
    j next2
abs2:
    move $t4, $t1
next2:
    bgez $t2, abs3
    sub $t5, $zero, $t2
    j next3
abs3:
    move $t5, $t2
next3:
    # Find max
    move $t6, $t3
    sltu $t7, $t6, $t4
    beqz $t7, check_c
    move $t6, $t4
check_c:
    sltu $t7, $t6, $t5
    beqz $t7, print_result
    move $t6, $t5
    
print_result:
    la $a0, result
    li $v0, 4
    syscall
    move $a0, $t6
    li $v0, 1
    syscall
    la $a0, newline
    li $v0, 4
    syscall
    
    j exit

exit:
    li $v0, 10
    syscall
# TODO: Write code to properly exit a SPIM simulation
