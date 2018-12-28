#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define R 7.5
 
typedef struct _node{//是节点了
	int x;
	int y;
}Node;
 
typedef struct _list{//一个路径链表
	int location;
	struct _list *next;
}List;
 
typedef struct _table{//一种特殊的结构
	int know; //记录是否被访问过了，没有写0，有了写1，能到岸上写2 
	int dv;  //记录总路径长短 
	int pre; //记录上一个节点 
}Table;
 
int  Number;
int  Stepsize;//步长
Node *Croco;
Table *Sheet;
 
int   find_shore(int x,int y,int range);//函数不少。。。
void  add_que(List *Beginer,int loc);
int   dele_que(List *Beginer);
void  Jump();
void  print_table();
int   find_root(int i);
int   find_termination();
void  print_croco(int loc);
 //真的算是比较恶心了
int main(){
	scanf("%d %d",&Number,&Stepsize);
    //一个动态扩增的，就这样
	Croco=(Node*)malloc((Number+1)*sizeof(Node));
	Sheet=(Table*)malloc((Number+1)*sizeof(Table));
	int i,j,k;
	for(k=0;k<Number+1;k++){
		Croco[k].x=0; Croco[k].y=0;
        //表单与鳄鱼有关
		Sheet[k].dv=100; //总路径长短先初始化为100？
        Sheet[k].know=0; //是否被访问过了。。。
         Sheet[k].pre=-1; //记录上一个节点是-1.。。看来是这样
	}
	//这里是初始化节点的操作了
	Sheet[0].dv=0;Sheet[0].pre=0;
	//
	for(k=1;k<Number+1;k++){
		scanf("%d %d",&i,&j);
		Croco[k].x=i;//这里才是录入。。。
		Croco[k].y=j;
	}
	
	Jump();//开始跳了
//	print_table();
	int termination=find_termination();//寻找最终节点？
	if(termination==-1){
		printf("0");
	}
	else{
		if(termination==0){
			printf("1");
		}
		else{
		printf("%d\n",Sheet[termination].dv+1);
		print_croco(find_termination());
		}
	}
	return 0;
}
 
void  Jump(){//跳函数
	List *Beginer=(List*)malloc(sizeof(List));//嗯，定义一个这个
	Beginer->next=NULL;
	int record=0;//一个什么记录
	int i=1;
	int reach=0;
	int k;
	add_que(Beginer,0); //把原点在Croco中的下标压进队列 
	record=dele_que(Beginer);  //原点出队列（出来的是在Croco中的下标） //都是在用队列进行模拟
	reach=find_shore(Croco[record].x,Croco[record].y,Stepsize+R);  //看看能不能到岸上 
	if(reach){  //能，Sheet中这点的Know写2 
		Sheet[record].know=2;
	}else{    //不行就写1 
		Sheet[record].know=1;
	}
	
	for(k=0;k<Number+1;k++){   //遍历整个Croco，找到还没有被访问过（know==0），并且能跳到的点 
		if(Sheet[k].know==0 && pow(Croco[k].x-Croco[record].x,2) + pow(Croco[k].y-Croco[record].y,2)<=pow(Stepsize+R,2)){
			add_que(Beginer,k);  //把这个点的下标写进去， 
			Sheet[k].dv=Sheet[record].dv+1;  //距离为之前节点距离+1 
			Sheet[k].pre=record;  //记录之前节点 
			Sheet[k].know=1;
		}
	}	
	
	while(Beginer->next){
		record=dele_que(Beginer);  //原点出队列（出来的是在Croco中的下标） 
		reach=find_shore(Croco[record].x,Croco[record].y,Stepsize);  //看看能不能到岸上 
		if(reach){  //能，Sheet中这点的Know写2 
			Sheet[record].know=2;
		}
		
		
		for(k=0;k<Number+1;k++){   //遍历整个Croco，找到还没有被访问过（know==0），并且能跳到的点 
			if(pow(Croco[k].x,2)+pow(Croco[k].y,2) > pow(7.5,2) && (abs(Croco[k].x)<50 && abs(Croco[k].y<50))){
				if(Sheet[k].know==0 && pow(Croco[k].x-Croco[record].x,2) + pow(Croco[k].y-Croco[record].y,2)<=pow(Stepsize,2)){
					add_que(Beginer,k);  //把这个点的下标写进去， 
					Sheet[k].dv=Sheet[record].dv+1;  //距离为之前节点距离+1 
					Sheet[k].pre=record;  //记录之前节点 
					Sheet[k].know=1;
				}
			}
		}
		
	}		
} 
 
void print_croco(int loc){
	if(Sheet[loc].pre==0){
		printf("%d %d\n",Croco[loc].x,Croco[loc].y);
	}
	else{
		print_croco(Sheet[loc].pre);
		printf("%d %d\n",Croco[loc].x,Croco[loc].y);
	}
}
 
int   find_root(int i){
	int loc;
	while(Sheet[i].pre != 0){
		 i=Sheet[i].pre;
	}
	loc=i;
	return loc;
}
 
int   find_termination(){
	int i;
	int Dis=200;
	int First=1000;
	int loction=-1;
	for(i=0;i<Number+1;i++){
		if(Sheet[i].know==2){
			if(Sheet[i].dv<Dis){
				loction=i;
				Dis=Sheet[i].dv;
				First=pow(Croco[find_root(i)].x,2)+ pow(Croco[find_root(i)].y,2);
			}
			else
			{ 
				if(Sheet[i].dv==Dis){
					if( pow(Croco[find_root(i)].x,2)+ pow(Croco[find_root(i)].y,2)<First){
						loction=i;
						Dis=Sheet[i].dv;
						First=pow(Croco[find_root(i)].x,2)+ pow(Croco[find_root(i)].y,2);			
					}	 
				}	
			}
		}
	}
	return loction;
}
 
void  add_que(List *Beginer,int loc){//入队操作
	List *p=Beginer;
	while(p->next){
		p=p->next;
	}
	List *q=(List*)malloc(sizeof(List));
	q->next=NULL;
	q->location=loc;//算是很简单了
	p->next=q;
}
 
int dele_que(List *Beginer){
	List *record;
	record=Beginer->next;
	if(record){
		Beginer->next=record->next;
	}
	int result=record->location;
	free(record);
	return result;
}
 
int find_shore(int x,int y,int range){
	
	int flag=0;
	if(x>=0){	x=x+range;	}
	else{		x=x-range;	}
	
	if(y>=0){	y=y+range;	}
	else{		y=y-range;	}
	
	if(abs(x)>=50 || abs(y)>=50){
		flag=1;
	}
	return flag;
}
 
void print_table(){
	int i=0;
	for(i=0;i<Number+1;i++){
		printf("x=%d\ty=%d\t",Croco[i].x,Croco[i].y);
		printf("know=%d\tdv=%d\tpre=%d\n",Sheet[i].know,Sheet[i].dv,Sheet[i].pre);
	}
}
