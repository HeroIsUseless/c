#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//后缀表达式计算，当输入的数比操作符大一时，开始执行计算，包括错误处理
typedef double ElementType;
#define Infinity 1e8
#define Max_Expr 30   /* max size of expression */

ElementType EvalPostfix( char *expr );

int main()
{
    ElementType v;
    char expr[Max_Expr];
    gets(expr);
    v = EvalPostfix( expr );
    if ( v < Infinity )
        printf("%f\n", v);
    else
        printf("ERROR\n");
    while(1){}
    return 0;
}

/* Your function will be put here */
ElementType EvalPostfix( char *expr )
{
    float SN[Max_Expr]; int Ntop = 0;
    char SO[Max_Expr]; int Otop = 0;
    float ft; int isDot; float dot; int i,j;//临时变量
    ElementType res = 0;//最终结果变量
    while(*expr != 0)
    {
        if(*expr>='0' && *expr<='9')//转换数字并压入数字
        {
            ft = 0.0;
            isDot = 0;//是否出现了小数点
            dot = 1;
            while(*expr != ' ')
            {
                if(*expr == '.') {isDot = 1; expr++; continue;}
                if(isDot)
                {
                    ft += ((float)(*expr-'0'))*dot*0.1; dot *= 0.1;
                    expr++;
                }
                else
                {
                    ft = ft*10 + *expr - '0';
                    expr++;
                }
            }
            SN[Ntop++] = ft;
        }
        if(*expr=='+' || *expr=='*' || *expr=='/')//判断运算符并开始计算
        {
            SO[Otop++] = *expr;
        }
        if(*expr=='-')//单独区分是负数（压入栈）还是减号（进行运算）
        {
            if(*(expr+1)==' '|| *(expr+1)=='\0')
                SO[Otop++] = *expr;
            else
            {
                expr++;//进入数字部分
                ft = 0.0;
                isDot = 0;//是否出现了小数点
                while(*expr != ' ')
                {
                    if(*expr == '.'){isDot = 1; expr++; continue;}
                    if(isDot)
                    {
                        ft += *expr*pow(0.1, isDot++);
                        expr++;
                    }
                    else
                    {
                        ft = ft*10 + *expr - '0';
                        expr++;
                    }
                }
                SN[Ntop++] = -ft;
            }
        }
        expr++;//空格进位
    }
    if(Ntop-Otop != 1)
        return Infinity+1;
    i=1;j=0;
    res = SN[0];
    while(j != Otop)
    {
        switch(SO[j])
        {
            case '+':
                res += SN[i];
                i++;j++;
                break;
            case '-':
                res -= SN[i];
                i++;j++;
                break;
            case '*':
                res *= SN[i];
                i++;j++;
                break;
            case '/':
                res /= SN[i];
                i++;j++;
                break;
        }
    }
    return res;
}
