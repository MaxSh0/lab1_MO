#include "stdafx.h"
#include "math.h"
#include <vector>
#include <conio.h>
#include <iostream>

using namespace std;

/*Поиск локального минимума функции*/
int main()
{
	setlocale(0, "");

	int n = 0;			// Размерность пространства
	double e = 0;			// Погрешность
	int step = 0;			// Номер шага по алгоритму
	int method;			// Номер метода решения
	int k;

	double function(vector<double> x);	// Целевая функция
	vector<double> operator-(vector<double> a, vector<double> b);
	vector<double> operator+(vector<double> a, vector<double> b);
	vector<double> operator*(double a, vector<double> b);
	vector<double> searching(vector<double> b, vector<double> h);

	// Ввод исходных данных
	printf("\n---ВВОД ИСХОДНЫХ ДАННЫХ ДЛЯ ПОИСКА---\n\n");
	printf("Введите размерность пространства n>0: ");
	cin >> n;

	vector<double> b1(n), b2(n);	// Вектора значений базисных точек
	vector<double> h(n);			// Вектор значений шага h
	vector<double> xk(n), x(n);		// Вектора значений xk

	printf("\nВведите координаты начальной базисной точки b: \n");
	for (int i = 0; i<n; i++)
	{
		printf("b[%d] = ", i + 1);
		cin >> b1[i];
	}
	printf("\nВведите приращения координат h>0: \n");
	for (int i = 0; i<n; i++)
	{
		printf("h[%d] = ", i + 1);
		cin >> h[i];

		// Проверка их на корректность
		if (h[i] <= 0)
		{
			printf("\nВведено некорректное значение h\nПопробуйте еще раз");
			//getch();
			return 0;
		}
	}
	printf("\nВведите параметр точности поиска e>0: ");
	cin >> e;


		printf("\n---ПОИСК МИНИМУМА ФУНКЦИИ ПО МЕТОДУ ХУКА-ДЖИВСА---\n\n");
		// Поиск точки минимума по методу Хука-Дживса
		step = 1;
		while (step != 0)
		{
			switch (step)
			{
				// 1-й шаг алгоритма
			case 1:
			{
				xk = b1;
				step = 2;
				printf("1-й шаг: xk=b1=(");
				for (int i = 0; i<n - 1; i++)
				{
					printf("%.2lf; ", xk[i]);
				}
				printf("%.2lf)\n", xk[n - 1]);
			}
			break;
			// 2-й шаг алгоритма
			case 2:
			{
				step = 3;
				b2 = searching(xk, h);

				printf("2-й шаг: b2=(");
				for (int i = 0; i<n - 1; i++)
				{
					printf("%.2lf; ", b2[i]);
				}
				printf("%.2lf)\n\n", b2[n - 1]);
			}
			break;
			// 3-й шаг алгоритма
			case 3:
			{
				xk = b1 + 2 * (b2 - b1);
				step = 4;

				printf("3-й шаг: xk=b1+2(b2-b1)=(");
				for (int i = 0; i<n - 1; i++)
				{
					printf("%.2lf; ", xk[i]);
				}
				printf("%.2lf)\n", xk[n - 1]);
			}
			break;
			// 4-й шаг алгоритма
			case 4:
			{
				step = 5;
				x = searching(xk, h);
				printf("4-й шаг: х=(");
				for (int i = 0; i<n - 1; i++)
				{
					printf("%.2lf; ", x[i]);
				}
				printf("%.2lf)\n\n", x[n - 1]);
			}
			break;
			// 5-й шаг алгоритма
			case 5:
			{
				b1 = b2;
				step = 6;

				printf("5-й шаг: b1=b2=(");
				for (int i = 0; i<n - 1; i++)
				{
					printf("%.2lf; ", b1[i]);
				}
				printf("%.2lf)\n\n", b1[n - 1]);
			}
			break;
			// 6-й шаг алгоритма
			case 6:
			{
				if (function(x) < function(b1))
				{
					b2 = x;
					step = 3;
					printf("6-й шаг: f(x)=%lf < f(b1)=%lf => b2=x=(", function(x), function(b1));
					for (int i = 0; i<n - 1; i++)
					{
						printf("%.2lf; ", b2[i]);
					}
					printf("%.2lf), переходим на 3-й шаг\n\n", b2[n - 1]);

				}
				else
				{
					step = 7;
					printf("6-й шаг: f(x)=%lf >= f(b1)=%lf => переходим на следующий шаг\n\n", function(x), function(b1));
				}
			}
			break;
			// 7-й шаг алгоритма
			case 7:
			{
				if (function(x) > function(b1))
				{
					step = 1;
					printf("7-й шаг: f(x)=%lf > f(b1)=%lf => переходим на 1-й шаг\n\n", function(x), function(b1));

				}
				else
				{
					step = 8;
					printf("7-й шаг: f(x)=%lf <= f(b1)=%lf => переходим на следующий шаг\n\n", function(x), function(b1));
				}
			}
			break;
			// 8-й шаг алгоритма
			case 8:
			{
				double tmp = 0;
				for (int i = 0; i<n; i++)
				{
					tmp += h[i] * h[i];
				}
				tmp = sqrt(tmp);

				if (tmp <= e)
				{
					step = 10;
					printf("8-й шаг: ||h||=%lf <= e=%lf => переходим на 10-й шаг\n\n", tmp, e);

				}
				else
				{
					step = 9;
					printf("8-й шаг: ||h||=%lf > e=%lf => переходим на следующий шаг\n\n", tmp, e);
				}
			}
			break;
			// 9-й шаг алгоритма
			case 9:
			{
				h = 0.1*h;
				step = 10;

				printf("9-й шаг: h=(");
				for (int i = 0; i<n - 1; i++)
				{
					printf("%.2lf; ", h[i]);
				}
				printf("%.2lf)\n\n", h[n - 1]);
			}
			break;
			// 10-й шаг алгоритма
			case 10:
			{
				step = 0;

				printf("10-й шаг: х*=(");
				for (int i = 0; i<n - 1; i++)
				{
					printf("%.2lf; ", b1[i]);
				}
				printf("%.2lf), f*=%lf\nЗаканчиваем поиск\n\n", b1[n - 1], function(b1));
			}
			break;
			}
		}
		printf("\n---ПОИСК МИНИМУМА ФУНКЦИИ ПО МЕТОДУ ХУКА-ДЖИВСА ЗАВЕРШЕН---\n\n");
		printf("Точка минимума функции: х*=(");
		for (int i = 0; i<n - 1; i++)
		{
			printf("%.2lf; ", b1[i]);
		}
		printf("%.2lf)\nЗначение функции в ней: f*=%lf\n\n", b1[n - 1], function(b1));

	return 0;
}

