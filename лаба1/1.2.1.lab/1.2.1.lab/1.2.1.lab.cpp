// 1.2.1.lab.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <conio.h>
#include <cmath>


float function(float x)
{
	float f;
	f = -sin(x) - sin(2 * x) - (2 * sin(3 * x)) / 3;
	//f = (x - 1)*(x - 1);
	//f = 4*x*x*x -8*x*x - 11*x + 5;
	//f = x + 3 / (x*x);
	return f;
}



int main()
{
	using namespace std;
	setlocale(LC_ALL, "Russian");

	float N, a, b, min, minf;

	cout << "Искать множество локальных точек минимума 1/0" << endl;
	char num = _getch();

	cout << "Введите число вычислений целевой функции N: ";
	cin >> N;

	cout << "Введите начало отрезка локализации минимума a: ";
	cin >> a;

	cout << "Введите конец отрезка локализации минимума b: ";
	cin >> b;

	float *x = new float[N];
	float *function_arr = new float[N];
	for (int i = 0; i < N; i++)
	{
		x[i] = a + i * ((b - a) / (N - 1));
	}

	for (int i = 0; i < N; i++)
	{
		function_arr[i] = function(x[i]);
	}
	if (num == '0') {
		minf = function_arr[0];
		min = 0;
		for (int i = 1; i < N; i++)
		{
			if (minf > function_arr[i])
			{
				minf = function_arr[i];
				min = x[i];
			}
		}
		cout << "Точка минимума x*: " << min << endl;
		cout << "Значение функции в точке минимума f*: " << minf << endl;
	}
	else
	{
		float e = (b - a) / (N - 1);
		cout << "Точность вычислений: " << e << endl;
		int j = 1;
		for (int i = 1; i < N; i++)
		{
			if (function_arr[i] < function_arr[i + 1] && function_arr[i] < function_arr[i - 1])
			{
				cout << "Точка точка локального минимума x^" << j << " :" << x[i] << endl;
				cout << "Значение функции в точке локального минимума x^" << j << " :" << function_arr[i] << endl;
				cout << endl;
				j++;
			}
		}
	}
	delete[] x;
	delete[] function_arr;
	_getch();
	return 0;
}
