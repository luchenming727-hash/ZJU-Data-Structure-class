#include <stdio.h>

#define MaxTree 10
#define ElementType char
#define Tree int
#define Null -1

/* 1. 定义静态链表结构 */
struct TreeNode {
    ElementType Element;
    Tree Left;
    Tree Right;
} T1[MaxTree], T2[MaxTree];

/* 2. 建树函数：返回根节点的下标 */
Tree BuildTree(struct TreeNode T[]) {
    int N, i;
    int check[MaxTree];
    char cl, cr;
    Tree Root = Null;

    if (scanf("%d\n", &N) && N > 0) {
        for (i = 0; i < N; i++) check[i] = 0;
        for (i = 0; i < N; i++) {
            scanf(" %c %c %c", &T[i].Element, &cl, &cr);
            
            // 处理左孩子
            if (cl != '-') {
                T[i].Left = cl - '0';
                check[T[i].Left] = 1;
            } else T[i].Left = Null;

            // 处理右孩子
            if (cr != '-') {
                T[i].Right = cr - '0';
                check[T[i].Right] = 1;
            } else T[i].Right = Null;
        }

        // 排除法找根节点：check依然为0的就是根
        for (i = 0; i < N; i++)
            if (!check[i]) break;
        Root = i;
    }
    return Root;
}

/* 3. 同构判别函数 */
int Isomorphic(Tree R1, Tree R2) {
    if ((R1 == Null) && (R2 == Null)) return 1; /* 都是空树 */
    if (((R1 == Null) && (R2 != Null)) || ((R1 != Null) && (R2 == Null))) return 0; /* 一空一不空 */
    if (T1[R1].Element != T2[R2].Element) return 0; /* 根节点数据不同 */

    // 如果左边都为空，直接比右边
    if ((T1[R1].Left == Null) && (T2[R2].Left == Null))
        return Isomorphic(T1[R1].Right, T2[R2].Right);

    // 如果左子树存在且数据一样，不需要交换
    if (((T1[R1].Left != Null) && (T2[R2].Left != Null)) &&
        (T1[T1[R1].Left].Element == T2[T2[R2].Left].Element))
        return (Isomorphic(T1[R1].Left, T2[R2].Left) &&
                Isomorphic(T1[R1].Right, T2[R2].Right));
    
    // 否则，尝试交换左右子树进行交叉对比
    else
        return (Isomorphic(T1[R1].Left, T2[R2].Right) &&
                Isomorphic(T1[R1].Right, T2[R2].Left));
}

int main() {
    Tree R1, R2;

    R1 = BuildTree(T1);
    R2 = BuildTree(T2);

    if (Isomorphic(R1, R2)) printf("Yes\n");
    else printf("No\n");

    return 0;
}
