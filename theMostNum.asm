; 同样开辟相同字节数的空间
; 对于每一个字，循环整个的字符串标记数量
; 然后开始找最大的那个数和它的位置
; 然后存进去就好了

; 假设没有重复的，就看整个数组中有没有比它大的
; 就是这么简单
table db 0,1,2,3,4,5,6,7,8,9
n_table db $-table dup(0)
; 两层循环遍历
; 首先找到一个值，存入ax
; 然后遍历整个的，然后用bx计数
; 最后存入
; 然后统计最高的数字和位置
lea bx, n_table ; 计数部分
mov cl, 10
lea si, table
tag1:
    mov ch, 10
    mov al, [si] ; 抽出这个值用于下面的比较
    mov dl, 0 ; 是它的有多少个的计数
    lea di, table ; 每次的循环的用于对比的数列
    tag2: ; 进行计数
        mov ah, [di]
        cmp al, ah
        je increase
        jmp nothing
        increase: inc dl
        nothing:
        inc di
        dec ch
    jnz tag2
    mov [bx][si-table]
    inc si
    dec cl
jnz tag1
