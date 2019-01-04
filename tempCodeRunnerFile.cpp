#include <cstdio>
#include "iostream"
#include <algorithm>
#include <vector>
using namespace std;
void merge_sort(int cmar[], int cn, int step){
    int tar[105];
    for(int i=0; cn-i>=step*2; i+=2*step){
        int s0 = i;
        int s1 = i, e1 = i+step-1;
	 	int s2 = i+step, e2 = i+2*step-1;
	 	while(s1 <= e1 && s2 <= e2) {
	 		if (cmar[s1] <= cmar[s2]) {
	 			tar[s0++] = cmar[s1++];
	 		} else {
	 			tar[s0++] = cmar[s2++];
	 		}
	 	}
	 	while(s1 <= e1) {
	 		tar[s0++] = cmar[s1++];
	 	}
	 	while(s2 <= e2){
	 		tar[s0++] = cmar[s2++];
		}
    }
    for(int i=0; i<cn; i++){
        cmar[i] = tar[i];
    }
}
bool cmp(int car1[], int car2[], int cn){
    bool res = true;
    for(int i=0; i<cn; i++){
        if(car1[i] != car2[i])
            res = false;
    }
    return res;
}
void print(int car[], int cn) {
    cout << car[0];
    for (int i = 1; i < cn; i++) {
        cout << " " << car[i];
    }
    cout << endl;
}
void MergeSortCheck(int cmar[], int crar[], int cn){
    int step = 1;
    while(step < cn){
        if(cmp(cmar, crar, cn)){
            cout << "Merge Sort" <<endl;
            merge_sort(cmar, cn, step);
            print(cmar, cn);
            return;
        }else{
            merge_sort(cmar, cn, step);
            step *=2;
        }
    }
} 
bool InsertSortCheck(int ciar[], int crar[], int cn){
    for(int i=1; i<cn; i++){
        if(cmp(ciar, crar, cn)){
            cout << "Insertion Sort" <<endl;
            sort(ciar, ciar+i);
            print(ciar, cn);
            return true;
        }else{
            sort(ciar, ciar+i);
        }
    }
    return false;
}
//最大N，Mg，后面N位没变化
//卡住Mg检查片段长度的错误算法，连续长度有3种
int main(){
    int n; cin >> n;
    vector<int> iv, mv, rv;//用它的比较函数
    int iar[105], mar[105], rar[105];
    for (int i = 0; i < n; ++i){
        int t; cin >> t;
        iar[i] = rar[i] = t;
    }
    for (int i = 0; i < n; ++i){
        int t; cin >> t;
        rar[i] = t;
    }//输入完毕
    if(!InsertSortCheck(iar, rar, n))
        MergeSortCheck(mar, rar, n);
    return 0;
}