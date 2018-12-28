#include<stdio.h>
#include<stdlib.h>
typedef  int  KeyType;
typedef  struct {                      
  KeyType *elem; /*elem[0]一般作哨兵或缓冲区*/                       
  int Length;      
}SqList;
void  CreatSqList(SqList *L);/*待排序列建立，由裁判实现，细节不表*/ 
void  MergeSort(SqList L,int low,int high);
void Merge(SqList L,int low,int m,int high); 
int main()
{
  SqList L;
  int i;
  CreatSqList(&L);
  MergeSort(L,1,L.Length);
  for(i=1;i<=L.Length;i++)
   {		
      printf("%d ",L.elem[i]);
   }
  return 0;
}
void MergeSort(SqList L,int low,int high)  {      
    if(low<high) {      
        int mid=(low+high)/2;        
        MergeSort(L,low,mid);          
        MergeSort(L,mid+1,high);        
        Merge(L,low,mid,high);        
    }  
}
void Merge(SqList L, int low, int m, int high){
    int n = high - low + 1;
    int *arr = (int*)malloc(sizeof(int)*n+10);
    int k = 0;
    int i=low, j=m+1;
    while(i<=m && j<=high){
        if(L.elem[i] > L.elem[j]){
            arr[k++] = L.elem[j++]; 
        }else{
            arr[k++] = L.elem[i++];
        }
    }
    while(i <= m) arr[k++] = L.elem[i++];
    while(j <= high) arr[k++] = L.elem[j++];
    for(int a=low; a<=high; a++){
        L.elem[a] = arr[a-low];//那么从0开始了
    }
}
void Merge(SqList L, int low, int m, int high){
    //分配空间而已
     int n1 = q - p + 1;
     int n2 = r - q;
     int *L;
     L = (int*)malloc(sizeof(int)*n1);
     int *R;
     R = (int*)malloc(sizeof(int)*n2);//开辟出这个来了
    //转移阵地而已
     int i = 0;//就不能复制两遍吗？
     int j = 0;
 
     for(i; i < n1; i++)
         L[i] = array[i + p];
     for(j; j < n2; j++)
         R[j] = array[j + q  +1];
 
     i = j = 0;
 
     int k = p;
    //进行比较
     while(i!=n1 && j!= n2) {
         if(L[i] <= R[j])
             array[k++] = L[i++];
         else
             array[k++] = R[j++];
     }
     while(i < n1)
         array[k++] = L[i++];
     while(j < n2)
         array[k++] = R[j++];
     free(L);
     free(R);
