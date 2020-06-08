#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define SIZE 10
#define LENGTH 128
#define OPTIONS 8

typedef struct Ttable
{
	int key;
	int version;
	char* info;
}
table;

int SearchByKey(const table* tab, const int key)
{
	int i=0, j=0;
	for (i; i<SIZE; i++)
	{
		if(tab[i].key==key)
		{
			return i;
			break;
		} 
	}

	return -1;
};

int SearchOfVersion(const table* tab, const int key)
{
	int i=0;
	int version;
	version=1;
	for (i; i<SIZE; i++)
	{
		if (tab[i].key==key)
			version++;
	}
	return version;
};

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

void DeleteByKey(table* tab, const int key)
{
	int i;
	int res = SearchByKey(tab, key);
	if (res == -1)
	{
		printf("The element was not found!\n");
	}
	else
	{
		for (i = res; tab[i].key == key; i++)
			res = i;
		for (i = res; tab[i].key == key; i--)
		{
			table Item = { 0, 0, NULL };
			tab[i] = Item;
		}
	}
//	Sorting(tab);
};

int SearchByVersion(const table* tab, const int key, const int version)
{
	int i=0;
	for (i; i<SIZE; i++)
	{
		if ((tab[i].key==key)&&(tab[i].version==version))
			return i;
	}
	return -1;
}

table* SearchKeyNewTab(table* tab, const int key)
{
	table* tab1=(table*)malloc(sizeof(table));
	tab1=NULL;
	int i,j;
	j=0;
	for(i=0; i<SIZE; i++)
	{
		if(tab[i].key==key)
		{
			tab1=(table*)realloc(tab1,sizeof(table)*(j+1));
			tab1[j]=tab[i];
			j++;
		}
	}
	return tab1;
}

table* SearchVersionNewTab(table* tab, const int key, const int version)
{
	table* tab1=(table*)malloc(sizeof(table));
	int i,j;
	j=0;
	for(i=0; i<SIZE; i++)
	{
		if((tab[i].key==key)&&(tab[i].version==version))
		{
			tab1[j]=tab[i];
			return tab1;
		}
	}
	return NULL;
}

void DeleteByVersion(table* tab, const int key, const int version)
{
	int res = SearchByVersion(tab, key, version);
	if (res == -1)
	{
		printf("The element was not found!");
	}
	else
	{
		table Item = { 0, 0, NULL };
		tab[res] = Item;
	}
}

void AddNewElement(table* tab, int key, char* info)
{
	if (SearchByKey(tab, 0) == -1)
	{
		printf("\n");
		printf("Place for this element was not found!\n");
	}
	else
	{
		int version = SearchOfVersion(tab, key);
		table Item = { key, version, info };
		tab[SearchByKey(tab, 0)] = Item;	
	}
}

void Printing( table *tab)
{
	size_t i;
	printf("   | KEY | VERSION | INFO |\n");
	for (i = 0; i < SIZE /*&& tab[i].key*/; i++)
		printf("%zu. |%5d|%9d|%6s|\n", i, tab[i].key, tab[i].version, tab[i].info); 
}

void PrintMenu(void)
{
	size_t i;
	char* menu[OPTIONS] =
	{
		"0 - Exit",
		"1 - Insert",
		"2 - Erase by key",
		"3 - Erase by key and version",
		"4 - Search by Key",
		"5 - Search by Version",
		"6 - Print",
		"7 - Show options"
	};

	for (i = 0; i < OPTIONS; ++i)
		printf("%s\n", menu[i]);

	printf("\n");
}

int main()
{
	PrintMenu();
	int i;
	table tab[SIZE] = { 0, 0, NULL};
	while (1)
	{
		size_t opt = 0;
		printf("Your option\n>");
		scanf("%zu", &opt);
		if (opt == 0)
			break;
		else if (opt == 1)
		{
			int key = 0;
			printf("Your key\n>");
			scanf("%d", &key);
			printf("Your info\n>");
			scanf("%*c");
			char* info = NULL;
			info = GetStr();
			if (info == NULL)
				return 0;
			AddNewElement(tab, key, info);
		}
		else if (opt == 2)
		{
			printf("Enter the key\n>");
			int key = 0;
			scanf("%d", &key);
			DeleteByKey(tab, key);
		}
		else if (opt == 3)
		{
			int key = 0,
			version = 0;
			printf("Enter your key\n>");
			scanf("%d", &key);
			printf("Enter your version\n>");
			scanf("%d", &version);
			DeleteByVersion(tab, key, version);
		}
		else if (opt == 4)
		{
			int i;
			table* tab1;
			int key = 0;
			printf("Enter your key\n>");
			scanf("%d", &key);
			tab1 = SearchKeyNewTab(tab, key);
			if (tab1==NULL)
				printf("No elements with such key were found\n");
			else
			{
				for(i=0; i<SIZE; i++)
				{
					if(tab1[i].key==key)
						printf("%d. |%5d|%9d|%6s|\n", i, tab1[i].key, tab1[i].version, tab1[i].info);
				}
			}
			free(tab1);
			
		}
		else if (opt == 5)
		{
			table* tab1;
			int key = 0;
			int version = 0;
			printf("Enter your key\n>");
			scanf("%d", &key);
			printf("Enter your version\n>");
			scanf("%d", &version);
			tab1=SearchVersionNewTab(tab,key,version);
			if (tab1!=NULL)
				printf("%d. |%5d|%9d|%6s|\n", i, tab1[i].key, tab1[i].version, tab1[i].info);
			else
				printf("No key this such version was found!\n");
			free(tab1);
			
		}
		else if (opt == 6)
			Printing(tab);
		else if (opt == 7)
		{
			printf("\n");
			PrintMenu();
		}
		else
			printf("The wrong option!\n");
		printf("\n");
	}
	return 0;
}
