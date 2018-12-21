#include<cstdio>
#include<queue>
using namespace std;
const int maxn = 110;
int map[maxn][maxn],//代表节点和之间的连线
    d[maxn],//代表路径
    indegree[maxn];//代表入度
//所以说，我要怎么做？
int main(){
    int n,m;//点数和条数
    scanf("%d%d",&n,&m);
    //初始化
    for(int i = 0; i < n; i++){
        d[i] = -1;
        indegree[i] = 0;
        for(int j = 0; j < n; j++){
            map[i][j] = map[j][i] = -1;
        }
    }
    int u,v,w;
    for(int i = 0; i < m; i++){
        scanf("%d%d%d",&u,&v,&w);
        map[u][v] = w;
        indegree[v]++;
    }
    //压入初始节点，虽然只有一个初始节点，但是这样的确是有意思多了
    queue<int> q;
    for(int i = 0; i < n; i++){
        if(!indegree[i]){
            q.push(i);
            d[i] = 0;//但这个又是什么？每个初始节点的这个设为0.。。原来是-1的，这个玩意代表路径
        }
    }
    //为什么d在最开始取-1
    //下面是最难的操作部分
    int cur;
    while(!q.empty()){
        cur = q.front(); q.pop();//拿出初始节点了
        for(int i = 0; i < n; i++){
            if(map[cur][i] != -1){//对于每一个初始节点，进行判断连线的操作
                indegree[i]--;//入度减1，是这个节点的入度减1
                //这里是最难理解的了，实际上就是针对每个连接的节点来说，付给它最大值，最晚的完成时间，就是这样
                if(d[cur] + map[cur][i] > d[i]){//这个是什么意思，难道不是恒成立吗？
                    d[i] = d[cur] + map[cur][i];//哦，进行转换操作，这个东西的确是路径
                }
                if(!indegree[i]){
                    q.push(i);
                }
            }
        }
    }
    //为什么每个节点的值都可以代表路径，并不是每个d都代表路径，只不过它肯定是小的
    //为什么
    int maxCost = -1;//来找最大值了
    int i;
    for(i = 0 ; i < n; i++){//又遍历一遍
        if(indegree[i]) break;//入度为0怎么了？表示初始节点，还能操作的，就这样不行，那么它应该是-1吧
        if(d[i] > maxCost) maxCost = d[i];//对每个节点的d求其最大值，那么这个d到底代表什么呢？每一个节点都存储着路径
        //那么那是怎样的路径呢？
    }
    if(i == n) printf("%d",maxCost);//表示最大时间了
    else printf("Impossible");
    return 0;
}