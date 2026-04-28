#include <stdio.h>
#include <stdlib.h>
#define MaxSize 1000
#define ElementType int
#define ERROR -1

// 结构体定义
typedef struct SNode *Stack;
struct SNode {
    ElementType Data[MaxSize];
    int Top;
};

// 建立空栈
Stack CreateStack() {
    Stack S = (Stack)malloc(sizeof(struct SNode));
    S->Top = -1;
    return S;
}

// 入栈操作
void Push(Stack S, ElementType item) {
    if (S->Top == MaxSize - 1) {
        printf("堆栈满\n");
    } else {
        S->Data[++(S->Top)] = item;
        printf("入栈成功: %d\n", item);
    }
}

// 出栈操作
ElementType Pop(Stack S) {
    if (S->Top == -1) {
        printf("堆栈空\n");
        return ERROR;
    } else {
        return S->Data[(S->Top)--];
    }
}

// 主函数测试
int main() {
    Stack myStack = CreateStack();

    printf("--- 顺序栈测试 ---\n");
    Push(myStack, 10);
    Push(myStack, 20);
    Push(myStack, 30);

    printf("出栈元素: %d\n", Pop(myStack)); // 应该是 30
    printf("出栈元素: %d\n", Pop(myStack)); // 应该是 20
    printf("出栈元素: %d\n", Pop(myStack)); // 应该是 10

    free(myStack); // 养成好习惯，释放内存
    return 0;
}
