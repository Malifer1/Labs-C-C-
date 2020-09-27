#include <iostream>
#include "Prog1.h"

using namespace Prog1;

// основная функция
int main()
{
	Line *arr = NULL; // исходный массив
	int m; // количество строк в матрице
	double res; // полученный результат

	arr = input(m); // ввод матрицы
	if (!arr){
		std::cout << "incorrect data" << std::endl;
		return 1;
	}
	if (minmax(arr, m, res)){  // вычисление требуемого результата
		std::cout << "Error in allocate memory" << std::endl;
		erase(arr, m);
		return 1;
	}
	output("Sourced matrix", arr, m);
	std::cout << "Result: " << res << std::endl;
	erase(arr, m); // освобождение памяти
	return 0;
}
