#include <stdio.h>
//数组元素循环右移问题
int main()
{
    int i;
    int n, m;
    int a[2000];
    scanf("%d %d", &n, &m);
    for(i=0; i<n-1; i++)
        scanf("%d ", &a[i]);
    scanf("%d", &a[n-1]);

    while(m >= n)
        m -= n;
    for(i=n-m; i<n; i++)
        printf("%d ", a[i]);
    for(i=0; i<n-m-1; i++)
        printf("%d ", a[i]);
    printf("%d", a[n-m-1]);
    return 0;
}
