#include "iostream"
#include "vector"
using namespace std;
//用一个类来做吧，实际上是进行学号的排列，额，不是
//首先抽出都大于h的，进行总分排序
//抽出德分大于h胜才分小于h，进行总分排序
//抽出德才分均低于h的，但是德分不低于才分的，进行总分排序
//其他达到l的，最后总分排序
//以上德分和才分都必须大于l
//列表排序，值得抽出来
//首先给出达到最低分数的人数M，然后进行排序
//当总分相同时，按照德分降序排列，若德分相同，
//按照学号升序排列
//定义一个结构体，然后定义一个结构体数组，然后定义一个
//具有可选参数的函数，通过选择排序，最终排好序
//其实这种问题的意义在于不改变相同元素的顺序进行排序
//就是稳定排序
//归并排序的递归与非递归只有主函数上的差别而已，用一个结构，
//然后用上几遍mergesort就可以了
//a new method is that, er, first, put them into diff vector
//then, sort is all same, yes.
//and next is how to create this sort function
//接下来是杂糅两个函数
//它是专门做了一个flag比较函数，排序还是一样的排序，如果说，插入到指定位置
//用vector，二分法查找位置插入就行了
void InsortSort(vector<Student> cstu, Student cs);
typedef struct Student{
    int id;
    int deScore;
    int caScore;
} Student;
int main(){
    int n, l, h;
    cin >> n >> l >> h;
    std::vector<Student> stu[4];//分别代表不同类型的学生
    for(int i=0; i<n; i++){
        int id, deScore, caScore;
        cin >> id >> deScore >> caScore;
        Student s; 
        s.id=id; s.deScore=deScore; s.caScore = caScore;
        if(deScore>h && caScore>h){
            InsortSort()
        }
    }
    //input is over

    return 0;
}
//when cstd2 is bigger then return true
bool cmp(Student cstd1, Student cstd2){
    int sum1 = cstd1.caScore + cstd2.deScore;
    int sum2 = cstd1.caScore + cstd2.deScore;
    if(sum1 != sum2) return sum1 < sum2;
    else if(cstd1.deScore != cstd2.deScore)
        return cstd1.deScore < cstd2.deScore;
    else return cstd1.id > cstd2.id;
}
//find a proper place to insert, using dmy
void InsortSort(vector<Student> cstu, Student cs){
    int low=0, high=cstu.size()-1;
    int mid;
    while(low <= high){
        mid = (low+high)/2;
        if(cmp(cstu[mid], cs)){//cs is bigger

        }else{//cs is smaller

        }
    }
}