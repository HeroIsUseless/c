#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int num;
    struct node *next,*prior;
} StackNode,  *LinkStack;


void print(LinkStack head){
    LinkStack p = head->next;
    while(p != NULL){
		printf("%d", p->num);
		 p= p->next;
    }
	printf("\n");
}

// 加法
void Sum(LinkStack head1,LinkStack head2)
{
    StackNode *top1, *top2;
    top1=head1; top2=head2;
    while(top1->next!=NULL)top1=top1->next;
    while(top2->next!=NULL)top2=top2->next;
    while(top1 !=head1 && top2 !=head2){
        top1->num += top2->num;
        if(top1->num >= 10){
            top1->num /= 10;
            top1->prior->num++;
        }
        top1=top1->prior; top2=top2->prior;
    }
    if(top1 == head1 && top2 != head2){ // 如果是1先结束，那么就转移链表
        top1=top1->next;
        head1->next = head2->next;
        top1->prior = top2->prior;
    }
    //输出答案
    print(head1);
}

void Min(LinkStack head1,LinkStack head2)
{//减法
    StackNode *top1, *top2;
    top1=head1; top2=head2;
    while(top1->next!=NULL)top1=top1->next;
    while(top2->next!=NULL)top2=top2->next;
    while(top1 !=head1 && top2 !=head2){
        top1->num -= top2->num;
        if(top1->num < 0){
            top1->num += 10;
            top1->prior->num--;
        }
        top1=top1->prior; top2=top2->prior;
    }
    if(top1 == head1 && top2 != head2){ // 如果是1先结束，那么就转移链表，然后继续操作
        head1->next = head2->next;
        top1->prior = top2->prior;
        while(top1 != head1){
            top1->num -= 10;
            if(top1->num < 0){
                top1->num += 10;
                top1->prior->num--;
            }
            top1=top1->prior;
        }
    }
    //输出答案
    print(head1);
}

LinkStack StrToLinkStack(char *s){
    LinkStack head = (LinkStack)malloc(sizeof(StackNode));
    head->next=NULL; head->prior=NULL;
    LinkStack top = head;
    int i=0;
    while(s[i]){
        LinkStack p = (LinkStack)malloc(sizeof(StackNode));
        p->next=NULL; p->num=s[i]-'0'; p->prior=top;
        top->next=p; top=top->next;
        i++;
    }
    return head;
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

