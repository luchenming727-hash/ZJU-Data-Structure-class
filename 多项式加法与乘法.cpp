#include <stdio.h>
#include <stdlib.h>

/* --- 1. 结构体与类型定义 --- */
typedef struct PolyNode *Polynomial;
struct PolyNode {
    int coef;    // 系数
    int expon;   // 指数
    Polynomial link;
};

/* --- 2. 核心辅助函数：Attach --- */
/* 将新项连接到当前结果链表的尾部 */
void Attach(int c, int e, Polynomial *pRear) {
    Polynomial P = (Polynomial)malloc(sizeof(struct PolyNode));
    P->coef = c;
    P->expon = e;
    P->link = NULL;
    (*pRear)->link = P; // 将新节点焊接到老尾巴上
    *pRear = P;         // 更新尾巴指针
}

/* --- 3. 多项式读取函数 --- */
Polynomial ReadPoly() {
    Polynomial P, Rear, temp;
    int c, e, N;

    if (scanf("%d", &N) != 1) return NULL;
    
    P = (Polynomial)malloc(sizeof(struct PolyNode)); // 哨兵位
    P->link = NULL;
    Rear = P;

    while (N--) {
        scanf("%d %d", &c, &e);
        if (c != 0) Attach(c, e, &Rear); // 只处理系数不为0的项
    }

    temp = P; P = P->link; free(temp); // 过河拆桥，删除哨兵
    return P;
}

/* --- 4. 多项式加法函数 --- */
Polynomial Add(Polynomial P1, Polynomial P2) {
    Polynomial front, rear, temp;
    int sum;

    rear = (Polynomial)malloc(sizeof(struct PolyNode));
    front = rear;

    while (P1 && P2) {
        if (P1->expon > P2->expon) {
            Attach(P1->coef, P1->expon, &rear);
            P1 = P1->link;
        } else if (P1->expon < P2->expon) {
            Attach(P2->coef, P2->expon, &rear);
            P2 = P2->link;
        } else {
            sum = P1->coef + P2->coef;
            if (sum) Attach(sum, P1->expon, &rear);
            P1 = P1->link;
            P2 = P2->link;
        }
    }
    for (; P1; P1 = P1->link) Attach(P1->coef, P1->expon, &rear);
    for (; P2; P2 = P2->link) Attach(P2->coef, P2->expon, &rear);

    rear->link = NULL;
    temp = front; front = front->link; free(temp);
    return front;
}

/* --- 5. 多项式乘法函数 (侦察兵逻辑) --- */
Polynomial Mult(Polynomial P1, Polynomial P2) {
    Polynomial P, t1, t2, Rear, temp;
    int c, e;

    if (!P1 || !P2) return NULL;

    t1 = P1; t2 = P2;
    P = (Polynomial)malloc(sizeof(struct PolyNode)); 
    P->link = NULL;
    Rear = P;

    // 先建立初始结果链表 (P1的第一项 * P2的所有项)
    while (t2) {
        Attach(t1->coef * t2->coef, t1->expon + t2->expon, &Rear);
        t2 = t2->link;
    }
    t1 = t1->link;

    // 开始逐项相乘并实时有序插入
    while (t1) {
        t2 = P2; Rear = P;
        while (t2) {
            e = t1->expon + t2->expon;
            c = t1->coef * t2->coef;

            // 侦察兵找位置：确保 Rear 停在插入点的前一个位置
            while (Rear->link && Rear->link->expon > e)
                Rear = Rear->link;

            if (Rear->link && Rear->link->expon == e) {
                if (Rear->link->coef + c != 0) {
                    Rear->link->coef += c;
                } else {
                    temp = Rear->link;
                    Rear->link = temp->link; // 旁路跳跃
                    free(temp); // 内存回收
                }
            } else {
                temp = (Polynomial)malloc(sizeof(struct PolyNode));
                temp->coef = c; temp->expon = e;
                temp->link = Rear->link;
                Rear->link = temp; // 插入新项
                Rear = Rear->link;
            }
            t2 = t2->link;
        }
        t1 = t1->link;
    }

    temp = P; P = P->link; free(temp);
    return P;
}

/* --- 6. 多项式打印函数 --- */
void PrintPoly(Polynomial P) {
    int flag = 0;
    if (!P) { printf("0 0\n"); return; }
    while (P) {
        if (!flag) flag = 1;
        else printf(" ");
        printf("%d %d", P->coef, P->expon);
        P = P->link;
    }
    printf("\n");
}

/* --- 7. 测试主函数 --- */
int main() {
    Polynomial P1, P2, PP, PS;

    printf("请输入多项式 P1 (格式: 项数 系数1 指数1 ...):\n");
    P1 = ReadPoly();
    printf("请输入多项式 P2 (格式: 项数 系数1 指数1 ...):\n");
    P2 = ReadPoly();

    printf("\n--- 计算结果 ---\n");
    PP = Mult(P1, P2);
    printf("乘法结果: ");
    PrintPoly(PP);

    PS = Add(P1, P2);
    printf("加法结果: ");
    PrintPoly(PS);

    return 0;
}

/*
 * 测试数据推荐：
 * P1: 4 3 4 -5 2  6 1  -2 0  (表示 3x^4 - 5x^2 + 6x - 2)
 * P2: 3 5 20  -7 4  3 1     (表示 5x^20 - 7x^4 + 3x)
 */
