#include "iostream"
#include "cstdio"
#include "map"
#include "set"
#include "algorithm"

using namespace std;
//家庭成员的最小编号 家庭人口数 人均房产套数 人均房产面积
typedef struct Result{
    int id;
    int count;
    double housCont;
    double housSqur;
}Res;
Res FamiRes[10000];
int frn=0;
std::set<int> peo;
int an[10000];
int housCont[10000];
int housSqur[10000];
void Init(){
    for(int id=0; id<10000; id++){
        an[id] = id;
        housCont[id] = 0;
        housSqur[id] = 0;        
    }
}
int Find(int id){//返回祖先值
    if(an[id] != id)
        an[id] = Find(an[id]);
    return an[id];
}
void Union(int id1, int id2){
    int anid1 = Find(id1); 
    int anid2 = Find(id2);
    if(anid1 != anid2)
        an[anid1] = an[anid2] = anid1<anid2? anid1:anid2;
}
//其中人均值要求保留小数点后3位。
void myCmp(Res &res1, Res &res2){
    Res tres;
    tres.id = res1.id; tres.count = res1.count; 
    tres.housCont = res1.housCont; tres.housSqur = res1.housSqur;

    res1.id = res2.id; res1.count = res2.count;
    res1.housCont = res2.housCont; res1.housSqur = res2.housSqur;

    res2.id = tres.id; res2.count = tres.count; 
    res2.housCont = tres.housCont; res2.housSqur = tres.housSqur; 
}
//家庭信息首先按人均面积降序输出，若有并列，则按成员编号的升序输出。
void mySort(){
    //人均面积降序
    for(int i=0; i<frn; i++){
        for(int j=i; j<frn; j++){
            if(j!=i){
                if(FamiRes[i].housSqur*1000 < FamiRes[j].housSqur*1000){
                    myCmp(FamiRes[i], FamiRes[j]);
                }
            }
        }
    }
    //成员id升序
    for(int i=0; i<frn; i++){
        for(int j=i; j<frn; j++){
            if(j!=i){
                if((int)FamiRes[i].housSqur*1000 == (int)FamiRes[j].housSqur*1000){
                    if(FamiRes[i].id > FamiRes[j].id){
                        myCmp(FamiRes[i], FamiRes[j]);
                    }
                }
            }
        }
    }
}
//输出：家庭成员的最小编号 家庭人口数 人均房产套数 人均房产面积
void myPrint(){
    for(int i=0; i<frn; i++){
        printf("%04d %d %.3f %.3f\n",FamiRes[i].id,
            FamiRes[i].count, FamiRes[i].housCont,FamiRes[i].housSqur);
    } 
}
int main(){
    Init();
    int n; cin >> n;
    //输入并找到自己的祖先
    for (int i = 0; i < n; i++)
    {
        int id, father, mother;
            cin >> id >> father >> mother;
        peo.insert(id);
        if (father != -1){
            peo.insert(father);
            Union(id, father);
        }
        if (mother != -1){
            peo.insert(mother);
            Union(id, mother);
        }
        int k; cin >> k;
        while (k--) {
            int child; cin >> child;
            peo.insert(child);
            Union(id, child);
        }
        cin >> housCont[id] >> housSqur[id];
    }
    //组建家庭
    std::map<int, set<int>> commu;
    for(auto var : peo) {
        if(Find(var) == var){
            std::set<int> family;
            family.insert(var);
            commu[var] = family;
        }else{
            commu[Find(var)].insert(var);
        }
    }
    cout << commu.size() <<endl;
    for(auto iter = commu.begin(); iter!=commu.end(); iter++){
        FamiRes[frn].id = iter->first;
        FamiRes[frn].count = iter->second.size();
        int HC=0, HS=0; 
        for(auto var : iter->second){
            HC += housCont[var];
            HS += housSqur[var];
        }
        FamiRes[frn].housCont = (double)HC/(double)iter->second.size();
        FamiRes[frn].housSqur = (double)HS/(double)iter->second.size();
        frn++;
    }
    mySort();
    myPrint();
    return 0;
}