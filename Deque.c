#include <stdio.h>
#include <stdlib.h>

#define ElementType int
#define ERROR 1e5
typedef enum { push, pop, inject, eject, end } Operation;

typedef struct Node *PtrToNode;
struct Node {
    ElementType Element;
    PtrToNode Next, Last;
};
typedef struct DequeRecord *Deque;
struct DequeRecord {
    PtrToNode Front, Rear;
};
Deque CreateDeque();
int Push( ElementType X, Deque D );
ElementType Pop( Deque D );
int Inject( ElementType X, Deque D );
ElementType Eject( Deque D );

Operation GetOp();          /* details omitted */
void PrintDeque( Deque D ); /* details omitted */

int main()
{
    ElementType X;
    Deque D;
    int done = 0;

    D = CreateDeque();
    while (!done) {
        switch(GetOp()) {
        case push:
            scanf("%d", &X);
            if (!Push(X, D)) printf("Memory is Full!\n");
            break;
        case pop:
            X = Pop(D);
            if ( X==ERROR ) printf("Deque is Empty!\n");
            break;
        case inject:
            scanf("%d", &X);
            if (!Inject(X, D)) printf("Memory is Full!\n");
            break;
        case eject:
            X = Eject(D);
            if ( X==ERROR ) printf("Deque is Empty!\n");
            break;
        case end:
            PrintDeque(D);
            done = 1;
            break;
        }
    }
    return 0;
}

/* Your function will be put here */
//通过用一个标记节点实现首次定位，相遇就是队列为空，防止两列分开
Deque CreateDeque()
{
    Deque D = (Deque)malloc(sizeof(struct DequeRecord));
    D->Front = NULL;
    D->Rear = NULL;
    return D;
}
int Push( ElementType X, Deque D )
{
    PtrToNode p = malloc(sizeof(struct Node));
    p->Element = X;
    if(D->Rear==NULL && D->Front==NULL)//代表是第一次刚创建时，否则不允许这两个量为NULL，要不就同时为0
    {
        D->Rear = D->Front = p;
        p->Next = p->Last = NULL;
    }
    else
    {
        p->Next = NULL;
        p->Last = D->Front;
        D->Front->Next = p;
        D->Front = D->Front->Next;
    }
}
ElementType Pop( Deque D )
{
    if(D->Front==NULL && D->Rear==NULL) return ERROR;
    ElementType e = D->Front->Element;
    if(D->Front->Last == NULL)
        D->Front = D->Rear = NULL;
    else
        D->Front = D->Front->Last;
    return e;
}
int Inject( ElementType X, Deque D )
{
    PtrToNode p = malloc(sizeof(struct Node));
    p->Element = X;
    if(D->Rear==NULL && D->Front==NULL)
    {
        D->Rear = D->Front = p;
        p->Last = p->Next = NULL;
    }
    else
    {
        p->Next = D->Rear;
        p->Last = NULL;
        D->Rear->Last = p;
        D->Rear = D->Rear->Last;
    }

}
ElementType Eject( Deque D )
{
    if(D->Rear == NULL) return ERROR;
    ElementType e = D->Rear->Element;
    if(D->Rear->Next == NULL)
        D->Rear = D->Front = NULL;
    else
        D->Rear = D->Rear->Next;
    return e;
}
