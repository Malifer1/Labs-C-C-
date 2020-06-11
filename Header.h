#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define SIZE 10
#define LENGTH 128
#define OPTIONS 8

struct ElementOfTree                                                                                                    //Структура стандартого элемента дерева
{
	char* key;
	char* str;
	struct ElementOfTree* Parent;
	struct ElementOfTree* Right;
	struct ElementOfTree* Left;
};

void Load(char* path, struct ElementOfTree** trunk);                                                                     //Ввод корня и запуск алгоритма наращивания веток изпо данным из файла 

char* GetStr(int a);                                                                                                     //Функция ввода строки символов

void PrintMenu(void);                                                                                                    //Функция для Вывода меню на экран

int AddNewBranch(struct ElementOfTree** trunk, char* key, char* str);                                                    //Функция добавления нового элемента графа

void Printing(struct ElementOfTree* trunk);                                                                              //Функция для Вывода элементов графа на экран

struct ElementOfTree* SearchNode(const struct ElementOfTree* Branch, char* key);                                         //Вспомогательная Функция для поиска конкретного элемента графа

void PrintOne(const struct ElementOfTree* Branch, const int key);                                                        //Функция для Вывода конкретного элемента графа на экран

void LoadingAdditional(struct ElementOfTree* Branch);                                                                    //Алгоритм наращивания веток по данным из файла

void WritingData(struct ElementOfTree* Branch);                                                                          //Алгоритм для записи в файл данных об элементах графа

void Save(char* path, struct ElementOfTree* Branch);                                                                     //Функция активирующая алгоритм по записи данных об элементах графа файл

int FromTo(char** key);                                                                                                  //Вспомогательная Функция по переводу символов по таблице ASCII в цифровой эквивалент

void DeleteNode(struct ElementOfTree** ptr, struct ElementOfTree* tmp);                                                  //Функция для удаления элемента графа

struct ElementOfTree* MaxElement(struct ElementOfTree* ptr);                                                             //Вспомогательная Функция по нахождению максимального элемента после переданного на вход 

struct ElementOfTree* MinElement(struct ElementOfTree* ptr);                                                             //Вспомогательная Функция по нахождению минимального элемента после переданного на вход 

int Timing( void );

void DelTree(struct ElementOfTree**);


















/*char* GetStr(void);

void AddNewBranch(struct ElementOfTree* trunk, int* key, char* str);

int FromTo(int* key);

int* GetKey(void);

void PrintMenu(void);

struct ElementOfTree* Habitation(struct ElementOfTree* trunk, int* key);

struct Node
{
	int key;
	struct Item* info;
};

struct Item
{
	int version;
	char* string;
	struct Item* next;
};

int SearchByKey(const struct Node* tab, const int key);

int SearchOfVersion(const struct Node* tab, const int key);

void Printing(struct Node* tab);

void swap(struct Node* tab, const size_t i, const size_t j);

void Sorting(struct Node* tab);

void DeleteByKey(struct Node* tab, const size_t key);

void DeleteByVersion(struct Node* tab, const size_t key, size_t version); */
