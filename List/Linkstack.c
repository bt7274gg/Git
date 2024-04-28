/*链栈*/
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>





typedef int DataType_t;



//链表的管理结构体
typedef struct Linkstack
{

    DataType_t              data;
    struct Linkstack       *next;
    
}LStack_t;


//创建链表并初始化
LStack_t* LStack_Create(void)
{
    //为头结点申请内存
    LStack_t* Head = (LStack_t*) calloc(1,sizeof(LStack_t));
    //错误判断
    if(NULL == Head){
        perror("calloc 内存申请失败\n");
        exit(-1);
    }
    Head->next = NULL;
    return Head;
}


//新建结点
LStack_t* LStack_New( DataType_t data)
{
    //为新结点申请内存
    LStack_t* New = (LStack_t*) calloc(1,sizeof(LStack_t));
     //错误判断
    if(NULL == New){
        perror("calloc 内存申请失败\n");
        exit(-1);
    }
    //初始化新结点
    New->data = data;
    New->next = NULL;
    return New;

}

//遍历
bool LStack_Show(LStack_t* Head)
{
    //判断链表是否为空
    LStack_t *Phead = Head;
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


//头插
bool LStack_HeadAdd(LStack_t* Head,DataType_t data)
{

//1.创建新的结点，并对新结点进行初始化
	LStack_t *New = LStack_New(data);
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

bool LList_TailInsert(LStack_t* Head,DataType_t data)
{
	//1.创建新的结点，并对新结点进行初始化
	LStack_t *New = LStack_New(data);
	LStack_t *Pend = Head;
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

int main()
{

    return 0;
}
