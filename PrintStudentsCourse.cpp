#include "iostream"
#include "stdio.h"
#include "algorithm"
using namespace std;
int RName(char cname[]){
    return (cname[0] - 'A') * 26 * 26 * 10 + 
    (cname[1] - 'A') * 26 * 10 + 
    (cname[2] - 'A') * 10 + cname[3] - '0';
}
//怎么办？用map，进行映射
typedef struct Student{
    int course[2501];
    int n = 0;
} Student;
Student student[3000000];
int main(){
    int n, k; 
    scanf("%d %d", &n, &k);
    char name[100];
    for(int i=1; i<=k; i++){
        int corse, cont; 
        cin >> corse >> cont;
        for(int j=0; j<cont; j++){
            scanf("%s", name);
            int iName = RName(name);
            student[iName].course[student[iName].n++] = corse;
        }
    }//信息全部输入完成
    for(int i=0; i<n; i++){
        scanf("%s", name);
        int iName = RName(name);
        printf("%s ", name);
        printf("%d", student[iName].n); 
        sort(student[iName].course, student[iName].course+
         student[iName].n);
        for(int k=0; k<student[iName].n; k++){
            printf(" %d", student[iName].course[k]);
        }
        printf("\n");
    }
    return 0;
}