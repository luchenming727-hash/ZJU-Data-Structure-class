#include<stdio.h>
#include<stdlib.h>//这是使用malloc的头文件
#define MAXSIZE 10
typedef int ElementType;//定义ElementType的类型是什么

//创建结构体以及相对应的指针 
struct LNode{
	ElementType Data[MAXSIZE];
	int Last;//指向最后一个元素的下标 
}; 
typedef struct LNode* List;


//创建空的顺序表
List MakeEmpty()
{
	List PtrL;
	PtrL=(List)malloc(sizeof(struct LNode));
	//malloc 在堆区造了一个“匿名”柜子，并把地址给了 PtrL
	PtrL->Last = -1;
	return PtrL;
 } 

//查找，按照值找下标
 int Find(ElementType X, List PtrL)
 {
 	int i=0;
 	while(i<=PtrL->Last && PtrL->Data[i] != X)
 	i++;
 	if(i>PtrL->Last)
 	{
 		return -1;
	}
	else
	{
		return i;
	} 
 }
 
//插入
void Insert(ElementType X, int i, List PtrL)
{
    int j;
    if (PtrL->Last == MAXSIZE - 1) 
	{
        printf("表满\n");
        return;
    }
    if (i < 1 || i > PtrL->Last + 2) 
	{
        printf("位置不合法\n");
        return;
    }
    for (j = PtrL->Last; j >= i - 1; j--) 
	{
        PtrL->Data[j + 1] = PtrL->Data[j];
    }
    
    PtrL->Data[i - 1] = X; 
    PtrL->Last++; 
}

//删除 
void Delete(int i, List PtrL)
{
    int j;
    if (i < 1 || i > PtrL->Last + 1) {
        printf("不存在第 %d 个元素\n", i);
        return;
    }
    for (j = i; j <= PtrL->Last; j++) {
        PtrL->Data[j - 1] = PtrL->Data[j];
    }
    
    PtrL->Last--;
}
int main()
{
	List myTable = MakeEmpty();
	//创建一个myTable来接收这个顺序表的地址，方便后期调用
	Insert(10, 1, myTable);
	Insert(20, 2, myTable);
	Insert(30, 2, myTable);
	//先是20在第二个位置，然后我插入30把20向后移动
	printf("插入后：");
	for(int i=0;i<=myTable->Last;i++)
	{
		printf("%d\n",myTable->Data[i]);
	}
	
	//删除
	 
	Delete(2, myTable);
	
	printf("删除后: ");
	for(int i=0;i<=myTable->Last;i++)
	{
		printf("%d\n",myTable->Data[i]);
	}
	
	
	//查找
	 
	int x=Find(10,myTable);
    if(x==-1)
	{
		printf("此顺序表中无此数字"); 
	} 
	 else
	{
	 	printf("找到了，这个元素在第：%d个",x+1);
	}
	
	return 0;
}
 
