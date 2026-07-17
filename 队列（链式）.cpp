#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ERROR -1  /* 定义错误标志 */
typedef int ElementType;

/* ========================================================
   1. 结构体声明
   ======================================================== */

/* 1.1 声明链表节点结构 */
struct Node {
    ElementType Data;
    struct Node *next;
    
};
typedef struct Node *PtrToNode;


/* 1.2 声明队列控制结构（包含头尾指针） */
struct QNode {
    struct Node *rear;
     struct Node *front;
    
};
typedef struct QNode *Queue;



/* ========================================================
   2. 队列核心操作函数
   ======================================================== */

/* 2.1 创建空队列 */
Queue CreateQueue()
{
    Queue Q=(Queue)malloc(sizeof(struct QNode));
    PtrToNode head=(PtrToNode)malloc(sizeof(struct Node));
    head->next=NULL;
    Q->front=head;
    Q->rear=head;
    return Q;

}


/* 2.2 判断队列是否为空 */
bool IsEmpty( Queue Q )
{
	return (Q->front==Q->rear);

}


/* 2.3 入队操作 */
bool AddQ( Queue Q, ElementType X )
{
   
    	PtrToNode Ptrl=(PtrToNode)malloc(sizeof(struct Node));
    	Ptrl->Data=X;
    	Ptrl->next=NULL;
    	Q->rear->next=Ptrl;
    	Q->rear=Ptrl;
    	return true;
}


/* 2.4 出队操作 */
ElementType DeleteQ( Queue Q )
{
   if(IsEmpty(Q))
   {
   	printf("队列为空，无法出队\n");
   	return ERROR;
   }
   else
   {
   	ElementType ans;
   	PtrToNode pre;
	pre=Q->front->next;
	ans=pre->Data;
	Q->front->next=pre->next;
	if(Q->rear==pre)
	{
		Q->rear=Q->front;
	}
	free(pre);
	return ans;
   }

}

int main() 
{
    // 1. 初始化队列
    Queue Q = CreateQueue();
    printf("=== 1. 成功创建带头结点的链式队列 ===\n\n");

    // 2. 测试空队列状态下的出队
    printf("=== 2. 测试空队列状态 ===\n");
    printf("当前队列是否为空？ %s\n", IsEmpty(Q) ? "【是】" : "【否】");
    printf("尝试在空队列时出队: ");
    DeleteQ(Q); // 应该输出 "队列为空，无法出队"
    printf("\n");

    // 3. 正常入队测试
    printf("=== 3. 元素入队 ===\n");
    printf("尝试入队 [10]: %s\n", AddQ(Q, 10) ? "成功" : "失败");
    printf("尝试入队 [20]: %s\n", AddQ(Q, 20) ? "成功" : "失败");
    printf("尝试入队 [30]: %s\n", AddQ(Q, 30) ? "成功" : "失败");
    printf("当前队列是否为空？ %s\n\n", IsEmpty(Q) ? "【是】" : "【否】");

    // 4. 正常出队测试
    printf("=== 4. 元素出队 ===\n");
    printf("出队元素 (预期 10): %d\n", DeleteQ(Q));
    printf("出队元素 (预期 20): %d\n\n", DeleteQ(Q));

    // 5. 测试单元素出队的极限情况（此时队内仅剩 30）
    printf("=== 5. 测试最后一个元素出队 ===\n");
    printf("出队元素 (预期 30): %d\n", DeleteQ(Q));
    printf("最后一个元素出队后，当前队列是否为空？ %s\n\n", IsEmpty(Q) ? "【是】" : "【否】");

    // 6. 再次入队出队（验证清空后，由于 rear 正确指回了头结点，队列依然完全可用）
    printf("=== 6. 验证队列清空后的复用性 ===\n");
    printf("重新入队 [100]: %s\n", AddQ(Q, 100) ? "成功" : "失败");
    printf("重新入队 [200]: %s\n", AddQ(Q, 200) ? "成功" : "失败");
    printf("出队元素 (预期 100): %d\n", DeleteQ(Q));
    printf("出队元素 (预期 200): %d\n", DeleteQ(Q));
    printf("当前队列是否为空？ %s\n\n", IsEmpty(Q) ? "【是】" : "【否】");

    // 7. 彻底释放内存
    // 此时队列为空，Q->front 指向“头节点”。需要先把这个头结点释放掉，再释放 Q 本身。
    free(Q->front); 
    free(Q);
    printf("=== 测试结束，内存安全释放，程序正常退出 ===\n");

    return 0;
}
