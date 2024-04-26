/********************************************************************************************************
*
*
* 设计双向循环链表的接口
*
* 
*
* Copyright (c)  2023-2024   cececlmx@126.com   All right Reserved
* ******************************************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//指的是双向循环链表中的结点有效数据类型，用户可以根据需要进行修改
typedef int  DataType_t;

//构造双向循环链表的结点,链表中所有结点的数据类型应该是相同的
typedef struct DoubleLinkedList
{
	DataType_t  		     data; //结点的数据域
	struct DoubleLinkedList	*prev; //直接前驱的指针域
	struct DoubleLinkedList	*next; //直接后继的指针域

}DoubleLList_t;


//创建一个空双向循环链表，空链表应该有一个头结点，对链表进行初始化
DoubleLList_t * DoubleCirLList_Create(void)
{
	//1.创建一个头结点并对头结点申请内存
	DoubleLList_t *Head = (DoubleLList_t *)calloc(1,sizeof(DoubleLList_t));
	if (NULL == Head)
	{
		perror("Calloc memory for Head is Failed");
		exit(-1);
	}

	//2.对头结点进行初始化，头结点是不存储数据域，指针域指向自身即可，体现“循环”
	Head->prev = Head;
	Head->next = Head;

	//3.把头结点的地址返回即可
	return Head;
}

//创建新的结点，并对新结点进行初始化（数据域 + 指针域）
DoubleLList_t * DoubleCirLList_NewNode(DataType_t data)
{
	//1.创建一个新结点并对新结点申请内存
	DoubleLList_t *New = (DoubleLList_t *)calloc(1,sizeof(DoubleLList_t));
	if (NULL == New)
	{
		perror("Calloc memory for NewNode is Failed");
		return NULL;
	}

	//2.对新结点的数据域和指针域（2个）进行初始化,指针域指向结点自身，体现“循环”
	New->data = data;
	New->prev = New;
	New->next = New;

	return New;
}

//遍历链表
bool Show_DoubleCirLList(DoubleLList_t *Head)
{
	DoubleLList_t *Phead = Head;
	
	//判断当前链表是否为空，为空则直接退出
	if (Head->next == Head)
	{
		printf("链表为空\n");
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



//头插
bool DoubCir_HeadAaa(DoubleLList_t *Head,DataType_t data)
{
	DoubleLList_t *New = DoubleCirLList_NewNode(data);
	
	//对New进行错误判断
	if (NULL == New)
	{
		printf("插入失败\n");
		return false;
	}

	//判断链表是否为空
	if(	Head->next == Head){
		Head->next = New;
		return true;
	}
	
	//链表不为空
	New->next 		 = Head->next;
	New->prev 		 = Head->next->prev;
	Head->next->prev = New;
	Head->next 		 = New;
	return true;

}

bool DoubCir_EndAaa(DoubleLList_t *Head,DataType_t data)
{
	DoubleLList_t *New = DoubleCirLList_NewNode(data);
	
	//对New进行错误判断
	if (NULL == New)
	{
		printf("插入失败\n");
		return false;
	}

	//判断链表是否为空
	if(	Head->next == Head){
		Head->next = New;
		return true;
	}

	New->prev 			   = Head->next->prev;
	New->next 			   = Head->next;
	Head->next->prev->next = New;
	Head->next->prev 	   = New;
	return true;
}

bool DoubCir_InstallAdd(DoubleLList_t *Head,DataType_t destval,DataType_t data)
{
	DoubleLList_t *New = DoubleCirLList_NewNode(data);
	DoubleLList_t *Phead = Head;
	//对New进行错误判断
	if (NULL == New)
	{
		printf("插入失败\n");
		return false;
	}

	//判断链表是否为空
	if(	Head->next == Head){
		Head->next = New;
		return true;
	}
	//从首结点开始遍历
	while(Phead->next)
	{
		//把头结点的直接后继作为新的头结点
		Phead = Phead->next;
		
		//判断是否找到要插入的位置
		if (destval == Phead->data)
		{
			New->prev 			= Phead;
			New->next 			= Phead->next;
			Phead->next->prev 	= New;
			Phead->next 		= New;
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

//头删
bool DoubCir_HeadDel(DoubleLList_t *Head)
{
	//对单向循环链表的头结点的地址进行备份
	DoubleLList_t *Phead = Head;
	DoubleLList_t *Pdel  = Head->next;

	//判断链表是否为空
	if(	Head->next == Head){
		printf("链表为空删除失败");
		return false;
	}
	//链表只有一个元素
	if(Pdel == Pdel->next){
			Head->next = Head;
			Pdel->next = NULL;
			Pdel->prev = NULL;
			free(Pdel);
			return true;
	}

	//链表不止一个元素
	Head->next 			= Pdel->next;
	Pdel->next->prev 	= Pdel->prev;
	Pdel->prev->next 	= Pdel->next;
	Pdel->next 			= NULL;
	Pdel->prev 			= NULL;
	free(Pdel);
	return true;

}
//尾部删除
bool DoubCir_EndDel(DoubleLList_t *Head)
{
	//对双向循环链表的头结点的地址进行备份
	DoubleLList_t *Phead = Head;
	DoubleLList_t *Pdel  = Head->next->prev;

	//判断链表是否为空
	if(	Head->next == Head){
		printf("链表为空删除失败");
		return false;
	}
	//链表只有一个元素
	if(Pdel == Pdel->next){
			Head->next = Head;
			Pdel->next = NULL;
			Pdel->prev = NULL;
			free(Pdel);
			return true;
	}
	//链表不止一个元素
	Pdel->next->prev = Pdel->prev;
	Pdel->prev->next = Head->next;
	Pdel->next = NULL;
	Pdel->prev = NULL;
	free(Pdel);
	return true;

}

//中间删除
bool DoubCir_InstallDel(DoubleLList_t *Head,DataType_t destval)
{
	DoubleLList_t *Pdel  = Head->next;

	//判断链表是否为空
	if(	Head->next == Head){
		printf("链表为空删除失败");
		return false;
	}
	//链表只有一个元素
	if(Pdel->next == Pdel && destval == Pdel->data){
			Head->next = Head;
			Pdel->next = NULL;
			Pdel->prev = NULL;
			free(Pdel); 
			return true;
	} 
	//链表不止一个元素,且删除的是第一个元素
	if(destval == Pdel->data){
		Head->next 			= Pdel->next;
		Pdel->next->prev 	= Pdel->prev;
		Pdel->prev->next 	= Pdel->next;
		Pdel->next 			= NULL;
		Pdel->prev 			= NULL;
		free(Pdel);
		return true;
	} 
	//从首结点开始遍历
	while(Pdel->next)
	{
		//把头结点的直接后继作为新的头结点
		Pdel = Pdel->next;
		
		//判断是否找到要插入的位置
		if (destval == Pdel->data)
		{	
			Pdel->prev->next = Pdel->next;
			Pdel->next->prev = Pdel->prev;
			Pdel->next		 = NULL;
			Pdel->prev		 = NULL;
			return true;
		}
		if (Pdel->next == Head->next && destval != Pdel->data)
		{
			break;
		}	
	}
	printf("链表中没有该元素\n");
	return false;

}

int main(int argc, char const *argv[])
{

	DoubleLList_t *List = DoubleCirLList_Create();
	DoubCir_EndAaa(List,1);
	DoubCir_EndAaa(List,2);
	DoubCir_EndAaa(List,3);
	DoubCir_EndAaa(List,4); 
	DoubCir_InstallDel(List,1);
	Show_DoubleCirLList(List);
	
	return 0;
}