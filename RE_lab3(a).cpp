#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define LENGTH 128

char* GetStr(void)
{
	char buf[LENGTH] = "";
	size_t len = 0;
	char* string = (char*)malloc(sizeof(char));
	if (!string)
	{
		printf("There's not enough memory!");
		return NULL;
	}
	*string = '\0';
	int n = 0;
	do
	{
		n = scanf("%127[^\n]", buf, LENGTH);
		if (n > 0)
		{
			len += strlen(buf);
			char* tmp_ptr = (char*)realloc(string, len + 1);
			if (!tmp_ptr)
			{
				printf("It's not enough memory!");
				free(string);
				return NULL;
			}
			string = tmp_ptr;
			strcat(string, buf);
		}
		else if (n == 0)
			scanf("%*c");
		else
		{
			free(string);
			return NULL;
		}
	} while (n > 0);
	return string;
}

char* SkipSpace(char* s)
{
	int k;
	k=strspn(s," \t");
	return s+k;
}

char* SkipWord(char* s)
{
	int k;
	k=strcspn(s," \t");
	return s+k;
}

char* BitOfTruth(char* s)
{
	int i,count_sum;
	int num,count;
	char bit_0[3]=" 0";
	char bit_1[3]=" 1";
	char* s1;
	s1=(char*)malloc(sizeof(char));
	count_sum=0;
	s1=s;
	for (i=0;s!='\0';i++)
	{
		s=SkipSpace(s);	
		if(strcspn(s," ")==0)
				break;
		num=atoi(s);
		while(num!=0)
		{
			count=num%10+count;
			num=num/10;
		}
		count_sum=count_sum+count;
		count=0;
		s=SkipWord(s);
	}
	if (count_sum%2==1)
		s1=strcat(s1,bit_1);
	else
		s1=strcat(s1,bit_0);
	printf("%s\n",s1);
	free(s1);
	return 0;
}

int main(void)
{
	int i,j,k;
	bool flag,flag1;
	char* s1;
	s1=(char*)malloc(sizeof(char));
	flag=true;
	flag1=true;
	k=0;
	while (puts("enter..."),s1=GetStr())
	{
		if ((atoi(s1)==0)&&(strcspn(s1,"0")==strlen(s1)))
			flag1=false;
		if(flag1)
			BitOfTruth(s1);
		flag1=true;
	}
	puts("That's all. Bye!'");
	free(s1);
}
