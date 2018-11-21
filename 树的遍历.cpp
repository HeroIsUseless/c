#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;
#define MAXSIZE 100000
//都是从1开始的
typedef struct BTree {
    int e;
    BTree *subTre1, *subTre2;
} BTree;
void Process(int ca[], int cb[], int cn, BTree *cpBT){
    int i; for(i=1; i<=cn; i++) if(ca[i] == cb[cn]) break;//找出中序的根节点位置
    if(i > 1 && i<=cn){
        BTree *tBTF = (BTree*)malloc(sizeof(BTree)); tBTF->subTre1=NULL; tBTF->subTre2=NULL;
        tBTF->e = cb[i-1];
        cpBT->subTre1 = tBTF;
        Process(ca, cb, i-1, tBTF);
    }
    if(i < cn && i>=1){
        BTree *tBTL = (BTree*)malloc(sizeof(BTree)); tBTL->subTre1=NULL; tBTL->subTre2=NULL;
        tBTL->e = cb[cn-1];
        cpBT->subTre2 = tBTL;
        Process(ca+i, cb+i-1, cn-i, tBTL);
    }
}
void Print(BTree *cpBT){
    BTree* que[MAXSIZE];
    int n = 0;
    que[++n] = cpBT;
    while(n != 0){
        if(cpBT->subTre1) que[++n] = cpBT->subTre1;
        if(cpBT->subTre2) que[++n] = cpBT->subTre2;
        if(n==1) printf("%d", que[1]->e); else printf("%d ", que[1]->e);
        n--; for(int i=1; i<=n; i++) que[i] = que[i+1];
        cpBT = que[1];
    }
}
int main()
{
    int i;
    int a[MAXSIZE],b[MAXSIZE];
    int n;
    scanf("%d",&n);
    for(i=1; i<=n; i++) scanf("%d",&b[i]);
    for(i=1; i<=n; i++) scanf("%d",&a[i]);
    BTree *pBT = (BTree*)malloc(sizeof(BTree));
    pBT->e=b[n]; pBT->subTre1=NULL; pBT->subTre2=NULL;
    Process(a, b, n, pBT);
    Print(pBT);
    return 0;
}



