#include <stdio.h>
#include <stdlib.h>

#define MaxSize 5    // 为了方便观察“队满”情况，我们设为5
#define ERROR -1
typedef int ElementType;

struct QNode {
    ElementType Data[MaxSize];
    int front; // 头指针（下标）
    int rear;  // 尾指针（下标）
};
typedef struct QNode *Queue;

// 初始化
Queue CreateQueue() {
    Queue Q = (Queue)malloc(sizeof(struct QNode));
    Q->front = Q->rear = 0; // 初始都在0
    return Q;
}

// 入队
void AddQ(Queue Q, ElementType item) {
    if ((Q->rear + 1) % MaxSize == Q->front) {
        printf("队列已满，%d 无法入队\n", item);
        return;
    }
    Q->rear = (Q->rear + 1) % MaxSize;
    Q->Data[Q->rear] = item;
}

// 出队
ElementType DeleteQ(Queue Q) {
    if (Q->front == Q->rear) {
        printf("队列已空\n");
        return ERROR;
    }
    Q->front = (Q->front + 1) % MaxSize;
    return Q->Data[Q->front];
}

// 打印队列（从队头到队尾）
void PrintQueue(Queue Q) {
    if (Q->front == Q->rear) return;
    int i = (Q->front + 1) % MaxSize;
    printf("当前队列内容: ");
    while (1) {
        printf("%d ", Q->Data[i]);
        if (i == Q->rear) break;
        i = (i + 1) % MaxSize;
    }
    printf("\n");
}

int main() {
    Queue Q = CreateQueue();
    AddQ(Q, 10); AddQ(Q, 20); AddQ(Q, 30); AddQ(Q, 40);
    PrintQueue(Q);
    printf("出队元素: %d\n", DeleteQ(Q));
    PrintQueue(Q);
    AddQ(Q, 50); // 此时会利用循环特性
    PrintQueue(Q);
    return 0;
}
