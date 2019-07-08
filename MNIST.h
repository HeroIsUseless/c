#ifndef MNIST_H
#define MNIST_H

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;

struct Image
{
    BYTE a[28][28]; // 存储像素的数组(0~255)
    Image(BYTE a[28][28])
    {
        for(int i=0; i<28; i++)
            for(int j=0; j<28; j++)
                this->a[i][j] = a[i][j];
    }
};

class MNIST
{
protected:
    DWORD magic_number;
public:
    DWORD count;
protected:
    DWORD reverse(DWORD &num); // 从文件里读取的数是倒着的，因此需要翻转一下
public:
    void virtual printInfo()=0;
    void virtual printData(int n=0)=0;
};

class MNIST_Image: public MNIST
{
public:
    Image* images[60000];
    DWORD rows;
    DWORD columns;
public:
    MNIST_Image(const char * const filepath);
    MNIST_Image(int count);
    void printInfo();
    void printData(int n=0);
};

class MNIST_Label: public MNIST
{
public:
    BYTE labels[60000];
public:
    MNIST_Label(const char * const filepath);
    MNIST_Label(int count);
    void printData(int n=0);
    void printInfo();
};
#endif