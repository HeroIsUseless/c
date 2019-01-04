#include "iostream"
#include "vector"
#include "cstdio"
#include "algorithm"
using namespace std;
typedef struct Student{
    int id;
    int deScore;
    int caScore;
} Student;
//比较函数,后面比较大返回true
bool cmp(Student cstd1, Student cstd2){
    int sum1 = cstd1.caScore + cstd1.deScore;
    int sum2 = cstd2.caScore + cstd2.deScore;
    if(sum1 != sum2) return sum1 > sum2;
    else if(cstd1.deScore != cstd2.deScore)
        return cstd1.deScore > cstd2.deScore;
    else return cstd1.id < cstd2.id;
}
Student student[4][100010];
int main(){
    int n, l, h;
    cin >> n >> l >> h;
    int count[4] = {0};
    for(int i=0; i<n; i++){
        int id, deScore, caScore;
        cin >> id >> deScore >> caScore;
        Student s; 
        s.id=id; s.deScore=deScore; s.caScore = caScore;
        if(deScore>=h && caScore>=h){
            student[0][count[0]++]=s;
        }else if(deScore>=h && caScore>=l){
            student[1][count[1]++]=s;
        }else if(deScore>=l && 
            caScore>=l &&
            deScore >= caScore){
            student[2][count[2]++]=s;
        }else if(deScore>=l && caScore>=l){
            student[3][count[3]++]=s;
        } 
    }//信息输入完毕
    //进行排序
    for(int i=0; i<4; i++){
        sort(student[i],student[i]+count[i],cmp);
    }  
    //下面进行输出
    int resCount = 0;
    for(int i=0; i<4; i++)
        resCount += count[i];
    cout << resCount <<endl;//输出总人数
    for(int i=0; i<4; i++){//输出其余项
        for(int j =0; j<count[i]; j++){
            printf("%d %d %d\n",student[i][j].id,student[i][j].deScore,
            student[i][j].caScore); 
        }
    }
    return 0;
}
