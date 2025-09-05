# Factorial.asm program
# For CMPSC 64
#
# Instructions: DO NOT MODIFY ANY CODE HERE, EXCEPT FOR Factorial!
# ONLY MODIFY THE Factorial FUNCTION AT THE BOTTOM OF THIS PROGRAM!!
#
# Once you have modified the Factorial function, save this file as:
# factorial_CCheck.asm
# and submit it to Gradescope.
.data
input_prompt: .asciiz "Enter n: "
output_prompt: .asciiz "n! = "
convention: .asciiz "Convention Check\n"
newline: .asciiz "\n"
.text
main:
la $a0, input_prompt # prompt user for string input
li $v0, 4
syscall
jal GetValue
move $a0, $v0
move $s0, $a0
ori $s1, $zero, 0
ori $s2, $zero, 0
ori $s3, $zero, 0
ori $s4, $zero, 0
ori $s5, $zero, 0
ori $s6, $zero, 0
ori $s7, $zero, 0
move $a0, $s0
jal Factorial
move $t0, $v0
add $s1, $s1, $s2
add $s1, $s1, $s3
add $s1, $s1, $s4
add $s1, $s1, $s5
add $s1, $s1, $s6
add $s1, $s1, $s7
add $s0, $s0, $s1
la $a0, output_prompt # give Output prompt
li $v0, 4
syscall
move $a0, $t0
li $v0, 1
syscall
la $a0, newline
li $v0, 4
syscall
j Exit

GetValue:
li $v0, 5
syscall
jr $ra
ConventionCheck:
addi $t0, $zero, -1
addi $t1, $zero, -1
addi $t2, $zero, -1
addi $t3, $zero, -1
addi $t4, $zero, -1
addi $t5, $zero, -1
addi $t6, $zero, -1
addi $t7, $zero, -1
ori $v0, $zero, 4
la $a0, convention
syscall
addi $v0, $zero, -1
addi $v1, $zero, -1
addi $a0, $zero, -1
addi $a1, $zero, -1
addi $a2, $zero, -1
addi $a3, $zero, -1
addi $k0, $zero, -1
addi $k1, $zero, -1
jr $ra
Exit:
ori $v0, $zero, 10
syscall
# COPYFROMHERE - DO NOT REMOVE THIS LINE
# YOU CAN ONLY MODIFY THIS FILE FROM THIS POINT ONWARDS:
#TODO: write your code for Factorial() here
Factorial:
# Initial setup stuff with stack & regs...
    addiu $sp, $sp, -8    # Allocate space for 2 words on stack
    sw $ra, 4($sp)       # Save return address
    sw $s0, 0($sp)
    move $s0, $a0
   # Call ConventionCheck here
   jal ConventionCheck


# Base Case & Recursion Case
    li $v0, 1
    li $t0, 1             
    ble $s0, $t0, done
    move $a0, $s0

    # Recursion Case: n * Factorial(n - 1)
    addi $a0, $a0, -1    
    jal Factorial           
    

done:
    mul $v0, $v0, $s0
    mflo $v0
    # Final setup stuff with stack & regs...
    lw $ra, 4($sp) 
    lw $s0, 0($sp)       # pop
    addiu $sp, $sp, 8   
    jr $ra
