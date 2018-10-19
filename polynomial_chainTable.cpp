#include <stdio.h>
#include <stdlib.h>
//规定有头指针
//规定只能从大到小排列
namespace Polynomial
{
    typedef struct Elem
    {
        float coef;//参数
        int expn;//指数
        Elem *next;
    };

    class Polynomial
    {
        public: Elem *head, *tail;
        public:
        //构造函数
        Polynomial()
        {
            head = (Elem*)malloc(sizeof(Elem));
            head->next = NULL;
            tail = head;
        }
        //清空
        void ClearPoly()
        {
            Elem *p1, *p2;
            p1 = head;
            p2 = head->next;
            p1->next = NULL;
            while(p2 != NULL)
            {
                p1 = p2;
                p2 = p2->next;
                free(p1);
            }
        }
        void CopyPoly(Polynomial pol)//就是从另外的多项式完全拷贝过来，但是有多余的真么办？挨个删掉
        {
            ELem *p1 = head, *p2 = pol.head->next, *p3;
            while(p2 != NULL)
            {
                if(p1->next != NULL)
                {
                    p1->coef = p2->coef;
                    p1->expn = p2->expn;
                }
                else
                {
                    p3 = malloc(sizeof(Elem));
                    p3->coef = p2->coef;
                    p3->expn = p2->expn;
                    p3->next = NULL;
                    p1->next = p3;
                }
                p1 = p1->next;
                p2 = p2->next;
            }
            p1 = p1->next;//这时候p1是最后一个了
            while(p1 != NULL)
            {
                p3 = p1->next;
                free(p1);
                p1 = p3;
            }
        }
        //打印
        void PrintPolyn()
        {
            Elem *p1;
            p1 = head->next;
            while(p1->next != NULL)
            {
                printf("%d %d ", p1->coef, p1->expn);
            }
            printf("%d %d", p1->coef, p1->expn);
        }
        //返回长度
        int PolyLength()
        {
            int n = 0;
            Elem *p1 = head;
            while(p1 != NULL)
            {
                p1 = p1->next;
                n++;
            }
            return n;
        }
        //添加节点
        void AddPolyn(Elem *cp)//规定只能从大到小输入
        {//这样的好处是方便的更改参数
            tail->next = cp;
            tail = tail->next;
            tail->next = NULL;
        }
        //多项式加法
        void AdditivePolyn(Polynomial pol)
        {
            Elem *p1, *p2=pol.head->next;
            while(p2 != NULL)
            {
                p1 = head->next;
                while(p1 != NULL)
                {
                    if(p1->expn == p2->expn)
                    {
                        p1->coef += p2->coef;
                        break;
                    }
                    p1 = p1->next;
                }
                if(p1 == NULL)//没有找到，新插入一个
                {
                    p1 = head;
                    while(1)
                    {
                        if(p1->next==NULL || p1->expn<p2->expn)
                        {
                            Elem *p3 = (Elem*)malloc(sizeof(Elem));
                            p3->coef = p2->coef;
                            p3->expn = p2->expn;
                            p3->next = p1->next;
                            p1->next = p3;
                        }
                        else
                        {
                            p1 = p1->next;
                        }
                    }
                }
                p2 = p2->next;
            }
        }
        //多项式减法
        void SubtractPolyn(Polynomial pol)//实现方法，以p2为循环条件，进行相减操作
        {
            Elem *p1 = head, *p2 = pol.head->next, *p3;
            while(p2 != NULL)//最好也只是循环一次
            {
                if(p1->next != NULL)
                {
                    if(p1->next->expn < p2->expn)//开辟新空间操作
                    {
                        p3 = (Elem*)malloc(sizeof(Elem));
                        p3->expn = p2->expn;
                        p3->coef = -p2->coef;
                        p3->next = p1->next;
                        p1->next = p3;
                        p1 = p1->next;
                        p2 = p2->next;
                    }
                    else if(p1->next->expn == p2->expn)//进行相减操作
                    {
                        p1->next->coef -= p2->coef;
                        p1 = p1->next;
                        p2 = p2->next;
                    }
                    else if(p1->next->expn > p2->expn)
                    {
                        p1 = p1->expn;
                    }
                }
                else
                {
                    p3 = malloc(sizeof(Elem));
                    p3->coef = -p2->coef;
                    p3->expn = p2->expn;
                    p3->next = NULL;
                    p1->next = p3;
                }
            }
        }

        //多项式乘法
        void MultiplyPolyn(Polynomial pol)//多项式乘法是拆分啊，每个都是一个新的天，然后合并相加
        {
            Elem *p1 = head, *p2 = pol.head->next;
            Polynomial poly = new Polynomial();
            Polynomial polySum = new Polynomial();
            while(p2 != NULL)//用每一项乘以那个项，最后相加，最后成功
            {
                poly.CopyPoly(this);
                poly.MultiplyCoef(p2->coef);
                poly.MultiplyExpn(p2->expn);
                polySum.AdditivePolyn(poly);
                poly.ClearPoly();
            }
            this.ClearPoly();
            this.CopyPoly(polySum);
        }
        //系数乘法
        void MultiplyCoef(float f)
        {
            Elem *p1 = head->next;
            while(p1 != NULL)
            {
                p1->coef *= f;
                p1 = p1->next;
            }
        }
        //指数乘法
        void MultiplyExpn(int e)
        {
            Elem *p1 = head->next;
            while(p1 != NULL)
            {
                p1->expn += e;
                p1 = p1->next;
            }
        }
        //多项式除法
        Polynomial DivisionPolyn(Polynomial pol)//除法怎么实现的来着？还要返回商和余数
        {//本类除成余数，返回商
            Elem *p;
            Polynomial polRes = new Polynomial();
            Polynomial polt = new Polynomial();
            if(this.head->next == NULL) return NULL;
            if(pol.head->next == NULL) return NULL;
            while(this.head->next->expn > pol.head->next->expn)
            {
                p = malloc(sizeof(Elem));
                p->coef = this.head->next->coef / pol.head->coef;
                p->expn = this.head->next->expn - pol.head->next->expn;
                polRes.AddPolyn(p);
                polt.CopyPoly(pol);
                polt.MultiplyCoef(p->coef);
                polt.MultiplyExpn(p->expn);
                this.DivisionPolyn(polt);
            }
            return polRes;
        }
        //析构函数
        ~Polynomial()
        {
            Elem *p1, *p2;
            p1 = head;
            p2 = head->next;
            free(p1);
            while(p2 != NULL)
            {
                p1 = p2;
                p2 = p2->next;
                free(p1);
            }
        }
    };
}
int main()//测试函数
{
    return 0;
}
