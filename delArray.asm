; 找到数，应该还知道位置
; 这样的话，那么只有倒着来了
table dw 10, 0,1,2,3,4,5,6,7,8,9
key dw 4
mov cx, [table]
mov ax, key
tag:
    mov bx, cx
    cmp ax, table[bx]
    je yes
loop tag
jmp no
yes:
    ; 差不多是这样了
no: