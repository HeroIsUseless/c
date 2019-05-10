;-------------------------------------------
    mov bx, 16
    mov cx, 16
    flag:
        shl bx, 1
        jc dTo1 
            mov dl, '0'
            jmp print
        dTo1:
            mov dl, '1'
        print:
            mov ah, 2
            int 21h
    loop flag
;-------------------------------------------
