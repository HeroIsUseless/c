#include "iostream"
using namespace std;
void swap(int carr[], int c1, int c2){
    int tmp = carr[c1];
    carr[c1] = carr[c2];
    carr[c2] = tmp;

}
void Print(int carr[], int carrN){
    for(int i=0; i<carrN; i++){
        cout << carr[i] << " ";
    }
}
void Perm(int carr[],int cs, int ce, void (*cfPrint)(int fcarr[], int fcarrN)){
    if(cs > ce) (*cfPrint)(carr, ce);
    else{
        for(int i=cs; i<ce; i++){
            swap(carr, cs, i);
            Perm(carr, cs+1, ce, cfPrint);
            swap(carr, cs, i);
        }
    }
}
void Comb(){

}
int main(){
    int n; cin >> n;
    int arr[100];
    int resArr[100][100];
    int resN = 0;
    for(int i=0; i<n; i++) {
        cin >> arr[i];
    }    
    Perm(arr,n, resArr, resN);





    return 0;
}