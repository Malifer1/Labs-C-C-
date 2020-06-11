//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                    Перед вами файл с функциями для выполнения программы                                                      */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                                                                                                                                //
																																								//
#define _CRT_SECURE_NO_WARNINGS																																	//
#include "Header.h"				     																															//
																																								//
#include <stdio.h>				     																															//
#include <stdbool.h>																																			//
#include <string.h>				    																															// 
#include <stdlib.h>			     																																//
#include <io.h>							            																											//
#include <time.h>																	     																		//
																																								//
extern FILE* f_ptr;																																				//
                                                                                                                                                                //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                        Далее находятся функции для Ввода и добавления                                                        */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char* GetStr(int a)                                                                                      //Функция ввода строки символов
{
	char buf[LENGTH] = "";
	int len = 0;
	char* string = (char*)malloc(sizeof(char));


	if (!string)
	{

		printf("There's not enough memory!");
		return NULL;

	}

	if (a == 0)
		scanf_s("%*c");
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

int AddNewBranch(struct ElementOfTree** trunk, char* key, char* str)                                     //Функция добавления нового элемента графа
{
	//struct ElementOfTree** Branch = *trunk;

	if (*trunk == NULL)
	{
		struct ElementOfTree* Leaf = (struct ElementOfTree*)malloc(sizeof(struct ElementOfTree));

		if (!Leaf)
			return 0;

		Leaf->Parent = NULL;
		Leaf->Left = NULL;
		Leaf->Right = NULL;
		Leaf->key = key;
		Leaf->str = str;

		*trunk = Leaf;
	}
	else
	{
		struct ElementOfTree* parent = *trunk;

		if (!parent)
			return 0;

		struct ElementOfTree* tmp = *trunk;
		struct ElementOfTree** pmt = NULL;

		if (!tmp)
			return 0;

		while (tmp != NULL)
		{
			parent = tmp;

			if (tmp->key == key)
			{
				printf("\nSorry, but an element with this key has already been added\n");
				return 0;
			}

			else if (FromTo(&tmp->key) > FromTo(&key))
				pmt = &tmp->Left, tmp = tmp->Left;

			else
				pmt = &tmp->Right, tmp = tmp->Right;

		}

		*pmt = (struct ElementOfTree*)malloc(sizeof(struct ElementOfTree));
		(*pmt)->Parent = parent;
		(*pmt)->Right = NULL;
		(*pmt)->Left = NULL;
		(*pmt)->key = key;
		(*pmt)->str = str;
	}
	return 1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                                           ******                                                                             */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                          Далее находятся функции для работы с файлом                                                         */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Load(char* path, struct ElementOfTree** trunk)                                                     //Функция для создания корня и запуск алгоритма наращивания веток по данным из файла 
{
	if (_access(path, 0))
	{
		printf("Creating the file with the name \"%s\"...\n", path);

		*trunk = NULL;
	}

	else
		printf("Loading the file with the name \"%s\"...\n", path);

	printf("\n");

	fopen_s(&f_ptr, path, "rb");

	if (!f_ptr)
		return;

	size_t sizeKey = 0;
	size_t sizeStr = 0;

	int a = fscanf_s(f_ptr, "%zu ", &sizeKey);
	if (a == -1)
		return;

	*trunk = (struct ElementOfTree*)malloc(sizeof(struct ElementOfTree));

	if (!(*trunk))
		return;

	

	(*trunk)->key = (char*)calloc(sizeKey + 1, sizeof(char));

	if (!(*trunk)->key)
		return;

	fgets((*trunk)->key, sizeKey + 1, f_ptr);

	(*trunk)->Parent = NULL;

	fscanf_s(f_ptr, "%zu ", &sizeStr);

	(*trunk)->str = (char*)calloc(sizeStr + 1, sizeof(char));

	if (!(*trunk)->str)
		return;

	(*trunk)->Left = NULL;

	(*trunk)->Right = NULL;

	fgets((*trunk)->str, sizeStr + 1, f_ptr);

	LoadingAdditional(*trunk, (*trunk)->Parent);

	fclose(f_ptr);
}                                                   //Функция активирующая алгоритм со

void LoadingAdditional(struct ElementOfTree* Branch)                                                   //Алгоритм наращивания веток по данным из файла
{
	char* key = (char*)malloc(sizeof(char));

	if (!key)
		return;

	char* str = (char*)malloc(sizeof(char));

	if (!str)
		return;

	size_t sizeKey = 0;
	size_t sizeStr = 0;


	while (fscanf_s(f_ptr, "%zu \n", &sizeKey) > 0)                                      
	{
		char* key = (char*)malloc(sizeof(char));

		if (!key)
			return;

		char* str = (char*)malloc(sizeof(char));

		if (!str)
			return;

		fgets(key, sizeKey + 1, f_ptr);
		fscanf_s(f_ptr, "%zu \n", &sizeStr);
		fgets(str, sizeStr + 1, f_ptr);

		AddNewBranch(&Branch, key, str);
	}
}

void WritingData(struct ElementOfTree* Branch)                                                          //Алгоритм для записи в файл данных об элементах графа 
{
	if (Branch == NULL)
		return;

	else
		fprintf(f_ptr, "%zu %s %zu %s\n", strlen(Branch->key), Branch->key, strlen(Branch->str), Branch->str);

	WritingData(Branch->Left);

	WritingData(Branch->Right);
}

void Save(char* path, struct ElementOfTree* Branch)                                                      //Функция активирующая алгоритм по записи данных об элементах графа файл
{
	fopen_s(&f_ptr, path, "w");

	if (!f_ptr)
		return;

	WritingData(Branch);

	fclose(f_ptr);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                                           ******                                                                             */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                           Далее находятся функции для Визуализации                                                           */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PrintMenu(void)                                                                                 //Функция для Вывода меню на экран
{
	char* menu[OPTIONS] =
	{
		"0 - Exit",
		"1 - Add",
		"2 - Timing",
		"3 - Erase by key",
		"4 - Search by Key",
		"5 - Print by Key",
		"6 - Print all",
		"7 - Show options"
	};

	for (int i = 0; i < OPTIONS; ++i)
		printf("%s\n", menu[i]);

	printf("\n");
}

void Printing(struct ElementOfTree* trunk)                                                            //Функция для Вывода элементов графа на экран
{
	if (trunk == NULL)
		return;

	Printing(trunk->Left);
	Printing(trunk->Right);
	if (trunk->key)
		printf("\n\nKey:%s\nString:%s", trunk->key, trunk->str);
}

void PrintOne(const struct ElementOfTree* Branch, const int key)                                     //Функция для Вывода конкретного элемента графа на экран
{
	if (Branch == NULL)
		return;
	if (Branch->key)
		printf("\n\nThe element is found\b\bKey:%s\nString:%s", Branch->key, Branch->str);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                                           ******                                                                             */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                            Далее находятся Вспомогательные функции                                                           */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int FromTo(char** key)                                                                              //Вспомогательная Функция по переводу символов по таблице ASCII в цифровой эквивалент
{
	char buf[LENGTH] = "";
	strcat(&buf, *key);
	
	int len = strlen(buf);
	int Res = 0;

	for (int i = 0; i < len; i++)
	{
		Res += buf[i];                                  
	}

	return Res;
}

struct ElementOfTree* SearchNode(const struct ElementOfTree* Branch, char* key)                        //Вспомогательная Функция для поиска конкретного элемента графа
{
	if (Branch == NULL)
		return NULL;
	if (Branch->key  == key)
		return Branch;

	if (FromTo(&Branch->key) > FromTo(&key))
		return SearchNode(Branch->Left, key);

	else if (FromTo(&Branch->key) < FromTo(&key))
		return SearchNode(Branch->Right, key);

	else
		return Branch;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                                           ******                                                                             */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                          Далее находятся функции для Удаления Графа                                                          */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DeleteNode(struct ElementOfTree** ptr, struct ElementOfTree* tmp)                                 //Функция для удаления элемента графа
{
	struct ElementOfTree* m = tmp->Parent;

	if (!tmp->Left && !tmp->Right)
	{
		if (m == NULL)
		{
			*ptr = NULL;

			free(*ptr);

			return;
		}

		else if (tmp == m->Left)
		{
			tmp->Parent->Left = NULL;

			free(tmp);

			return;
		}

		else
		{
			tmp->Parent->Right = NULL;

			free(tmp);

			return;
		}
	}

	else if (!tmp->Left && tmp->Right) // Правое поддерево 
	{
		if (!m)
		{
			*ptr = tmp->Right;

			free((*ptr)->Parent);

			(*ptr)->Parent = NULL;

			return;
		}

		if (tmp == m->Right)// С правой стороны
		{
			struct ElementOfTree* max = MaxElement(tmp);

			struct ElementOfTree* min = MinElement(max);

			m->Right = max;

			if (tmp->Right != max)
			{
				max->Parent->Right = NULL;

				max->Parent = m;

				min->Left = tmp->Right;

				tmp->Right->Parent = min;
			}

			else
				max->Parent = m;

			free(tmp);

			tmp = NULL;

			return;
		}

		else// С левой стороны
		{

			struct ElementOfTree* max = MaxElement(tmp);

			struct ElementOfTree* min = MinElement(max);

			m->Left = max;

			if (tmp->Right != max)
			{
				max->Parent->Right = NULL;

				max->Parent = m;

				min->Left = tmp->Right;

				tmp->Right->Parent = min;
			}

			else
				max->Parent = m;

			free(tmp);

			tmp = NULL;

			return;
		}
	}

	else if (tmp->Left && !tmp->Right) // Левое поддерево
	{
		if (!m)
		{
			*ptr = tmp->Left;

			free((*ptr)->Parent);

			(*ptr)->Parent = NULL;

			return;
		}

		if (tmp == m->Right)// С правой стороны
		{
			struct ElementOfTree* max = MaxElement(tmp);

			struct ElementOfTree* min = MinElement(max);

			m->Right = max;

			if (tmp->Left != max)
			{
				max->Parent->Right = NULL;

				max->Parent = m;

				min->Left = tmp->Left;

				tmp->Left->Parent = min;
			}

			else
				max->Parent = m;

			free(tmp);

			tmp = NULL;

			return;
		}

		else// С левой стороны
		{
			struct ElementOfTree* max = MaxElement(tmp);

			struct ElementOfTree* min = MinElement(max);

			m->Left = max;

			if (tmp->Left != max)
			{
				max->Parent->Right = NULL;

				max->Parent = m;

				min->Left = tmp->Left;

				tmp->Left->Parent = min;
			}

			else
				max->Parent = m;

			free(tmp);

			tmp = NULL;

			return;
		}
	}

	else // И левое и правое поддеревья
	{
		if (!m)
		{
			*ptr = tmp->Right;

			(*ptr)->Left = (*ptr)->Parent->Left;

			(*ptr)->Left->Parent = *ptr;

			free((*ptr)->Parent);

			(*ptr)->Parent = NULL;

			return;
		}

		struct ElementOfTree* max = MaxElement(tmp);

		struct ElementOfTree* min = MinElement(max);

		if (tmp == m->Right)
			m->Right = max;

		else
			m->Left = max;

		if (tmp->Right != max)
		{
			max->Parent->Right = NULL;

			max->Parent = m;

			tmp->Left->Parent = tmp->Right;

			tmp->Right->Left = tmp->Left;

			min->Left = tmp->Right;

			tmp->Right->Parent = min;
		}

		else
		{
			max->Parent = m;

			min->Left = tmp->Left;

			tmp->Left->Parent = min;
		}

		free(tmp);

		tmp = NULL;

		return;
	}
}

struct ElementOfTree* MaxElement(struct ElementOfTree* ptr)                                            //Вспомогательная Функция по нахождению максимального элемента после переданного на вход 
{
	struct ElementOfTree* max = ptr;

	if (max->Right)

		while (max->Right)
			max = max->Right;

	else
	{
		if (max->Left->Right)
		{
			max = max->Left;

			while (max->Right)
				max = max->Right;
		}

		else
			max = max->Left;
	}

	return max;
}

struct ElementOfTree* MinElement(struct ElementOfTree* ptr)                                            //Вспомогательная Функция по нахождению минимального элемента после переданного на вход 
{
	struct ElementOfTree* min = ptr;

	while (min->Left)
		min = min->Left;

	return min;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                                           ******                                                                             */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                           Далее находятся функции для Таймирования                                                           */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Timing()
{
	struct ElementOfTree* root = NULL;

	int n = 10,
		k = 0,
		cnt = 1000000,
		i = 0,
		m = 0;

	char* key = (char*)malloc(10000 * sizeof(char));

	if (!key)
		return 0;

	clock_t first, last;

	srand(time(NULL));

	while (n-- > 0) {

		for (i = 0; i < 10000; ++i)
			key[i] = rand() * rand();

		for (i = 0; i < cnt; )
		{

			k = rand() * rand();

			if (AddNewBranch(&root, (char*)k, NULL))
				++i;
		}

		m = 0;

		first = clock();

		for (i = 0; i < 10000; ++i)

			if (SearchNode(root, key[i]))
				++m;

		last = clock();

		printf("%d items was found\n", m);

		printf("test #%d, number of nodes = %d, time = %d\n", 10 - n, (10 - n) * cnt, last - first);
	}

	DelTree(&root);

	return 1;

}

void DelTree(struct ElementOfTree** root)
{
	if (*root)
	{
		DelTree(&(*root)->Left);

		DelTree(&(*root)->Right);

		free(*root);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                                           ******                                                                             */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////