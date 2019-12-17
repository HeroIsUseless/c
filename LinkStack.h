// 栈定义
typedef struct Stack
{
    char c[100];
    int n;  
} Stack;
// 压入一个元素
void push(Stack *stack, char c){
    stack->c[stack->n++] = c;
}
// 弹出一个元素
char pop(Stack *stack){
    return stack->c[--stack->n];
}
// 获取最上面的元素
char top(Stack *stack){
    return stack->c[stack->n-1];
}
// 获取最上面不是'('的元素
char top2(Stack *stack){
    int i=1;
    while (stack->c[stack->n-i] == '(') i++;
    return stack->c[stack->n-i];
}