#include <stdio.h>
#include <string.h>

#define KEYLENGTH 15                   /* 关键词字符串的最大长度 */
typedef char ElementType[KEYLENGTH+1]; /* 关键词类型用字符串 */
typedef int Index;                     /* 散列地址类型 */
typedef enum {false, true} bool;

typedef struct LNode *PtrToLNode;
struct LNode {
    ElementType Data;
    PtrToLNode Next;//下一个元素指针
};
typedef PtrToLNode Position;//这是一个node
typedef PtrToLNode List;//是一个指针

typedef struct TblNode *HashTable; /* 散列表类型 */
//是一个指针什么的
struct TblNode {   /* 散列表结点定义 */
    int TableSize; /* 表的最大长度 */
    List Heads;    /* 指向链表头结点的数组 */
    //但它是一个结构
};

Index Hash( ElementType Key, int TableSize )
{
    return (Key[0]-'a')%TableSize;
}//this is a hash func

HashTable BuildTable(); /* 裁判实现，细节不表 */
bool Delete( HashTable H, ElementType Key );
//这个分离链接法不是最后开辟出一个空间，而是所有相同的
//值放在同一个链表中，是这样的
int main()
{
    HashTable H;
    ElementType Key;

    H = BuildTable(); 
    scanf("%s", Key);
    if (Delete(H, Key) == false)
        printf("ERROR: %s is not found\n", Key);
    if (Delete(H, Key) == true)
        printf("Are you kidding me?\n");
    return 0;
}

/* 你的代码将被嵌在这里 */
bool Delete(HashTable H, ElementType Key){
   int pos = Hash(Key, H->TableSize);
   PtrToLNode pre, del;
   pre = H->Heads + pos;
   del = H->Heads[pos].Next;
   while(!(del==NULL || strcmp(del->Data, Key)==0)){
        pre = del;
        del = del->Next;
   }
   if(del == NULL) return false;
   else {
        pre->Next = del->Next;
        free(del);
        printf("%s is deleted from list Heads[%d]\n", Key, pos);
        return true;       
   }
}
bool Delete( HashTable H, ElementType Key )
{
	Position p,tmp;
	Index pos;  //关键字地址 
	pos=Hash(Key, H->TableSize);  //初始化散列位置 
	p=H->Heads[pos].Next;         //从该邻接表第一个节点开始 
	/* 当未到表尾，并且Key未找到时 */
	while(p&&strcmp(p->Data,Key)){ 
	  tmp=p;
	  p=p->Next;
	}
	if(p==NULL)
		return false;
  else{
    	printf("%s is deleted from list Heads[%d]",Key,pos);
    	tmp=p->Next; //删除p节点
    	free(p);     //释放p内存
    	return true;
	}	
}
