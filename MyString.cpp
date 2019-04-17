#include "iostream"
using namespace std;

class MyString{
    char* val;
    public:
    MyString(); // 产生空串
    MyString(int iVal);  //将iVal转成字符串，并初始化成员变量val
    MyString(double fVal);//将fVal转成字符串，并初始化成员变量val
    MyString(char const *s);   //用s来初始化成员变量val
    MyString(const MyString& obj);//拷贝构造函数
    MyString operator+(char* s);
    MyString operator+(char c);
    MyString operator+(MyString& obj);
    MyString& operator=(char* );
    MyString& operator=(MyString obj);
    char operator[](int index);
    ~MyString();
    void print(){cout << val <<endl;}
};
MyString::MyString(){
    val = new char[1];
    val[0] = '\0';
}
MyString::MyString(int iVal){
    char ch_t[20] = {0}; 
    int n=0;
    while(iVal!=0){
        ch_t[n++] = iVal%10 + 48;
        iVal /= 10;
    }
    val = new char[n+1];
    for(int i=0; i<n; i++){val[i] = ch_t[n-1-i];}
    val[n] = '\0';
}
MyString::MyString(double fVal){
    char str_int[20] = {0};
    char str_dec[20] = {0};
    int n_int=0, n_dec=0;
    int ch_int = fVal; // 整数部分
    float ch_dec = fVal-ch_int; // 小数部分
    // 先计算整数部分
    while(ch_int!=0){
        str_int[n_int++] = ch_int % 10;
        ch_int /= 10;
    }
    // 计算小数部分，就计算6位
    int n=6;
    do{
        ch_dec *= 10;
        str_dec[n_dec++] =  (int)ch_dec;
    }while(0 <-- n);    
    // 合并
    val = new char[20];
    for(int i=0; i<n_int; i++){
        val[i] = str_int[n_int-1-i]+48;
    }
    val[n_int] = '.';
    for(int i=0; i<6; i++){
        val[n_int+i+1] = str_dec[i]+48;
    }
    val[n_int+n_dec+1]='\0';
}
MyString::MyString(char const *s){
    int n=0; while(s[n] != '\0') n++;
    val = new char[n+1];
    for(int i=0; i<n; i++) val[i] = s[i];
    val[n] = '\0';
}
MyString::MyString(const MyString& obj){
    int n=0;
    while(obj.val[n] != '\0') n++;
    val = new char[n+1];
    for(int i=0; i<n+1; i++) val[i] = obj.val[i];
}
MyString MyString::operator+(char *s){
    int n_val = 0;
    while(val[n_val]!=0) n_val++;
    int n_s = 0;
    while(s[n_s]!=0) n_s++;
    char *ch_t = new char[n_val+n_s+1];
    for(int i=0; i<n_val; i++) ch_t[i] = val[i];
    for(int i=0; i<n_s; i++) ch_t[n_val+i] = s[i];
    ch_t[n_val+n_s] = 0;
    MyString ms_t(ch_t);
    return ms_t;
}
MyString MyString::operator+(char c){
    int n_val = 0;
    while(val[n_val]!=0) n_val++;
    char *ch_t = new char[n_val+2];
    for(int i=0; i<n_val; i++) ch_t[i] = val[i];
    ch_t[n_val] = c;
    ch_t[n_val+1] = 0;
    MyString ms_t(ch_t);
    return ms_t;

}
MyString MyString::operator+(MyString& obj){
    int n_val = 0;
    while(val[n_val]!=0) n_val++;
    int n_obj = 0;
    while(obj.val[n_obj]!=0) n_obj++;
    char *ch_t = new char[n_val+n_obj+1];
    for(int i=0; i<n_val; i++) ch_t[i] = val[i];
    for(int i=0; i<n_obj; i++) ch_t[n_val+i] = obj.val[i];
    ch_t[n_val+n_obj] = 0;
    MyString ms_t(ch_t);
    return ms_t;
}
MyString& MyString::operator=(char* s){
    int n=0; while(s[n]!=0) n++;
    char* ch_t = new char[n+1];
    for(int i=0; i<n; i++) val[i] = s[i];
    val[n] = 0;
    return *this;
}
MyString& MyString::operator=(MyString const obj){
    int n=0; while(obj.val[n]!=0) n++;
    char* ch_t = new char[n+1];
    for(int i=0; i<n; i++) val[i] = obj.val[i];
    val[n] = 0;
    return *this;

}
char MyString::operator[](int index){
    return val[index];
}
MyString::~MyString(){
    delete[] val;
}
int main(){
    MyString ms1; ms1.print();
    MyString ms2(12345); ms2.print();
    MyString ms3(2.234567); ms3.print();
    MyString ms4("abcde"); ms4.print();
    MyString ms5(ms4); ms5.print();
    MyString ms6(ms5+(char*)"abcd"); ms6.print();
    MyString ms7(ms5+'o'); ms7.print();
    MyString ms8(ms5+ms6); ms8.print();
    ms8 = (char*)"qwertyui"; ms8.print();
    ms8 = ms7; ms8.print();
    cout << ms8[1]<<endl;
    return 0;
}