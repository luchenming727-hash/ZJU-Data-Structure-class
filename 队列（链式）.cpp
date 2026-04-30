#include <stdio.h>
#include <stdlib.h>

#define ERROR -1
typedef int ElementType;

struct Node {
    ElementType Data;
    struct Node *Next;
};

struct QNode {
    struct Node *front;
    struct Node *rear;
};
typedef struct QNode *Queue;

// 初始化
Queue CreateQueue() {
    Queue Q = (Queue)malloc(sizeof(struct QNode));
    Q->front = Q->rear = NULL;
    return Q;
}

// 入队
void AddQ(Queue Q, ElementType item) {
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->Data = item;
    temp->Next = NULL;

    if (Q->front == NULL) { // 第一次入队
        Q->front = Q->rear = temp;
    } else {
        Q->rear->Next = temp; // 先拉手
        Q->rear = temp;       // 后换位
    }
}

// 出队
ElementType DeleteQ(Queue Q) {
    if (Q->front == NULL) {
        printf("队列已空\n");
        return ERROR;
    }
    struct Node *FrontCell = Q->front;
    ElementType item = FrontCell->Data;

    if (Q->front == Q->rear) { // 只有最后一个元素了
        Q->front = Q->rear = NULL;
    } else {
        Q->front = Q->front->Next;
    }
    free(FrontCell);
    return item;
}

// 打印队列
void PrintQueue(Queue Q) {
    struct Node *curr = Q->front;
    if (!curr) { printf("队列为空\n"); return; }
    printf("当前链式队列内容: ");
    while (curr) {
        printf("%d ", curr->Data);
        curr = curr->Next;
    }
    printf("\n");
}

int main() {
    Queue Q = CreateQueue();
    AddQ(Q, 100); AddQ(Q, 200); AddQ(Q, 300);
    PrintQueue(Q);
    printf("出队元素: %d\n", DeleteQ(Q));
    PrintQueue(Q);
    return 0;
}
