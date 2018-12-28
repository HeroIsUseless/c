#include<stdio.h>
#include<stdlib.h>
typedef  int  KeyType;
typedef  struct {                      
  KeyType *elem; /*elem[0]一般作哨兵或缓冲区*/                       
  int Length;      
}SqList;
void  CreatSqList(SqList *L);/*待排序列建立，由裁判实现，细节不表*/ 
int Partition ( SqList  L,int low,  int  high );
void Qsort ( SqList  L,int low,  int  high );
int main()
{
  SqList L;
  int i;
  CreatSqList(&L);
  Qsort(L,1,L.Length);
  for(i=1;i<=L.Length;i++)
   {		
     printf("%d ",L.elem[i]);
   }
  return 0;
}
void Qsort ( SqList  L,int low,  int  high ) //这里实现了
//中间的部分
{  int  pivotloc;//也不知道这个是啥意思
//这个叫基准记录
   if(low<high)//还没到中间
    {  
        //这个是毛的函数。。。
	pivotloc = Partition(L, low, high ) ;
    //快排左边的
        Qsort (L, low, pivotloc-1) ; 
        //快排右边的。。。我知道是递归，但是
        //怎样的一个过程呢？
        Qsort (L, pivotloc+1, high );
     }
}
/*你的代码将被嵌在这里 */
//插入排序具有最好的平均性能
//用递归方法实现最为简单
int Partition(SqList L, int low, int high){
    int a=low, b=high;
    int base = L.elem[low];
    while(a < b){
        while(L.elem[b]>=base && a<b) 
            b--;
        if(a < b) 
            L.elem[a] = L.elem[b];
        while(L.elem[a]<=base && a<b) 
            a++;
        if(a < b) 
            L.elem[b] = L.elem[a];
    }
        L.elem[a] = base;
        return a;
}
