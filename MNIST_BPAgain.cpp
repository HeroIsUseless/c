#include "iostream"
#include "stdlib.h"
#include "math.h"
#include <time.h>
#include "MNIST.h"
#include "MNIST.cpp"
using namespace std;
#define HIDDEN_NODE_COUNT 100
int flag = 0; // 一个测试变量
class InputLayer
{
public:
    double a[784];
};

class HiddenLayer
{
public:
    double w[HIDDEN_NODE_COUNT][784];
    double b[HIDDEN_NODE_COUNT];
    double a[HIDDEN_NODE_COUNT];
    double z[HIDDEN_NODE_COUNT];

    void active()
    {
        for(int i=0; i<HIDDEN_NODE_COUNT; i++){
           a[i] = 1/(1+exp((-1)*z[i]));
        }    
    }
};

class OutputLayer
{
public:
    double w[10][HIDDEN_NODE_COUNT];
    double b[10];
    double a[10];
    double z[10];
    double q[10];

    void active()
    {
        for(int i=0; i<10; i++){
            a[i] = 1/(1+exp((-1)*z[i]));
        }
    }
};

class MNIST_BP
{
    double a; // 学习率
    double e; // 误差精度
    InputLayer input_layer;
    HiddenLayer hidden_layer;
    OutputLayer output_layer; 

public:
    // 初始化函数
    MNIST_BP(double a, double e) : a(a), e(e)
    {
        srand(time(NULL)); // 设定随机函数
        // 隐含层初始化
        for(int i =0; i<HIDDEN_NODE_COUNT; i++)
        {
            for(int j=0; j<784; j++)
            {
                hidden_layer.w[i][j] = (rand()%14) * 0.001;
            }
            hidden_layer.b[i] = 0.0;
            hidden_layer.z[i] = 0.0;
        }
        // 输出层初始化
        for(int i=0; i<10; i++)
        {
            for(int j=0; j<HIDDEN_NODE_COUNT; j++)
            {
                output_layer.w[i][j] =  (rand()%10) * 0.001;
            }
            output_layer.b[i] = 0.0;
            output_layer.z[i] = 0.0;
        }
    }
    // 训练函数
    void train(MNIST_Image &mn_img, MNIST_Label &mn_lab)
    {
        double e_t = 1; // 临时误差变量
        int step = 0; // 循环控制变量
        //while (e_t > e)
        while (1)
        {
            e_t = 0;
            for (int i = 0; i < 100; i++) // 随机挑出100个
            {
                int j = rand() % 60000;
                forward(*(mn_img.images[j]));
                e_t += backward(mn_lab.labels[j]);
            }
            e_t /= 100;
            step++;
            if (step > 10000)
                break;
            cout <<endl<<"[train] step:"<<(double)step/100<<"%"<<"    "<<"loss:"<<e_t<<endl;
        }
    }
    // 单个样本的前向算法
    int forward(Image &img)
    {
        // 输入层的初始化，二维转一维
        for (int i = 0; i < 28; i++) 
        {
            for (int j = 0; j < 28; j++)
            {
                input_layer.a[i * 28 + j] = (double)img.a[i][j]/255.0;
            }
        }
        // 隐含层初始化
        for(int i=0; i<HIDDEN_NODE_COUNT; i++)
        {
            hidden_layer.z[i] = 0;
        }
        // 输出层初始化
        for(int i=0; i<10; i++)
        {
            output_layer.z[i] = 0;
        }
        // 输入层到隐含层的传播
        for (int i = 0; i < HIDDEN_NODE_COUNT; i++) // 对于一个隐含层的每一个神经单元
        {                                
            for (int j = 0; j < 784; j++) // 进行加权加偏移
            {
                hidden_layer.z[i] += hidden_layer.w[i][j] * input_layer.a[j];
            }
            hidden_layer.z[i] += hidden_layer.b[i];
        }
        hidden_layer.active();
        // 隐含层到输出层的传播
        for (int i = 0; i < 10; i++) // 对于输出层的每一个神经单元
        {                                              
            for (int j = 0; j < HIDDEN_NODE_COUNT; j++) // 进行加权加偏移
            {
                output_layer.z[i] += output_layer.w[i][j] * hidden_layer.a[j];
            }
            output_layer.z[i] += output_layer.b[i];
        }
        output_layer.active();
        return result(output_layer.a);
    }
    int result(double *a)
    {
        int res = 0;
        double max = -1;
        for (int i = 0; i < 10; i++)
        {
            if (max < a[i])
            {
                max = a[i];
                res = i;
            }
        }
        return res;
    }
    double* anti_result(int label)
    {
        double *res = new double[10];
        for (int i = 0; i < 10; i++)
        {
            if (i == label)
                res[i] = 1;
            else
                res[i] = 0;
        }
        return res;
    }
    // 单个样本的后向算法
    double backward(int label)
    {
        double *a = anti_result(label);
        //  先计算输出层误差
        for(int i=0; i<10; i++)
        {
            output_layer.q[i] = (-1)*(a[i] - output_layer.a[i])*de_active(output_layer.a[i]);
        }
        // 输出层到隐含层
        for(int i=0; i<10; i++) // 对于每个神经元
        {
            for(int j=0; j<HIDDEN_NODE_COUNT; j++) // 对于每个权重值
            {
                double h = hidden_layer.a[j];
                output_layer.w[i][j] -= this->a * output_layer.q[i]*h;
            }
            output_layer.b[i] -= this->a * output_layer.q[i];
        }
        // 隐含层到输入层
        for(int i=0; i<HIDDEN_NODE_COUNT; i++) // 对于每个神经元
        {
            double q = 0;
            for(int k=0; k<10; k++)
            {
                q += output_layer.q[k] * 
                    output_layer.w[k][i] * 
                    de_active(hidden_layer.a[i]);
            } 
            for(int j=0; j<784; j++) // 对于每个权重值
            {
                double h = input_layer.a[j];
                hidden_layer.w[i][j] -= this->a * q*h;
            }
            hidden_layer.b[i] -= this->a * q;
        }
        double res = cost(a);
        return res;
    }
    double de_active(double a)
    {
        return a*(1-a);
    }
    // 单个误差函数
    double cost(double a[])
    {
        double res = 0;
        for(int i=0; i<10; i++)
        {
            res += (pow((a[i]-output_layer.a[i]), 2) * 0.5);
        }
        delete[] a;
        return res;
    }
    // 测试函数
    double test(MNIST_Image &mn_img, MNIST_Label &mn_lab)
    {
        double match = 0;
        double loss = 0;
        for (int i = 0; i < mn_img.count; i++)
        {
            int lab = forward(*(mn_img.images[i]));
            if(lab == mn_lab.labels[i]){
                match += 1; // 这里是识别率，因此要这么算
            }
        }
        return match/mn_lab.count * 100;
    }
};

int main()
{
    MNIST_Image mntrain_img("E:\\train-images.idx3-ubyte");
    MNIST_Label mntrain_lab("E:\\train-labels.idx1-ubyte");
    MNIST_Image mntest_img("E:\\t10k-images.idx3-ubyte");
    MNIST_Label mntest_lab("E:\\t10k-labels.idx1-ubyte");
    MNIST_BP mn_bp(0.1, 0.0000000001);                       // 设定学习率和误差精度
    mn_bp.train(mntrain_img, mntrain_lab);           // 进行训练
    double res = mn_bp.test(mntest_img, mntest_lab); // 进行测试
    cout <<endl<< "[main] correct: " << res <<"%"<< endl;
    return 0;
}
