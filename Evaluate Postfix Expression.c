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
    ElementType SN[Max_Expr]={0}; int Ntop = 0;//指向头的指针，从0开始，头指针指向为空
    float ft; int isDot; float dot;//临时变量
    //读取字符串
    while(*expr != 0)
    {
        if(*expr>='0' && *expr<='9')//转换数字并压入数字
        {
            ft = 0.0;
            isDot = 0;//是否出现了小数点
            dot = 1;
            while(*expr != ' ' && *expr != '\0')
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
            if(Ntop < 2)
                return Infinity;
            switch(*expr)
            {
                case '+':
                    SN[Ntop-2] += SN[Ntop-1];
                    SN[Ntop-1] = 0;Ntop--;
                    break;
                case '-':

                    break;
                case '*':
                    SN[Ntop-2] *= SN[Ntop-1];
                    SN[Ntop-1] = 0;Ntop--;
                    break;
                case '/':
                    if(SN[Ntop-1]<0.1 && SN[Ntop-1]>-0.1) return Infinity;
                    SN[Ntop-2] /= SN[Ntop-1];
                    SN[Ntop-1] = 0;Ntop--;
                    break;
            }
        }
        if(*expr=='-')//单独区分是负数（压入栈）还是减号（进行运算）
        {
            if(*(expr+1)==' '|| *(expr+1)=='\0')
            {
                if(Ntop < 2) return Infinity;
                SN[Ntop-2] -= SN[Ntop-1];
                SN[Ntop-1] = 0;Ntop--;
            }
            else
            {
                expr++;//进入数字部分
                ft = 0.0;
                isDot = 0;//是否出现了小数点
                while(*expr != ' ' && *expr != '\0')
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
    if(Ntop > 1) return Infinity;
    else return SN[0];
}
