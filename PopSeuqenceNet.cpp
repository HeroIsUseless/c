#include <iomanip>  
#include<unordered_map>  
#include<set>  
#include<queue>  
#include<map>  
#include<vector>  
#include <algorithm>  
#include<stdio.h>  
#include<iostream>  
#include<string>  
#include<memory.h>  
#include<limits.h>  
#include<stack>  
using namespace std;  
  
int main(void)  
{  
    int maxCap, maxSequence, querySum;  
    cin >> maxCap >> maxSequence >> querySum;  
    for (int k = 0; k < querySum; k++)  
    {  
        int idx = 1;  
        stack<int> sta;  
        int maxNum = maxCap;//栈里面能够存在的最大的值  
        vector<int> sequence(maxSequence);  
        for (int i = 0; i < maxSequence; i++)  
            scanf("%d", &sequence[i]);  //输入完毕
        bool result = true;  //设定了一个res
        //看原理是什么，找到原理就行了
        for (int i = 0; i < maxSequence; i++) {//同样，每次只判断一个是非常通俗的方式
            if (sequence[i]>maxNum)  {//不合理  
                result = false;  
                break;  
            }  
            while ((sta.empty() || (!sta.empty() && sta.top() != sequence[i])) 
                && idx <= maxSequence && sta.size() <= maxCap){
                    // 如果栈为空，或者栈不为空但是头部不等于目标值，并且还有值可以压入，
                    // 队列size小于最大容量  
                sta.push(idx++);  //好像是继续压入
            }  
            if (sta.top() != sequence[i]){//如果经过上面的压入操作后，仍不满足要求，则不合理  
                result = false;  
                break;  
            }  
            sta.pop();  
            maxNum++;//弹出了一个，可以压入更大的一个值  
  
        }  
        if (result)  
            cout << "YES" << endl;  
        else  
            cout << "NO" << endl;  
    }  
    return 0;  
}  