// 2.1.2.lab.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
//#include <conio.h>
#include <cmath>


float* end(float x0[], float h[], int T, float e, float a);
float f(int T, float b[])
{
	float *x = new float[T];

	for (int i = 0; i < T; i++)
	{
		x[i] = b[i];
	}
	float value_func = (x[0]  + 10*x[1])*(x[0] + 10 * x[1])+5*(x[2] - x[3])*(x[2] - x[3]) + (x[1] - 2*x[2])*(x[1] - 2 * x[2])*(x[1] - 2 * x[2])*(x[1] - 2 * x[2])+10*(x[0]-x[3])*(x[0] - x[3])*(x[0] - x[3])*(x[0] - x[3]);
	delete[] x;
	return value_func;
}


float exit_point(const float* x)
{
	float dx = sqrt(x[0] * x[0] + x[1] * x[1]);
	return dx;
}





float* sumArr(float arr[], float arr1[], int T)
{
	for (int i = 0; i < T; i++)
	{
		arr[i] = arr[i] + arr1[i];
	}
	return arr;
}

float* differenceArr(float arr[], float arr1[], int T)
{
	for (int i = 0; i < T; i++)
	{
		arr[i] = arr[i] - arr1[i];
	}
	return arr;
}

float* copyArr(float arr[], float arr1[], int T)
{
	for (int i = 0; i < T; i++)
	{
		arr[i] = arr1[i];
	}
	return arr;
}

void printFloatArr(float arr[], int T)
{
	using namespace std;
	cout << "[";
	for (int i = 0; i < T - 1; ++i) {
		cout << arr[i] << ", ";
	}

	cout << arr[T - 1] << "]";
}


float* exploratory_search(float x0[], float h[], int T, float a, float e, bool &luck)
{
	using namespace std;
	float *x1 = new float[T];
	copyArr(x1, x0, T);
	float x0dublikate[4];
	copyArr(x0dublikate, x0, T);

	x1[0] = x0dublikate[0] + h[0];
	if (T == 2) {
		if (f(T, x1) < f(T, x0dublikate))
		{
			luck = true;
			return x1;
		}
		else
		{
			x1[1] = x0dublikate[1] + h[1];
		}

		if (f(T, x1) < f(T, x0dublikate))
		{
			luck = true;
			return x1;
		}
		else
		{
			x1[0] = x0dublikate[0] - 2 * h[0];
		}

		if (f(T, x1) < f(T, x0dublikate))
		{
			luck = true;
			return x1;
		}
		else
		{
			x1[1] = x0dublikate[1] - 2 * h[1];
		}

		if (f(T, x1) < f(T, x0dublikate))
		{
			luck = true;
			return x1;
		}
		else
		{
			luck = false;
			return x1;
		}
	}
	else 
	{
		for (int i = 1; i < T; i++) 
		{
			if (f(T, x1) < f(T, x0dublikate)) 
			{
				luck = true;
				return x1;
			}
			else 
			{
				x1[i] = x0dublikate[i] + h[i];
			}
		}

		for (int i = 0; i < T; i++) 
		{
			x1[i] = x0dublikate[i] - h[i];
		}
		x1[0] = x0dublikate[0] - h[0];
		for (int i = 1; i < T; i++)
		{
			if (f(T, x1) < f(T, x0dublikate))
			{
				luck = true;
				return x1;
			}
			else
			{
				x1[i] = x0dublikate[i] - h[i];
			}
		}
	}

	return x1;
	delete[] x1;

}

float* end(float x0[], float h[], int T, float e, float a, bool& luckEND)
{
	//Шаг 4. Проверка на окончание поиска. Выполняется ли неравенство |Δx| ≤ ε? 
	using namespace std;
	if (exit_point(h) > e)
	{
		luckEND = false;
		cout << "Неравенство |dx| <= e не выполняется, уменьшаем приращение h = ";
		for (int i = 0; i < T; i++)
		{
			h[i] = h[i] / a;
		}
		printFloatArr(h, 4);
		cout << endl;
		return h;
	}
	else
	{//Да: окончание поиска, т.е. текущая точка аппроксимирует точку экстремума x*.
		luckEND = true;
		cout << "Точка апроксимации = x";
		printFloatArr(x0, T);
		cout << "  f(x) = " << f(4, x0) << endl;
	}
}

