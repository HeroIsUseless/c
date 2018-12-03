#include <iostream>
using namespace std;
typedef int TElemType;
typedef enum PionterTag{Link, Thread}PointerTag;
typedef struct BiThrNode{
    TElemType data;
    struct BiThrNode *lchild, *rChild;
    PointerTag LTag, RTag;
}BiThrNode;
void InOrderTraverse_Thr(BiThrNode* T, void(*visit)(TElemType e)){
    BiThrNode *p = T->lchild;
    while(p != T){
        while(p->LTag==Link){
            p = p->lchild;//进入第一个节点，把左节点循环完毕
            visit(p->data);
        } 
        while(p->RTag==Thread && p->rChild!=T){//一般是它的根节点，是while，把线索循环完毕
            p = p->rChild;
            visit(p->data);
        }
        p = p->rChild;//因为右节点不是孩子就是线索，不存在空指针了，不论是孩子还是线索，都要这么做
    }
}
void InOrderThreading(BiThrNode *Thrt, BiThrNode *T){
    BiThrNode* pre;
    Thrt = (BiThrNode*)malloc(sizeof(BiThrNode));
    Thrt->LTag = Link; Thrt->RTag = Thread;
    Thrt->rChild = Thrt; //右指针回指
    if(!T) Thrt->lchild = Thrt;
    else{
        Thrt->lchild = T; pre = Thrt;
        InTreading(T);
        pre->rChild = Thrt; pre->RTag = Thread;
        Thrt->rChild = pre;
    }
}
void InTreading(BitThrNode *p){//这时一个递归函数
    if(p){
        InThreading(p->lchild);//左子树线索化
        if(!p->lchild){//前驱线索
            p->LTag = Thread;
            p->lchild = pre;
        }
        if(!pre->rChild){//后继线索
            pre->RTag = Thread;
            pre->rChild = p;
        }
        pre = p;
        InThreading(p->rchild);
    }
    
    if(p){
        InTreading(p->lchild);
        if(!p->lchild){
            p->LTag = Thread;
            p->lchild = pre;
        }
        if(!p->rchild){
            pre->RTag = Thread;
            pre->rchild = pre;
        }
        pre = p;
        InThreading(p->rChild);
    }
}
int main(){
    cout << "Hello World!";
    return 0;
}