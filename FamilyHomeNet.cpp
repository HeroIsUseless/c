
#include<iostream>
#include<set>
#include<algorithm>
using namespace std;
set<int>s,ss;	//它用了set，我了个天，真好。。。
int f[10001],id,fa,ma,mj,num,k=0,x,y,z,n,i,a[10001],b[10001];
struct home
{
	int id,sum;
	double ave1,ave2;
}h[10001];
int find(int x)
{
	if(f[x]==x) return x;
	else return f[x]=find(f[x]);
}
void mer(int x,int y)//这里是进行融合的
{
	int a=find(x),b=find(y);
	if(a<b) f[b]=a;
	else f[a]=b;//这里好简单。。。
}
int cmp(home x,home y)
{
	return x.ave2>y.ave2;
}
int main()
{
	for(i=0;i<=10000;i++) f[i]=i;
	cin>>n;
	while(n--)
	{
		cin>>id>>fa>>ma;
		s.insert(id);//
		if(fa!=-1) 
		{
			s.insert(fa);
			mer(id,fa);
		}
		if(ma!=-1) 
		{
			s.insert(ma);
			mer(id,ma);
		}
		cin>>x;
		while(x--)
		{
			cin>>num;
			s.insert(num);
			mer(id,num);
		}
		cin>>y>>z;
		a[id]=y,b[id]=z;//把房产什么的放进去了，并没有组合。。。
	}
    //输出：家庭成员的最小编号 家庭人口数 人均房产套数 人均房产面积
    //嗯，最好的办法还是不用stl，另外就是把累加的时候放在最开始。。。
	set<int>::iterator it,ot;
	for(it=s.begin();it!=s.end();it++) ss.insert(find(*it));
	cout<<ss.size()<<endl;//首先输出了这个总家庭数
	for(it=ss.begin();it!=ss.end();it++)//现在是对于每一个家庭而言
	{
		h[k].id=*it;//h是啥？k是啥？
		for(ot=s.begin();ot!=s.end();ot++)
		{
			if(find(*it)==find(*ot))//遍历一遍获取数值
			{
				if(a[*ot]!=0) h[k].ave1=h[k].ave1+a[*ot];
				if(b[*ot]!=0) h[k].ave2=h[k].ave2+b[*ot];
				h[k].sum++;
			}
		}
		h[k].ave1=h[k].ave1/(double)h[k].sum;
		h[k].ave2=h[k].ave2/(double)h[k].sum;
		k++;
	}
	stable_sort(h,h+k,cmp);
	for(i=0;i<k;i++) 
		printf("%04d %d %.3f %.3f\n",h[i].id,h[i].sum,h[i].ave1,h[i].ave2);
	return 0;
}