#include "iostream"
using namespace std;
typedef  int  KeyType;
typedef  struct {                      
  KeyType *elem; /*elem[0]一般作哨兵或缓冲区*/                       
  int Length;      
}SqList;
SqList chek;
int isInsertSortRight = 0;
void MergeSortCheck(SqList L,int low,int high);
void Merge(SqList L, int low, int m, int high);
int InsertSortCheck(SqList L);
int IsCheckRight(SqList L);
//写出Merge函数和Insert函数，单步验证即可
//插入排序很明显是找到小的插在前面
//归并排序就是普通的归并排序
//先验证插入排序，再验证归并排序
//注意的是这里是输出下一步，就是这样
int main(){
    int n; cin >> n;
    int *arr_inse = new int[n];
    int *arr_merg = new int[n];
    int *arr_chec = new int[n];
    for(int i=0; i<n; i++){
        cin >> arr_inse[i];
        arr_merg[i] = arr_inse[i];
    } 
    for(int i=0; i<n; i++){
        cin >> arr_chec[i];
    }
    chek.elem = arr_chec;
    //输入完毕
    //下面进行插入排序的比较
    SqList l_inse;
    l_inse.elem = arr_inse;
    l_inse.Length = n;
    int isInsertRight = 0;
    isInsertRight = InsertSortCheck(l_inse);
    //下面进行归并排序的比较
    SqList l_merg;
    l_merg.elem = arr_merg;
    l_merg.Length = n;
    if(isInsertRight){
        cout << "Insertion Sort" <<endl;
        for(int i=0; i<l_inse.Length-1; i++){
            cout << l_inse.elem[i] <<" ";
        }
        cout << l_inse.elem[l_inse.Length-1];
    }else{//mergeSort同样需要判断
        MergeSortCheck(l_merg, 0, n-1);
        cout << "Merge Sort" <<endl;
        for(int i=0; i<l_inse.Length-1; i++){
            cout << l_inse.elem[i] <<" ";
        }
        cout << l_inse.elem[l_inse.Length-1];
    }
    delete[] arr_inse;
    delete[] arr_merg;
    return 0;
}
//递归做不知道怎么中断啊
//检查对准了，再做一次
void MergeSortCheck(SqList L,int low,int high)  {     
    int res = 0; 
    if(low<high) {      
        int mid=(low+high)/2;        
        MergeSortCheck(L,low,mid);          
        MergeSortCheck(L,mid+1,high);        
        Merge(L,low,mid,high);        
        if(res) return;
        if(IsCheckRight(L)) res = 1;
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
//注意是插在前排，从0开始
//如果进行排的话，为什么0会在最后面呢？它不应该是最先排的吗？
//明白了，插入排序是，恩，对已经排好序的序列进行移动的
//如果说是，没有重复元素的话，那么就可以对其用set就足够了
//即便这样，排序算法也不是很难的
//实现用二分法排序好了
//首先，从1开始拿一个，那么排好序的空间就是0-i个
//二分法找到0-i-1序列中的位置，取小值就是都会移动了
//将这个找到的值到i-1的内容向后移动
//插入判断即可
int InsertSortCheck(SqList L){
    int res = 0;
    for(int i=1; i<L.Length; i++){
        int t = L.elem[i], tPos = i;
        int low = 0, high = i-1;
        //二分法查找位置
        //那么返回的是，比它稍微大一点的那个
        //如果没有比它大的，那么返回该元素，不影响的
        //如果没有比它小的，正常返回即可
        int notFind=-1;
        while(low<=high) {
            int mid=(high+low)/2;
            if(L.elem[mid] > t) {
                if(low == mid){
                    tPos = low;
                    break;
                }    
                high=mid-1;
            }else if(L.elem[mid] < t) {
                if(high == low){
                    tPos = low+1;
                    break;
                }
                low=mid+1;
            }
            else {//容错判断：有没有相同的元素
                tPos = mid;
                break;
            }
        }
        //二分法判断完毕
        //进行移位，是往上移位
        for(int k=i; k>tPos; k--){
            L.elem[k] = L.elem[k-1];
        }
        L.elem[tPos] = t;
        //现在就是一个排好的数组了
        if(IsCheckRight(L)) res = 1;
        //现在的话只是输出下一步，所以要尽快截至
        if(res) return res;
    }
    return res;
}

int IsCheckRight(SqList L){
    int res = 1;
    for(int i=0; i<L.Length; i++){
        if(L.elem[i] != chek.elem[i]){
            res = 0;
        }
    }
    return res;
}