#include <stdio.h>

#define ElementType int
#define MAXN 100

void merge_pass( ElementType list[], ElementType sorted[], 
int N, int length );

void output( ElementType list[], int N )
{
    int i;
    for (i=0; i<N; i++) printf("%d ", list[i]);
    printf("\n");
}

void  merge_sort( ElementType list[],  int N )
{
    ElementType extra[MAXN];//多余的空间 
    int  length = 1;  //迭代的初始条件
    while( length < N ) { 
        merge_pass( list, extra, N, length );//进行融合
        //就是靠每次的步长进行排列啊
        //把list填入extra中
        output( extra, N );//输出
        length *= 2;//乘以两倍
        merge_pass( extra, list, N, length );//又进行融合 
        //又给填回去，不忘弄一下
        output( list, N );
        length *= 2;
    }
} 

//这回貌似从0开始了
int main()
{
    int N, i;
    ElementType A[MAXN];

    scanf("%d", &N);
    for (i=0; i<N; i++) scanf("%d", &A[i]);
    //A的确从0开始的
    merge_sort(A, N);
    //最后输出一个好的
    output(A, N);

    return 0;
}

/* Your function will be put here */
//这里需要判断步长，别再越界了就不好了
//把第一个条件按照后面的条件填入第二个条件中去
//还是偶错误
void merge_pass(ElementType list[], ElementType sorted[], int N, int length){
    int i;
    int k = 0;
    int a, b, aEnd, bEnd;
    if(length > N) length = N;
    for(i=0; i<N; i+=length*2){
        a = i; b = i+length;//前后坐标
        aEnd = i+length; //但这里是实际存在了
        bEnd = i+length*2 < N ? i+length*2 : N;
        while(a<aEnd && b<bEnd){
            if(list[a] < list[b]){
                sorted[k++] = list[a++]; 
            }else{
                sorted[k++] = list[b++];
            }
        }
        while(a < aEnd) sorted[k++] = list[a++];
        while(b < bEnd) sorted[k++] = list[b++];
    }
}