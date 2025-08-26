# fibonacci.asm program
# CMPSC 64, (c) 2025, Z.Matni
#
# unsigned int n, f1 = 1, f2 = 1, i = 2, nextfib;
# cout << "Enter a number:\n";
# cin >> n;
# if (n > 1) {
# cout << "The first " << n << " numbers in the Fibonacci series are:\n";
# cout << f1 << " " << f2;
# while (i < n) {
# nextfib = f1 + f2;
# f1 = f2;
# f2 = nextfib;
# cout << " " << nextfib;
# i++;
# }
# }
# cout << endl;
.data
prompt: .asciiz "Enter a number:\n"
first: .asciiz "The first "
numbers: .asciiz " numbers in the Fibonacci series are:\n"
spacech: .asciiz " "
newline: .asciiz "\n"
.text
main:
    # Print the prompt and get user input
    la $a0, prompt
    li $v0, 4
    syscall
    
    li $v0, 5
    syscall
    move $t0, $v0
    
    #if less than z exit
    bltz $t0, exit
    
    # Initialize all registers needed in the program (as appropriate)
    li $t1, 1
    li $t2, 1
    li $t3, 2

    # if (exit conditions are met) then go to exit
    sltiu $t4, $t0, 2
    bnez $t4, exit
    
    # print "The first " n " numbers in the Fibonacci series are:\n"
    la $a0, first
    li $v0, 4
    syscall
    
    #n
    move $a0, $t0
    li $v0, 1
    syscall
    
    #numbers
    la $a0, numbers
    li $v0, 4
    syscall
    
    # print f1 " " f2
    move $a0, $t1
    li $v0, 1
    syscall
    
    la $a0, spacech
    li $v0, 4
    syscall
    
    move $a0, $t2
    li $v0, 1
    syscall

loop:
    sltu $t4, $t3, $t0
    beqz $t4, exit
    
    addu $t5, $t1, $t2
    move $t1, $t2
    move $t2, $t5
    
    la $a0, spacech
    li $v0, 4
    syscall
    
    move $a0, $t5
    li $v0, 1
    syscall
    
    addiu $t3, $t3, 1
    j loop

exit:
    la $a0, newline
    li $v0, 4
    syscall
    
    li $v0, 10
    syscall
# print newline
# quit program
