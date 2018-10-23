#include <stdio.h>
//判断栈能否从大到小排列，这个应该是比较正确的
int main()
{
    int i,j,a,M,N,K;
    int A[1000]={0},NA=0,
        B[1000]={0},NB=0,
        Nid=1;
    scanf("%d%d%d", &M, &N, &K);
    while(K--)
    {
        for(i=1; i<=N; i++) {scanf("%d", &a); A[i] = a;}
        NA = N; B[0] = 1001; NB = 0; Nid = 1;
        while(NA!=0)                    //只要A能清空就行
        {
            if(A[NA]<B[NB])             //当A[NA]<B[NB]，直接压入
                if(NB >= N)             //栈满直接错误退出
                    {printf("NO\n"); goto Error;}
                else                    //插入
                    B[++NB] = A[NA--];
            else                        //当A[NA]>B[NB]，弹出判断，再压入A
            {
                while(A[NA] > B[NB])    //弹出所有小于A[NA]的值
                {
                    if(B[NB] != Nid)    //如果没有按顺序弹出，错误退出
                        {printf("NO\n"); goto Error;}
                    else
                        {NB--; Nid++;}
                }
                B[++NB] = A[NA--];
            }
        }
        printf("YES\n");
        Error:;
    }
    return 0;
}
