#include "iostream"
#include "vector"
#include "algorithm"
using namespace std;

class Stats{
    public:
    Stats(int miss_lbak, int sava_lbak, 
        int miss_boat, int sava_boat, 
        int miss_rbak, int sava_rbak, int step):
        miss_lbak(miss_lbak), sava_lbak(sava_lbak), 
        miss_boat(miss_boat), sava_boat(sava_boat),
        miss_rbak(miss_rbak), sava_rbak(sava_rbak),
        step(step){};
    int miss_lbak;
    int sava_lbak; 
    int miss_boat;
    int sava_boat;
    int miss_rbak;
    int sava_rbak;
    int step;  
    void print(){
        if(step % 2) // 如果是奇数
            cout <<"["<<miss_lbak<<","<<sava_lbak<<"]<-"
                <<"("<<miss_boat<<","<<sava_boat<<")<-"
                <<"["<<miss_rbak<<","<<sava_rbak<<")"<<endl;
        else
            cout <<"["<<miss_lbak<<","<<sava_lbak<<"]->"
                <<"("<<miss_boat<<","<<sava_boat<<")->"
                <<"["<<miss_rbak<<","<<sava_rbak<<")"<<endl;
    }
};
vector<Stats> close;
vector<Stats> crossRiver(Stats stats){
    if(stats.miss_lbak==0 && stats.sava_lbak==0) return stats.step;
    else{
        for(int i=1; i<=shipMax; i++){ // 船上成员从1->Max
            int miss_boat, sava_boat;
            for(sava_boat=0; sava_boat<=i; sava_boat++){ // sava:0->i
                miss_boat=min(i-sava_boat, stats.miss_lbak);
                if(miss_boat==0 && sava_boat==0) continue;
                Stats stats_next = stats;
                int reStep = 10000;
                vector<Stats> stepV_next;
                if()
                if(resStep < minStep){
                    minStep=reStep;
                    bufferInsert.clear();
                    bufferInsert.insert(bufferInsert.begin(), nextStepv.begin(),nextStepv.end());

                }
            }
        }
        stepv.insert(stepv.end(), bufferInsert.begin(), bufferInsert.end());
    }
}
// 野人问题，输出步数，输出移动状态
// 但是状态是什么呢？我想输出没有船移动的状态，这个好办，根据船的状态处理即可
// 因此每一个状态其实是船从左向右走还是从右向左走，这不是状态，这是操作步骤
// 可以预见的是，当操作步骤为单时，将从左向右走
// 当操作步骤为双时，将从右向左走
// 如果step能够自动维护就好了


// 我打算输出什么？它的步骤
// [1,2](0,0)----[0,0]
// [1,1]>>(0,1)>>[0,0]
// [1,1]----(0,0)[0,1]
// 就像这样，然后每一条都是一个state，然后调用state.print()就ok了，把这些state放到一个states[]里面，完美
const int shipMax = 2;
const int miss=3, sava=3;
int main(){
    Stats start(miss,sava, 0,0, 0,0, 0);
    vector<Stats> resV;
    resV = crossRiver(start); 
    for(int i=0; i<resV.size(); i++){
        resV[i].print();
    }
    return 0;
}