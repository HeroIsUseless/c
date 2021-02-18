#include <iostream>
using namespace std;

int n, // n个群众
    k, // k个坐标在方框里就不行了
    t, // t个坐标
    xl, yd, // 左下角坐标
    xr, yu; // 右上角坐标

bool isInArea(int x, int y)
{
    if ((x >= xl && x <= xr) && (y >= yd && y <= yu))
        return true;
    else
        return false;
}

int main(){
    cin >> n >> k >> t >> xl >> yd >> xr >> yu;
    // 接收数据
    int *arr = new int[n * 2 * t];
    for (int i = 0; i < n; i++){
        for (int j = 0; j < t; j++){
            int x, y;
            cin >> x >> y;
            arr[i * (t * 2) + j * 2] = x;
            arr[i * (t * 2) + j * 2 + 1] = y;
        }
    }
    // 进行验算
    int res1 = 0; // 经过高危区域的人数
    int res2 = 0; // 曾在高危区域逗留的人数
    for(int i=0; i<n; i++){
        //cout << i << endl;
        int count = 0;
        bool flag = false; // 用于记录经过高危区域的人数变量的改动情况
        for (int j = 0; j < t; j++){
            int x = arr[i * (t * 2) + j * 2];
            int y = arr[i * (t * 2) + j * 2 + 1];
            if(isInArea(x, y)){
                count++;
                //cout << "Y-";
            }
            else{
                count = 0;
                //cout << "N-";
            }
            // cout << "[" << arr[i * (t * 2) + j * 2]
            //      << "," << arr[i * (t * 2) + j * 2 + 1]
            //      << "]" << endl;
            if(count > 0 && flag == false){
                res1++;
                flag = true;
            }
            if(count >= k){
                res2++;
                //cout << "yes in" << endl;
                break;
            }
        }
    }
    cout << res1 << endl;
    cout << res2 << endl;
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < t; j++)
    //     {
    //         cout << "[" << arr[i * (t * 2) + j * 2] 
    //              << "," << arr[i * (t * 2) + j * 2 + 1] 
    //              << "]" << endl;
    //     }
    // }
    return 0;
}