vector<double> operator-(vector<double> a, vector<double> b)
{
	vector<double> result(a.size());
	for (int i = 0; i<a.size(); i++)
	{
		result[i] = a[i] - b[i];
	}
	return result;
}

vector<double> operator+(vector<double> a, vector<double> b)
{
	vector<double> result(a.size());
	for (int i = 0; i<a.size(); i++)
	{
		result[i] = a[i] + b[i];
	}
	return result;
}

vector<double> operator*(double a, vector<double> b)
{
	vector<double> result(b.size());
	for (int i = 0; i<b.size(); i++)
	{
		result[i] = b[i] * a;
	}
	return result;
}

/*Нахождение значения целевой функции в точке Х*/
double function(vector<double> x)
{
	//return (x[0]*x[0]+x[1]-11)*(x[0]*x[0]+x[1]-11)+(x[0]+x[1]*x[1]-7)*(x[0]+x[1]*x[1]-7); // Функция Химмельблау
	//return 4*(x[0]-5)*(x[0]-5)+(x[1]-6)*(x[1]-6); // Тестовая задача
	return (x[0]+10*x[1])*(x[0]+10*x[1])+5*(x[2]-x[3])*(x[2]-x[3])+pow((x[1]-2*x[2]),4)+10*pow((x[0]-x[3]),4); // Функция Пауэлла
	//return 100 * (x[1] - x[0] * x[0])*(x[1] - x[0] * x[0]) + (1 - x[0])*(1 - x[0]) + 90 * (x[3] - x[2] * x[2])*(x[3] - x[2] * x[2]) + (1 - x[2])*(1 - x[2]) + 10 * ((x[2] - 1)*(x[2] - 1) + (x[3] - 1)*(x[3] - 1)) + 20 * (x[1] - 1)*(x[3] - 1);
}

