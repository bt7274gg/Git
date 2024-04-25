/********************************************************************
*          
*          文件名:		linkedlist.cc	
*          作者:		7355608bs@136.com
*          日期:		2024/4/25
*          文件作用:	实现单链表的增删改查
*          注意事项:	NONE
*
*        CopyRight (c)     2024/4/25   c7355608bs@136.com      All Right Reseverd     
*          
********************************************************************/

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>





//指的是单向链表中的结点有效数据类型，用户可以根据需要进行修改
typedef int  DataType_t;

//构造链表的结点,链表中所有结点的数据类型应该是相同的
typedef struct LinkedList
{
	DataType_t  		 data; //结点的数据域
	struct LinkedList	*next; //结点的指针域

}LList_t;


/*****************************************************************************
*                 函数名称:		LList_Create
*                 函数功能：	创建一个空链表，空链表应该有一个头结点，对链表进行初始化
*                 函数参数：	NONE
*                 返回结果：	Head	返回头结点的地址
*                 注意事项：	NONE
*                 函数作者：	c7355608bs@136.com
*                 创建日期：	2024/4/25
*                 修改历史：	2024/4/1.0
*                 函数版本：	1.0
*
******************************************************************************/

LList_t * LList_Create(void)
{
	//1.创建一个头结点并对头结点申请内存
	LList_t *Head = (LList_t *)calloc(1,sizeof(LList_t));
	if (NULL == Head)
	{
		perror("Calloc 内存申请失败");
		exit(-1);
	}

	//2.对头结点进行初始化，头结点是不存储有效内容的！！！
	Head->next = NULL;

	//3.把头结点的地址返回即可
	return Head;
}


/*****************************************************************************
*                 函数名称:		LList_NewNode
*                 函数功能：	创建新的结点，并对新结点进行初始化
*                 函数参数：	
*								@a：data	新增的元素的值
*                 返回结果：	New	返回新结点的地址
*                 注意事项：	NONE
*                 函数作者：	c7355608bs@136.com
*                 创建日期：	2024/4/25
*                 修改历史：	2024/4/1.0
*                 函数版本：	1.0
*
******************************************************************************/

LList_t * LList_NewNode(DataType_t data)
{
	//1.创建一个新结点并对新结点申请内存
	LList_t *New = (LList_t *)calloc(1,sizeof(LList_t));
	if (NULL == New)
	{
		perror("Calloc 内存申请失败");
		return NULL;
	}

	//2.对新结点的数据域和指针域进行初始化
	New->data = data;
	New->next = NULL;

	return New;
}



/*****************************************************************************
*                 函数名称:		LList_Print
*                 函数功能：	遍历
*                 函数参数：	
*								@a：data	新增的元素的值
*                 返回结果：	布尔型
*                 注意事项：	NONE
*                 函数作者：	c7355608bs@136.com
*                 创建日期：	2024/4/25
*                 修改历史：	2024/4/1.0
*                 函数版本：	1.0
*
*******************************************************************************/
bool LList_Print(LList_t *Head)
{
	//对链表的头文件的地址进行备份
	LList_t *Phead = Head;
	//判断当前链表是否为空，为空则直接退出
	if (Head->next == NULL)
	{
		printf("链表为空\n");
		return false;
	}
	//首结点
	while(Phead->next)
	{
		//把头的直接后继作为新的头结点
		Phead = Phead->next;
		//输出头结点的直接后继的数据域
		printf("data = %d\n",Phead->data);
	}
	return true;
}



/*****************************************************************************
*                 函数名称:		LList_HeadInsert
*                 函数功能：	向链表的头部插入元素
*                 函数参数：	
*								@a：Head	操作的链表
*								@b：data	新增的元素的值
*                 返回结果：	布尔型
*                 注意事项：	NONE
*                 函数作者：	c7355608bs@136.com
*                 创建日期：	2024/4/25
*                 修改历史：	2024/4/1.0
*                 函数版本：	1.0
*
*******************************************************************************/
bool LList_HeadInsert(LList_t *Head,DataType_t data)
{
	//1.创建新的结点，并对新结点进行初始化
	LList_t *New = LList_NewNode(data);
	if (NULL == New)
	{
		printf("不能加入新元素\n");
		return false;
	}

	//2.判断链表是否为空，如果为空，则直接插入即可
	if (NULL == Head->next)
	{
		Head->next = New;
		return true;
	}

	//3.如果链表为非空，则把新结点插入到链表的头部
	New->next  = Head->next;
	Head->next = New;

	return true;
}

/*****************************************************************************
*                 函数名称:		LList_TailInsert
*                 函数功能：	向链表的尾部插入元素
*                 函数参数：	
*								@a：Head	操作的链表
*								@b：data	新增的元素的值
*                 返回结果：	布尔型
*                 注意事项：	NONE
*                 函数作者：	c7355608bs@136.com
*                 创建日期：	2024/4/25
*                 修改历史：	2024/4/1.0
*                 函数版本：	1.0
*
*******************************************************************************/
bool LList_TailInsert(LList_t *Head,DataType_t data)
{
	//1.创建新的结点，并对新结点进行初始化
	LList_t *New = LList_NewNode(data);
	LList_t *Pend = Head;
	if (NULL == New)
	{
		printf("不能加入新元素\n");
		return false;
	}

	//2.判断链表是否为空，如果为空，则直接插入即可
	if (NULL == Head->next)
	{
		Head->next = New;
		return true;
	}
	//3.插入
	while(Pend->next)
	{
		//把头的直接后继作为新的头结点
		Pend = Pend->next;
	}

	Pend->next = New ;
	return true;
}