float* pattern_matching(float xpk1[], float xk[], float* xk0, int T)
{
	float xkdublikate[4];
	float xkdublikate2[4];
	float xk0dublikate2[4];
	copyArr(xkdublikate, xk, T);
	copyArr(xkdublikate2, xk, T);
	copyArr(xk0dublikate2, xk0, T);
	copyArr(xpk1, sumArr(xkdublikate, differenceArr(xkdublikate2, xk0dublikate2, T), T), T);
	return xpk1;
}



int main()
{
	using namespace std;
	setlocale(LC_ALL, "Russian");

	bool luck;
	bool luck2;
	bool luckEND;
	int T = 4;
	float e, a;
	//cout << "Введите количество элементов векторов T: ";
	//cin >> T;
	float *x0 = new float[T];
	float *xk = new float[T];
	float *xk0 = new float[T];
	float *h = new float[T];
	float *xkp1 = new float[T];
	float *xk1 = new float[T];

	//Шаг 1. Определить начальную точку x0; приращения (шаги) ∆i; коэффициент уменьшения шага α>1; параметр оконча­ния поиска ε<1.

	for (int i = 0; i < T; i++) {
		cout << "Введите элемент вектора начальной базисной точки x0" << i + 1 << ": ";
		cin >> x0[i];
	}
	copyArr(xk0, x0, T);

	for (int i = 0; i < T; i++) {
		cout << "Введите элемент вектора положительных приращений координат h" << i + 1 << ": ";
		cin >> h[i];
	}
	cout << "Введите точность E: ";
	cin >> e;

	cout << "Введите шаг A: ";
	cin >> a;
	cout << endl;


	cout << "Шаг 2 Проводим исследующий поиск" << endl;
	xk = exploratory_search(x0, h, T, a, e, luck);
	goto after2steps;
step2replay:
	xk = exploratory_search(xkp1, h, T, a, e, luck);
after2steps:

	cout << "Шаг 3 был ли исследующий поиск удачным" << endl;
	if (luck)
	{
		cout << "Исследующий поиск удачный xk = ";
		printFloatArr(xk, T);
		cout << " f(xk) = " << f(T, xk);

		cout << endl;

		cout << "перейдем на шаг 5" << endl;
		goto step5;
	}

	else {
		cout << "Исследующий поиск неудачный, перейдем на шаг 4" << endl;

	step4:
		cout << "Шаг 4  Проверка на окончание поиска" << endl;
		h = end(xk, h, T, e, a, luckEND);
		if (luckEND)
		{
			goto end;
		}
		goto step2replay;
	}


step5:
	cout << "Шаг 5 Проводим поиск по образцу Xkp+1 = ";
	copyArr(xkp1, pattern_matching(xkp1, xk, xk0, T), T);
	printFloatArr(xkp1, T);
	copyArr(xk, xkp1, T);
	cout << endl;

	cout << "Шаг 6. Провести исследующий поиск, используя точку xpk+1 в качестве временной базовой точки. Пусть в результате получена точка xk+1 = ";
	xk1 = exploratory_search(xkp1, h, T, a, e, luck2);
	printFloatArr(xk1, T);


	if (luck2)
	{
		cout << "Исследующий поиск удачный xk = ";
		printFloatArr(xk, T);
		cout << " f(xk) = " << f(T, xk);
		cout << endl;
	}

	else {
		cout << "Исследующий поиск неудачный, перейдем на шаг 4" << endl;
		cout << "Шаг 4  Проверка на окончание поиска" << endl;
		h = end(xk, h, T, e, a, luckEND);
		if (luckEND)
		{
			goto end;
		}
		goto step2replay;
	}




	cout << "Шаг 7. Выполняется ли неравенство: f(xk+1) < f(xk)?" << endl;
	if (f(T, xk1) < f(T, xk))
	{
		cout << "Да: положить xk - 1 = xk; xk = xk + 1. Переход на Шаг 5." << endl;
		copyArr(xk0, xk, T);
		copyArr(xk, xk1, T);
		goto step5;
	}
	else
	{
		cout << "Нет: переход на Шаг 4." << endl;
		goto step4;
	}

	//delete[] b2;
	//delete[] x;
	//delete[] xk;
	//delete[] h;
	//delete[] b;
end:
	//_getch();
	return 0;
}

