
/* Лаба 1. Вариант 30.
	Из входного потока вводится прямоугольная сильно разреженная матрица целых чисел [aij], i = 1, …, m, j = 1, …, n.  Значения m и n заранее не известны и вводятся из входного потока.
Сформировать новую матрицу, поместив в ее i-ую строку элементы из i-ой строки исходной матрицы, являющиеся палиндромами.
Исходную и полученную матрицы вывести в выходной поток с необходимыми комментариями.*/


#include "Lab1.h"

using namespace Lab1;

extern const char* msgs[];




/* Массив указателей на функции - для реализации выбора функции; порядок перечисления функций в списке инициализации должен соответсвовать порядку указания альтернатив в списке альтернатив */
int(*fptr[])(SparseMatrix*) = { NULL, D_Add, D_Show };


int main() {
	setlocale(0, "");
	SparseMatrix SourceMatrix = { 0, 0, nullptr };		// Исходная разряженная матрица
	SparseMatrix ResultMatrix = { 0 , 0, nullptr };		// Результирующая матрица
	Input(SourceMatrix);
	int rc;
	while (rc = dialog(msgs, NMsgs))
		if (!fptr[rc](&SourceMatrix))
			break;
	Delete(&SourceMatrix);
	Delete(&ResultMatrix);
	return 0;
}