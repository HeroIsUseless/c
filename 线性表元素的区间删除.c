#include <stdio.h>
//线性表元素的区间删除
#define MAXSIZE 20
#define ERROR -1

typedef enum {false, true} bool;
typedef int ElementType;
typedef int Position;
typedef struct LNode *List;
struct LNode {
    ElementType Data[MAXSIZE];
    Position Last; /* 保存线性表中最后一个元素的位置 */
};

List ReadInput(); /* 裁判实现，细节不表。元素从下标0开始存储 */
void PrintList( List L ); /* 裁判实现，细节不表 */
List Delete( List L, ElementType minD, ElementType maxD );
List MakeEmpty()
{
    struct LNode *pList = malloc(sizeof(struct LNode));
    pList->Last = -1;//-1代表没有数据
    return pList;
}
bool Insert( List L, ElementType X, Position P )
{
    int i;
    if(L->Last+1 >= MAXSIZE)
    {
        printf("FULL");
        return false;
    }
    if(P>L->Last+1 || P<0)//数据不准插入到数列之后的地方
    {
        printf("ILLEGAL POSITION");
        return false;
    }
    for(i=L->Last; i>=P; i--)
        L->Data[i+1] = L->Data[i];
    L->Last += 1;
    L->Data[P] = X;
    return true;
}
int main()
{
    List L;
    ElementType X;
    ElementType minD, maxD;
    Position P;
    int N;
    int i;
    L = MakeEmpty();
    scanf("%d", &N);
    while ( N-- ) {
        scanf("%d", &X);
        if ( Insert(L, X, 0)==false )
            printf(" Insertion Error: %d is not in.\n", X);
    }
    printf("输入完成\n");
    scanf("%d %d", &minD, &maxD);
    L = Delete( L, minD, maxD );
    for(i=0; i<=L->Last; i++)
        printf("%d ", L->Data[i]);
    free(L);
    return 0;
}

/* 你的代码将被嵌在这里 */
//设计的删除函数，删除值为min与max之间的元素
List Delete( List L, ElementType minD, ElementType maxD )
{
    int i, n=0;
    ElementType a[MAXSIZE];
    for(i=0; i<=L->Last; i++)
    {
        if(!(L->Data[i]>minD && L->Data[i]<maxD))
                a[n++] = L->Data[i];
    }
    for(i=0; i<n; i++)
        L->Data[i] = a[i];
    L->Last = n-1;
    return L;
}
















