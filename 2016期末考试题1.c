#include <stdio.h>
#include <stdlib.h>
#define LEN sizeof(struct Q)
struct P{
    int a;
    struct P *pnext;
};
struct Q{
    int a;
    int b;
    struct Q *pnext;
};
struct Q *SUM(struct P*lp1,struct P*lp2){
    struct Q *phead,*p1,*p2;
    int n=0;
    p1=p2=(struct Q*)malloc(LEN);
    phead=NULL;
    while(lp1!=NULL){
        while(lp2!=NULL){
            if(lp1->a+lp2->a==15){
                n++;
                p1->a=lp1;
                p1->b=lp2;
                if(n==1) phead=p1;
                else {p2->pnext=p1;p2=p2->pnext;}
                p1=(struct Q*)malloc(LEN);
            }
            lp2=lp2->pnext;
        }
        lp1=lp1->pnext;
    }
    p2->pnext=NULL;
    return phead;
}
int main()
{

    return 0;
}
