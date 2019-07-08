#include "iostream"
#include "stdio.h"
#include "MNIST.h"
#include "stdlib.h"
using namespace std;

DWORD MNIST::reverse(DWORD &num) // 从文件里读取的数是倒着的，因此需要翻转一下
{
    int res = 0;
    for(int i=0; i<4; i++)
    {
        res = res << 8;
        unsigned char tc = num >> i*8; 
        res |= tc;
    }
    return num = res;
}

MNIST_Image::MNIST_Image(const char * const filepath)
{
    FILE *fp;
    fp=fopen(filepath,"rb");
    if(fp != NULL){
        fread(&magic_number,1,4,fp); reverse(magic_number);
        fread(&count,1,4,fp); reverse(count);
        fread(&rows,1,4,fp); reverse(rows);
        fread(&columns,1,4,fp); reverse(columns);
        for(int i=0; i<60000; i++)
        {
            BYTE arr_t[28][28];
            fread(&arr_t, 1, sizeof(BYTE)*28*28, fp);
            images[i] = new Image(arr_t);
        }
    }
    else cout <<"[error]: file open failed" <<endl;
    fclose(fp);
}

MNIST_Image::MNIST_Image(int count):rows(28), columns(28)
{
    this->count = count;
}

void MNIST_Image::printInfo()
{
    cout <<endl<<"magic_number: "<<magic_number<<endl;
    cout <<"count: "<<count<<endl;
    cout <<"rows: "<<rows<<endl;
    cout <<"columns: "<<columns<<endl;
}

void MNIST_Image::printData(int n)
{
    for(int i=0; i<28; i++)
    {
        printf("[");
        for(int j=0; j<28; j++)
        {
            printf("%3d", images[n]->a[i][j]+0);
            if(j!=27) printf(",");
            else printf("],\n");
        }
    }
}

MNIST_Label::MNIST_Label(const char * const filepath)
{
    FILE *fp;
    fp=fopen(filepath,"rb");
    if(fp != NULL)
    {
        fread(&magic_number,1,4,fp); reverse(magic_number);
        fread(&count,1,4,fp); reverse(count);
        for(int i=0; i<60000; i++)
        {
            BYTE item_t;
            fread(&item_t, 1, sizeof(BYTE), fp);
            labels[i] = item_t;
        }
    }
    else cout <<"[error]: file open failed" <<endl;
    fclose(fp);
}

MNIST_Label::MNIST_Label(int count)
{
    this->count = count;
}

void MNIST_Label::printData(int n)
{
    for(int i=0; i<n; i++)
        cout<<labels[i]+0<<endl;
}

void MNIST_Label::printInfo()
{
    cout <<endl<<"magic_number: "<<magic_number<<endl;
    cout <<"count: "<<count<<endl;
}

// int main()
// {
//     char filepath[100] = "E:\\train-images.idx3-ubyte";
//     MNIST_Image mnist("E:\\train-images.idx3-ubyte");
//     mnist.printInfo();
//     mnist.printData(1);
//     char filepath2[100] = "E:\\train-labels.idx1-ubyte";
//     MNIST_Label mlb(filepath2);
//     mlb.printInfo();
//     mlb.printData(5);
//     return 0;
// }