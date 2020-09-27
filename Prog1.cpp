#include <iostream>
#include "Prog1.h"

namespace Prog1{
	// функция ввода
	Line* input(int &rm)
	{
		const char *pr = ""; // будущее сообщение об ошибке
		Line *lines = NULL;  // динамический массив строк матрицы
		int m;	// количество строк матрицы
		// сначала вводим количество строк
		do{
			std::cout << pr << std::endl;
			std::cout << "Enter number of lines: --> ";
			pr = "You are wrong; repeat please!";
			if (getNum(m) < 0) // обнаружена ошибка ввода или конец файла
				return NULL;
		} while (m < 1);

		// выделяем память под массив структур - строк матрицы
		try{
			lines = new Line[m];
		}
		catch (std::bad_alloc &ba)
		{
			std::cout << "------ too many rows in matrix: " << ba.what() << std::endl;
			return NULL;
		}
		for (int i = 0; i < m; i++){
			// теперь для каждой строки матрицы вводим количество столбцов 
			pr = "";
			do{
				std::cout << pr << std::endl;
				std::cout << "Enter number of items in line #" << (i + 1) << " --> ";
				pr = "You are wrong; repeat please!";
				if (getNum(lines[i].n) < 0){ // обнаружена ошибка ввода или конец файла
					erase(lines, i); // освобождение памяти, занятой ранее введенными строками
					return NULL;
				}
			} while (lines[i].n < 1);

 
			// и выделяем необходимую память под элементы строки
			try{
				lines[i].a = new double[lines[i].n];
			}
			catch (std::bad_alloc &ba)
			{
				std::cout << "------ too many items in matrix: " << ba.what() << std::endl;
				erase(lines, i);
				return NULL;
			}

			// теперь можно вводить сами элементы данной строки матрицы
			std::cout << "Enter items for matrix line #" << (i + 1) << ":" << std::endl;
			for (int j = 0; j < lines[i].n; j++){
				if (getNum(lines[i].a[j]) < 0){ // обнаружена ошибка ввода или конец файла
					erase(lines, i + 1); // освобождение памяти, занятой ранее введенными строками
					return NULL;
				}
			}
		}
		// формируем результат - количество строк в матрице
		rm = m;
		return lines;
	}

	// функция вывода
	void output(const char *msg, Line *a, int m)
	{
		int i, j;
		std::cout << msg << ":\n";
		for (i = 0; i < m; ++i){
			for (j = 0; j < a[i].n; ++j)
				std::cout << a[i].a[j] << "  ";
			std::cout << std::endl;
		}
	}

	// функция освобождения занятой памяти
	Line *erase(Line *&lines, int m)
	{
		int i;
		for (i = 0; i < m; i++)
			delete[] lines[i].a;
		delete[] lines;
		return NULL;
	}
	
	// функция для поиска полиндромов
	int minmax( Line* &lines, int m, double & res)
	{
		Line* lines2 = NULL;
		bool flag;
		flag = 1;
		int i, j, k, count;
		count = 0;
		for (i = 0; i < m; i++)
		{
			for (j = 0; j < lines[i].n; j++)
			{
				if (lines[i].a[j] != lines[i].a[lines[i].n - j])
					flag = 0;
			}
			if (flag)
				count++;
			flag = 1;
		}
		lines2 = new Line[count];
		count = 0;
		for (i = 0; i < m; i++)
		{
			for (j = 0; j < lines[i].n; j++)
			{
				if (lines[i].a[j] != lines[i].a[lines[i].n - j])
					flag = 0;
			}
			if (flag)
			{
				lines2[count].a = new double[lines2[count].n];
				count++;
				for (k = 0; k < lines[i].n; k++)
					lines2[count - 1].a[k] = lines[i].a[k];
			}
			flag = 1;
		}
		return 0;
	}

	// функция вычисления min/max элемента вектора
	double minmax(double a[], int m, int(*f)(double, double))
	{
		double res = a[0];
		int i;
		for (i = 0; i < m; ++i)
		if (f(a[i], res) > 0)
			res = a[i];
		return res;
	}
}
