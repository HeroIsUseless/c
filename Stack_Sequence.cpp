#include <stdlib.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define TRUE 1
#define FALSE 0
#define OK 1
#define INFEASIBLE -1
#define OVERFLOW -2
//这个栈的特点是top不放元素，栈底呃
typedef int SElemType;
typedef int Status

class Stack
{
public:
    SElemType *base;
    SElemType *top;
    int elemcount;
    int stacksize;
public:
    void InitStack()
    {
        this.base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
        this.top = this.base;
        stacksize = STACK_INIT_SIZE;
        elemcount = 0;
    }
    void DestroyStack()
    {

    }
    void ClearStack()
    {

    }
    int isStackEmpty()
    {
        if(this.top == this.base)
            return TRUE;
        else
            return FALSE;
    }
    int StackLength()
    {

    }
    int GetTop()
    {
        if(this.top == this.base) return ERROR;
        e = *(this.top - 1);
        return OK;
    }
    Push(SElemType e)
    {
        if(this.top-this.base >= this.stacksize)
        {
            this.base = realloc(this.base, (this.stacksize + STACKINCREMENT) *sizeof(SElemType));
            this.top = this.base+this.stacksize;
            this.stacksize += STACKINCREMRNT;
        }
        this.top++ = e;
    }
    int Push(SElemType e)
    {
        if(this.top - this.base >= this.stacksize)
        {
            this.base = (SElemType*)realloc(this.base, this.stacksize + STACKINCREMENT) * sizeof(SElemType));
            if(!this.base) exit(OVERFLOW);
            this.top = this.base + this.stacksize;
            this.stacksize += STACKINCREMENT;
        }
        *this.top++ = e;
        return OK;
    }
    int Pop()//返回是否到达栈底
    {
        if(this.top == this.base) return ERROR;
        e = * --this.top;
        return OK;
    }
    StackTraverse(visit())//从栈底到栈顶一次对每个元素调用函数
    {

    }























};
