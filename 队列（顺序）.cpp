#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MaxSize 10000
#define ERROR -1  /* 定义错误标志 */
typedef int ElementType;
typedef int Position;

/* 1. 声明循环队列结构体 */
struct QNode {
	ElementType Data[MaxSize];
	Position Rear,Front; 
    
};
typedef struct QNode *Queue;


/* 2. 创建队列 */
Queue CreateQueue(  )
{
    Queue Q;
    Q=(Queue)malloc(sizeof(struct QNode));
    Q->Front=0;
	Q->Rear=0;
    return Q;

}


/* 3. 判断队列是否已满 */
bool IsFull( Queue Q )
{
    if((Q->Rear+1)%MaxSize==Q->Front)
    {
    	printf("队列满");
    	return true;
	}
	return false;

}


/* 4. 入队操作 */
bool AddQ( Queue Q, ElementType X )
{
   bool t;
   t=IsFull(Q);
   if(t)
   {
   	printf("队列已满，不允许入队");
   	return false;
   }
   else
   {
   	Q->Rear=(Q->Rear+1)%MaxSize;
   	Q->Data[Q->Rear]=X;
   	return true;
   }

}


/* 5. 判断队列是否为空 */
bool IsEmpty( Queue Q )
{
	return((Q->Rear)%MaxSize==Q->Front);

}


/* 6. 出队操作 */
ElementType DeleteQ( Queue Q )
{
    bool t;
	t=IsEmpty(Q);
	if(t)
	{
		printf("队列为空，无法出队");
		return ERROR;
	 }
	 else
	 {
	 	Q->Front=(Q->Front+1)%MaxSize;
	 	return(Q->Data[Q->Front]);
	 }

}

int main() {
    // 1. 创建队列
    Queue Q = CreateQueue();
    printf("=== 1. 成功创建循环队列 ===\n");
    printf("队列当前容量 MaxSize: %d (实际可装载上限: %d)\n\n", MaxSize, MaxSize - 1);

    // 2. 测试空队列状态下的出队
    printf("=== 2. 测试空队列状态 ===\n");
    printf("当前队列是否为空？ %s\n", IsEmpty(Q) ? "【是】" : "【否】");
    printf("尝试在空队列时出队: ");
    ElementType temp = DeleteQ(Q); // 应该输出 "队列为空，无法出队"
    printf("\n\n");

    // 3. 测试入队，将队列塞满
    printf("=== 3. 往队列中连续写入数据直至装满 ===\n");
    printf("正在写入前 3 个测试数据...\n");
    AddQ(Q, 10);
    AddQ(Q, 20);
    AddQ(Q, 30);
    
    printf("正在快速写入剩余数据（直到填满上限 9999 个）...\n");
    // 从第 4 个元素开始写入，一直写到 9999 个
    for (int i = 4; i < MaxSize; i++) {
        AddQ(Q, i * 10); 
    }
    printf("写入完成！\n\n");

    // 4. 测试队列满状态下的入队
    printf("=== 4. 测试队列满状态 ===\n");
    printf("当前队列是否已满？ %s\n", IsFull(Q) ? "【是】" : "【否】");
    printf("尝试在队列已满时再次入队 [99999]: ");
    AddQ(Q, 99999); // 应该输出 "队列满" 和 "队列已满，不允许入队"
    printf("\n\n");

    // 5. 测试出队前几个元素
    printf("=== 5. 测试出队操作 ===\n");
    printf("出队元素 1 (预期 10): %d\n", DeleteQ(Q));
    printf("出队元素 2 (预期 20): %d\n", DeleteQ(Q));
    printf("出队元素 3 (预期 30): %d\n", DeleteQ(Q));
    printf("出队元素 4 (预期 40): %d\n", DeleteQ(Q));
    printf("当前队列是否还处于已满状态？ %s\n\n", IsFull(Q) ? "【是】" : "【否】");

    // 6. 测试循环写入特征
    printf("=== 6. 测试循环写入（此时队尾已能折返回数组头部） ===\n");
    printf("尝试重新入队 [888]: %s\n", AddQ(Q, 888) ? "成功" : "失败");
    printf("尝试重新入队 [999]: %s\n", AddQ(Q, 999) ? "成功" : "失败");
    printf("\n");

    // 7. 依次出队直到队列变空
    printf("=== 7. 依次出队直到清空 ===\n");
    int count = 0;
    while (!IsEmpty(Q)) {
        ElementType val = DeleteQ(Q);
        count++;
        // 仅打印前 3 个和最后 2 个出队的数据，避免屏幕被 9990+ 行输出刷屏
        if (count <= 3 || IsEmpty(Q)) {
            printf("第 %d 次出队，元素值为: %d\n", count, val);
        } else if (count == 4) {
            printf("... 中间省略 %d 个元素的出队展示 ...\n", MaxSize - 1 - 5);
        }
    }
    
    printf("\n当前队列是否为空？ %s\n", IsEmpty(Q) ? "【是】" : "【否】");
    printf("再次尝试出队: ");
    DeleteQ(Q); // 应该输出 "队列为空，无法出队"
    printf("\n");

    // 8. 释放内存 (这里千万不能 free(Q->Data)，只释放 Q 即可)
    free(Q);
    printf("\n=== 测试结束，内存安全释放，程序正常退出 ===\n");

    return 0;
}
