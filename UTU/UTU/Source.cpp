#include <iostream>
#include <cmath>

using namespace std;
const int e = 4;


void create_MTRX(double** mtrx, int& rows, int& columns, double* b) {

	cout << "Mtrx" << endl;

	for (int i = 0; i < rows; i++) {
		mtrx[i] = new double[columns];
		for (int j = 0; j < columns; j++) {
			cin >> mtrx[i][j];
		}
	}
	
		cout << "Coef" << endl;

		for (int i = 0; i < columns; i++) {
			cin >> b[i];
		}
	

}

void print_MTRX(double** mtrx, int rows, int columns, double* b) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			cout << mtrx[i][j] << " ";
		}
	
			cout << " | " << b[i];
		
		cout << endl;
	}

	cout << endl;
}

void nice_MTRX(double** mtrx, int rows, int columns)
{
	bool flag = true;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if ((mtrx[i][i] == 0) || (mtrx[i][i] < 0))
			{
				cout << "error" << endl;
				system("pause");
			}
			if (mtrx[i][j] != mtrx[j][i])
			{
				flag = false;
				break;
			}
		}
		if (!flag)
		{
			break;
		}
	}
	if (!flag)
	{
		cout << "error" << endl;
		system("pause");
	}
}

void numbersRound(double& number) {
	int h = number * pow(10, e);
	number = h * pow(10, (-1) * e);
}


void find_U(double** mtrx, double** u, int rows, int columns)
{

	double* b = new double[columns];

	for (int i = 0; i < rows; i++)
	{
		u[i] = new double[columns];
		for (int j = 0; j < columns; j++)
		{
			if (i < j)
			{
				double sym = 0;
				for (int k = 0; k < i; k++)
				{
					sym += u[k][j] * u[k][i];
				}

				u[i][j] = (mtrx[i][j] - sym) / u[i][i];
				numbersRound(u[i][j]);

			}
			else if (i == j)
			{
				double sym = 0;
				for (int k = 0; k < i; k++)
				{
					sym += pow(u[k][i], 2);
				}
				double h = mtrx[i][j] - sym;
				if (h < 0)
				{
					cout << "error" << endl;
					system("pause");
				}
				u[i][j] = pow(h, 0.5);
				numbersRound(u[i][j]);
			}
			else
			{
				u[i][j] = 0;
			}

		}

	}

}

double determinant_MTRX(double** u, int rows, int columns)
{
	double det_m = 1;
	for (int i = 0; i < rows; i++)
	{
		det_m *= u[i][i] * u[i][i];
	}
	return det_m;
}

void find_X_Y(double** u, double* b, double* x, double* y, int columns)
{
	for (int i = 0; i < columns; i++)
	{
		double sum = 0;
		for (int k = 0; k < i; k++)
		{
			sum += u[k][i] * y[k];
		}
		y[i] = (b[i] - sum) / u[i][i];
		numbersRound(y[i]);
	}

	for (int i = columns - 1; i >= 0; i--)
	{
		double sum = 0;
		for (int k = i + 1; k < columns; k++)
		{
			sum += u[i][k] * x[k];
		}

		x[i] = (y[i] - sum) / u[i][i];
		numbersRound(x[i]);
	}

}


int main() {
	cout << " S                L                     A                  R" << endl;
	int rows, columns;
	cout << "n*n " << endl;
	cin >> rows;
	columns = rows;
	double** mtrx = new double* [rows];
	double** u = new double* [rows];
	double* b = new double[columns];
	double* x = new double[columns];
	double* y = new double[columns];
	create_MTRX(mtrx, rows, columns, b);
	nice_MTRX(mtrx, rows, columns);
	print_MTRX(mtrx, rows, columns, b);
	find_U(mtrx, u, rows, columns);
	cout << "Matrix U" << endl;
	print_MTRX(u, rows, columns, b);
	double determ_m = determinant_MTRX(u, rows, columns);
	if (determ_m == 0)
	{
		cout << "This system does not have a solution" << endl;
		system("pause");
		return 0;
	}
	else
	{
		numbersRound(determ_m);
		cout << "Determinant := " << determ_m << endl;

		cout << endl;
	}
	find_X_Y(u, b, x, y, columns);
	cout << "the roots of the equation  Y: " << endl;
	for (int i = 0; i < columns; i++)
		cout << "y[" << i << "]=" << y[i] << " " << endl;
	cout << endl;
	cout << "the roots of the equation X: " << endl;
	for (int i = 0; i < columns; i++)
		cout << "x[" << i << "]=" << x[i] << " " << endl;
	for (int i = 0; i < rows; i++)
		delete[] u[i];
	delete u;
	for (int i = 0; i < rows; i++)
		delete[] mtrx[i];
	delete[] mtrx;
	delete x;
	delete b;
	delete y;
	system("pause");
	return 0;
}
	