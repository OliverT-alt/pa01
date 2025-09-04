# print_array.asm program
# For CMPSC 64
#
# Instructions: MODIFY THE PROGRAM PER THE DETAILS BELOW
#
# Once you have finished modifying everything, save this file as:
# print_reverse_array.asm
# and submit it to Gradescope.
.data
array: .word   1, 2, 3, 4, 5, 60, 70, 80, 90, 100
newline: .asciiz "\n"
cout: .asciiz "The contents of the array are:\n"

.text
printArr:
    li $t0, 9    
    la $t1, array
loop:
    #check condition
    blt $t0, $zero, done  

    sll $t2, $t0, 2 # Multiply i by 4 
    add $t2, $t1, $t2 # add base address to get array[i] address

    lw $a0, 0($t2)  
    li $v0, 1       
    syscall

    la $a0, newline 
    li $v0, 4      
    syscall

    addi $t0, $t0, -1 # i = i - 1
    j loop           

done:
    jr $ra         

main: # DO NOT MODIFY THE MAIN SECTION
li $v0, 4
la $a0, cout
syscall
la $a0, array
li $a1, 10
jal printArr

exit:
li $v0, 10
syscall
