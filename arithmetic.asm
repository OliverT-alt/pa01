# arithmetic.asm program
# CS 64, Z.Matni
#
# 1. Prompt the user for 3 inputs: a, b, c
# 2. Calculate 32*(8*b – 2*a) + 5*c using only one mult instruction
# 3. Print out the result
.text
main:
    #Read abc
    li $v0, 5
    syscall
    move $t0, $v0
    
   
    li $v0, 5
    syscall
    move $t1, $v0
    

    li $v0, 5
    syscall
    move $t2, $v0

    # 2*a
    sll $t3, $t0, 1   
    
    # 8*b
    sll $t4, $t1, 3    # $t4 
    
    # 8*b - 2*a
    sub $t5, $t4, $t3  # $t5 
    
    # 32 * (8*b - 2*a)
    li $t6, 32        
    mult $t5, $t6    
    mflo $t7           
    
    # 5 * c
    mul $t3, $t2, 5    
    
    # 32*(8*b - 2*a) + 5*c
    add $t4, $t7, $t3  
    
    # Print result
    move $a0, $t4      
    li $v0, 1         
    syscall

exit:
    li $v0, 10
    syscall

