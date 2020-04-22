#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define LENGTH 128

typedef struct Node
{
	char Head;
	struct Node *next;
} Node;

Node *CreateList(const char *str)
{
	Node head={'*',NULL};
	Node *last=&head;
	while(*str!='\0')
	{
		last->next=(Node*)malloc(sizeof(Node));
		last=last->next;
		last->Head=*str++;
		last->next=NULL;
	}
	return head.next;
}

Node *add_space (Node *p)
{
	Node *head;
	head=p;
	while(p->next!=NULL)
		p=p->next;
	p->next=(Node*)malloc(sizeof(Node));
	p=p->next;
	p->Head=' ';
	p->next=NULL;
	return head;
}

Node *DeleteList(Node *ptr)
{
	Node *tmp=NULL;
	while (ptr!=NULL)
	{
		tmp=ptr;
		ptr=ptr->next;
		free(tmp);
	}
	return ptr;
}

Node *SkipWord(Node *ptr)
{
	while((ptr->Head!=' ')&&(ptr->Head!='\t'))
		ptr=ptr->next;
	return ptr;
}

Node *SkipSpace(Node *ptr)
{
	while((ptr->Head==' ')||(ptr->Head=='\t'))
		ptr=ptr->next;
	return ptr;
}

Node *SkipSpace_ex_one(Node *ptr)
{
	while((ptr->next!=NULL)&&((ptr->next->Head==' ')||(ptr->next->Head=='\t')))
		ptr=ptr->next;
	return ptr;
}

void putList(char *msg, Node *ptr)
{
	printf("%s:\"",msg);
	for(; ptr!=NULL;ptr=ptr->next)
		printf("%c",ptr->Head);
	printf("\"\n");
}

int getList(Node **pptr)
{
	char buf[81], *str;
	Node head = {'*', NULL };
	Node *last = &head;
	int n, rc = 1;
	do
	{
		n = scanf("%80[^\n]", buf);
		if(n < 0)
		{
			DeleteList(head.next);
			head.next = NULL;
			rc = 0;
			continue;
		}
	if(n > 0)
	{
		for(str = buf; *str != '\0'; ++str)
		{
			last->next = (Node *)malloc(sizeof(Node));
			last = last->next;
			last->Head = *str;
		}
	last->next = NULL;
	}
	else
		scanf("%*c");
	}
	while(n > 0);
	*pptr = head.next;
	return rc;
}

Node *find_last_letter (Node *p)
{
	while((p->next->Head!=' ')&&(p->next->Head!='\t')&&(p->next!=NULL))
		p=p->next;
	return p;
}

Node *find_last_prev_letter (Node *p, Node *p1)
{
	if(p!=p1)
	{
		while(p->next!=p1)
			p=p->next;
	}
	return p;
}

Node *reorg (Node *ptr)
{
	Node *last=NULL;
	Node *last1=NULL;
	Node *first;
	Node *tmp;
	Node *tmp1;
	bool flag;
	flag=1;
	tmp=SkipWord(ptr);
	last=find_last_letter(ptr);
	while(tmp!=NULL)
	{
		do
		{
			last1=find_last_prev_letter(ptr,last);
			last->next=last1;
			if(flag)
			{
				first=last;
				flag=false;
			}
			last=last->next;
		}while(last1!=ptr);
		ptr=SkipSpace_ex_one(tmp);
		if(ptr->Head=='\t')
			ptr->Head=' ';
		if(ptr->next==NULL)
			last->next=NULL;
		else
		{
			last->next=ptr;
			last=last->next;
		}
		if(last->next==NULL)
			break;
		tmp1=ptr->next;
		tmp=SkipWord(tmp1);
		ptr=ptr->next;
		last->next=find_last_letter(ptr);
		last=last->next;
	}
	return first;
}


int main(void)
{
	Node *ptr;
	Node *tmp;
	while(puts("enter the string..."),getList(&ptr))
	{
		ptr=SkipSpace(ptr);
		ptr=add_space(ptr);
		ptr=reorg(ptr);
		putList("Result of reorganisation",ptr);
		ptr=DeleteList(ptr);
	}
	return 0;
}
