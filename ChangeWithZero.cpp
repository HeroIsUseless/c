#include "iostream"
using namespace std;
//first input nums;
//return the count of how many swap
int HowManySort(int carr[], int cn);
//思路是什么呢？明白了，就是根据当前的位置，遍历出那个数据
//然后进行交换，同时进行计数，直到check没事即可
void Swap(int &ca, int &cb){
    int t = ca; ca = cb; cb = t;
}
bool Check(int carr[], int cn){
    bool res = true;
    for(int i=0; i<cn; i++){
        if(i != carr[i])
            res = false;
    }    
    return res;
}
int main(){
    int n; cin >> n;
    int arr[1000];
    for(int i=0; i<n; i++){
        cin >> arr[i];
    }
    int res = HowManySort(arr, n);
    cout << res;
    return 0;
}
int HowManySort(int carr[], int cn){
    int cont = 0;
    int pos_0;
    for(int i=0; i<cn; i++){//找到0所在的初始位置
        if(carr[i] == 0)
            pos_0 = i;
    }
    //对啊，如果归零了，然后怎么办？第一个就出现这种问题。。。
    //还真有这种可能。。。
    while(carr[0] != 0){
    int i;
    for(i=0; i<cn; i++){
        if(carr[i] == pos_0)
            break;  
    }//找到pos_0相对应的那个数
    Swap(carr[i], carr[pos_0]);
    pos_0 = i;//进行切换，0移动到了i所在位置
    cont++;
    }        
    return cont;
}