#include <stdio.h>
//k阶斐波那契数列
//输入两个数，返回一个数
int Fibonacci(int k, int m)
{
    return fibonacci_recursive(m-k+2);
}
int fibonacci_recursive(int m)
{
    if(m <= 0) return 0;
    if(m == 1) return 1;
    return fibonacci_recursive(m-2) + fibonacci_recursive(m-1);
}
int fibonacci_iteration(int n)//这个是迭代的方法
{
    int i;
    int num = 0;
    int fib_minusone = 1;
    int fib_minustwo = 0;
    if(n <= 0) return 0;
    if(n == 1) return 1;
    for(i=2; i<=n; i++)
    {
        num = fib_minusone + fib_minustwo;
        fib_minustwo = fib_minusone;
        fib_minusone = num;
    }
    return num;
}
int main()
{
    int i;
    scanf("%d", &i);
    printf("%d %d", fibonacci_iteration(i), fibonacci_recursive(i));

    return 0;
}

