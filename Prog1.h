namespace Prog1{
	// структура для задания строки матрицы
	struct Line{
		int n; // количество элементов в строке матрицы
		double *a; // массив элементов
	};


	// шаблон функций ввода одного значения
	template <class T>
	int getNum(T &a)
	{
		std::cin >> a;
		if (!std::cin.good())	// обнаружена ошибка ввода или конец файла
			return -1;
		return 1;
	}

 
	// функции сравнения
	inline int isgreater(double a, double b)
	{
		return a > b;
	}

	inline int isless(double a, double b)
	{
		return a < b;
	}

	// прототипы функций
	Line* input(int &); // ввод матрицы
	void output(const char *msg, Line a[], int m); // вывод матрицы
	Line *erase(Line *&a, int m); // освобождение занятой памяти
	int minmax(Line a[], int m, double &); // вычисление главного результата
	double minmax(double a[], int m, int(*f)(double, double)); // вычисление min/max элемента вектора
}
