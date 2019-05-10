DATA DW 1,2,3,4,5,6,7,8,9,10

lea si, DATA
mov bx, 0
mov cx, 10
flag:
    mov ax, [si]
    test ax, 0001h
    jnz continue
    cmp bx, ax
    jnb continue
    mov bx, ax 
    continue:
    add si, 2
    dec cx
loop flag