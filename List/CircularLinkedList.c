/********************************************************************************************************
*
*
* 设计单向循环链表的接口
*
* 
*
* Copyright (c)  2023-2024   cececlmx@126.com   All right Reserved
* ******************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


//指的是单向循环链表中的结点有效数据类型，用户可以根据需要进行修改
typedef int  DataType_t;

//构造单向循环链表的结点,链表中所有结点的数据类型应该是相同的
typedef struct CircularLinkedList
{
	DataType_t  		 data; //结点的数据域
	struct CircularLinkedList	*next; //结点的指针域

}CircLList_t;


//创建一个空单向循环链表，空链表应该有一个头结点，对链表进行初始化
CircLList_t * CircLList_Create(void)
{
	//1.创建一个头结点并对头结点申请内存
	CircLList_t *Head = (CircLList_t *)calloc(1,sizeof(CircLList_t));
	if (NULL == Head)
	{
		perror("Calloc memory for Head is Failed");
		exit(-1);
	}

	//2.对头结点进行初始化，头结点是不存储数据域，指针域指向自身，体现“循环”思想
	Head->next = Head;

	//3.把头结点的地址返回即可
	return Head;
}

//创建新的结点，并对新结点进行初始化（数据域 + 指针域）
CircLList_t * CircLList_NewNode(DataType_t data)
{
	//1.创建一个新结点并对新结点申请内存
	CircLList_t *New = (CircLList_t *)calloc(1,sizeof(CircLList_t));
	if (NULL == New)
	{
		perror("Calloc memory for NewNode is Failed");
		return NULL;
	}

	//2.对新结点的数据域和指针域进行初始化
	New->data = data;
	New->next = NULL;

	return New;
}

//头插
bool CircLList_HeadInsert(CircLList_t *Head,DataType_t data)
{
	//1.创建一个新结点并对新结点申请内存
	CircLList_t *New = CircLList_NewNode(data);
	CircLList_t *Phead = Head;
	if (NULL == New)
	{
		perror("Calloc memory for NewNode is Failed");
		return false;
	}
	//2.检查链表是否为空
	if(Head->next == Head){
		
		Head->next = New;
		New->next = New;

		return true;
	}
	//3.链表不为空
	//从首结点开始遍历
	while(Phead->next)
	{
		//把头结点的直接后继作为新的头结点
		Phead = Phead->next;

		//判断是否到达尾结点，尾结点的next指针是指向首结点的地址
		if (Phead->next == Head->next)
		{
			break;
		}	
	}
	New->next 	= Head->next;
	Head->next 	= New;
	Phead->next = New;
	return true;
}

//尾插
bool CircLList_TailInsert(CircLList_t *Head,DataType_t data)
{
	//1.创建一个新结点并对新结点申请内存
	CircLList_t *New = CircLList_NewNode(data);
	CircLList_t *Pend = Head;
	if (NULL == New)
	{
		perror("Calloc memory for NewNode is Failed");
		return false;
	}
	//2.检查链表是否为空
	if(Head->next == Head){
		
		Head->next = New;
		New->next = New;

		return true;
	}
	while(Pend->next)
	{
		//把头结点的直接后继作为新的头结点
		Pend = Pend->next;

		//判断是否到达尾结点，尾结点的next指针是指向首结点的地址
		if (Pend->next == Head->next)
		{
			break;
		}	
	}
	Pend->next = New;
	New->next 	= Head->next;
}


//指定位置插入
bool CircLList_DestInsert(CircLList_t *Head,DataType_t destval,DataType_t data)
{
	
	//1.创建一个新结点并对新结点申请内存
	CircLList_t *New = CircLList_NewNode(data);
	CircLList_t *Phead = Head;
	if (NULL == New)
	{
		perror("Calloc memory for NewNode is Failed");
		return false;
	}
	//2.检查链表是否为空
	if(Head->next == Head){
		
		Head->next = New;
		New->next = New;

		return true;
	}
	while(Phead->next)
	{
		//把头结点的直接后继作为新的头结点
		Phead = Phead->next;

		//判断是否找到要插入的位置
		if (destval == Phead->data)
		{
			New->next = Phead->next;
			Phead->next = New;
			return true;
		}
		if (Phead->next == Head->next && destval != Phead->data)
		{
			break;
		}		
	}
	printf("元素插入失败\n");
	return false;
}


//遍历链表
bool CircLList_Print(CircLList_t *Head)
{
	//对单向循环链表的头结点的地址进行备份
	CircLList_t *Phead = Head;
	
	//判断当前链表是否为空，为空则直接退出
	if (Head->next == Head)
	{
		printf("current linkeflist is empty!\n");
		return false;
	}

	//从首结点开始遍历
	while(Phead->next)
	{
		//把头结点的直接后继作为新的头结点
		Phead = Phead->next;

		//输出头结点的直接后继的数据域
		printf("data = %d\n",Phead->data);

		//判断是否到达尾结点，尾结点的next指针是指向首结点的地址
		if (Phead->next == Head->next)
		{
			break;
		}	
	}

	return true;
}

//头删
bool CircLLis_HeadDel(CircLList_t *Head)
{
	//对单向循环链表的头结点的地址进行备份
	CircLList_t *Phead = Head;
	CircLList_t *Pdel = Head->next;

	//1.检查链表是否为空
	if(Head->next == Head){
		printf("链表为空，删除失败\n");
		return false;
	}

	//2.判断链表中是否只有首届点
	if(Pdel->next == Head->next )
	{
		Head->next = Head;
		Pdel->next = NULL;
		free(Pdel);
		return true;
	}

	//3.链表不为空，遍历找到尾部
	while(Phead->next)
	{
		//把头结点的直接后继作为新的头结点
		Phead = Phead->next;

		//判断是否到达尾结点，尾结点的next指针是指向首结点的地址
		if (Phead->next == Head->next)
		{
			break;
		}	
	}

	//3.删除并释放内存
	Phead->next = Pdel->next;
	Head->next  = Pdel->next;
	Pdel->next  = NULL;
	free(Pdel);
	return true;
}


//尾部删除
bool CircLLis_EndDel(CircLList_t *Head)
{
	//对单向循环链表的头结点的地址进行备份
	CircLList_t *Phead = Head;
	CircLList_t *Pdel = Head->next;

	//1.检查链表是否为空
	if(Head->next == Head){
		printf("链表为空，删除失败\n");
		return false;
	}
	//2.判断链表中是否只有首届点
	if(Pdel->next == Head->next )
	{
		Head->next = Head;
		Pdel->next = NULL;
		free(Pdel);
		return true;
	}
	//3.链表不为空，遍历找到尾部
	while(Pdel->next)
	{
		//把头结点的直接后继作为新的头结点
		Phead = Phead->next;
		Pdel = Pdel->next;
		//判断是否到达尾结点，尾结点的next指针是指向首结点的地址
		if (Pdel->next == Head->next)
		{
			break;
		}	
	}
	Phead->next = Pdel->next;
	Pdel->next = NULL;
	free(Pdel);
	return true;
}


bool CircLLis_InstallDel(CircLList_t *Head,DataType_t destval)
{
	//对单向循环链表的头结点的地址进行备份
	CircLList_t *Phead = Head;
	CircLList_t *Pdel = Head->next;

	//1.检查链表是否为空
	if(Head->next == Head){
		printf("链表为空，删除失败\n");
		return false;
	}
	//2.当destval是链表的首结点 并且 链表只有一个元素
	if( destval == Pdel->data )
	{
		CircLLis_HeadDel(Head);
		return true;
	}
	//3.链表不为空，遍历
	while(Pdel->next)
	{

		//把头结点的直接后继作为新的头结点
		Phead = Phead->next;
		Pdel = Pdel->next;
		if(destval == Pdel->data){
			Phead->next = Pdel->next;
			Pdel->next = NULL;
			free(Pdel);
			return true;
		}
		//判断是否到达尾结点，尾结点的next指针是指向首结点的地址
		if (Pdel->next == Head->next)
		{
			break;
		}	
	}
	printf("链表中没有该元素\n");
} 





int main(int argc, char const *argv[])
{
	CircLList_t *New = CircLList_Create();
	CircLList_TailInsert(New,1);
	CircLLis_InstallDel(New,1);
	CircLList_Print(New);
	return 0;
}