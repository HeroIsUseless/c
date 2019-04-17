#include<iostream>
using namespace std;
class Complex {
    double real, image;
public:
    Complex(double r=0, double i=0);
    Complex(const Complex& other);
    void print();
    Complex operator + ( const Complex& other); 
    Complex operator - ( const Complex& other); //减法， 二元
    Complex operator - ( );  //求负，一元
    Complex operator = ( const Complex& other); //赋值， 二元
    Complex operator = (char* s); //赋值， 二元
    friend Complex operator*(Complex& c1, Complex& c2);
};
Complex Complex:: operator - (const Complex& other)
{  Complex temp;
   temp.real=real-other.real;
   temp.image= image -other.image;
   return temp;
}
Complex Complex:: operator - ( )
{  Complex temp;
   temp.real= - real;
   temp.image= - image;
   return temp;
}
Complex Complex:: operator = (const Complex& other)
{  //此赋值运算符的重载与缺省赋值运算相同，可以省略。
   real= other.real;
   image= other.image;
   return *this;
} 
Complex Complex:: operator = (char* s)
{  
    char ch_real[20], ch_image[20];
    int n_real=0, n_image=0;
    int i=0;
    int flag = 0;
    while(s[i] != 0){
        if(flag == 0){
            if(s[i]=='-'){flag = -1;goto end;}
            if(s[i]=='+'){flag =  1;goto end;}
            ch_real[n_real++] = s[i];
        }
        else{
            if(s[i]=='i') goto end;
            ch_image[n_image++] = s[i];
        }
        end: i++;
    }    
   real=0, image=0;
   for(int i=0; i<n_real; i++){
       real += ch_real[n_real-1-i];
       real *= 10;
   }
   for(int i=0; i<n_image; i++){
       image += ch_image[n_image-1-i];
       image *= 10;
   }
   image *= flag;
   return *this;
} 
Complex operator*(Complex& c1, Complex& c2){
    return Complex(c1.real*c2.real-c1.image*c2.image, 
                        c1.real*c2.image+c1.image*c2.real);
}
int main()
{ 	
	Complex c1(1,2);
	Complex c2(2);
	Complex c3(c1);
	c3.print();
	c1=c1+c2+c3;
	c2= - c3;
	c3=c2-c1;
	c3.print();
    return 0;
}
