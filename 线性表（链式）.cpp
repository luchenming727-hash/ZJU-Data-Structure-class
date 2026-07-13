#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ERROR NULL 

typedef int ElementType;
typedef struct LNode *PtrToLNode;
struct LNode {
    ElementType Data;
    PtrToLNode Next;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;

// ========================================================
// 1. 初始化：创建一个带头结点的空链表
// ========================================================
List MakeEmpty() {
   List p;
   p=(List)malloc(sizeof(struct LNode));
   p->Next=NULL;
   return p; 
}

// ========================================================
// 2. 查找（挖空）
// 提示：让一个指针 p 从 L->Next 开始，只要 p 不为空且没找到 X，就一直 p = p->Next
// ========================================================
Position Find( List L, ElementType X )
{
   List p;
   p=L->Next;
   while(p&&p->Data!=X)
   {
   	p=p->Next;
   }
   return p;
   
}

// ========================================================
// 3. 插入（带头结点）
// 提示：先找 P 的前一个节点 pre。如果找到了，malloc 一个 tmp 节点，
//       改改指针修改牵手关系：tmp->Next = P; pre->Next = tmp;
// ========================================================
bool Insert( List L, ElementType X, Position P )
{
   List pre;
	pre=L;
   while(pre)
   {
   	if(pre->Next==P)
   	{
   		List tmp;
		tmp=(List)malloc(sizeof(struct LNode));
		tmp->Data=X;
   		tmp->Next=pre->Next;
   		pre->Next=tmp;
   		return true;
	}
	pre=pre->Next;
   }
   printf("插入位置参数错误\n"); 
   return false;
   
}

// ========================================================
// 4. 删除（带头结点）
// 提示：先找 P 的前一个节点 pre。如果 pre 和 P 都合法，
//       让 pre->Next 跳过 P 指向 P->Next，最后千万别忘了 free(P)！
// ========================================================
bool Delete( List L, Position P )
{
   List pre;
   pre=L;
   while(pre)
   {
   	if(pre->Next==P)
   	{
   		pre->Next=P->Next;
		free(P); 
		return true;   
	}
	pre=pre->Next;
   }
   printf("删除位置错误\n");
   return false;
}
// ========================================================
// 5. 按位置查找
// 参数：K 代表要找第几个节点（1代表第一个有效数据节点，2代表第二个...）
// 返回值：找到的节点指针 Position，找不到则返回 NULL
// ========================================================
Position FindKth( List L, int K )
{
    // 检查不合法的位置，比如我想找第 -1 个或者第 0 个节点（头结点不算有效数据）
    if (K < 1) {
        return NULL;
    }
    else
	{
		List p;
		p=L->Next;
		int i=1;
		while(p!=0&&i<K)
		{
			p=p->Next;
			i++;
		}
		if(p==NULL)
		{
			printf("越界，无法查询\n");
		}
		return p;
	 } 

}


// ========================================================
// 辅助打印函数
// ========================================================
void PrintList(List L) {
    Position p = L->Next; // 跳过不存数据的头结点
    printf("当前链表内容: ");
    if (p == NULL) {
        printf("[ 空 ]");
    }
    while (p != NULL) {
        printf("%d -> ", p->Data);
        p = p->Next;
    }
    printf("NULL\n\n");
}

// ========================================================
// 主函数测试舞台
// ========================================================
int main()
{
    // 1. 初始化带头结点的空链表
    List L = MakeEmpty();
    printf("--- 1. 初始化链表 ---\n");
    PrintList(L);

    // 2. 测试插入（因为是找位置指针，我们先在“末尾NULL”前面插，相当于头插/尾插）
    // 写完 Insert 后，可以逐步取消下面的注释进行测试
    
    printf("--- 2. 测试插入元素 ---\n");
    Insert(L, 10, L->Next); // 在空链表末尾插入 10
    Insert(L, 30, L->Next); // 在 10 前面插入 30
    PrintList(L);          // 预期：30 -> 10 -> NULL
    

    // 3. 测试查找
    
    printf("--- 3. 测试查找元素 ---\n");
    Position pos = Find(L, 10);
    if (pos != ERROR) {
        printf("找到元素 10，它存在于地址: %p，值是: %d\n\n", pos, pos->Data);
    } else {
        printf("未找到元素 10\n\n");
    }
    

    // 4. 测试删除
    
    printf("--- 4. 测试删除元素 ---\n");
    if (pos != ERROR) {
        printf("删除刚刚找到的节点 10...\n");
        Delete(L, pos);
        PrintList(L);      // 预期：30 -> NULL
    }
    // 5. 测试按位置查找
    
    printf("--- 5. 测试按位置查找 ---\n");
    // 假设现在链表里有数据：30 -> 10 -> NULL
    Position posK = FindKth(L, 1); // 查找第 1 个节点
    if (posK != NULL) {
        printf("链表中第 1 个节点的值是: %d (预期是 30)\n", posK->Data);
    } else {
        printf("未找到第 1 个节点\n");
    }

    posK = FindKth(L, 5); // 查找第 5 个节点（故意越界）
    if (posK == NULL) {
        printf("查找第 5 个节点返回 NULL (验证通过！)\n\n");
    }
    
    
    return 0;
}
