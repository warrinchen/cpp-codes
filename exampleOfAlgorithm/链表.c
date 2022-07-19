#include <stdio.h>
#include <stdlib.h>

typedef struct NODE
{
	int val;
	struct NODE *next;
} ND;
ND *creatList()//尾插法
{
	ND *head, *p1, *tmpHead;
	int i = 0;

	head = NULL;
	p1 = (ND *)malloc(sizeof(ND));
	for(i = 0;i < 3;i++)//长度为3的链表
	{
		scanf("%d", &p1->val);
		if(head == NULL)
			head = p1;
		else
			tmpHead->next = p1;
		tmpHead = p1;
		p1 = (ND *)malloc(sizeof(ND));
		//scanf("%d", &p1->val);
	}
	tmpHead->next = NULL;
	free(p1);
	
	return head;
}

/*******
 *定头法：p->next = head->next;   head->next = p; 
*******/

ND *creatList2()//头插法--移头法
{
	ND *head, *p;
	int i = 0;

	head = NULL;
	p = (ND*)malloc(sizeof(ND));
	for(i = 0;i < 3;i++)
	{
		scanf("%d", &p->val);
		if(head == NULL)
		{
			head = p;
			head->next = NULL;
		}
		else
		{
			p->next = head;
			head = p;
		}
		p = (ND *)malloc(sizeof(ND));
	}
	free(p);
	return head;
}

void outputList(ND *head)//输出链表
{
	for(;head != NULL;head = head->next)
		printf("%d\n", head->val);
}

//void del//删除节点

void insert(ND *head, int pos)//在pos后增加节点
{
	int i = 0;
	ND *p = NULL;
	for(i = 1;head != NULL;i++)
	{
		if(i == pos)
		{
			p = (ND *)malloc(sizeof(ND));
			scanf("%d", &p->val);
			p->next = head->next;
			head->next = p;
			break;
		}
	}
}
int main()
{
	ND *st;
	st = creatList();
	insert(st,2);
	outputList(st);
	return 0;
}