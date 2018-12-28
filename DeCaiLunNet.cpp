#include<cstdio>
#include<queue>
#include<iostream>
using namespace std;
struct node{
	long long stuNo;
	int de;
	int cai;
	int sum;//定义了总分，嗯
	bool operator <(const node &a)const{//重载了符号，嗯
		if(sum!=a.sum)//是总数的排名
		return sum<a.sum;//返回的是什么啊？
		else if(de!=a.de)//如果不行就是de的返回
		return de<a.de;
		else
		return stuNo>a.stuNo;//然后返回学号，返回的是true，false值
	}//哇，这个简直就是良心定做的
}w;
int main(){
	priority_queue<node>q[4];//优先队列，不知道为什么用这个
	int N,L,H,M=0;
	cin>>N>>L>>H;
	for(int i=0;i<N;i++){
		scanf("%lld%d%d",&w.stuNo,&w.de,&w.cai);
        //嗯，还行。。。
		w.sum=w.de+w.cai;
		if(w.de<L||w.cai<L) continue;
		if(w.de>=H&&w.cai>=H){
			q[0].push(w);
			M++;
		}
		else if(w.de>=H){
			q[1].push(w);
			M++;
		}//una, put into seperate que, fine.
		else if((w.cai<H&&w.de<H)&&w.de>=w.cai){
			q[2].push(w);
			M++;
		}
		else{
			q[3].push(w);
			M++;
		}
	}
	cout<<M<<endl;
    // oh my god, splendid.
    //but it's ok.
	for(int i=0;i<4;i++){
		int len=q[i].size();
		for(int j=0;j<len;j++){
			node tmp=q[i].top();q[i].pop();
			printf("%lld %d %d\n",tmp.stuNo,tmp.de,tmp.cai);
		}
	}
	return 0;
}
//几乎没有改进的余地了

#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct student{
	char id[10];//为毛是10个id
	int de,cai,sum;
	int flag;
}stu[100005];
bool cmp(student a,student b){//比较函数
	if(a.flag!=b.flag) return a.flag<b.flag;//也是一个truefalse什么的，就是一个🚩
	else if(a.sum!=b.sum) return a.sum>b.sum;
	else if(a.de!=b.de) return a.de>b.de;
	else return strcmp(a.id,b.id)<0;//真的有意思，这个返回id的对比，偶，这么干
}
int main(){
	int n,L,h;
	scanf("%d%d%d",&n,&L,&h);
	int m=n;//首先初始化这个，ok
	for(int i=0;i<n;i++){
		scanf("%s%d%d",&stu[i].id,&stu[i].de,&stu[i].cai);//还行
		stu[i].sum=stu[i].de+stu[i].cai;//还行
		if(stu[i].de<L||stu[i].cai<L){//代表这个是一个劣质学生
			stu[i].flag=5;//等于第五类
			m--;//偶一直减
		}
		else if(stu[i].de>=h&&stu[i].cai>=h)  stu[i].flag=1;
		else if(stu[i].de>=h&&stu[i].cai<h)  stu[i].flag=2;
		else if(stu[i].de>=stu[i].cai)  stu[i].flag=3;
		else stu[i].flag=4;//判断它的类型
	}
	sort(stu,stu+n,cmp);//用了一个排序，就输出了？//可能用cmp排序，真的是强👍
	printf("%d\n",m);
	for(int i=0;i<m;i++){
		printf("%s %d %d\n",stu[i].id,stu[i].de,stu[i].cai);
	}
	return 0;
}
