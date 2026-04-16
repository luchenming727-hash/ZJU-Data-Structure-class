#include<stdio.h>
#include<stdlib.h>
typedef struct LNode* PtrToNode;//创建链表指针 
typedef int ElementType;

//创建链表结构体 
struct LNode{
	ElementType Data;
	PtrToNode Next;
};
typedef PtrToNode List;

//按照下标进行查找 
List FindKth(int K,List PtrL)
{
	List p=PtrL;
	int j=1;
	while(p!=NULL&&j<K)
	{
		p=p->Next;
		j++;
	}
	if(j==K)
	{
		return p;
	}
	else
	return NULL;
}

//按照值进行查找 
List Find(int K,List PtrL)
{
	List p=PtrL;
	while(p)
	{
		if(p->Data==K)
		{
			return p;
		}
		p=p->Next;
	}
	return NULL;
}

//插入 
List Insert(int X,int i,List PtrL)
{
	List p,s;
	if(i==1)
	{
		s=(List)malloc(sizeof(struct LNode));//为新结点申请空间 
		s->Data=X;
		s->Next=PtrL;
		return s;
	}
	p=FindKth(i-1,PtrL);//查找这个位置是否合法 
	if(p==NULL)
	{
		printf("输入位置非法\n");
		return NULL; 
	}
	else
	{
		s=(List)malloc(sizeof(struct LNode));
		s->Data=X;
		s->Next=p->Next;
		p->Next=s;
		return PtrL;
	}
}

//删除 
List Delete(int i,List PtrL)
{
	List p,s;
	if(i==1)//如果删除第一个 
	{
		s=PtrL;
		if(PtrL!=NULL)
		{
			PtrL=PtrL->Next;
		}
		else
		{
			return NULL;
		}
		free(s);
		return PtrL;
	}
	p=FindKth(i-1,PtrL);
		if(p==NULL||p->Next==NULL) 
		//p是第i-1位，所以不仅需要保证他是有数据的
		//而且需要保证i后边也是有数据的
		//这样在删除i之后就可以让i-1和i+1连起来了 
		{
			printf("第%d个结点不存在\n",i);
			return NULL;
		}
		else
		{
			s=p->Next;
			p->Next=s->Next;
			free(s);
			return PtrL;
		}
}

//打印链表 
void PrintList(List PtrL)
{
	List p=PtrL;
	printf("当前链表内容：");
	while(p)
	{
		printf("%d->",p->Data);
		p=p->Next;
	}
	printf("NULL"); 
}

int main()
{
	List L=NULL; 
	L=Insert(10,1,L);
	L = Insert(20, 2, L);
	L = Insert(30, 1, L);
	PrintList(L);
	
	// 测试删除
    printf("\n删除第2个元素...\n");
    L = Delete(2, L); // 删掉 10
    PrintList(L);
	return 0;
 } 
