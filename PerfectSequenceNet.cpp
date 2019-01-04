#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
	int n,p; cin >> n >> p;
	vector<int> v;
	for(int i=0;i<n;i++){
        int t; cin >> t;
        v.push_back(t);
    }//输入完毕
    //下面找出最大子序列
	sort(v.begin(), v.end());//先从头到尾进行排序
	int cont=0;//设一个0计数，还好
	for(int i=n-1;i>=0;i--) {//这个是倒着来
        for(int j=0; j<i; j++){//这个是正着来
            if(p*v[j] > v[i]){//这个是一个简单的比较
                if(cont < i-j+1){ //这个又是一个简单的比较
                    cont = i-j+1;//完成了哈哈
                }
            }
        }
    }
	cout << cont;
	return 0;
}