/*****************************************************************************
*                 函数名称:		LList_DestInsert
*                 函数功能：	向链表的中间插入元素
*                 函数参数：	
*								@a：Head	操作的链表
*								@b：data	新增的元素的值
*                 返回结果：	布尔型
*                 注意事项：	NONE
*                 函数作者：	c7355608bs@136.com
*                 创建日期：	2024/4/25
*                 修改历史：	2024/4/1.0
*                 函数版本：	1.0
*
*******************************************************************************/
bool LList_DestInsert(LList_t *Head,DataType_t dest,DataType_t data)
{
	//1.创建新的结点，并对新结点进行初始化
	LList_t *New = LList_NewNode(data);
	LList_t *Phead = Head;				//记录前驱
	if (NULL == New)
	{
		printf("不能加入新元素\n");
		return false;
	}

	//2.判断链表是否为空，如果为空，则直接插入即可
	if (NULL == Head->next)
	{
		Head->next = New;
		return true;
	}

	//3.遍历链表比较数值
	while( Phead->next )
	{
		Phead = Phead->next;
		if( Phead->data== dest ){
			New->next   = Phead->next;
			Phead->next = New;
			return true;
		}
		
	}
	return false;

}




/*****************************************************************************
*                 函数名称:		HeadDel
*                 函数功能：	从链表的头部删除元素
*                 函数参数：	
*								@a：Head	操作的链表
*								@b：data	新增的元素的值
*                 返回结果：	布尔型
*                 注意事项：	NONE
*                 函数作者：	c7355608bs@136.com
*                 创建日期：	2024/4/25
*                 修改历史：	2024/4/1.0
*                 函数版本：	1.0
*
*******************************************************************************/
bool HeadDel(LList_t *Head)
{
	LList_t *Phead = Head->next;			//记录首结点
	//1.判断链表是否为空，如果为空，则直接插入即可
	if (NULL == Head->next)
	{
		printf("链表为空，删除失败\n");
		return false;
	}
	//2.链表不为空
	 Head->next  = Phead->next;
	 Phead->next = NULL;
	//3.释放空间
	free(Phead);
	return true;
}





/*****************************************************************************
*                 函数名称:		EndDel
*                 函数功能：	从链表的尾部删除元素
*                 函数参数：	
*								@a：Head	操作的链表
*								@b：data	新增的元素的值
*                 返回结果：	布尔型
*                 注意事项：	NONE
*                 函数作者：	c7355608bs@136.com
*                 创建日期：	2024/4/25
*                 修改历史：	2024/4/1.0
*                 函数版本：	1.0
*
*******************************************************************************/
bool EndDel(LList_t *Head)
{
	LList_t *Prev = Head;				//记录前驱
	LList_t *Pend = Head->next;			//记录首结点
	//1.判断链表是否为空，如果为空，则直接插入即可
	if (NULL == Head->next)
	{
		printf("链表为空，删除失败\n");
		return false;
	}
	//2.遍历
	while( Pend->next )
	{
		Prev = Prev->next;
		Pend = Pend->next;
	}

	//3.删除并释放
	Prev->next = NULL;
	free(Pend);
	return true;
}

/*****************************************************************************
*                 函数名称:		InstallDel
*                 函数功能：	从链表的中间删除元素
*                 函数参数：	
*								@a：Head	操作的链表
*								@b：data	新增的元素的值
*                 返回结果：	布尔型
*                 注意事项：	NONE
*                 函数作者：	c7355608bs@136.com
*                 创建日期：	2024/4/25
*                 修改历史：	2024/4/1.0
*                 函数版本：	1.0
*
*******************************************************************************/
bool InstallDel(LList_t *Head,DataType_t dest)
{
	LList_t *Prev = Head;				//记录前驱
	LList_t *Pend = Head->next;
	
	//1.判断链表是否为空，如果为空，则直接插入即可
	if (NULL == Head->next)
	{
		printf("链表为空，删除失败\n");
		return false;
	}

	//2.遍历
	while( Pend->next )
	{

		Prev = Prev->next;
		Pend = Pend->next;
		if( Pend->data== dest ){
			Prev->next = Pend->next;
			Pend->next = NULL;
			free(Pend);
			return true;
		}
	}
	printf("链表里面没有该元素\n");
	return false;
}

int main(int argc, char const *argv[])
{

	LList_t *List = LList_Create();
	LList_TailInsert(List,10);
	LList_TailInsert(List,1);
	LList_TailInsert(List,0);
	LList_TailInsert(List,100);
	LList_TailInsert(List,4);
	LList_Print(List);
	InstallDel(List,5);
	LList_Print(List);
	return 0;
}