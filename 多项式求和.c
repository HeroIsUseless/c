#include <stdio.h>
//多项式求和，输入
int main()
{
    int i;
    int n;//多项式系数
    float x;//自变量x的取值
    float a[40000];
    float b = 1;
    float c = 0;

    scanf("%d %f", &n, &x);
    for(i=0; i<n; i++)
        scanf("%f ", &a[i]);
    scanf("%f", &a[n]);

    for(i=0; i<=n; i++)
    {
        c += b * a[n-i];
        b *= x;
    }

    printf("%.3f\n", c);
    return 0;
}

