#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElementType;

/* =======================================================
   1. 结构体定义挑战
   提示：链式栈的结点需要存“当前数据”和“指向下一个结点的指针”
   ======================================================= */
struct Node {
    
    ElementType Data;
	struct Node* Next; 
    
};
typedef struct Node *PtrToNode;
typedef PtrToNode Stack; 
// 注意：在这里，Stack 类型其实就是一个指向结点的指针。
// 创建栈时，我们会创建一个头结点，用这个头结点来代表整个栈。


/* =======================================================
   2. 创建栈函数
   提示：malloc 一个头结点，并让它的 Next 指向 NULL，表示空栈
   ======================================================= */
Stack CreateStack()
{
	Stack Ptrl;
	Ptrl=(Stack)malloc(sizeof(struct Node));
	Ptrl->Next=NULL;
	return Ptrl;
	   
}


/* =======================================================
   3. 判断栈空函数
   提示：看头结点的 Next 是不是 NULL
   ======================================================= */
bool IsEmpty( Stack S )
{
    if(S->Next)
    {
    	printf("栈不是空的");
    	return false;
	}
	else
	return true;
    
}


/* =======================================================
   4. 入栈函数 (Push)
   提示：
   - 链式栈理论上不会满（除非内存爆了），所以不需要写 IsFull。
   - 步骤：1. malloc 一个新结点 2. 把数据填入新结点 3. 把新结点插到头结点后面
   ======================================================= */
bool Push( Stack S, ElementType X )
{
    Stack t;
    t=(Stack)malloc(sizeof(struct Node));
    t->Data=X;
    t->Next=S->Next;
    S->Next=t;
    return true;
    
}


/* =======================================================
   5. 出栈函数 (Pop)
   提示：
   - 1. 先检查是不是空栈！如果是空的，报错并返回错误标记（如 -1）。
   - 2. 如果不空，找到第一个有效结点（S->Next），暂存它里面的数据。
   - 3. 把这个结点从链表中“断开”并 free 掉，最后返回暂存的数据。
   ======================================================= */
ElementType Pop( Stack S )
{
  if(IsEmpty(S))
  {
  	printf("栈为空，无法出栈");
  	return -1;
  }
  Stack tmp;
  ElementType ans;
  tmp=S->Next;
  ans=tmp->Data;
  tmp->Next=S->Next;
  free(tmp);
  return ans;
    
}
int main()
{
    printf("=== 1. 开始创建链式栈 ===\n");
    Stack S = CreateStack();
    if (S != NULL) {
        printf("链式栈（头结点）创建成功！\n\n");
    }

    printf("=== 2. 测试初始栈空状态 ===\n");
    if (IsEmpty(S)) {
        printf("结果：栈当前为空（正确）\n\n");
    } else {
        printf("结果：栈当前非空（有Bug）\n\n");
    }

    printf("=== 3. 开始连续入栈 (100, 200, 300) ===\n");
    Push(S, 100);
    Push(S, 200);
    Push(S, 300);
    printf("入栈成功！\n\n");
    
    printf("=== 5. 开始连续出栈 ===\n");
    // 链式栈是后进先出，预期弹出顺序：300 -> 200 -> 100
    printf("弹出元素: %d (预期: 300)\n", Pop(S));
    printf("弹出元素: %d (预期: 200)\n", Pop(S));
    printf("弹出元素: %d (预期: 100)\n\n", Pop(S));
    
    free(S);
    printf("=== 测试结束，内存已安全释放 ===\n");
    return 0;
}
