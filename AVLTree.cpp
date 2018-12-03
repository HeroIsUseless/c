#include <stdio.h>
#include <stdlib.h>
#include "iostream"
using namespace std;
typedef struct AVLNode *PtrToAVLNode;
struct AVLNode
{
    int Key;            //值
    PtrToAVLNode Left;  //左孩子
    PtrToAVLNode Right; //右孩子
    int Height;         //只做高度用
};
typedef PtrToAVLNode AVLTree;
AVLTree Insert(AVLTree T, int Key);
void PostOrderPrint(AVLTree T); /* details omitted */
void InOrderPrint(AVLTree T);   /* details omitted */

int main()
{
    int N, Key, i;
    AVLTree T = NULL;

    scanf("%d", &N);
    for (i = 0; i < N; i++)
    {
        scanf("%d", &Key);
        T = Insert(T, Key);
    }
    //printf("\n");
    PostOrderPrint(T);
    printf("\n");
    InOrderPrint(T);

    return 0;
}
/* Your function will be put here */
void InOrderPrint(AVLTree T){
    if(T->Left) InOrderPrint(T->Left );
    if(T) printf("%d ", T->Key);
    if(T->Right)InOrderPrint(T->Right);
}
void PostOrderPrint(AVLTree T){
    if(T->Left) PostOrderPrint(T->Left );
    if(T->Right)PostOrderPrint(T->Right);
    if(T) printf("%d ", T->Key);
}
#define true 1
#define false 0
void PostTravers(AVLTree cT, int (pF_Visit)(AVLTree fC_T)){
    if(cT->Left) PostTravers(cT->Left,  pF_Visit);
    if(cT->Right)PostTravers(cT->Right, pF_Visit);
    if(cT) pF_Visit(cT);
}
int GetHei(AVLTree cT){
    int rH=0, lH=0;
    if(!cT) return 0;
    if(cT->Left) lH = GetHei(cT->Left );
    if(cT->Right)rH = GetHei(cT->Right);
    int res = cT->Height = rH>lH?rH+1:lH+1;
    return res;
}
AVLTree BST_Insert(AVLTree cT, int cKey){
    AVLTree avl = (AVLTree)malloc(sizeof(struct AVLNode));
    avl->Key = cKey; avl->Height = 0;
    avl->Left = avl->Right = NULL;
    if(cT == NULL) cT = avl;
    AVLTree tAVL = cT;
    while (true) {
        if (cKey < tAVL->Key) {
            if (tAVL->Left != NULL) tAVL = tAVL->Left;
            else { tAVL->Left = avl; break; }
        }else if (cKey > tAVL->Key) {
            if (tAVL->Right != NULL) tAVL = tAVL->Right;
            else {tAVL->Right = avl; break; }
        }else if(cKey == tAVL->Key)  break;
    }
    PostTravers(cT, GetHei);
    return cT;
}
AVLTree R_Rot(AVLTree cAVL){
    AVLTree tAVL = cAVL->Left->Right;
    cAVL->Left->Right = cAVL;
    cAVL = cAVL->Left;
    cAVL->Right->Left = tAVL;
    return cAVL;
}
AVLTree L_Rot(AVLTree cAVL){
    AVLTree tAVL = cAVL->Right->Left;
    cAVL->Right->Left = cAVL;
    cAVL = cAVL->Right;
    cAVL->Left->Right = tAVL;
    return cAVL;    
}
AVLTree R_Balan(AVLTree cAVL){
    int hs = GetHei(cAVL->Left)-GetHei(cAVL->Right);
    int ss = GetHei(cAVL->Right->Left)-GetHei(cAVL->Right->Right);
    if(hs*ss > 0){
        cAVL = L_Rot(cAVL);
    }else{
        if(cAVL->Right->Right){
            AVLTree tAVL = cAVL->Right->Left;
            cAVL->Right->Left=tAVL->Right;
            tAVL->Right= cAVL->Right;
            cAVL->Right= tAVL;
            cAVL = L_Rot(cAVL);
        }else{
            AVLTree tAVL = cAVL->Right;
            cAVL->Right->Left->Right= cAVL->Right;
            cAVL->Right= cAVL->Right->Left;
            tAVL->Right= tAVL->Left= NULL;
            cAVL = L_Rot(cAVL);  
        }
    }
    return cAVL;
}
AVLTree L_Balan(AVLTree cAVL){
    int hs = GetHei(cAVL->Left)-GetHei(cAVL->Right);
    int ss = GetHei(cAVL->Left->Left)-GetHei(cAVL->Left->Right);
    if (hs*ss > 0){
        cAVL = R_Rot(cAVL);
    }else{
        if(cAVL->Left->Left){
            AVLTree tAVL = cAVL->Left->Right;
            cAVL->Left->Right=tAVL->Left;
            tAVL->Left = cAVL->Left;
            cAVL->Left = tAVL;
            cAVL = R_Rot(cAVL);
        }else{
            AVLTree tAVL = cAVL->Left;
            cAVL->Left->Right->Left = cAVL->Left;
            cAVL->Left = cAVL->Left->Right;
            tAVL->Left = tAVL->Right = NULL;  
            cAVL = R_Rot(cAVL);
        }
    }
    return cAVL;
}
AVLTree CheckBalance(AVLTree cT){
    AVLTree wAVL=NULL, wL_AVL=NULL, wR_AVL=NULL;
    if(cT->Left)  wL_AVL = CheckBalance(cT->Left );
    if(cT->Right) wR_AVL = CheckBalance(cT->Right);
    int lH = 0; if(cT->Left) lH = GetHei(cT->Left );
    int rH = 0; if(cT->Right)rH = GetHei(cT->Right);
    if(lH-rH>1 || lH-rH<-1) wAVL = cT;
    if(wL_AVL) return wL_AVL;
    else if(wR_AVL) return wR_AVL;
    else return wAVL;
}
//获取父节点，如果没有父节点，返回NULL
AVLTree GetParent(AVLTree cT, AVLTree cAVL){
    if(cT == cAVL) return NULL;
    AVLTree tAVL = NULL;
    if(cT->Left) 
        if(cT->Left == cAVL) {if(tAVL==NULL) tAVL = cT;}
        else {if(tAVL==NULL) tAVL = GetParent(cT->Left, cAVL);}
    if(cT->Right) 
        if(cT->Right ==cAVL) {if(tAVL==NULL) tAVL = cT;}
        else {if(tAVL==NULL) tAVL = GetParent(cT->Right, cAVL);}
    return tAVL;
}
AVLTree Process(AVLTree cT, AVLTree cAVL){
    AVLTree pareAVL = GetParent(cT, cAVL);
    int lH = 0; if(cAVL->Left ) lH = GetHei(cAVL->Left );
    int rH = 0; if(cAVL->Right) rH = GetHei(cAVL->Right);
    AVLTree tAVL;
    if(lH-rH > 1) tAVL = L_Balan(cAVL);//左边比较多，用左平衡
    if(lH-rH <-1) tAVL = R_Balan(cAVL);//右边比较多，用右平衡
    if(pareAVL){
        if(pareAVL->Left == cAVL) pareAVL->Left = tAVL;
        if(pareAVL->Right== cAVL) pareAVL->Right= tAVL; 
        return cT;
    }else return tAVL;
}
AVLTree Insert(AVLTree T, int key){
    T = BST_Insert(T, key);       //插入
    AVLTree avl = CheckBalance(T);//查错
    if(avl) T = Process(T, avl);  //改正
    return T;
}