vector<double> searching(vector<double> b, vector<double> h)
{
	int step = 1;
	int ii = 1;
	double fb = function(b), f = 0;
	vector<double> he(b.size());

	printf("\n-------------------------------------------------------------------\n");
	printf("Исследующий поиск вокруг точки b=(");
	for (int i = 0; i<b.size() - 1; i++)
	{
		printf("%.2lf; ", b[i]);
	}
	printf("%.2lf) \n\n", b[b.size() - 1]);

	while (step != 0)
	{
		switch (step)
		{
			// 1-й шаг алгоритма
		case 1:
		{
			step = 2;
			printf("1-й шаг: fb=%lf\n\n", fb);
		}
		break;
		// 2-й шаг алгоритма
		case 2:
		{
			step = 3;
			printf("2-й шаг: i=1\n\n", fb);
		}
		break;
		// 3-й шаг алгоритма
		case 3:
		{
			for (int i = 0; i<b.size(); i++)
			{
				he[i] = 0;
			}
			he[ii - 1] = h[ii - 1] * 1;
			f = function(b + he);

			step = 4;
			printf("3-й шаг: he=(");
			for (int i = 0; i<b.size() - 1; i++)
			{
				printf("%.2lf; ", he[i]);
			}
			printf("%.2lf), f(b+he)=%lf \n\n", he[b.size() - 1], f);
		}
		break;
		// 4-й шаг алгоритма
		case 4:
		{
			if (f < fb)
			{
				step = 7;
				b = b + he;

				printf("4-й шаг: f=%lf < fb=%lf => b=(", f, fb);
				for (int i = 0; i<b.size() - 1; i++)
				{
					printf("%.2lf; ", b[i]);
				}
				printf("%.2lf), fb=%lf, переходим на 7-й шаг\n\n", b[b.size() - 1], f);

				fb = f;
			}
			else
			{
				step = 5;
				printf("4-й шаг: f=%lf >= fb=%lf => переходим на следующий шаг\n\n", f, fb);
			}
		}
		break;
		// 5-й шаг алгоритма
		case 5:
		{
			f = function(b - he);

			step = 6;
			printf("5-й шаг: he=(");
			for (int i = 0; i<b.size() - 1; i++)
			{
				printf("%.2lf; ", he[i]);
			}
			printf("%.2lf), f(b-he)=%lf\n\n", he[b.size() - 1], f);
		}
		break;
		// 6-й шаг алгоритма
		case 6:
		{
			if (f < fb)
			{
				step = 7;
				b = b - he;

				printf("6-й шаг: f=%lf < fb=%lf => b=(", f, fb);
				for (int i = 0; i<b.size() - 1; i++)
				{
					printf("%.2lf; ", b[i]);
				}
				printf("%.2lf), fb=%lf\n\n", b[b.size() - 1], f);

				fb = f;
			}
			else
			{
				step = 7;
				printf("6-й шаг: f=%lf >= fb=%lf => переходим на следующий шаг\n\n", f, fb);
			}
		}
		break;
		// 7-й шаг алгоритма
		case 7:
		{
			if (ii == b.size())
			{
				step = 9;
				printf("7-й шаг: i=%d = n=%d => переходим на 9-й шаг\n\n", ii, b.size());
			}
			else
			{
				step = 8;
				printf("7-й шаг: i=%d < n=%d => переходим на следующий шаг\n\n", ii, b.size());
			}
		}
		break;
		// 8-й шаг алгоритма
		case 8:
		{
			step = 3;
			ii = ii + 1;

			printf("8-й шаг: i=%d \nПереходим на 3-й шаг\n\n", ii);
		}
		break;
		// 9-й шаг алгоритма
		case 9:
		{
			step = 0;
			printf("9-й шаг: b=(");
			for (int i = 0; i<b.size() - 1; i++)
			{
				printf("%.2lf; ", b[i]);
			}
			printf("%.2lf)\nЗавершаем поиск", b[b.size() - 1]);
		}
		break;
		}
	}

	printf("\n-------------------------------------------------------------------\n\n");
	return b;
}
