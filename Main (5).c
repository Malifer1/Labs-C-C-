#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"

#include <stdio.h>

FILE* f_ptr = NULL;

int main()
{

	struct ElementOfTree* Trunk = NULL;

	printf("Enter the name of file to cteate or load, please: ");

	char* path = GetStr(1);

	printf("\n");

	Load(path, &Trunk);

	PrintMenu();
	printf("\n\nNow, chose next option.\n\n");

	int i = 1;

	while (true)
	{
		size_t opt = 0;
		if (i != 1)
			printf("\nSelect the option\n\n");
		i++;

		scanf_s("%i", &opt);

		if (opt == 0)                                                                                  //Exit
		{
			Save (path, Trunk);
			break;
		}
		if (opt == 1)                                                                                  //Add
		{

			printf("\n\nEnter our Key: ");
			char* key = GetStr(0);
			printf("\n\nEnter your String: ");
			char* str = GetStr(1);

			AddNewBranch(&Trunk, key, str);
		}
		if (opt == 2)                                                                                  //Timing
		{
			Timing();
		}
		if (opt == 3)                                                                                  //Erase by key
		{

			printf("\n\nEnter your key:\n>");

			char* key = GetStr(0);

			struct ElementOfTree* tmp = SearchNode(Trunk, key);

			if (!tmp)
				printf("\nThere are no any elements with that key!\nTry another one!\n");

			else
				DeleteNode(&Trunk, tmp);
		}
		if (opt == 4)                                                                                  //Search by Key
		{
			printf("\n\nEnter our Key: ");
			char* keyo = GetStr(0);
			struct ElementOfTree* Element = SearchNode;
			PrintOne(Element, keyo);
		}
		if (opt == 5)                                                                                  //Print by Key
		{
			printf("\n\nEnter the Key you are looking for : ");
			char* keyS = GetStr(0);
			Printing(SearchNode(Trunk, keyS));
			printf("\n\n");
		}
		if (opt == 6)                                                                                  //Print all
		{
			Printing(Trunk);
			printf("\n\n");
		}
		if (opt == 7)                                                                                  //Show options
		{
			printf("\n");
			PrintMenu();
		}

		if (opt > 7)
			printf("The wrong option!\n");
	}
	return 0;
}