//起始字符是#，用两个栈，OPTR为寄存运算符，OPND寄存操作数或运算结果
void EvaluateExpression()
{
    InitStack(OPTR);
    Push(OPTR, '#');
    InitStack(OPND);
    c = getchar();
    while(c!='#' || GetTop(OPTR)!='#')
    {
        if(!In(c, OP))//判断是操作数还是操作符，可以放在一个字符串里，用字符串函数即可，可以加空格防止误判
        {
            Push(OPND, c);
            c = getchar();
        }
        else
        {
            switch(Precede(GetTop(OPND), c))//判断栈顶运算符与读入运算符优先级
            {
                case '<':
                    push(OPTR, c);
                    c = getchar();
                    break;
                case '=':
                    Pop(OPTR, x);//脱括号
                    c = getchar();
                    break;
                case '>':
                    Pop(OPTR, theta);
                    Pop(OPND, b);
                    Pop(OPND, a);
                    Push(OPND, Opreate(a, theta, b));//只是一个运算函数
                    break;
            }
        }
        return;
    }



}
