#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <locale.h>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

double a = 0, A = 1.5, b = 1, B = 2;
const double e = 2.7182818284590452353602874713527;
int** lamda_matrix;

bool is_in_D(double x, double y)
{
	if ((y >= 1) && (x >= 0) && (y <= 2) && (x <= 0.5 * y + 0.5))
		return true;
	return false;
}

double f(double x, double y)
{
	if (is_in_D(x, y))
		return (pow(e, x));
	return 0;
}

double F(double y)
{
	return (2 * pow(e, (0.5 * y + 0.5)) - y);
}

double x_i(int i, int n)
{
	return a + i * ((double)A - a) / (2.0 * n);
}

double y_i(int j, int m)
{
	return b + j * ((double)B - b) / (2.0 * m);
}

void fill_lambda_matrix(int n, int m)
{
	lamda_matrix = new int* [2 * m + 1];
	for (int i = 0; i <= 2 * m; i++)
	{
		lamda_matrix[i] = new int[2 * n + 1];
	}

	for (int i = 0; i <= 2 * m; i++)
		for (int j = 0; j <= 2 * n; j++)
			lamda_matrix[i][j] = 0;

	lamda_matrix[0][0] = 1;
	lamda_matrix[2 * m][2 * n] = 1;
	lamda_matrix[2 * m][0] = 1;
	lamda_matrix[0][2 * n] = 1;

	int counter = 0;
	for (int i = 1; i < 2 * m; i++)
	{
		if ((counter % 2) == 1)
		{
			lamda_matrix[i][0] = 2;
			lamda_matrix[i][2 * n] = 2;
		}
		else
		{
			lamda_matrix[i][0] = 4;
			lamda_matrix[i][2 * n] = 4;
		}
		counter++;
	}

	counter = 0;
	for (int i = 1; i < 2 * n; i++)
	{
		if ((counter % 2) == 1)
		{
			lamda_matrix[0][i] = 2;
			lamda_matrix[2 * m][i] = 2;
		}
		else
		{
			lamda_matrix[0][i] = 4;
			lamda_matrix[2 * m][i] = 4;
		}
		counter++;
	}

	for (int i = 1; i < 2 * m; i++)
	{
		for (int j = 1; j < 2 * n; j++)
		{
			lamda_matrix[i][j] = lamda_matrix[0][j] * lamda_matrix[i][0];
		}
	}
	cout << "Матрица:" << endl;
	for (int i = 0; i <= 2 * m; i++) {
		for (int j = 0; j <= 2 * n; j++) {
			cout << setw(3) << lamda_matrix[i][j] << " ";
		}
		cout << endl;
	}
}

int main()
{
	int n, m;
	setlocale(LC_ALL, "Russian");
	cout << "Введите n1\n";
	cin >> n;
	cout << "Введите m1\n";
	cin >> m;
	cout << "\n";
	int n1, m1;
	cout << "Введите n2\n";
	cin >> n1;
	cout << "Введите m2\n";
	cin >> m1;
	cout << "\n";
	fill_lambda_matrix(n, m);
	double h = ((double)A - a) / (2.0 * n);
	double k = ((double)B - b) / (2.0 * m);

	double I_Sim = 0;
	for (int j = 0; j <= 2 * m; j++)
	{
		for (int i = 0; i <= 2 * n; i++)
		{
			I_Sim += h * k / 9 * lamda_matrix[j][i] * f(x_i(i, n), y_i(j, m));
		}
	}
	double I = F(B) - F(b);
	fill_lambda_matrix(n1, m1);
	printf("+---+---+---------------+---------------+---------------+\n");
	printf("| n | m |       I       |     I(Sim)    |  |I-I(Sim)|   |\n");
	printf("+---+---+---------------+---------------+---------------+\n");
	printf("|%3d|%3d|%15.10f|%15.10f|%15.10f|\n", n, m, I, I_Sim, fabs(I - I_Sim));
	printf("+---+---+---------------+---------------+---------------+\n");
	h = ((double)A - a) / (2.0 * n1);
	k = ((double)B - b) / (2.0 * m1);



	I_Sim = 0;
	for (int j = 0; j <= 2 * m1; j++)
	{
		for (int i = 0; i <= 2 * n1; i++)
		{
			I_Sim += h * k / 9 * lamda_matrix[j][i] * f(x_i(i, n1), y_i(j, m1));
		}
	}


	printf("|%3d|%3d|%15.10f|%15.10f|%15.10f|\n", n1, m1, I, I_Sim, fabs(I - I_Sim));
	printf("+---+---+---------------+---------------+---------------+\n");
	return 0;
}