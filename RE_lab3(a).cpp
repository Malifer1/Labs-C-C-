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

char* SkipSpaceExOne(char* s)
{
	int k;
	k=strspn(s," \t");
	if(k==0)
		return s+k;
	else
		return s+k-1;
}

char* BitOfTruth(char* s)
{
	int i,count_sum,j,k;
	int num,count,str_len;
	char bit_0[2]="0";
	char bit_1[2]="1";
	char bit_Sp[2]=" ";
	char* s1;
	s1=(char*)malloc(1);
	*s1='\0';
	str_len=strlen(s);
	j=0;
	i=0;
	while (j<str_len)
	{
		count=0;	
		while(i!=strcspn(s," \t"))
		{
			if(s[i]=='1')
			{
				s1=(char*)realloc(s1,strlen(s1)+1);
				count=count+1;
				strncat(s1,bit_1,1);
			}
			else
			{
				s1=(char*)realloc(s1,strlen(s1)+1);
				strncat(s1,bit_0,1);
			}
			i++;
		}
		if(count%2==1)
		{
			s1=(char*)realloc(s1,strlen(s1)+1);
			strncat(s1,bit_1,1);
		}
		s1=(char*)realloc(s1,strlen(s1)+1);
		strncat(s1,bit_Sp,1);
		while ((s[i]==' ')||(s[i]=='\t'))
			i++;
		s=SkipWord(s);
		s=SkipSpace(s);
		j=j+i;
		i=0;
	}
	strncat(s1,"\n",1);
	printf("%s",s1);
	s1=NULL;
	free(s1);
	return 0;
}

int main(void)
{
	int i,j,k;
	bool flag,flag1;
	char* s1;
	char* s2;
	flag1=true;
	k=0;
	while (puts("enter..."),s1=GetStr())
	{
		s2=s1;
		s1=SkipSpace(s1);
		for(i=0;i!=strlen(s1)-1;i++)
		{
			if((s1[i]!='0')&&(s1[i]!='1')&&(s1[i]!='\t')&&(s1[i]!=' '))
			{
				flag1=false;
				break;
			}
		}
		if(flag1)
			BitOfTruth(s1);
		flag1=true;
		free(s2);
	}
	puts("That's all. Bye!'");
}
