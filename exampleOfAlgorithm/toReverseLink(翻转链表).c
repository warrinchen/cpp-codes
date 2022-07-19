#include<stdio.h>
#include<stdlib.h>

#define N 20

/* User Code Begin(Limit: lines<=5, lineLen<=60, 考生可在本行后添加代码、仅5行、行长<=60字符，功能是节点类型Link定义) */
struct Link
{
	int data;
	struct Link *next;
};
/* User Code End(考生添加代码结束) */

void dispLink(struct Link *Head);  /* 根据给定的链首Head，显示整个链表中的数据，同时检查两次使用的链表是否刚好反序 */
/* User Code Begin(Limit: lines<=2, lineLen<=60, 考生可在本行后添加代码、仅2行、行长<=60字符，功能是用户自定义函数的原型声明) */
struct Link *reverseLink(struct Link *Head);
struct Link *creatLink();
/* User Code End(考生添加代码结束) */

int main(void)
{
	struct Link *Head;

	Head = creatLink();  /* 创建新链表 */
	printf("\nbefore:");
	dispLink(Head);

	Head = reverseLink(Head);  /* 反转链表 */
	printf("\nafter:");
	dispLink(Head);

	return 0;
}

void dispLink(struct Link *Head)
{
	static struct Link *oLink[2][N];
	static int callNumber = -1;
	int i = 0;

	callNumber++;
	if (callNumber > 1)
	{
		printf("Error, call invalid!\n");
		return ;
	}
		
	while (Head != NULL)
	{
		oLink[callNumber][i] = Head;
		i++;
		printf("%d ", Head->data);
		Head = Head->next;
	}
	printf("\n");

	if (1 == callNumber)
	{
		for (i=0; i<N; i++)
		{
			if (oLink[0][i] != oLink[1][N-1-i])
			{
				printf("Error, Link not reverse!\n");
				return ;
			}
		}
	}
}

/* User Code Begin(考生在此后根据设计需要完成程序的其它部分，行数不限) */
struct Link *creatLink()
{
	struct Link *head = NULL, *p1=NULL, *p2=NULL;
	int i;

	p2 = p1 =(struct Link *)malloc(sizeof(struct Link));
	for(i = 0;i<20;i++)
	{
		p1->data = i;
		if(head==NULL)
			head = p1;
		else
			p2->next = p1;
		p2 = p1;
		p1 = (struct Link *)malloc(sizeof(struct Link));
	}
	p2->next=NULL;
	free(p1);
	return head;
}

struct Link *reverseLink(struct Link *Head)//翻转链表
{
	struct Link *pt,*ph,*pn;//phead, ptemporary, pnext， 三个一起移动
	ph=pt=pn=Head;
	Head=Head->next;
	ph->next=NULL;
	for(;Head!=NULL;)
	{
		pt=Head;
		pn=Head->next;
		Head->next =ph;
		ph = pt;
		Head=pn;
	}
	Head=ph;
	return Head;
}