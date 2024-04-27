/********************************************************************************************************
*
*
* 该程序实现循环队列元素的增删改查，目的是提高设计程序的逻辑思维，另外为了提高可移植性，所以循环队列中元素
* 的数据类型为DataType_t，用户可以根据实际情况修改循环队列中元素的类型。
*
* 另外，为了方便管理循环队列,所以用户设计SeqList_t结构体，该结构体中包含三个成员：地址+容量+有效元素的下标
*
* 
*
* Copyright (c)  2023-2024   cececlmx@126.com   All right Reserved
* ******************************************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>




//指的是循环队列中的元素的数据类型，用户可以根据需要进行修改
typedef int  DataType_t;

//构造记录循环队列CircularQueue各项参数(循环队列的首地址 + 循环队列的容量 + 循环队列队尾下标+队首下标)的结构体
typedef struct CircularQueue
{
	DataType_t * Addr;		//记录循环队列首地址
	unsigned int Size;		//记录循环队列的容量
	int			 Rear;      //循环队列队尾下标	
	int			 Front;     //循环队列队首下标

}CirQueue_t;


//创建循环队列并对循环队列进行初始化
CirQueue_t * CirQueue_Create(unsigned int size)
{
	//1.利用calloc为循环队列的管理结构体申请一块堆内存
	CirQueue_t *Manager = (CirQueue_t *)calloc(1,sizeof(CirQueue_t));

	if(NULL == Manager)
	{
		perror("calloc memory for manager is failed");
		exit(-1); //程序异常终止
	}

	//2.利用calloc为所有元素申请堆内存
	Manager->Addr = (DataType_t *)calloc(size,sizeof(DataType_t));

	if (NULL == Manager->Addr)
	{
		perror("calloc memory for element is failed");
		free(Manager);
		exit(-1); //程序异常终止
	}

	//3.对管理循环队列的结构体进行初始化（循环队列容量 + 队尾下标+队首下标）
	Manager->Size = size;	//对循环队列中的容量进行初始化
	Manager->Rear = 0;		//队尾下标初值为0
	Manager->Front = 0;		//队首下标初值为0
	
	return Manager;
}


//判断循环队列是否已满
bool CirQueue_IsFull(CirQueue_t *Manager)
{
	return ( (Manager->Rear + 1) % Manager->Size == Manager->Front ) ? true : false;
}


//入队
bool CirQueue_Enqueue(CirQueue_t *Manager, DataType_t Data)
{
	//1.判断循环队列是否已满
	if ( CirQueue_IsFull(Manager) )
	{
		printf("CirQueue is Full!\n");
		return false;
	}

	//2.如果循环队列有空闲空间，则把新元素添加到循环队列尾部
	Manager->Addr[Manager->Rear] = Data;


	//防止队尾下标越界
	Manager->Rear = (Manager->Rear+1) % Manager->Size;


	return true;
}





//判断循环队列是否为空
bool CirQueue_IsEmpty(CirQueue_t *Manager)
{
	return (Manager->Front == Manager->Rear) ? true : false;
}



//出队
DataType_t CirQueue_Dequeue(CirQueue_t *Manager)
{
	DataType_t temp =0;

	//1.判断循环队列是否为空
	if ( CirQueue_IsEmpty(Manager) )
	{
		printf("CirQueue is Empty!\n");
		return false;
	}

	//2.把元素从队首出队，并备份到变量temp
	temp = Manager->Addr[Manager->Front];
	
	//防止队首下标越界
	Manager->Front = (Manager->Front+1) % Manager->Size;


	return temp;
}






int main(int argc, char const *argv[])
{
	
	return 0;
}

