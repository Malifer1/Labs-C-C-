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

void swap(table *const tab, const size_t i, const size_t j)
{
	table tmp = tab[i];
	tab[i] = tab[j];
	tab[j] = tmp;
}

void Sorting(table* tab)
{
	size_t i,j;
	for (i = 0; i < SIZE; i++)

		for (j = i; j < SIZE; j++)

			if (tab[i].key)
			{
				if (tab[i].key > tab[j].key)
					swap(tab, i, j);

				if (tab[i].key == tab[j].key && tab[i].version > tab[j].version)
					swap(tab, i, j);
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
		Sorting(tab);	
	}
};

int SearchOfVersion(const table* tab, const int key)
{
	size_t i;
	int pos = SearchByKey(tab, key);
	if (pos == -1)
		return 1;
	int version = 0;
	int max_version = 0;
	for (i = pos; pos != 0 && tab[i].key == key; i--)
		version++;	
	for (i = pos; tab[i].key == key; i++)
	{
		max_version = tab[i].version;
		version = max_version;
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
		n = scanf_s("%127[^\n]", buf, LENGTH);
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
			scanf_s("%*c");
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
	Sorting(tab);
};

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
	Sorting(tab);
};

int SearchByKey(const table* tab, const int key)
{
	int left = 0, 
		mid = 0,
		right = SIZE - 1;

	while (left <= right)
	{
		mid = (left + right) / 2;

		if (tab[mid].key < key)
			left = mid + 1;

		else if (tab[mid].key > key)
			right = mid - 1;

		else if (tab[mid].key == key)
			return mid;
	}

	return -1;
};

int SearchByVersion(const table* tab, const int key, const int version)
{
	int left = 0,
		mid = 0,
		right = SIZE - 1;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (tab[mid].key < key)
			left = mid + 1;
		else if (tab[mid].key > key)
			right = mid - 1;
		else if (tab[mid].key == key)
			while (left <= right)
			{
				mid = (left + right) / 2;
				if (tab[mid].version < version)
					left = mid + 1;
				else if (tab[mid].version > version)
					right = mid - 1;
				else if (tab[mid].version == version)
					return mid;
			}

	}
	return -1;
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
};

int main()
{
	PrintMenu();
	int i;
	table tab[SIZE] = { 0, 0, NULL};
	while (1)
	{
		size_t opt = 0;
		printf("Your option\n>");
		scanf_s("%zu", &opt);
		if (opt == 0)
			break;
		else if (opt == 1)
		{
			int key = 0;
			printf("Your key\n>");
			scanf_s("%d", &key);
			printf("Your info\n>");
			scanf_s("%*c");
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
			scanf_s("%d", &key);
			DeleteByKey(tab, key);
		}
		else if (opt == 3)
		{
			int key = 0,
			version = 0;
			printf("Enter your key\n>");
			scanf_s("%d", &key);
			printf("Enter your version\n>");
			scanf_s("%d", &version);
			DeleteByVersion(tab, key, version);
		}
		else if (opt == 4)
		{
			int key = 0;
			printf("Enter your key\n>");
			scanf_s("%d", &key);
			int pos = SearchByKey(tab, key);
			if (pos == -1)
				printf("The element was not found!\n");
			else
			{
				printf("   | KEY | VERSION | INFO |\n");
				for (i = pos; tab[i].key == key; i--)
					pos = i;
				for (i = pos; tab[i].key == key; i++)
				{
					printf("%d. |%5d|%9d|%6s|\n", i, tab[i].key, tab[i].version, tab[i].info);
				}

			}
		}
		else if (opt == 5)
		{
			
			int key = 0;
			int version = 0;
			printf("Enter your key\n>");
			scanf_s("%d", &key);
			printf("Enter your version\n>");
			scanf_s("%d", &version);
			int pos = SearchByVersion(tab, key, version);
			if (pos == -1)
				printf("The element was not found!\n");
			else 
			{
				printf("   | KEY | VERSION | INFO |\n");
				printf("%d. |%5d|%9d|%6s|\n", pos, tab[pos].key, tab[pos].version, tab[pos].info);
			}
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
