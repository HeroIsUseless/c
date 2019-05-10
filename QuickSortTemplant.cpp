#include "iostream"
using namespace std;

template <typename T>
void QuickSort(T a[], int b, int e){
    int i, m=b;
    if (b >= e) return;
    for(int i=e; i>b; i--)
        if(a[b] > a[i]){
            int t=a[b]; a[b]=a[i]; a[i]=t;
            m = i;
        }
    for(int i=b; i<m; i++)
        if(a[m] < a[i]){
            int t=a[m]; a[m]=a[i]; a[i]=t;
            m = i;
        }
    QuickSort(a, b, m-1);
    QuickSort(a, m+1, e);
}

template<>
void QuickSort(char a[], int b, int e){
    int i, m=b;
    if (b >= e) return;
    for(int i=e; i>b; i--)
        if(a[b] > a[i]){
            int t=a[b]; a[b]=a[i]; a[i]=t;
            m = i;
        }
    for(int i=b; i<m; i++)
        if(a[m] < a[i]){
            int t=a[m]; a[m]=a[i]; a[i]=t;
            m = i;
        }
    QuickSort(a, b, m-1);
    QuickSort(a, m+1, e);
}

int main(){
    int a[]= {3,1,4,1,5,9,2,6,5,3,5,4,6,7,8,4};
    QuickSort(a, 0, 15);
    for(int i=0; i<16; i++) cout << a[i] <<" ";
    cout<<endl;
    char b[] = "Hello World!";
    QuickSort(b, 0, 11);
    for(int i=0; i<11; i++) cout << b[i];
    cout<<endl;
    return 0;
}