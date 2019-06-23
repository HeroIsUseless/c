#include<stdio.h>
#include<stdlib.h>
typedef struct node{
          int num;
          struct node *next,*prior;/*指向下一个节点和前一个节点*/
} StackNode,  *LinkStack;

void Sum(LinkStack head1,LinkStack head2)// 加法
    {
        StackNode *p1,*p2,*p,*top,*p3;
        top=head1;
        while(top->next!=NULL)top=top->next;/* 指向第一张链表的尾端（计算结果存储与此链表中）*/
        p1=head1->next;
        p2=head2->next;/*指向两个存储大整数的链表*/
        while(p1!=NULL)
        {
            if(p2!=NULL)
            {
                p1->num+=p2->num;
                if(p1->num>=10)//进位
                {

                    p3=p1;
                    while(p3!=NULL)
                    {
                        if(p3->num>=10)
                        p3->num-=10;
                        if(p3->next!=NULL)
                        {
                            p3->next->num+=1;
                        }
                        else//创建新节点
                        {
                            p=(LinkStack)malloc(sizeof(StackNode));
                            p->next=NULL;//先指向空
                            p->num=1;
                            p->prior=top;//指向父节点
                            top->next=p;//连接新节点
                            top=top->next;//更新top节点
                            break;
                        }
                        p3=p3->next;
                    }
                 }

            }
            p1=p1->next;
            if(p2!=NULL&&p1!=NULL)p2=p2->next;
        }
        if(p2!=NULL)
        {
            p2=p2->next;
            top=head1;
            while(top->next!=NULL)top=top->next;
        }
        while(p2!=NULL)
        {
            p=(LinkStack)malloc(sizeof(StackNode));
            p->next=NULL;//先指向空
            p->num=p2->num;
            p->prior=top;//指向父节点
            top->next=p;//连接新节点
            top=top->next;//更新top节点
            p2=p2->next;
        }
        //输出答案
        while(top!=head1)
        {
            printf("%d",top->num);
            top=top->prior;
        }
        printf("\n");
    }
    void Min(LinkStack head1,LinkStack head2)
    {//减法
        StackNode *p1,*p2,*p,*top;
        int flag=0;
        top=head1;
        while(top->next!=NULL)top=top->next;
        p1=head1->next;
        p2=head2->next;
        while(p1!=NULL)
        {
            if(p2!=NULL)p1->num-=p2->num;
            else break;
            p1=p1->next;
            if(p2!=NULL&&p1!=NULL)p2=p2->next;
        }
        //把head2剩下数据按负数连进head1
        if(p2!=NULL)
        {
            p2=p2->next;
            while(p2!=NULL)
            {
                p=(LinkStack)malloc(sizeof(StackNode));
                p->next=NULL;//先指向空
                p->num=-p2->num;
                p->prior=top;//指向父节点
                top->next=p;//连接新节点
                top=top->next;//更新top节点
                p2=p2->next;
            }
        }
         if(top->num<0)
            {//全部取反
            flag=1;
            p1=head1->next;
            while(p1!=NULL)
            {
                p1->num=-p1->num;
                p1=p1->next;
            }
        }
        //借位
        p1=head1->next;
        while(p1!=NULL)
        {
            if(p1->num<0){
			p1->next->num--;
			p1->num+=10;
		}
        p1=p1->next;
        }
        //输出答案
        if(flag==1)printf("-");
        while(top->num==0&&top->prior!=head1)top=top->prior;
        while(top!=head1){
		printf("%d",top->num);
		top=top->prior;
	}
	printf("\n");
}


LinkStack StrToLinkStack(char *s){
    LinkStack head = (LinkStack)malloc(sizeof(StackNode));
    head->next=NULL; head->prior=NULL;
    LinkStack top = head;
    int i=0;
    while(s[i]) i++;
    while(s[--i]){
        LinkStack p = (LinkStack)malloc(sizeof(StackNode));
        p->next=NULL; p->num=s[i]-'0'; p->prior=top;
        top->next=p; top=top->next;
    }
    return head;
}

void print(StackNode *head){
    StackNode *p = head->next;
    while(p != NULL){
		printf("%d", p->num);
		 p= p->next;
    }
	printf("\n");
}

// 1213901156781234+1213901156781234=2427102311112468
int main(){
    char s1[100]={0};
    char s2[100]={0};
    printf("please input two num:\n");
    scanf("%s %s", s1, s2);
    LinkStack head1 = StrToLinkStack(s1);
    LinkStack head2 = StrToLinkStack(s2);
    Sum(head1, head2);  
    return 0;
}

