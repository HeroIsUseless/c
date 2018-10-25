#include <stdio.h>
//判断栈能否从大到小排列，这个数不是相等就肯定比这个数大，就往前找OK
int main()
{
    int i,n,M,N,K;
    int A[1000]={0},NA=0,B[1000]={0},NB=0;
    scanf("%d%d%d", &M, &N, &K);
    while(K--)
    {
        for(i=1; i<=N; i++)
            scanf("%d",&A[i]);
        n=1;
        B[0]=1001; NB=0;
        for(i=1; i<=N; i++)//只要能正常循环完，就证明能经过压入弹出输入从小到达排列的数字
        {
            if()
        }
        printf("YES\n");
        Error:;
    }
    return 0;
}
