#include <stdio.h>

#define MAXTABLESIZE 100000  /* 允许开辟的最大散列表长度 */
typedef int ElementType;     /* 关键词类型用整型 */
typedef int Index;           /* 散列地址类型 */
typedef Index Position;      
/* 数据所在位置与散列地址是同一类型 */
/* 散列单元状态类型，分别对应：有合法元素、空单元、有已删除元素 */
typedef enum { Legitimate, Empty, Deleted } EntryType;

typedef struct HashEntry Cell; /* 散列表单元类型 */
struct HashEntry{
    ElementType Data; /* 存放元素 */
    EntryType Info;   /* 单元状态 */
};

typedef struct TblNode *HashTable; /* 散列表类型 */
struct TblNode {   /* 散列表结点定义 */
    int TableSize; /* 表的最大长度 */
    Cell *Cells;   /* 存放散列单元数据的数组 */
};

HashTable BuildTable(); /* 裁判实现，细节不表 */
Position Hash( ElementType Key, int TableSize )
{
    return (Key % TableSize);//除余法获得id
}
//此为散列函数
#define ERROR -1
//编写find查找函数吗？
Position Find( HashTable H, ElementType Key );

int main()
{
    HashTable H;
    ElementType Key;
    Position P;

    H = BuildTable(); //创建一个哈希表不用说
    //用线性探测法实现的，大概是用正负一什么的实现的
    scanf("%d", &Key);//获得这个值还是它的索引什么的。。。
    P = Find(H, Key);
    if (P==ERROR)
        printf("ERROR: %d is not found and the table is full.\n", Key);
    else if (H->Cells[P].Info == Legitimate)
        printf("%d is at position %d.\n", Key, P);
    else
        printf("%d is not found.  Position %d is returned.\n", Key, P);

    return 0;
}

/* 你的代码将被嵌在这里 */
//通过输入一个值，找到它所在的位置，一个逆向的过程
//做法是
Position Find(HashTable H, ElementType Key){
    Position p,m;//嗯，两个位置
    p=Hash( Key, H->TableSize );
    //呃，什么鬼，没有冲突处理的哈希函数
    //你要清楚它是怎么添加的
    if(H->Cells[p].Data==Key||H->Cells[p].Info==Empty)
    //为什么信息要说是空呢？
    //是两者有一个成立就成，如果为空那么也返回，返回什么呢？
        return p;
    else
    {
        for(int i=1;i<H->TableSize;i++)//它小于最大长度
        {
            m=(p+i)%H->TableSize;
            if(H->Cells[m].Data==Key||H->Cells[m].Info==Empty)
            //只要是这样就会成立，嗯
                return  m;
        }
        //东西很简单，但是代码不懂
        return ERROR;
    }
}