#include<stdio.h>
#include<stdlib.h>
typedef  int  KeyType;
typedef  struct {                      
  KeyType *elem; /*elem[0]一般作哨兵或缓冲区*/                       
  int Length;      
}SqList;
typedef SqList HeapType; 
void  CreatSqList(HeapType *L);/*待排序列建立，由裁判实现，细节不表*/ 
void HeapAdjust( HeapType  H, int s, int m);
void HeapSort( HeapType  H);
int main()
{
  HeapType L;
  int i;
  CreatSqList(&L);
  HeapSort(L);//仍然是一个列表，不是一棵树
  for(i=1;i<=L.Length;i++)
   {		
     printf("%d ",L.elem[i]);
   }
  return 0;
}
void HeapSort( HeapType  H) { 
  int i; KeyType rc;
  for(i=H.Length/2; i>0; i--) {
      //是所有中间节点调整一遍，因为这个堆排序只能排一个链
      HeapAdjust(H, i, H.Length);
   }
  for(i=H.Length;i>1;i--) {
      rc=H.elem[1];
      H.elem[1]=H.elem[i]; 
      H.elem[i]=rc;
      //因为根会被每一条链遍历到，所以可行
      HeapAdjust(H, 1, i-1); 
   }
 }
void HeapAdjust(HeapType H, int s, int m){
    int node = s;
    int child = node*2;
    while (child <= m) {
        if (child+1<=m && H.elem[child]<H.elem[child+1])
            child += 1;
        if (H.elem[node] > H.elem[child]) 
            return;
        else { 
            int t = H.elem[node];
            H.elem[node] = H.elem[child];
            H.elem[child] = t;
            node = child;
            child = node*2;
        }
    }
}
 