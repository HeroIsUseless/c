#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ERROR -1
#define NULL -1
typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
struct NodeDel {
    ElementType Data;
    PtrToNode   Next;
};
struct Nod {
    ElementType Data;
    ElementType Next;
};
typedef PtrToNode List;

//设一个标记数组，只循环一遍,方法是读取一个节点，在数组中查看重复，如果有重复则去掉这个节点
int main()
{
    int n, pHead, pHDel=0, pDel, addr=00100, p1, p2;
    struct Nod list[100001];
    int a[100001] = {0};//保存了节点的数据，有了就变1
    scanf("%d %d", &pHead, &n);
    printf("%d %d\n", pHead, n);
    while(n--)
    {
        //scanf("%d %d %d", &addr, &list[addr].Data, &list[addr].Next);
        printf("%d %d %d\n", addr, list[addr].Data, list[addr].Next);
    }


    p1 = pHead;
    p2 = list[pHead].Next;
    pDel = pHDel;
    while(p2 != NULL)
    {
        if(a[abs(list[p2].Data)] != 1)
            a[abs(list[p2].Data)] = 1;
        else//去掉这个节点
        {
            list[p1].Next = list[p2].Next;
            list[pDel].Next = p2;
            list[p2].Next = NULL;
            pDel = list[pDel].Next;
        }
    }

    return 0;
}
void RemovRep(List cpHead)
{
    PtrToNode p1, p2;
    List pHead;
    List pHDel;
    List pDel;
    int p[10001] = {0};//保存了节点的数据，有了就加1
    p1 = cpHead;
    if(pHead->Next != NULL) p2 = pHead->Next; else return;
    while(p2 != NULL)
    {
        if(p[abs(p2->Data)] != 1)
            p[abs(p2->Data)] = 1;
        else//去掉这个节点
        {
            p1->Next = p2->Next;
            pDel->Next = p2;
            p2->Next = NULL;
            pDel = pDel->Next;
        }
    }
}

