data segment
ends

stack segment
    dw   1000  dup(0)
ends    

code segment 
print macro m, n
    push ax 
    push dx
    mov bl, dl
    mov dl, m
    mov ah, 2
    int 21h
    mov dl, ">"
    int 21h
    mov dl, bl 
    int 21h
    mov dl, 0AH
    int 21h
    mov dl, 0DH
    int 21h
    pop dx 
    pop ax 
endm

hanoi proc
    pop bx ; 此为取出函数地址
    pop dx
    pop ax ; 取出操作数
    push bx ; 安装函数地址 
    cmp ah, 0
    je exit ; 与0进行比较，等于0时结束递归，不等于0时继续递归 
    dec ah ; 如果不相等则减1，代表进行下一次的转移
    push ax
    push dx
    rol dx, 8
    push ax 
    push dx  
    call hanoi ; (1)~(n-1):a->b
    pop dx
    pop ax
    print al, dl ; 打印出来    
    inc cx ; (n):a->c   
    mov bl, al
    mov al, dh
    mov dh, bl
    push ax
    push dx 
    call hanoi ; (1)~(n-1)b->c 
    exit:  
    ret 
hanoi endp

start:
    mov ax, data   ; 进行初始化
    mov ds, ax
    mov ax, stack
    mov ss, ax

    mov ah, 3 ; 这里是要输入的数值
    mov al, 'a'
    push ax
    mov dh, 'b'
    mov dl, 'c'
    push dx
    mov cx, 0 ; 作为最终计数结果
    call hanoi 
ends
end start    