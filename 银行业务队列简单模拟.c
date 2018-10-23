//银行队列简单模拟，每输出两个A，输出一个B
#include <stdio.h>
#define MAXLENGTH 1000
int main()
{
    int n;
    int i, j, k;
    int isFirst;
    int A[MAXLENGTH]={0},NA=0, B[MAXLENGTH]={0},NB=0;
    scanf("%d", &n);
    for(i=0; i<n; i++)
    {
        scanf("%d", &k);
        if(k%2) A[NA++] = k; else B[NB++] = k;
    }
    i=0; j=0; isFirst = 1;
    while(!(i==NA && j==NB))
    {
        if(i<=NA-1) if(isFirst){printf("%d", A[i]); isFirst=0; i++;} else {printf(" %d", A[i]); i++;}
        if(i<=NA-1) if(isFirst){printf("%d", A[i]); isFirst=0; i++;} else {printf(" %d", A[i]); i++;}
        if(j<=NB-1) if(isFirst){printf("%d", B[j]); isFirst=0; j++;} else {printf(" %d", B[j]); j++;}
    }
    return 0;
}



