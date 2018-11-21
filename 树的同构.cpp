#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
#define MAXSIZE 1000
typedef struct BTree { char e; BTree *subTre1, *subTre2; } BTree;
typedef struct BTArr { char e; char subTre1, subTre2; } BTArr;
bool Process(BTree *cpBT1, BTree *cpBT2){//此函数仅仅只是比较两个子节点
    if(cpBT1->subTre1==NULL && cpBT1->subTre2==NULL){
        if(cpBT2->subTre1==NULL&&cpBT2->subTre2==NULL)
            return true;
    }
    if(cpBT1->subTre1==NULL && cpBT1->subTre2!=NULL){
        if(cpBT2->subTre1==NULL)
            if(cpBT2->subTre2->e==cpBT1->subTre2->e)
                return Process(cpBT2->subTre2,cpBT1->subTre2);
        if(cpBT2->subTre2==NULL)
            if(cpBT2->subTre1->e==cpBT1->subTre2->e)
                return Process(cpBT1->subTre2,cpBT2->subTre1);
    }
    if(cpBT1->subTre1!=NULL && cpBT1->subTre2==NULL){
        if(cpBT2->subTre1==NULL)
            if(cpBT2->subTre2->e==cpBT1->subTre1->e)
                return Process(cpBT2->subTre2,cpBT1->subTre1);
        if(cpBT2->subTre2==NULL)
            if(cpBT2->subTre1->e==cpBT1->subTre1->e)
                return Process(cpBT1->subTre1,cpBT2->subTre1);
    }
    if(cpBT1->subTre1!=NULL && cpBT1->subTre2!=NULL){
        if(cpBT2->subTre1==NULL || cpBT2->subTre2==NULL) return false;
        if(cpBT1->subTre1->e==cpBT2->subTre1->e && cpBT1->subTre2->e==cpBT2->subTre2->e)
            return Process(cpBT1->subTre1,cpBT2->subTre1) && Process(cpBT1->subTre2,cpBT2->subTre2);
        if(cpBT1->subTre1->e==cpBT2->subTre2->e && cpBT1->subTre2->e==cpBT2->subTre1->e)
            return Process(cpBT1->subTre1,cpBT2->subTre2) && Process(cpBT1->subTre2,cpBT2->subTre1);
    }
    return false;//凡是运行到这里就是不相等了
}
void Print(BTree *cpBT){
    printf("%c ",cpBT->e);
    if(cpBT->subTre1)
    printf("%c ",cpBT->subTre1->e);else printf("N ");
    if(cpBT->subTre2)
    printf("%c ",cpBT->subTre2->e);else printf("N ");
    printf("\n");

    if(cpBT->subTre1){Print(cpBT->subTre1);}
    if(cpBT->subTre2){Print(cpBT->subTre2);}
}
BTree* CreaBTree(BTArr cBTArr[],int cn){
    BTree *pBT[MAXSIZE];
    for(int i=0; i<cn; i++) {
        pBT[i]=(BTree*)malloc(sizeof(BTree));
        pBT[i]->e=cBTArr[i].e;
    }
    for(int i=0; i<cn; i++){
        if(cBTArr[i].subTre1 != '-')
            pBT[i]->subTre1 = pBT[(int)(cBTArr[i].subTre1-'0')];
        else
            pBT[i]->subTre1 = NULL;
        if(cBTArr[i].subTre2 != '-')
            pBT[i]->subTre2 = pBT[(int)(cBTArr[i].subTre2-'0')];
        else
            pBT[i]->subTre2 = NULL;
    }
    for(int i=0; i<cn; i++)
        if(pBT[i]->e=='A')
            return pBT[i];
}
int main()
{
    int r1n,r2n;
    BTArr r1arr[MAXSIZE], r2arr[MAXSIZE];
    cin >> r1n;for(int i=0; i<r1n; i++)cin >> r1arr[i].e >> r1arr[i].subTre1 >> r1arr[i].subTre2;
    cin >> r2n;for(int i=0; i<r2n; i++)cin >> r2arr[i].e >> r2arr[i].subTre1 >> r2arr[i].subTre2;
    BTree *rot1=NULL, *rot2=NULL;
    rot1=CreaBTree(r1arr,r1n);rot2=CreaBTree(r2arr,r2n);
    //Print(rot1);Print(rot2);
    if(r1n==0 && r2n==0){
        printf("Yes");
        return 0;
    }
    if(r1n != r2n)
    {
        printf("No");
        return 0;
    }
    if(rot1->e==rot2->e && Process(rot1,rot2)) printf("Yes"); else printf("No");
    return 0;
}


