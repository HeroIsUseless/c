#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ERROR -1
#define NULL -1
struct Nod {
    int Data;
    int Next;
};
struct Nod list[100010];
int a[100000] = {0};
void print(int cp)
{
    if(list[cp].Next == -1)
        printf("%05d %d %d\n", cp, list[cp].Data, list[cp].Next);
    else
        printf("%05d %d %05d\n", cp, list[cp].Data, list[cp].Next);
}
/*
*方法：设一个标记数组，只循环一遍,方法是读取一个节点，在数组中查看重复，如果有重复则去掉这个节点
*极端情况：没有重复，只有一个节点
*/
int main()
{
    int n, pHead, pHDel=100001, pDel, addr=1, p1, p2;
    scanf("%d %d", &pHead, &n);
    while(n--)
    {
        scanf("%d %d %d", &addr, &p1, &p2);
        list[addr].Data = p1;
        list[addr].Next = p2;
    }
    //进行处理
    p1 = pHead;
    a[abs(list[p1].Data)] = 1;
    p2 = list[pHead].Next;
    list[pHDel].Next = NULL;
    pDel = pHDel;
    while(p2 != NULL)
    {
        if(a[abs(list[p2].Data)] != 1)//如果没有重复，前进
        {
            a[abs(list[p2].Data)] = 1;
            p2 = list[p2].Next;
            p1 = list[p1].Next;
        }
        else//如果重复，就去掉这个节点
        {
            list[p1].Next = list[p2].Next;
            list[pDel].Next = p2;
            pDel = list[pDel].Next;
            p2 = list[p2].Next;
            list[pDel].Next = NULL;
        }
    }
    //输出去重后的节点
    p1 = pHead;
    while(p1 != NULL)
    {
        print(p1);
        p1 = list[p1].Next;
    }
    //输出被删除的节点
    p2 = list[pHDel].Next;
    while(p2 != NULL)
    {
        print(p2);
        p2 = list[p2].Next;
    }
    return 0;
}
