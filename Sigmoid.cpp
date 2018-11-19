#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <math.h>
using namespace std;
typedef struct Matrix {
    double data[100][100];
    int xn, yn;
} Matrix;
void TranMatrix(Matrix cm, Matrix *cpm){
    cpm->xn = cm.yn; cpm->yn = cm.xn;
    for(int i=1; i<=cm.xn; i++)
        for(int j=1; j<=cm.yn; j++)
            cpm->data[j][i] = cm.data[i][j];
}
void MultMatrix(Matrix cm1, Matrix cm2, Matrix *cpm){
    cpm->xn=cm1.xn; cpm->yn=cm2.yn;
    memset(cpm->data, 0, sizeof(cpm->data));
    for(int i=1; i<=cpm->xn; i++){
        for(int j=1; j<=cpm->yn; j++){
            for(int k=1; k<=cm1.yn; k++){
                cpm->data[i][j] += cm1.data[i][k]*cm2.data[k][j];
            }
        }
    }
}
void InputMatrix(Matrix *cpm, int cxn, int cyn){
    cpm->xn=cxn; cpm->yn=cyn;
    for(int i=1; i<=cxn; i++)
        for(int j=1; j<=cyn; j++)
            scanf("%lf", &cpm->data[i][j]);
}
void OutPutMatrix(Matrix cm){
    for(int i=1; i<=cm.xn; i++){
        for(int j=1; j<=cm.yn; j++){
            printf("%.2lf ", cm.data[i][j]);
        }
        printf("\n");
    }
}
void Sigmoid(Matrix cm, Matrix *pcms){
    pcms->xn = cm.xn; pcms->yn = cm.yn;
    for(int i=1; i<=cm.xn; i++)
        for(int j=1; j<=cm.yn; j++)
            pcms->data[i][j] = 1/(1+exp(-cm.data[i][j]));
}
void G(Matrix cm, Matrix *cpmg){
    double t;
    cpmg->xn=cm.xn; cpmg->yn=cm.yn;
    for(int i=1; i<=cm.xn; i++){
        for(int j=1; j<=cm.yn; j++){
            t = exp(cm.data[i][j]);
            cpmg->data[i][j] = t/pow(t+1, 2);
        }
    }
}
int main(){
    int m,n,p;
    scanf("%d%d%d", &m, &n, &p);
    Matrix ma, *pma=&ma, mag, *pmag=&mag; InputMatrix(pma, m, n);
    Matrix mb, *pmb=&mb, mbg, *pmbg=&mbg; InputMatrix(pmb, n, p);
    Matrix mc, *pmc=&mc, mcg, *pmcg=&mcg, mcs, *pmcs=&mcs;
    MultMatrix(ma, mb, pmc);
    Sigmoid(mc, pmcs); OutPutMatrix(mcs); printf("\n");
    G(mc, pmcg); OutPutMatrix(mcg); printf("\n");
    Matrix mat, *pmat=&mat, mbt, *pmbt=&mbt;
    TranMatrix(mb, pmbt); MultMatrix(mcg,mbt, pmag);OutPutMatrix(mag); printf("\n");
    TranMatrix(ma, pmat);MultMatrix(mat,mcg, pmbg); OutPutMatrix(mbg); printf("\n");

    return 0;
}




















