#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 1000000
typedef int ElemType;
typedef struct Triple{
    int x,y;
    ElemType e;
} Triple;
typedef struct SMatrix {
    Triple data[MAXSIZE];
    int xn, yn, coun;
    int rpos[MAXSIZE];
} SMatrix;
void ProcSMatrix(SMatrix *cm){
    int i;
    int num[MAXSIZE] = {0};
    for(i=1; i<cm->coun; i++) num[cm->data[i].y]++;
    cm->rpos[1] = 1;
    for(i=2; i<=cm->coun; i++)  cm->rpos[i] = cm->rpos[i-1];
}
void FastTrasposeSMatrix(SMatrix cm, SMatrix cn, SMatrix *cpq){
    int cmLin, cmLinNod, cmEd, cnLin, cnLinNod, cnEd, cpqLinNod, cpqRow;
    int tmpLin[MAXSIZE];
    if(cm->yn!=cn->xn || cm->coun*cn->coun==0) return;
    ProcSMatrix(cm);ProcSMatrix(cn);
    cpq->coun=0; cpq->xn=cm->xn; cpq->yn=cn->yn;
    for(cmLin=1; cmLin<=cm->xn; cmLin++){
        memset(tmpLin, 0, sizeof(tmpLin));
        if(cmLin < cm->xn) cmEd = cm->rpos[cmLin+1]; else cmEd = cm->coun+1;
        for(cmLinNod=cm->rpos[cmLin]; cmLinNod<cmEd; cmLinNod++){
            cnLin = cm->data[cmLinNod].y;
            if(cnLin < cn->xn) cnEd = cn->rpos[cnLin+1]; else cnEd = cn->coun+1;
            for(cnLinNod=cn->rpos[cnLin]; cnLinNod<cnEd; cnLinNod++){
                cpqRow = cn->data[cnLinNod].y;
                tmpLin[cpqRow] += cm->data[cmLinNod].e * cn->data[cnLinNod].e;
            }//for cnLinNod
        }//for cmLinNod
        for(cpqLinNod=1; cpqLinNod<=cpqRow; cpqLinNod++){
            if(tmpLin[cpqLinNod] != 0){
                cpq->coun++;
                cpq->data[cpq->coun].e = tmpLin[cpqLinNod]. e;
                cpq->data[cpq->coun].x = tmpLin[cpqLinNod]. x;
                cpq->data[cpq->coun].y = tmpLin[cpqLinNod]. y;
            }
        }
    }// for cmLin

}
int main()
{
    int a, b;
    scanf("%s%s%s",ps,cs,xs);
    b = GetResult(ps, xs);
    printf("%d %d\n",a,b);
    return 0;
}



