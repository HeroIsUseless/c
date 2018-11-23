#include <stdio.h>
#include <stdlib.h>
#define ERROR 1e8
typedef int ElementType;
typedef enum { push, pop, end } Operation;
//用从两边向中间的方法，而且不用扩容
typedef struct StackRecord *Stack;
struct StackRecord  {
    int Capacity;       /* maximum size of the stack array */
    int Top1;           /* top pointer for Stack 1 */
    int Top2;           /* top pointer for Stack 2 */
    ElementType *Array; /* space for the two stacks */
};

Stack CreateStack( int MaxElements );
int IsEmpty( Stack S, int Stacknum );
int IsFull( Stack S );
int Push( ElementType X, Stack S, int Stacknum );
ElementType Top_Pop( Stack S, int Stacknum );

Operation GetOp();  /* details omitted */
void PrintStack( Stack S, int Stacknum ); /* details omitted */

int main()
{
    int N, Sn, X;
    Stack S;
    int done = 0;

    scanf("%d", &N);
    S = CreateStack(N);//创建一个栈，N为栈数组的大小
    while ( !done ) {
        switch( GetOp() ) {//操作方法
        case push:
            scanf("%d %d", &Sn, &X);//X为操作数，S是两个栈，Sn为哪一个栈
            if (!Push(X, S, Sn)) printf("Stack %d is Full!\n", Sn);
            break;
        case pop:
            scanf("%d", &Sn);
            X = Top_Pop(S, Sn);
            if ( X==ERROR ) printf("Stack %d is Empty!\n", Sn);
            break;
        case end:
            PrintStack(S, 1);//打印出两个栈
            PrintStack(S, 2);
            done = 1;
            break;
        }
    }
    return 0;
}

/* Your function will be put here */
Stack CreateStack(int MaxElements)
{
    Stack s;
    s->Array = (ElementType*)malloc(sizeof(MaxElements * ElementType));
    s->Capacity = MaxElements;
    s->Top1 = 0;
    s->Top2 = MaxElements;
    return s;
}
int IsEmpty(Stack S, int Stacknum)
{
    if(Stacknum == 1)
    {
        if(S->Top1 == 0)
            return 1;
        else
            return 0;
    }
    if(Stacknum == 2)
    {
        if(S->Top2 == S->Capacity)
            return 1;
        else
            return 0;
    }
}
int IsFull(Stack S)
{
    if(S->Top1+(S->Capacity-S->Top2) >= S->Capacity)
        return 1;
    else
        return 0;
}
int Push(ElementType X, Stack S, int Stacknum)
{
    if(IsFull(S))
    {
        return 0;
    }
    if(Stacknum == 1)
        *(S->Array+S->Top1++) == X;
    if(Stacknum == 2)
        *(S->Array-S->Top2--) == X;
    return 1;
}
ElementType Top_Pop(Stack S, int Stacknum)
{
    if(IsEmpty(S, Stacknum))
        return ERROR;
    if(Stacknum == 1)
        return *(S->Array-(--S->Top1));
    if(Stacknum == 2)
        return *(S->Array+(++S->Top2));
}











