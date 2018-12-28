#include<stdio.h>
#include<stdlib.h>
typedef  int  KeyType;
typedef  struct {                      
  KeyType *elem; /*elem[0]一般作哨兵或缓冲区*/                       
  int Length;      
}SqList;
void  CreatSqList(SqList *L);/*待排序列建立，由裁判实现，细节不表*/ 
void  InsertSort(SqList L);
int main()
{
  SqList L;
  int i;
  int arr[] = {0,5,2,4,1,8,9,10,12,3,6};
  L.elem = arr;
  L.Length = 10;
  InsertSort(L);
  for(i=1;i<=L.Length;i++)
   {		
      printf("%d ",L.elem[i]);
    }
  return 0;
}
/*你的代码将被嵌在这里 */
//直接插入排序的问题是需要将比较大的元素向后移动
void InsertSort(SqList L){
    int a;
    for(int i=2; i<=L.Length; i++){//对于每个拿出来的元素
        a = L.elem[i];
        int j;
        for(j=1; j<=i-1; j++){//在已经排好序的元素中检查
            if(L.elem[j] >= L.elem[i]){//应该插到j之前
                break;
            }
        }
        for(int k=i; k>j; k--){//大数向后移动
            L.elem[k] = L.elem[k-1];
        }
        L.elem[j] = a;//插入数据
    }
}