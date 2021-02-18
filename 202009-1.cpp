#include <iostream>
#include <math.h>
using namespace std;

int main(){
    int n, X, Y;
    cin >> n >> X >> Y;
    int *arr = new int[n * 2];
    for (int i = 0; i < n; i++){
        int x, y;
        cin >> x >> y;
        arr[i * 2] = x;
        arr[i * 2 + 1] = y;
    }
    int *res = new int[n];
    for (int i = 0; i < n; i++){
        res[i] = (int)(pow(abs(arr[i * 2] - X), 2) + pow(abs(arr[i * 2 + 1] - Y),2));
        //cout << "res:" << res[i] << endl;
    }
    // 然后排序打印出前三个 // 主意如果这里只有前1个或者前两个就会出现问题
    // 注意是读题错了
    int max1 = 0x7fffffff, max1_i=0;
    for (int i = 0; i < n; i++){
        if(res[i] < max1){
            max1 = res[i];
            max1_i = i;
        }
    }
    cout << max1_i + 1 << endl;
    int max2 = 0x7fffffff, max2_i = 0;
    for (int i = 0; i < n; i++)
    {
        if ((res[i] < max2) && (i != max1_i))
        {
            max2 = res[i];
            max2_i = i;
        }
    }
    cout << max2_i + 1 << endl;
    int max3 = 0x7fffffff, max3_i = 0;
    for (int i = 0; i < n; i++)
    {
        if (res[i] < max3 && (i != max1_i) && (i != max2_i))
        {
            max3 = res[i];
            max3_i = i;
        }
    }
    cout << max3_i + 1 << endl;
    delete[] arr;
    delete[] res;
    return 0;
}