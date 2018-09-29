#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define LEN 40
//有50*50点阵，然后随机输入初始状态，然后进行运算，然后打印出来
int a[LEN][LEN] = {0};

int main()
{
    int i, j, k;
    srand(time(NULL));
    for(i=0; i<LEN; i++)
        for(j=0; j<LEN; j++)
            a[i][j] = rand()%2;

    i=1;
    while(i>0)
    {
        Sleep(1000);
        system("cls");
        for(i=0; i<LEN; i++)
        {
            for(j=0; j<LEN; j++)
            {
                k = 0;
                if(i-1>=0 && j-1>=0)
                    if(a[i-1][j-1] == 1)
                        k++;
                if(i-1>=0 && j>=0)
                    if(a[i-1][j] == 1)
                        k++;
                if(i-1>=0 && j+1>=0)
                    if(a[i-1][j+1] == 1)
                        k++;
                if(i>=0 && j-1>=0)
                    if(a[i][j-1] == 1)
                        k++;
                if(i>=0 && j+1>=0)
                    if(a[i][j+1] == 1)
                        k++;
                if(i+1>=0 && j-1>=0)
                    if(a[i+1][j-1] == 1)
                        k++;
                if(i+1>=0 && j>=0)
                    if(a[i+1][j] == 1)
                        k++;
                if(i+1>=0 && j+1>=0)
                    if(a[i-1][j-1] == 1)
                        k++;
                if(k == 3)
                    a[i][j] = 1;
                else if(k == 2)
                    a[i][j] = a[i][j];
                else
                    a[i][j] = 0;
            }
        }

        for(i=0; i<LEN; i++)
            for(j=0; j<LEN; j++)
            {
                if(a[i][j])
                    printf("%c ", 1);
                else
                    printf("  ");
                if(j == LEN-1)
                    printf("\n");
            }
    }

    return 0;
}
