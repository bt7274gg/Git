/********************************************************************************************************
*
*
* 该程序实现顺序表元素的增删改查，目的是提高设计程序的逻辑思维，另外为了提高可移植性，所以顺序表中元素的
* 数据类型为DataType_t，用户可以根据实际情况修改顺序表中元素的类型。
*
* 另外，为了方便管理顺序表,所以用户设计SeqList_t结构体，该结构体中包含三个成员：地址+容量+有效元素的下标
*
* 
*
* Copyright (c)  2023-2024   cececlmx@126.com   All right Reserved
* ******************************************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>




//指的是顺序表中的元素的数据类型，用户可以根据需要进行修改
typedef int  DataType_t;

//构造记录顺序表SequenceList各项参数(顺序表的首地址 + 顺序表的容量 + 顺序表中最后有效元素的下标)的结构体
typedef struct SequenceList
{
	DataType_t * Addr;		//记录顺序表首地址
	unsigned int Size;		//记录顺序表的容量
	int			 Last;      //顺序表中最后元素的下标	

}SeqList_t;


//创建顺序表并对顺序表进行初始化
SeqList_t * SeqList_Create(unsigned int size)
{
	//1.利用calloc为顺序表的管理结构体申请一块堆内存
	SeqList_t *Manager = (SeqList_t *)calloc(1,sizeof(Manager));

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

	//3.对管理顺序表的结构体进行初始化（元素容量 + 最后元素下标）
	Manager->Size = size;	//对顺序表中的容量进行初始化
	Manager->Last = -1;		//由于顺序表为空，则最后元素下标初值为-1
	
	return Manager;
}


//判断顺序表是否已满
bool SeqList_IsFull(SeqList_t *Manager)
{
	return (Manager->Last + 1 == Manager->Size) ? true : false;
}


//向顺序表的尾部加入元素
bool SeqList_TailAdd(SeqList_t *Manager, DataType_t Data)
{
	//1.判断顺序表是否已满
	if ( SeqList_IsFull(Manager) )
	{
		printf("SequenceList is Full!\n");
		return false;
	}

	//2.如果顺序表有空闲空间，则把新元素添加到顺序表尾部
	Manager->Addr[++Manager->Last] = Data;

	return true;
}

//向顺序表的头部加入元素
bool SeqList_HeadAdd(SeqList_t *Manager, DataType_t Data)
{
	//1.判断顺序表是否已满
	if ( SeqList_IsFull(Manager) )
	{
		printf("SequenceList is Full!\n");
		return false;
	}

	//2.如果顺序表有空闲空间，则需要把顺序表所有元素向后移动1个单位
	for (int i = Manager->Last;i >= 0;i--)
	{
		Manager->Addr[i+1] = Manager->Addr[i];
	}

	//3把新元素添加到顺序表的头部,并且更新管理结构体中的元素下标+1
	Manager->Addr[0] = Data;
	Manager->Last++;

	return true;
}





//删除顺序表的元素
bool SeqList_Del(SeqList_t *Manager,DataType_t DestVal)
{
	int temp = -1;  //记录要删除的元素的下标

	//1.判断顺序表是否为空
	if ( SeqList_IsFull(Manager) )
	{
		printf("SequenceList is Empty!\n");
		return false;
	}

	//2.此时需要查找目标值是否在顺序表中
	for (int i = 0; i <= Manager->Last; ++i)
	{	
		//如果目标值和顺序表中元素的值相同
		if (DestVal == Manager->Addr[i])
		{
			temp = i; //把目标元素的下标备份到变量temp中
			break;
		}		
	}
	
	//3.如果顺序表没有目标值的元素则直接终止函数
	if (-1 == temp)
	{
		printf("destval [%d] is not found\n",DestVal);
		return false;
	}

	//4.如果找到了目标元素，则直接把该元素的后继元素向前移动一个单位
	for (int i = temp ; i < Manager->Last ; ++i)
	{
		Manager->Addr[i] = Manager->Addr[i+1];
	}

	//5.由于删除了一个元素，则需要让顺序表的有效元素下标-1
	Manager->Last--;

	return true;
}


//遍历顺序表的元素
void SeqList_Print(SeqList_t *Manager)
{
	for (int i = 0; i <= Manager->Last; ++i)
	{
		printf("Element[%d] = %d\n",i,Manager->Addr[i]);
	}
}


int main(int argc, char const *argv[])
{

	//1.创建顺序表
	SeqList_t * Manager = SeqList_Create(10);
	SeqList_Print(Manager);
	
	/* //2.向顺序表中的尾部插入新元素
	SeqList_TailAdd(Manager,5);
	SeqList_TailAdd(Manager,2);
	SeqList_TailAdd(Manager,1);
	SeqList_TailAdd(Manager,4);
	SeqList_TailAdd(Manager,6);  


	//3.遍历顺序表
	SeqList_Print(Manager); // -- 5 2 1 4 6
	printf("\n"); */
	///4.向顺序表中的头部插入新元素
	SeqList_HeadAdd(Manager,9);
	SeqList_HeadAdd(Manager,7);
	SeqList_HeadAdd(Manager,8);
	SeqList_HeadAdd(Manager,0);
	SeqList_HeadAdd(Manager,10);  

	//5.遍历顺序表
	SeqList_Print(Manager); // --10 0 8 7 9 5 2 1 4 6
	printf("\n");	
	//6.删除顺序表的元素
	SeqList_Del(Manager,20);
	SeqList_Del(Manager,5);
	SeqList_Del(Manager,10);
	SeqList_Del(Manager,0);
	SeqList_Del(Manager,30); 

	//7.遍历顺序表
	SeqList_Print(Manager); // --8 7 9 2 1 4 6
	printf("\n"); 
	return 0;
}

