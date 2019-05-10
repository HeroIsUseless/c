dat dw 100H dup(1)
len = ($-dat)/2
lea si, dat
mov ax, 0
mov cx, len
lp:
    add ax, [si]
    add si, 2
loop lp
div len