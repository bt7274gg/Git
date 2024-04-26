/********************************************************************************************************
*
*
* 设计双向链表的接口
*
* 
*
* Copyright (c)  2023-2024   cececlmx@126.com   All right Reserved
* ******************************************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>




//指的是双向链表中的结点有效数据类型，用户可以根据需要进行修改
typedef int  DataType_t;

//构造双向链表的结点,链表中所有结点的数据类型应该是相同的
typedef struct DoubleLinkedList
{
	DataType_t  		     data; //结点的数据域
	struct DoubleLinkedList	*prev; //直接前驱的指针域
	struct DoubleLinkedList	*next; //直接后继的指针域

}DoubleLList_t;


//创建一个空双向链表，空链表应该有一个头结点，对链表进行初始化
DoubleLList_t * DoubleLList_Create(void)
{
	//1.创建一个头结点并对头结点申请内存
	DoubleLList_t *Head = (DoubleLList_t *)calloc(1,sizeof(DoubleLList_t));
	if (NULL == Head)
	{
		perror("Calloc memory for Head is Failed");
		exit(-1);
	}

	//2.对头结点进行初始化，头结点是不存储数据域，指针域指向NULL
	Head->prev = NULL;
	Head->next = NULL;

	//3.把头结点的地址返回即可
	return Head;
}

//创建新的结点，并对新结点进行初始化（数据域 + 指针域）
DoubleLList_t * DoubleLList_NewNode(DataType_t data)
{
	//1.创建一个新结点并对新结点申请内存
	DoubleLList_t *New = (DoubleLList_t *)calloc(1,sizeof(DoubleLList_t));
	if (NULL == New)
	{
		perror("Calloc memory for NewNode is Failed");
		return NULL;
	}

	//2.对新结点的数据域和指针域（2个）进行初始化
	New->data = data;
	New->prev = NULL;
	New->next = NULL;

	return New;
}

//遍历
bool ShowDoubList(DoubleLList_t *Head)
{
	DoubleLList_t *Phead = Head;
	//判断链表是否为空
	if(	NULL == Head->next){
		printf("该链表为空\n");
		return false;
	}
	//链表不为空
	//首结点
	while(Phead->next){

		//把头的直接后继作为新的头结点	
		Phead = Phead->next;
		//输出头结点的直接后继的数据域
		printf("data = %d\n",Phead->data);
	}

}


//头插

bool HeadAdd(DoubleLList_t *Head,DataType_t data)
{
	DoubleLList_t *New = DoubleLList_NewNode( data);

	//对New进行错误判断
	if (NULL == New)
	{
		printf("can not insert new node\n");
		return false;
	}

	//判断链表是否为空
	if(	NULL == Head->next){
		Head->next = New;
		return true;
	}

	//如果链表为非空，则把新结点插入到链表的头部
	New->next = Head->next;
	Head->next->prev = New;
	Head->next = New;
	
	return true;
}


//尾插
bool EndAdd(DoubleLList_t *Head,DataType_t data)
{
	DoubleLList_t *New = DoubleLList_NewNode( data);
	DoubleLList_t *Phead = Head;
	//1.对New进行错误判断
	if (NULL == New)
	{
		printf("can not insert new node\n");
		return false;
	}

	//2.判断链表是否为空
	if(	NULL == Head->next){
		Head->next = New;
		return true;
	}

	//3.如果链表为非空，则把新结点插入到链表的尾部

	//遍历链表
	while(Phead->next){

		//把头的直接后继作为新的头结点	
	
		Phead = Phead->next;
	}

	//插入
	Phead->next = New;
	New->prev   = Phead;
	return true;

}

//中间插入
bool InstallAdd(DoubleLList_t *Head,DataType_t dets,DataType_t data)
{

	DoubleLList_t *New = DoubleLList_NewNode( data);
	DoubleLList_t *Phead = Head;
	//1.对New进行错误判断
	if (NULL == New)
	{
		printf("can not insert new node\n");
		return false;
	}

	//2.判断链表是否为空
	if(	NULL == Head->next){
		Head->next = New;
		return true;
	}

	//3.遍历链表
	while(Phead->next){
		
		//把头的直接后继作为新的头结点	
		Phead = Phead->next;
		  if(Phead->data == dets && Phead->next != NULL){

			New->next = Phead->next;
			Phead->next->prev = New;
			New->prev = Phead;
			Phead->next = New;
			return true;
			}  
	}
	//刚好到最后一个
	if(Phead->data == dets){
		Phead->next = New;
		New->prev = Phead;
		return true;
	}
	else{
	printf("链表插入失败\n");
	return false;
	}
}

//头删

bool HeadDel(DoubleLList_t *Head)
{
	DoubleLList_t *Phead = Head->next;				//记录首结点的地址

	//1.判断链表是否为空
	if(	NULL == Head->next){
		printf("链表为空，删除失败\n");
		return false;
	}

	//2.链表不为空
	Head->next 			 = Phead->next;
	Phead->next->prev	 = NULL;
	Phead->next 		 = NULL;
	//3.释放内存
	free(Phead);

	return true;


}

//尾删
bool EndDel(DoubleLList_t *Head)
{
	DoubleLList_t *Pend = Head->next;				//用来记录尾结点的地址
	//1.判断链表是否为空
	if(	NULL == Head->next){
		printf("链表为空，删除失败\n");
		return false;
	}
	//2.遍历链表
	while(Pend->next){
		Pend = Pend->next;	
	}

	//3.删除
	Pend->prev->next = NULL;
	Pend->prev = NULL;
	free(Pend);
	return true;
}



//中间删除
bool InstallDel(DoubleLList_t *Head,DataType_t data)
{
	DoubleLList_t *Phead = Head->next;				//用来记录尾结点的地址
	//1.判断链表是否为空
	if(	NULL == Head->next){
		printf("链表为空，删除失败\n");
		return false;
	}
	//2.刚好是第一个元素
	if(Phead->data == data){
		
		Head->next		   = Phead->next;
		Phead->next->prev  = NULL;
		Phead->next 	   = NULL;
		free(Phead);
		return true;
	}
	//2.遍历链表
	while(Phead->next){
		
		//把头的直接后继作为新的头结点	
		Phead = Phead->next;
		  if(Phead->data == data && Phead->next != NULL){
			
			Phead->prev->next = Phead->next;
			Phead->next->prev = Phead->prev;
			Phead->next 		 = NULL;
			Phead->prev 		 = NULL;
			return true;
			}  
	}
	//3.刚好是最后一个
	if(Phead->data == data){

		Phead->prev->next 	= NULL;
		Phead->prev 		= NULL;
		free(Phead);
		return true;
	}
	else
	{
		printf("链表中没有该元素，删除失败\n");
		return false;
	}
}

int main(int argc, char const *argv[])
{
	DoubleLList_t * List = DoubleLList_Create();
	EndAdd(List,67);
	EndAdd(List,7);
	EndAdd(List,6);
	EndAdd(List,17);
	EndAdd(List,627);
	InstallDel(List,67);
	ShowDoubList(List);






	return 0;
}