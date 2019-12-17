#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//��׺����ʽ���㣬����������Ȳ�������һʱ����ʼִ�м��㣬����������
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
    ElementType SN[Max_Expr]={0}; int Ntop = 0;//ָ��ͷ��ָ�룬��0��ʼ��ͷָ��ָ��Ϊ��
    float ft; int isDot; float dot;//��ʱ����
    //��ȡ�ַ���
    while(*expr != 0)
    {
        if(*expr>='0' && *expr<='9')//ת�����ֲ�ѹ������
        {
            ft = 0.0;
            isDot = 0;//�Ƿ������С����
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
        if(*expr=='+' || *expr=='*' || *expr=='/')//�ж����������ʼ����
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
        if(*expr=='-')//���������Ǹ�����ѹ��ջ�����Ǽ��ţ��������㣩
        {
            if(*(expr+1)==' '|| *(expr+1)=='\0')
            {
                if(Ntop < 2) return Infinity;
                SN[Ntop-2] -= SN[Ntop-1];
                SN[Ntop-1] = 0;Ntop--;
            }
            else
            {
                expr++;//�������ֲ���
                ft = 0.0;
                isDot = 0;//�Ƿ������С����
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
        expr++;//�ո��λ
    }
    if(Ntop > 1) return Infinity;
    else return SN[0];
}
