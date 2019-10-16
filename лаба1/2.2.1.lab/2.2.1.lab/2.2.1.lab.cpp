// 2.2.1.lab.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>

using namespace std;

double f(double x, double y) {
	return 4 * (x - 5)*(x - 5) + (y - 6)*(y - 6); //функцию сюда свою можно вписать
}

double diffx(double x, double eps) {
	return 8*(x-5);
}

double diffy(double x, double eps) {
	return 2*(x-6);
}

double gradient(double x, double y, double eps)
{
	return sqrt(diffx(x, eps)*diffx(x, eps) + diffy(x, eps)*diffy(x, eps));
}

int main()
{
	setlocale(LC_ALL, "Russian");
	double x0[2];
	double eps;
	double a = 1;
	int k = 0;
	cout << "Введите x0" << endl;
	for (int i = 0; i < 2; i++)
	{
		cin >> x0[i];
	}
	cout << "Введите параметр точности Eps" << endl;
	cin >> eps;

step2:

	cout << "шаг 1 вычислим частные производные для заданной функции:" << endl;
	cout << "df/dx(" << x0[0] << "," << x0[1] << ") = " << diffx(x0[0], eps) << '\n' << "df/dy(" << x0[0] << "," << x0[1] << ") = " << diffy(x0[1], eps) << '\n';
	cout << "шаг 2 вычислим градиент для заданной функции:" << endl;
	cout << gradient(x0[0], x0[1], eps) << endl;

	if (gradient(x0[0], x0[1], eps) < eps)
	{
		goto end;
	}

	x0[0] = x0[0] - diffx(x0[0], eps);
	x0[1] = x0[1] - diffy(x0[1], eps);
	cout << "Новые значения x" << k << "=" << x0[0] << "   x" << k << " = " << x0[1] << endl;
	k++;
	goto step2;

end:
	cout << "ОТВЕТ:" << endl << "x = [" << x0[0] << "," << x0[1] << "]" << endl << "f(x) = " << f(x0[0], x0[1]);


	return 1;
}

/*
float fmin(float x)
{
	return (x - 1)*(x - 1);
}

int min()
{
	setlocale(LC_ALL, "Russian");

	float a, b, e, t, x1, x2;


	cout << "Для решения данной задачи необходимо задать интервал на отрезке [a,b]" << endl;
	cout << "Введите начало интервала a: ";
	cin >> a;
	cout << "Введите конец интервала b: ";
	cin >> b;
	cout << "Введите параметр точности поиска e : ";
	cin >> e;

	t = (sqrt(5) + 1) / 2;


	x1 = a + (b - a) / (t * t);
	x2 = a + (b - a) / t;


metka:
	if (fmin(x1) <= fmin(x2))
	{
		b = x2;
		x2 = x1;
		x1 = a + b - x2;
	}

	else
	{
		a = x1;
		x1 = x2;
		x2 = a + b - x1;
	}

	if ((b - a) / 2 < e)
	{
		return (a + b) / 2;
	}

	else
	{
		goto metka;
	}
	return 0;
}
*/