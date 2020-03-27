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
	} 
	while (n > 0);
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
	int* num;
	int* count;
	count=(int*)calloc(1000,sizeof(int));
	num=(int*)calloc(1000,sizeof(int));
	char bit_0[3]=" 0";
	char bit_1[3]=" 1";
	char* s1;
	char** s0;
	s0=(char**)calloc(1000,sizeof(char*));
	s0[i]=(char*)malloc(sizeof(char));
	i=0;
	count_sum=0;
	s1=s;
	for (i=0;s!='\0';i++)
	{
		if(i==0)
			s0[i]=s;
		else
		{
			s=SkipWord(s);
			s=SkipSpace(s);
			s0[i]=s;
			if(strcspn(s," ")==0)
				break;
		}
		num[i]=atoi(s0[i]);
		while(num[i]!=0)
		{
			count[i]=num[i]%10+count[i];
			num[i]=num[i]/10;
		}
	}
	for(i=0;count[i]!='\0';i++)
		count_sum=count_sum+count[i];
	if (count_sum%2==1)
		s1=strcat(s1,bit_1);
	else
		s1=strcat(s1,bit_0);
	printf("%s",s1);
	return 0;
}

int main()
{
	int i,j,k;
	bool flag,flag1;
	char* s1;
	char* s2;
	s1=(char*)malloc(sizeof(char));
	s2=(char*)malloc(sizeof(char));
	flag=true;
	flag1=true;
	k=0;
	while (flag)
	{
		printf("Enter the string\n");
		s1=GetStr();
		s1=SkipSpace(s1);
		if ((atoi(s1)==0)&&(strcspn(s1,"0")==strlen(s1)))
			flag1=false;
		printf("%s\n",s1);
		printf("Have u done with entering strings? Press 0 to finish or 1 to continue\n");
		scanf("%d",&flag);
	//	printf("%s\n",strchr(s1,k));
		if(flag1)
			BitOfTruth(s1);
		flag1=true;
		
	}
	
}
