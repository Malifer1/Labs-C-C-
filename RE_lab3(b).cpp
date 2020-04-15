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

Node *change_pointers (Node *p1, Node *p2)
{
	Node *tmp;
	tmp=p1;
	p1=p2;
	p2=tmp;
}

Node *find_last_letter (Node *p)
{
	while((p->Head!=' ')||(p->Head!='\t'))
		p=p->next;
	return p;
}

Node *find_last_prev_letter (Node *p, Node *p1)
{
	while(p->next!=p1)
		p=p->next;
}

Node *reorg (Node *p)
{
	Node *last=NULL;
	Node *last1=NULL;
	Node *first=p;
	Node *first1=p;
	Node *tmp=NULL;
	bool flag;
	flag=1;
	p=SkipSpace(p);
	tmp=find_last_letter(p);
	printf("%c",tmp->Head);
	while(p!=NULL)
	{
		last=find_last_letter(p);
		printf("%c",last->Head);
		do
		{
			printf("%d\n",flag);
			last=find_last_prev_letter(p,last);
			last1=last;
			first1=first;
			change_pointers(first,last);
			first=first1->next;
			last=last1;
		}
		while((first->next!=last)||(first!=last));
		p=find_last_letter(p)->next;
		if(p==NULL)
			break;
		while((p->Head==' ')||(p->Head=='\t'))
			p=p->next;
	}	
		
}


int main(void)
{
	Node *ptr;
	Node *tmp;
	while(puts("enter the string..."),getList(&ptr))
	{
		putList("Entered string",ptr);
		reorg(ptr);
		putList("Entered string",ptr);
		ptr=DeleteList(ptr);
	}
	return 0;
}
