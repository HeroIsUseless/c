#include <stdio.h>
//先把两个等长非降序数列求并集，然后求它的中位数
//当i+j=n-1的时候，必有一个是n-1的那个数
//另外一个应该是前面的那个数
//求和除2即可
int a[200000];
int b[100000];
int c[100000];
int n;
int main()
{
    int i, j, a1, a2;
    scanf("%d", &n);
    for(i=0; i<n; i++)
        scanf("%d", &b[i]);
    for(i=0; i<n; i++)
        scanf("%d", &c[i]);
    i=0; j=0;
    while(1)
    {
        if(i+j == n-1)
            break;
        if(b[i]>=c[j])
            j++;
        else
            i++;
    }
    printf("%d\n",(b[i]+c[j])/2);
    return 0;
}

