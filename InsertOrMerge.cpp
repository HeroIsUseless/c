#include <cstdio>
#include "iostream"
#include <algorithm>
#include <vector>
using namespace std;
void merge_sort(vector<int> &ctv, vector<int> &cmv, int step){
    for(int i=0; cmv.size()-i>=step*2; i+=2*step){
        int s0 = i;
        int s1 = i, e1 = i+step-1;
	 	int s2 = i+step, e2 = i+2*step-1;
	 	while(s1 <= e1 && s2 <= e2) {
	 		if (cmv[s1] <= cmv[s2]) {
	 			ctv[s0++] = cmv[s1++];
	 		} else {
	 			ctv[s0++] = cmv[s2++];
	 		}
	 	}
	 	while(s1 <= e1) {
	 		ctv[s0++] = cmv[s1++];
	 	}
	 	while(s2 <= e2){
	 		ctv[s0++] = cmv[s2++];
		}
    }
}
void print(vector<int> &cv){
    for(int i=0; i<cv.size(); i++){
        if(i==0) cout << cv[i];
        else cout <<" "<< cv[i];
    }
}
void MergeSortCheck(vector<int> &cmv, vector<int> &crv){
    bool flag = false;
    int step = 1;
    std::vector<int> tv = cmv;
    while(step < cmv.size()){
        if(cmv == crv){
            cout << "Merge Sort" <<endl;
            flag = true;
        }
        merge_sort(tv, cmv, step);
        step *=2;
        cmv = tv;
        if(flag){
            print(cmv);
            return;
        }
    }
} 
bool InsertSortCheck(vector<int> &civ, vector<int> &crv){
    for(int i=1; i<civ.size(); i++){
        //找到并插入完毕，先判断
        if(civ == crv){
            cout << "Insertion Sort" <<endl;
            
        }
        int a, j; a = civ[i];
        for(j=0; j<i; j++){
            if(civ[j]>civ[i]){
                break;
            }
        }
        for(int k=i; k>j; k--){
            civ[k] = civ[k-1];
        }
        civ[j] = a;
        if(flag){
            print(civ);
            return true;
        }
    }
    return false;
}
//最大N，Mg，后面N位没变化
//卡住Mg检查片段长度的错误算法，连续长度有3种
int main()
{
    int n; cin >> n;
    vector<int> iv, mv, rv;//用它的比较函数
    for (int i = 0; i < n; ++i){
        int t; cin >> t;
        iv.push_back(t);
        mv.push_back(t);
    }
    for (int i = 0; i < n; ++i){
        int t; cin >> t;
        rv.push_back(t);
    }//输入完毕
    if(!InsertSortCheck(iv, rv))
        MergeSortCheck(mv, rv);
    return 0;
}