#include <stdlib.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef int DataType_t ;


typedef struct LinkQueue
{
    struct LinkQueue *next;
    DataType_t         data;
}LinQue_t;



/*****************************************************************************
*                 函数名称:     LinQue_Create
*                 函数功能：    创建头结点
*                 函数参数：    NONE
*                 返回结果：    Head    返回头结点的地址
*                 注意事项：    NONE
*                 函数作者：    c7355608bs@136.com
*                 创建日期：    2024/4/26
*                 修改历史：    2024/4
*                 函数版本：    1.0
*
*****************************************************************************/
//创建初始化链表
LinQue_t* LinQue_Create(void)
{
    //为头结点申请空间
    LinQue_t* Head = ( LinQue_t*)calloc(1,sizeof(LinQue_t));
    //错误判断
   if (NULL == Head)
	{
		perror("Calloc 内存申请失败");
		return NULL;
	}
   //头结点指向空
    Head->next = NULL;

    return Head;
}

/*****************************************************************************
*                 函数名称:     LinQue_New
*                 函数功能：    创建新元素并初始化
*                 函数参数：
*                          @   data   新元素的值
*                 返回结果：
*                 注意事项：
*                 函数作者：    c7355608bs@136.com
*                 创建日期：    2024/4/26
*                 修改历史：    2024/4
*                 函数版本：    1.0
*
*****************************************************************************/

//创建新结点
LinQue_t* LinQue_New(DataType_t data)
{
    //为新结点申请空间
     LinQue_t* New = ( LinQue_t*)calloc(1,sizeof(LinQue_t));
     //错误判断
    if (NULL == New)
	{
		perror("Calloc 内存申请失败");
		return NULL;
	}
    //新结点初始化
    New->data = data;
    New->next = NULL;

    return New;

}


/*****************************************************************************
*                 函数名称:     LinQue_show
*                 函数功能：    遍历队列
*                 函数参数：
*                          @Head    操作的队列
*                 返回结果：    布尔型
*                 注意事项：    NONE
*                 函数作者：    c7355608bs@136.com
*                 创建日期：    2024/4/26
*                 修改历史：    2024/4
*                 函数版本：    1.0
*
*****************************************************************************/
//遍历队列
bool LinQue_show( LinQue_t* Head )
{
    //备份头结点
    LinQue_t* Phead = Head;
   
    //判断链表是否为空
    if(Head->next == NULL){
        printf("该单链表队列为空\n");
        return false;
    }
    //遍历链表
    while (Phead->next)
    {
        Phead = Phead->next; 
        printf("data = %d\n",Phead->data);
    }

    return true;

}


/*****************************************************************************
*                 函数名称:     LinQue_RearAdd
*                 函数功能：
*                 函数参数：
*                          @Head    操作的队列
*                          @data    插入的元素的值
*                 返回结果：    布尔型
*                 注意事项：    NONE
*                 函数作者：    c7355608bs@136.com
*                 创建日期：    2024/4/26
*                 修改历史：    2024/4
*                 函数版本：    1.0
*
*****************************************************************************/
//尾插
bool LinQue_RearAdd(LinQue_t* Head,DataType_t data)
{
    //备份头结点
    LinQue_t* Phead = Head;
    //创建新结点
    LinQue_t* New  = LinQue_New(data);
    if(New == NULL){

        printf("加入元素失败\n");
        return false;
    }
    //判断链表是否为空
    if(NULL == Head->next){
        Head->next = New;
        return true;
    }
    //链表不为空
    //遍历链表
    while (Phead->next)
    {
        Phead = Phead->next; 
    }
    Phead->next = New;
   
    return true;

}


/*****************************************************************************
*                 函数名称:     LinQue_FrontDel
*                 函数功能：    删除队列元素
*                 函数参数：
*                          @Head    操作的队列
*                 返回结果：   布尔型 
*                 注意事项：    NONE
*                 函数作者：    c7355608bs@136.com
*                 创建日期：    2024/4/26
*                 修改历史：    2024/4
*                 函数版本：    1.0
*****************************************************************************/
//头删
bool LinQue_FrontDel(LinQue_t* Head)
{
    //备份头结点
    LinQue_t* Phead = Head->next;

    //判断链表是否为空
    if(NULL == Head->next){
        printf("链表为空，删除失败\n");
        return false;
    }

    //删除首结点
    Head->next  = Phead->next;
    Phead->next = NULL;
    free(Phead);
    return true;
}



int main()
{
    LinQue_t* List = LinQue_Create();

    LinQue_show(List);
    LinQue_FrontDel(List);
    LinQue_RearAdd(List,1);
    LinQue_RearAdd(List,2);
    LinQue_RearAdd(List,3);
    LinQue_RearAdd(List,4);
    LinQue_show(List);
    LinQue_FrontDel(List);
     LinQue_show(List);

}