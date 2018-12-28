#include<stdio.h>
#include<stdlib.h>
typedef  int  KeyType;
typedef  struct {                      
  KeyType *elem; //作为哨兵意味着不使用这个0                
  int Length;      
}SqList;
void  CreatSqList(SqList *L);/*待排序列建立，由裁判实现，细节不表*/ 
void bubble_sort(SqList L);
int main()
{
  SqList L;
  int i;
  CreatSqList(&L);//就把它放进去了
  bubble_sort( L);
  for(i=1;i<=L.Length;i++)
   {		
     printf("%d ",L.elem[i]);  
   }
  return 0;
}
/*你的代码将被嵌在这里 */
//待测序列长度为1~1000
//由小到大输出
void bubble_sort(SqList L){
    for(int i=L.Length; i>0; i--){
        for(int j=1; j<i; j++){
            if(L.elem[j] > L.elem[j+1]){
                int t = L.elem[j];
                L.elem[j] = L.elem[j+1];
                L.elem[j+1] = t;
            }
        }
    }
}