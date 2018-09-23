#include <stdio.h>
#define BYEAR 1949
#define EYEAR 2000
//列出从BYEAR到EYEAR日期的日历
//格式：一个月一个段，共四列三行为一年，再隔一行是下一年，花里胡哨的东西有很多，先把过程实现了再说其他的
int lmonth[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
void printDate();
int month[4][35] = {{0}};//一共从1-4个月
int main()
{
    FILE *pFile = fopen("date.txt","w");
    //判断是闰年还是平年
    for(int y=BYEAR; y<=EYEAR; y++)//有多少年
    {
        isRunNian(y);
        for(int m=0; m<3; m++)//三大列
        {
            printDate();//输出汉字
            getData(y,m);//把三个数组填满
            printDay();//输出，置0
        }
    }
    fclose(pFile);
    return 0;
}
void printDate()
{
    for(int a=1; a<=4; a++)
    {
        for(int b=0; b<=6; b++)
        {
            switch(b)
            {
                case 0:
                    fprintf(pFile, "日 ");
                    break;
                case 1:
                    fprintf(pFile, "一 ");
                    break;
                case 2:
                    fprintf(pFile, "二 ");
                    break;
                case 3:
                    fprintf(pFile, "三 ");
                    break;
                case 4:
                    fprintf(pFile, "四 ");
                    break;
                case 5:
                    fprintf(pFile, "五 ");
                    break;
                case 6:
                    fprintf(pFile, "六   ");
                    break;
            }
        }
    }
    fprintf(pFile,"\n");
}
void getData(int y, int m)//m是从0开始的
{
    int mo = 0;
    int theFirstDay = 0;//代表的是1号是数组里的第几位
    for(int i=0; i<4; i++)
    {
        mo = m*4+i+1;
        theFirstDay = getTED(y,mo)
        for(int j=0; j<lmonth[mo-1]; j++)
        {//我艹还要有一层循环
            month[i][theFirstDay+j]=j+1;//哎呀我的个天
        }//我感觉差不多了
    }
}
void printDay()
{
   for(int i=0; i<5; i++)
   {
       for(int j=0; j<4; j++)
       {

       }
   }
}
void isRunNian(int y)
{
     if((y%100!=0 && y%4==0) || (y%400==0))
    {
        lmonth[1] = 29;//二月就是序号12
    }
    else
    {
        lmonth[1] = 28;
    }
}
