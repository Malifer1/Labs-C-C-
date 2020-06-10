#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <io.h>

#define SIZE 10
#define LENGTH 128
#define OPTIONS 9

typedef struct Ttable
{
	int key;
	int version;
	char* info;
	int size;
}table;

extern FILE* f_ptr;

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

void AddNewElement(table* tab, int key, char* info, int size)
{
	if (SearchByKey(tab, 0) == -1)
	{
		printf("\n");
		printf("Place for this element was not found!\n");
	}
	else
	{
		char* info1 = (char*)malloc(strlen(info));
		info1 = strcpy(info1,info);
		int version = SearchOfVersion(tab, key);
		table Item = { key, version, info1, size };
		tab[SearchByKey(tab, 0)] = Item;	
	}
}

table* load_from_file(table* tab)
{
	if (access("Genoside", F_OK) != -1)
        {
                FILE * fp;
                fp = fopen("Genoside", "r");
                if (fp == NULL)
                        exit(1);
		table* element = (table*)malloc(sizeof(table));
		while (!feof(fp))
		{
			int ret = fread(element, sizeof(table), 1, fp);
			if (feof(fp))
			{
				fclose(fp);
				free(element);
				return tab;
			}
			char* info = (char*)malloc(element->size);
			fread(info, sizeof(char), element->size, fp);
			AddNewElement(tab, element->key, info, element->size);
			free(info);
		}
		free(element);
	    fclose(fp);
        }
        return tab;
}

int send_to_file(table* tab)
{
	int i1,i2;
	if (tab == NULL) return 1;
        FILE *fp;
        fp = fopen("Genoside", "w+");
        for (i1=0; i1<SIZE; i1++)
        {
        	if(tab[i1].info)
        	{
        		fwrite(tab+i1, sizeof(table), 1, fp);
        		fwrite((*(tab+i1)).info, sizeof(char),(*(tab+i1)).size, fp);
        	}
		}
        fclose(fp);
        return 0;
}

void Printing(table *tab)
{
	size_t i;
	printf("   | KEY | VERSION | INFO |\n");
	for (i = 0; i < SIZE /*&& tab[i].key*/; i++)
		printf("%zu. |%5d|%9d|%6s|\n", i, tab[i].key, tab[i].version, tab[i].info); 
}

void DeleteAllVersions(table* tab)
{
	int i, j, k, count, max_version, current_key;
	max_version=1;
	for (i=0; i<SIZE; i++)
	{
		if (tab[i].key!=0)
		{
			current_key=tab[i].key;
			for (j=0; j<SIZE; j++)
			{
				if ((tab[i].key==tab[j].key)&&(max_version<tab[j].version))
					max_version=tab[j].version;	
			}
			for (j=0 ; j<SIZE; j++)
			{
				if ((tab[j].key==current_key)&&(tab[j].version<max_version))
				{
					table Item = {0, 0, NULL, 0};
					tab[j]=Item;
				}
			}
			max_version=1;
		}
	}
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
		"4 - Delete all versions except last",
		"5 - Search by Key",
		"6 - Search by Version",
		"7 - Print",
		"8 - Show options"
	};

	for (i = 0; i < OPTIONS; ++i)
		printf("%s\n", menu[i]);

	printf("\n");
}

int main()
{
	PrintMenu();
	int i;
	table tab[SIZE] = { 0, 0, NULL, 0};
	load_from_file(tab);
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
			AddNewElement(tab, key, info, strlen(info));
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
		else if (opt ==4)
		{
			DeleteAllVersions(tab);
			printf("All extra versions were deleted succesfully!\n");
		}
		else if (opt == 5)
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
		else if (opt == 6)
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
		else if (opt == 7)
			Printing(tab);
		else if (opt == 8)
		{
			printf("\n");
			PrintMenu();
		}
		else
			printf("The wrong option!\n");
		printf("\n");
	}
	send_to_file(tab);
	free(tab);
	return 0;
}

