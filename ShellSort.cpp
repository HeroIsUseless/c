#include<stdio.h>
#include<stdlib.h>
typedef  int  KeyType;
typedef  struct {                      
  KeyType *elem; /*elem[0]一般作哨兵或缓冲区*/                       
  int Length;      
}SqList;
void  CreatSqList(SqList *L);/*待排序列建立，由裁判实现，细节不表*/ 
void  ShellInsert(SqList L,int dk);
void  ShellSort(SqList L);

int main()
{
  SqList L;
  int i;
  int arr[] = {0,5,2,4,1,8,9,10,12,3,6};
  L.elem = arr;
  L.Length = 10;
  ShellSort(L);
  for(i=1;i<=L.Length;i++)
   {		
     printf("%d ",L.elem[i]);
   }
  return 0;
}
void   ShellSort(SqList L)
{
  /*按增量序列dlta[0…t-1]对顺序表L作Shell排序,假设规定增量序列为5,3,1*/
   int k;
   //称为增量序列
   int dlta[3]={5,3,1};
   int t=3;
   for(k=0;k<t;++k)
   //进行了3次希尔排序，称作increment
       ShellInsert(L,dlta[k]);
} 
/*你的代码将被嵌在这里 */
//s是一种说不清道不明的排序了
//比直接插入多了一个increment而已
void ShellInsert(SqList L, int dk){
    int a;
    for(int i=1+dk; i<=L.Length; i+=dk){//对于每个拿出来的元素
        a = L.elem[i];
        int j;
        for(j=1; j<=i-1; j+=dk){//在已经排好序的元素中检查
            if(L.elem[j] >= L.elem[i]){//应该插到j之前
                break;
            }
        }
        for(int k=i; k>j; k-=dk){//大数向后移动
            L.elem[k] = L.elem[k-dk];
        }
        L.elem[j] = a;//插入数据
    }
}
