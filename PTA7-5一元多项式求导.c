#include <stdio.h>
//用最后一个0代表输入的完成，
//这组数据不被输出
//但如果只有这组数据则输出
//极端情况：只有一个元素
int main()
{
    int xi, zhi, a=1;//代表第一次输入
    while(scanf("%d%d", &xi, &zhi) != EOF)
    {
        if(xi*zhi != 0)
            if(a)
            {
                printf("%d %d", xi*zhi, zhi-1);
                a=0;
            }
            else
                printf(" %d %d", xi*zhi, zhi-1);
        else
            break;
    }
    if(a) printf("0 0");
    return 0;
}
