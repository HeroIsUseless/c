#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 5
#define ERROR -1

typedef enum {false, true} bool;
typedef int ElementType;
typedef int Position;
typedef struct LNode *List;
struct LNode {
    ElementType Data[MAXSIZE];
    Position Last; /* 保存线性表中最后一个元素的位置 */
};

List MakeEmpty();
Position Find( List L, ElementType X );
bool Insert( List L, ElementType X, Position P );
bool Delete( List L, Position P );
//顺序表操作集
int main()
{
    List L;
    ElementType X;
    Position P;
    int N;
    L = MakeEmpty();
    scanf("%d", &N);
    while ( N-- ) {
        scanf("%d", &X);
        if ( Insert(L, X, 0)==false )
            printf(" Insertion Error: %d is not in.\n", X);
    }
    scanf("%d", &N);
    while ( N-- ) {
        scanf("%d", &X);
        P = Find(L, X);
        if ( P == ERROR )
            printf("Finding Error: %d is not in.\n", X);
        else
            printf("%d is at position %d.\n", X, P);
    }
    scanf("%d", &N);
    while ( N-- ) {
        scanf("%d", &P);
        if ( Delete(L, P)==false )
            printf(" Deletion Error.\n");
        if ( Insert(L, 0, P)==false )
            printf(" Insertion Error: 0 is not in.\n");
    }
    free(L);
    return 0;
}

//顺序表操作集接口
//用数组的方法做的，位置允许0

//创建并返回一个空的线性表
List MakeEmpty()
{
    struct LNode *pList = malloc(sizeof(struct LNode));
    pList->Last = -1;//-1代表没有数据
    return pList;
}
//返回线性表中x的位置
Position Find( List L, ElementType X )
{
    int i;
    for(i=0; i<=L->Last; i++)
        if(L->Data[i] == X)//如果有两个以上一样的数据，只返回第一个数据的位置
            return i;
    return ERROR;
}
//将x插入在位置P并返回true
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
//将位置P的元素删除并返回true
bool Delete( List L, Position P )
{
    int i;
    if(P>L->Last || P<0)
    {
        printf("POSITION %d EMPTY", P);
        return false;
    }
    for(i=P; i<L->Last; i++)
        L->Data[i] = L->Data[i+1];
    L->Last -= 1;
    return true;
}
