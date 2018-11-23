#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//中缀表达式转换成后缀表达式，当输入的数比操作符大一时，开始执行计算，不包括错误处理
typedef double ElementType;
#define Infinity 1e8
#define Max_Expr 30   /* max size of expression */

void TralPostfix( char *expr );

int main()
{
    char expr[Max_Expr];
    gets(expr);
    TralPostfix( expr );
    return 0;
}

/* Your function will be put here */
void TralPostfix( char *expr )
{
    float SN[Max_Expr]; int Ntop = 0;
    char SO[Max_Expr]; int Otop = 0;
    float ft; int isDot; float dot; int i;//临时变量
    while(*expr != 0)
    {
        if(*expr>='0' && *expr<='9')//转换数字并压入数字
        {
            ft = 0.0;
            isDot = 0;//是否出现了小数点
            dot = 1;
            while(*expr!=' ' || *expr!='(' || *expr!=')')
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
        if(*expr=='+' || *expr=='*' || *expr=='/')//压入运算符
        {
            SO[Otop++] = *expr;
        }
        if(*expr=='-')//单独区分是负数还是减号
        {
            if(*(expr+1)==' '|| *(expr+1)=='\0')
                SO[Otop++] = *expr;
            else
            {
                expr++;//进入数字部分
                ft = 0.0;
                isDot = 0;//是否出现了小数点
                while(*expr!=' ' || *expr!='(' || *expr!=')')
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
        //判断是否可以输出了
        if(Ntop-Otop == 1)
        {
            for(i=0; i<Ntop; i++)
                printf("%f ", SN[i]);
            Ntop = 0;
            for(i=0; i<Otop; i++)
                printf("%c ", SO[i]);
            Otop = 0;
        }
    }
}





