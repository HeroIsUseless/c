#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#define MAN 0
#define WOMAN 1
using namespace std;

struct Student
{
    string id;
    string name;
    int sex;
    int age;
    int grade;
    int english;
    int math;
    int physics;
    int rank;
    Student *next;
    Student(
        string id,
        string name,
        int sex,
        int age,
        int grade,
        int english,
        int math,
        int physics):id(id),name(name),sex(sex),age(age),grade(grade),
            english(english),math(math),physics(physics){
        next = nullptr;
    }
};
// （1）	创建以上链表，10个节点的
Student* create(){
    Student *head = new Student("", "", 0, 0, 0, 0, 0, 0);
    Student *pstudent = head;
    // 随机生成10个学生
    for (int i = 0; i < 10; i++)
    {
        Student *student = new Student("", "", rand() % 100, 
            rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100);
        pstudent->next = student;
        pstudent = pstudent->next;
    }
    return head;
}
//（2）	显示链表。
void print(Student* head){
    Student* pstudent = head->next;
    while(pstudent)
    {
        cout << pstudent->id << " "
             << pstudent->name << " "
             << pstudent->sex << " "
             << pstudent->age << " "
             << pstudent->grade << " "
             << pstudent->english << " "
             << pstudent->math << " "
             << pstudent->physics << endl;
        pstudent = pstudent->next;
    }
}
//（3）	添加节点。
void add(
    Student *head, 
    string id,
    string name,
    int sex,
    int age,
    int grade,
    int english,
    int math,
    int physics)
{
    Student *pstudent = new Student(id,name,sex,age,grade,english,math,physics);
    Student *p = head;
    while(p->next)
        p = p->next;
    p->next = pstudent;
}
void remove(Student* head, string id){
    Student *parent = head;
    Student *pstudent = head->next;
    while (pstudent)
    {
        if(pstudent->id == id){
            parent->next = pstudent->next;
            free(pstudent);
            break;
        }
        else{
            parent = parent->next;
            pstudent = pstudent->next;
        }
    }
    
}
void getTotal(Student *head)
{
    Student *pstudent = head->next;
    while (pstudent)
    {
        cout 
             << pstudent->english
             +  pstudent->math
             +  pstudent->physics << endl;
        pstudent = pstudent->next;
    }
}
void sortByEnglish(Student *head){
    Student *pstudent = head;
    while(pstudent)
    {
        Student *back_student = pstudent->next;
        while (back_student)
        {
            if (pstudent->english < back_student->english)
            {
                string str;
                str = pstudent->id;
                pstudent->id = back_student->id;
                back_student->id = str;
                str = pstudent->name;
                pstudent->name = back_student->name;
                back_student->name = str;
                int t;
                t = pstudent->sex;
                pstudent->sex = back_student->sex;
                back_student->sex = t;
                t = pstudent->age;
                pstudent->age = back_student->age;
                back_student->age = t;
                t = pstudent->grade;
                pstudent->grade = back_student->grade;
                back_student->grade = t;
                t = pstudent->english;
                pstudent->english = back_student->english;
                back_student->english = t;
                t = pstudent->math;
                pstudent->math = back_student->math;
                back_student->math = t;
                t = pstudent->physics;
                pstudent->physics = back_student->physics;
                back_student->physics = t;
            }
            back_student = back_student->next;
        }
        pstudent = pstudent->next;
    }
}

int main(){
    // 创建10个节点
    cout << "create 10 nodes:" << endl;
    Student *head = create();
    print(head);
    // 添加一个节点
    cout << "add a node:" << endl;
    add(head, "0", "0", 1, 2, 3, 4, 5, 6);
    print(head);
    // 删除一个节点
    cout << "delete a node:" << endl;
    remove(head, "0");
    print(head);
    // 获取总分数
    cout << "get total grade:" << endl;
    getTotal(head);
    // 进行按照英语排序
    cout << "sort by english:" << endl;
    sortByEnglish(head);
    print(head);
    return 0;
}