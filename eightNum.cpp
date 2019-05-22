#include "iostream"
#include<cstdio>
#include<queue>
#include<map>
using namespace std;

int str_final[] = "123804765";
int numList_final = 123804765;

struct Node{
    MyValue mv; // 这段数列
	int pos_0; // 0的位置
    int f; // 估价函数
    int g; // 从初始节点到当前节点的步数(层数)

    public:
    Node(MyValue mv, int g):mv(mv), g(g){
		int h=0; 
		char str_tmp[10];  
		sprintf(str_tmp,"%09d",numList);  
		for(int i=0;i<9;i++) if(str_final[i] != str_tmp[i]) h++;
		f = h + g;  
        

    }
};
// 它每一个都是一个数据，然后遵循上左下右
int changable[9][4]={{-1,-1,3,1},{-1,0,4,2},{-1,1,5,-1},
					{ 0,-1,6,4},{ 1,3,7,5},{ 2,4,8,-1},
					{3,-1,-1,7},{4,6,-1,8},{5,7,-1,-1}};

Map<int,bool> flag;
priority_queue<Node> que;//优先级队列 
// 一个交换函数，交换什么呢？字符串里面的交换
void swap(char* str,int a,int b){
    char c=str[a]; str[a]=str[b]; str[b]=c;
}

int solve(Value &mv){ 
    int pos_0 = mv.find(0);
	Node node_start(mv, 0); 
	que.push(node_start); 
	flag[mv] = 1; 

    // 下面开始循环
	while(!que.empty()){  
		Node node_tmp = que.top(); que.pop(); 
        char str_tmp[10];
		sprintf(str_tmp,"%09d",node_tmp.numList);  
		int pos_0 = node_tmp.pos_0, k; 
		for(int i=0;i<4;i++){  
			if(changable[pos_0][i]!=-1){
				swap(str_tmp, pos_0, changable[pos][i]);  
                int numList_tmp;
				sscanf(str_tmp,"%d",&numList_tmp); 
                // 判断是否相等退出
				if(numList_tmp == numList_final) return numList_tmp.g + 1; 
                else{
                    if(flag.count(numList_tmp) == 0){  
                        Node node_tmp2(str_tmp, node_tmp.g+1);  
                        que.push(node_tmp2);  
                        flag[numList_tmp] = 1;  
                    }
                    swap(str_tmp, pos_0, changable[pos_0][i]);                     
                }
			}
		}
	}
}
// 直接打印出过程
int main(){
    Value mv({2,8,3,1,0,4,7,6,5});
    int g = solve(mv);
    cout << g <<endl;
	return 0;
}