#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

#define MAXSIZE 10
#define ERROR -1

typedef int ElementType;
typedef int Position;
typedef struct LNode *List;

struct LNode {
    ElementType Data[MAXSIZE];
    Position Last;
};

// ========================================================
// 1. 初始化（挖空）
// 提示：用 malloc 申请结构体内存，将 Last 置为 -1，最后返回指针
// ========================================================
List MakeEmpty()
{
    List Ptrl;
	Ptrl=(List)malloc(sizeof(struct LNode));
	Ptrl->Last=-1;
	return Ptrl; 
}

// ========================================================
// 2. 查找（挖空）
// 提示：用 while 或 for 遍历，找到返回下标，找不到返回 ERROR
// ========================================================
Position Find( List L, ElementType X )
{
    ElementType ret=X;
    Position i=0;
    while(i<=L->Last&&L->Data[i]!=X)
    {
    	i++;
	}
	if(i>L->Last)
	{
		return ERROR;
	}
	else
	return i;
}

// ========================================================
// 3. 插入（挖空）
// 提示：检查表满（Last == MAXSIZE-1）和位置合法性（P<0 或 P>Last+1）
//       从后往前挪数据（i=Last 到 P），放入 X，Last++，返回 true
// ========================================================
bool Insert( List L, ElementType X, Position P )
{
    if(L->Last==MAXSIZE-1)
    {
    	printf("当前表已满，不能继续插入");
		return false; 
	}
	else if(P<0||P>L->Last+1)
	{
		printf("位置不合法，不能插入");
		return false;
	}
	else
	{
		for(int i=L->Last;i>=P;i--)
		{
			L->Data[i+1]=L->Data[i];
		}
		L->Data[P]=X;
		L->Last++;
		return true;
	}

}

// ========================================================
// 4. 删除（挖空）
// 提示：检查位置合法性（P<0 或 P>Last）
//       从前往后挪数据覆盖 P（i=P+1 到 Last），Last--，返回 true
// ========================================================
bool Delete( List L, Position P )
{
   if(P<0||P>L->Last+1)
   {
   	printf("位置不合法，不能删除");
   	return true;
	}
	else
	{
		for(int i=P+1;i<=L->Last;i++)
		{
			L->Data[i]=L->Data[i+1];
		}
		L->Last--;
		return true;
	 } 

}

// ========================================================
// 辅助打印函数
// ========================================================
void PrintList(List L) {
    printf("当前顺序表内容: ");
    if (L->Last == -1) {
        printf("[ 空 ]");
    }
    for (int i = 0; i <= L->Last; i++) {
        printf("%d ", L->Data[i]);
    }
    printf("\n(Last下标: %d, 当前元素个数: %d)\n\n", L->Last, L->Last + 1);
}

// ========================================================
// 主函数测试舞台
// ========================================================
int main()
{
    // 1. 测试初始化
    List L = MakeEmpty();
    printf("--- 1. 初始化表 ---\n");
    PrintList(L);

    // 2. 测试插入元素
    
    printf("--- 2. 测试插入元素 ---\n");
    Insert(L, 10, 0); 
    Insert(L, 30, 1); 
    Insert(L, 20, 1); 
    PrintList(L);
    

    // 3. 测试查找元素
    
    printf("--- 3. 测试查找元素 ---\n");
    Position pos = Find(L, 20);
    if(pos != ERROR) {
        printf("元素 20 的存储下标是: %d\n\n", pos);
    } else {
        printf("未找到元素 20\n\n");
    }
    

    // 4. 测试删除元素
    
    printf("--- 4. 测试删除元素 ---\n");
    printf("删除下标为 1 的元素...\n");
    Delete(L, 1); 
    PrintList(L);
    free(L);
    return 0;
}
