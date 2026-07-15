#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MaxSize 1000 
typedef int ElementType;
typedef int Position;

/* =======================================================
   1. 结构体定义挑战
   提示：里面需要有存数据的动态数组指针、栈顶位置、最大容量
   ======================================================= */
struct SNode {
    ElementType Data[MaxSize];
	Position Top; 
};
typedef struct SNode *Stack;


/* =======================================================
   2. 创建栈函数
   提示：需要 malloc 结构体本身，再 malloc 内部的 Data 数组
   ======================================================= */
Stack CreateStack()
{
    Stack Ptrl;
    Ptrl=(Stack)malloc(sizeof(struct SNode));
    Ptrl->Top=-1;
    return Ptrl;
    
}


/* =======================================================
   3. 判断栈满函数
   提示：比较当前 Top 和最大容量的关系
   ======================================================= */
bool IsFull( Stack S )
{
    if(S->Top==MaxSize-1)
    {
    	printf("栈满了");
    	return false;
	}
	else
	return true;
    
}


/* =======================================================
   4. 入栈函数
   提示：记得先检查是否满了；如果没满，“先腾地方，再放东西”
   ======================================================= */
bool Push( Stack S, ElementType X )
{
    bool t=IsFull(S);
    if(t)
    {
    	S->Data[++(S->Top)]=X;
		return true;
	}

}


/* =======================================================
   5. 判断栈空函数
   提示：看 Top 是否回到了初始的空位置
   ======================================================= */
bool IsEmpty( Stack S )
{
	if(S->Top==-1)
	{
		printf("栈空");
		return false;
	}
	else
	return true;
    
}


/* =======================================================
   6. 出栈函数 (Pop)
   提示：
   - 记得先检查是不是空栈！如果是空的，可以输出错误并返回一个错误标记（比如 ERROR，这里可以暂定返回 false 或特定值，或者函数返回类型设为 ElementType）
   - 如果不空，利用“先拿东西，再退位置”的逻辑，取出栈顶元素并返回。
   ======================================================= */
ElementType Pop( Stack S )
{
    bool t=IsEmpty(S);
    if(t)
    {
    	ElementType x;
    	x=S->Data[(S->Top)--];
    	return x;
	}
    
}
int main()
{
	Stack Ptrl=CreateStack();
	if(Ptrl!=NULL)
	{
		printf("栈创建成功，当前Top = %d\n\n",Ptrl->Top);
	}
	
	
	// 2. 测试栈空判断
    printf("--- 2. 测试栈空判断 ---\n");
    if (IsEmpty(Ptrl)) {
        printf("结果：栈当前为空（正确）\n\n");
    } else {
        printf("结果：栈当前非空（有Bug）\n\n");
    }
    
    
    // 3. 连续入栈，测试 Push 函数
    printf("--- 3. 开始连续入栈 (10, 20, 30) ---\n");
    Push(Ptrl, 10);
    Push(Ptrl, 20);
    Push(Ptrl, 30);
    printf("入栈后当前 Top = %d (预期应为 2)\n\n", Ptrl->Top);
    
    
    // 4. 测试出栈，测试 Pop 函数
    printf("--- 4. 开始出栈 ---\n");
    // 应该依次弹出 30, 20, 10（先进后出）
    printf("弹出元素: %d (预期: 30)\n", Pop(Ptrl));
    printf("弹出元素: %d (预期: 20)\n", Pop(Ptrl));
    printf("当前 Top = %d (预期应为 0)\n\n", Ptrl->Top);
	return 0;
}
