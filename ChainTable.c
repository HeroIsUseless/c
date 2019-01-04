#include <stdio.h>
#include <stdlib.h>
#define LEN sizeof(struct St)
struct St{
    int id;

    struct St *pnext;
};
struct St* createSt(int _n);
void       destroySt(struct St *_phead);
struct St* getSt(struct St *_phead,int _n);
void       insertSt(struct St *_phead,int _n);
void       deleteSt(struct St *_phead,int _n);
int        getStLength(struct St *_phead);
void       exchangeSt(struct St *_phead,int m,int n);
int        selectionSortSt(struct St *_phead);
struct St* combineSt(struct St *_pst1,struct St *_pst2);//byID
int        chainToArray(struct St *_phead,int _a[]);
struct St* copySt(struct St *_phead);
void       deleteStM(struct St *_phead,int a,int b);
void       insertStM(struct St *_phead,int a,int n);
void       overChain(struct St *_phead);
int main()
{
    int i,a[100],b;
    struct St *phead1,*phead2,*phead3,*pst;
    phead1=createSt(100);
    phead2=createSt(100);
    for(i=1;i<=100;i++){
        pst=getSt(phead1,i);
        pst->id=i;
        pst=getSt(phead2,i);
        pst->id=2*i+101;
    }

    //insertStM(phead1,50,10);
    deleteStM(phead1,50,60);
    pst=phead1->pnext;
    if(pst==NULL) printf("NULL");
    while(pst!=NULL){
        printf("%d\n",pst->id);
        pst=pst->pnext;
    }
    return 0;
}
/*****************************test********************************/

/******************************************************************/
struct St* createSt(int _n){
    int i;
    struct St *phead,*pst1,*pst2;
    phead=malloc(LEN);
    for(i=1;i<=_n;i++){
        if(i==1){
            pst1=(struct St*)malloc(LEN);
            pst1->pnext=NULL;
        }else{
            pst2=(struct St*)malloc(LEN);
            pst2->pnext=pst1;
            pst1=pst2;
        }
    }
    phead->pnext=pst1;
    return phead;
}
void destroySt(struct St *_phead){
    struct St *pst1,*pst2;
    pst1=_phead;
    while(pst1->pnext!=NULL){
        pst2=pst1->pnext;
        free(pst1);
        pst1=pst2;
    }
    free(pst1);
}
struct St* getSt(struct St *_phead,int _n){
    int i;
    struct St *pst1;
    pst1=_phead;
    for(i=1;i<=_n;i++){
        pst1=pst1->pnext;
    }
    return pst1;
}
void insertSt(struct St *_phead,int _n){
    int i;
    struct St *pst1,*pst2,*pst3;
    pst1=getSt(_phead,_n-1);
    pst2=getSt(_phead,_n);
    pst3=(struct St*)malloc(LEN);
    pst1->pnext=pst3;
    pst3->pnext=pst2;
}
void deleteSt(struct St *_phead,int _n){
    int i;
    struct St *pst1,*pst2;
    pst1=_phead;
    for(i=1;i<=_n-1;i++)
        pst1=pst1->pnext;
    pst2=pst1->pnext;
    pst1->pnext=pst2->pnext;
    free(pst2);
}
struct St* combineSt(struct St *_pst1,struct St *_pst2){
    struct St *pst1,*pst2,*pst3,*phead;
    pst1=_pst1->pnext;
    pst2=_pst2->pnext;
    phead=pst1->id > pst2->id?_pst2:_pst1;
    pst3=phead;


    while(pst1!=NULL && pst2!=NULL){
        if(pst1->id > pst2->id){
            pst3->pnext=pst2;
            pst2=pst2->pnext;
            pst3=pst3->pnext;
        }
        if(pst1->id < pst2->id){
            pst3->pnext=pst1;
            pst1=pst1->pnext;
            pst3=pst3->pnext;
        }
    if(pst1==NULL) pst3->pnext=pst2;
    if(pst2==NULL) pst3->pnext=pst1;
        if(pst1->id== pst2->id){
            //pst3->pnext=pst1;
            //pst1=pst1->pnext;
            //pst3=pst3->pnext;
            //pst3->pnext=pst2;
            //pst2=pst2->pnext;
            //pst3=pst3->pnext;
        }
    }
    return phead;
}
int getStLength(struct St *_phead){
    int i=0;
    struct St *pst=_phead->pnext;
    while(pst!=NULL){
        i++;
        pst=pst->pnext;
    }
    return i;
}
int selectionSortSt(struct St *_phead){
    int i,j,a,k=0,m,n;
    struct St *pst;
    a=getStLength(_phead);
    for(i=0;i<a-1;i++){
        k=i;
        pst=getSt(_phead,k);
        m=pst->id;
        for(j=i+1;j<a;j++){
            pst=getSt(_phead,j);
            n=pst->id;
            if(m>n)
                k=j;
        }
        exchangeSt(_phead,i,k);
    }
    pst=getSt(_phead,a);
    return pst->id;
}
void exchangeSt(struct St *_phead,int m,int n){
    struct St *ptem,*pst1,*pst2,*pst3,*pst4;
    pst1=getSt(_phead,m-1);
    pst2=getSt(_phead,m);
    pst3=getSt(_phead,n-1);
    pst4=getSt(_phead,n);

    pst1->pnext=pst4;
    ptem=pst4->pnext;
    pst4->pnext=pst2->pnext;
    pst3->pnext=pst2;
    pst2->pnext=ptem;
}
int chainToArray(struct St *_phead,int _a[]){
    int i=0;
    struct St *pst;
    pst=_phead->pnext;
    while(pst!=NULL){
        _a[i]=pst->id;
        i++;
        pst=pst->pnext;
    }
    return i;
}
struct St* copySt(struct St *_phead){
    struct St *pst1,*pst2,*pst3,*phead;
    pst1=phead=(struct St*)malloc(LEN);
    pst3=_phead->pnext;
    while(pst3!=NULL){
        pst2=(struct St*)malloc(LEN);
        pst1->pnext=pst2;
        pst1=pst1->pnext;
        *pst1=*pst3;
        pst3=pst3->pnext;
    }
    return phead;
}
void overChain(struct St *_phead){
    struct St *pst1,*pst2,*pst3;
    pst1=_phead->pnext;
    pst2=pst1->pnext;
    pst3=pst2->pnext;
    pst1->pnext=NULL;
    while(pst3!=NULL){
        pst2->pnext=pst1;
        pst1=pst2;
        pst2=pst3;
        pst3=pst3->pnext;
    }
    pst2->pnext=pst1;
    _phead->pnext=pst2;
}
void deleteStM(struct St *_phead,int a,int b){
    struct St *pst1,*pst2;
    pst1=getSt(_phead,a-1);
    pst2=getSt(_phead,b);
    pst1->pnext=pst2->pnext;
}
void insertStM(struct St *_phead,int a,int n){
    int i;
    struct St *pst;
    for(i=0;i<n;i++){
        pst=(struct St*)malloc(LEN);
        insertSt(_phead,a);
    }
}
