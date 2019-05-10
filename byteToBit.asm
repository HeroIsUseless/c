DSEG   SEGMENT
   TEMP   DB  4DUP(?)
   DSEG   ENDS
          ……
   START:MOV  CL,4
         MOV  CH,4
         LEA  SI,TEMP ; 这里设了地址
   L1:   MOV  DX,AX ; 把ax给了dx，可以
         AND  DX,0FH ; 去后两位
         MOV  BYTE  PTR[SI],DL ; 把dl运送出去
         INC  SI ; 加一可以理解
         SHR  AX,CL ; 循环右移4个单位长度
         DEC  CH ; ch高位减1变成3
         JNZ   L1 ; 判断，dec的确会影响这个zf标志的，直到又4个循环，将cl与ch拆成两个
         ; 因为移进去后还有个0f处理，就是这样消掉了前面的那个数
         MOV   DL,TEMP
         MOV   CL,TEMP+1
         MOV   BL,TEMP+2
         MOV   AL,TEMP+3
         RET