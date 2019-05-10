M dw 1,2,3,4,5,6,7,8,9,0
max dw ?
max_add dw ?

lea si, M
mov ax, -1000
mov cx, max-M
tag:
    mov bx, [si]
    test bx, 8000h
    jnz negtive
    jmp positive
    negtive: neg bx
    positive: 
    cmp ax, bx
    jl lo
    jmp hig
    lo: mov ax, [si]
    hi: 
    add si, 2
loop tag