int Joseph()//约翰逊环，用的并不是递归
{
   int i, p, n;
    List pStart, p1, p2;
    //输入数据
    scanf("%d %d", &n, &p);
    for(i=1; i<=n; i++)
    {
        p1 = malloc(sizeof(struct Node));
        p1->Data = i; p1->Next = NULL;
        if(i == 1)
        {
            pStart = p1;
            p2 = p1;
        }
        else
        {
            p2->Next = p1;
            p2 = p2->Next;
        }
    }

    p1 = pStart;
    p2->Next = pStart;
    //进行处理
    while(1)
    {
        if(p1 == p2)
        {
            printf("%d\n", p1->Data);
            break;
        }
        i = 1;
        while(i != p)
        {
            p1 = p1->Next;
            p2 = p2->Next;
            i++;
        }
        printf("%d ",p1->Data);
        p1 = p1->Next;
        p2->Next = p1;
    }
}
int JosephRing(int n, int k, int i)//约翰逊环，用的是递归，并不是链表
{
    if(i == 1)
        return (k-1)%n;
    else
        return (JosephRing(n-1, k, i-1) + k) % n;
}
void ChainTableCombine()//顺序链表的合并链表合并
{
    int a, n1, n2;
    PtrToNode L;
    List pHead1 = malloc(sizeof(struct Node));
    List pHead2 = malloc(sizeof(struct Node));
    List pHead3 = malloc(sizeof(struct Node));
    PtrToNode p1, p2, p3;
    pHead1->Data = pHead2->Data = pHead3->Data = 0;
    pHead1->Next = pHead2->Next = pHead3->Next = NULL;

    p2 = pHead1;
    scanf("%d", &a);
    while(a != -1)
    {
        p1 = malloc(sizeof(struct Node));
        p1->Data = a; p1->Next = NULL;
        p2->Next = p1;
        p2 = p2->Next;
        scanf("%d",&a);
    }

    p2 = pHead2;
    scanf("%d", &a);
    while(a != -1)
    {
        p1 = malloc(sizeof(struct Node));
        p1->Data = a; p1->Next = NULL;
        p2->Next = p1;
        p2 = p2->Next;
        scanf("%d",&a);
    }

    p1 = pHead1->Next; p2 = pHead2->Next; p3 = pHead3;
    while(p1!=NULL && p2!=NULL)
    {
        if(p1->Data <= p2->Data)
        {
            p3->Next = p1;
            p1 = p1->Next;
        }
        else
        {
            p3->Next = p2;
            p2 = p2->Next;
        }
        p3 = p3->Next;
    }
    if(p1 == NULL)
        p3->Next = p2;
    else
        p3->Next = p1;

    if(pHead3->Next == NULL)
    {
        printf("NULL\n");
    }
    else
    {
        L = pHead3->Next;
        while(L->Next != NULL)
        {
            printf("%d ", L->Data);
            L = L->Next;
        }
        printf("%d\n",L->Data);
    }
    free(pHead1);
    free(pHead2);
}
//用递归的方法来做，每完成一次反转，头指针向后移K位然后递归
void K_Reverse(List L, int K)//链表反转
{
    int i, n=1;
    List p0, p1, p2, p3;
    if(L->Next == NULL || K<=1) return;
    //数出K个数
    p0 = L->Next;
    while(p0->Next != NULL && n<K)
    {
        n++;
        p0 = p0->Next;
    }
    if(n != K) return;
    //进行逆序操作
    p1 = L->Next;
    p3 = L->Next->Next;
    p1->Next = p0->Next;//段首连接
    p0 = p1;
    for(i=1; i<K; i++)  //中间反连
    {
        p2 = p3;
        p3 = p2->Next;
        p2->Next = p1;
        p1 = p2;
    }
    L->Next = p2;       //段尾连接
    //递归
    L = p0;//头指针向后移动K位
    K_Reverse(L, K);
}
//比第一个还小
//比最后一个还大
//就1个或者两个节点
List Insert(List L, ElementType X)//链表插入
{
    PtrToNode pHead = L;
    PtrToNode pNode = malloc(sizeof(struct Node));
    pNode->Data = X;
    pNode->Next = NULL;
    if(L->Next == NULL)
    {
        L->Next = pNode;
        return pHead;
    }

    L = L->Next;//因为带有头节点，所以这才是第一个节点
    if(L->Data >= X)//判断第一个是不是小于X
    {
        pNode->Next = L;
        pHead->Next = pNode;
        return pHead;
    }
    while(L->Next != NULL)//这样最坏会到倒数第一个，中间的判断
    {
        if(L->Data<=X && L->Next->Data>X)
        {
            pNode->Next = L->Next;
            L->Next = pNode;
            return pHead;
        }
        L = L->Next;
    }
    //到了尾节点
    if(L->Data <= X)
    {
        L->Next = pNode;
        return pHead;
    }
}
//首先遍历一遍有n个
void K2_Reverse(List L, int K)//普通方法做的链表反转
{
    int i, j, n = 1;
    List pHead = L;
    PtrToNode p1, p2, p3, p4, p5=pHead;
    if(pHead->Next == NULL) return;
    L = pHead->Next;
    while(L->Next != NULL)
    {
        n++;
        L = L->Next;
    }
    p1 = p2 = p3 = p4 = p5->Next;
    for(i=1; i*K<=n; i++)
    {
        p1 = p2 = p3 = p4;
        for(j=1; j<K; j++)
        {
            if(j == 1) {p4 = p4->Next; p3->Next = NULL;}
            p2 = p4;
            p4 = p2->Next;
            p2->Next = p1;
            p1 = p2;
        }
        p5->Next = p2;
        p5 = p3;
        p3->Next = p4;
    }
}
//时间和空间上都尽可能高效的算法，在不改变链表的前提下，求链式存储的线性表的倒数第m（>0）个元素。
ElementType Find( List L, int m )
{
    PtrToNode p1;
    PtrToNode p2;
    if(L->Next == NULL) return ERROR;
    p1 = L->Next;
    p2 = L->Next;
    while(p1->Next != NULL)
    {
        p1 = p1->Next;
        if(m != 1) m--;
        else p2 = p2->Next;
    }
    if(m != 1)
        return ERROR;
    else
        return p2->Data;
}















