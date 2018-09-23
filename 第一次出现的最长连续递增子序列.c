#include <stdio.h>
//输出第一次出现的最长连续递增子序列
int a[200000]={0};
int main()
{
    int i, j;
    int n = 0;
    int p = 0;
    int m = 1;
    int t;
    scanf("%d", &n);
    for(i=0; i<n-1; i++)
    {
        scanf("%d ", &a[i]);
    }
    scanf("%d", &a[n-1]);

    for(i=0; i<n; i++)
    {
      t = 1;
        for(j=i; j<n; j++)
        {
            if(j == n-1) break;
            if(a[j] < a[j+1])
            {
                t++;
                if(m < t)
                {
                    m = t;
                    p = i;
                }
            }
            else
                break;
        }
    }

        for(i=0; i<m-1; i++)
            printf("%d ", a[p+i]);
        printf("%d", a[p+m-1]);

    return 0;
}

