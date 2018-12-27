#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <iomanip>
#include <ctime>
#include <ratio>
#include <chrono>
using namespace std;
using namespace std::chrono;

class Matrix
{
private:
	double** matrix;
	size_t x_size;
	size_t y_size;
public:
	Matrix(int x, int y) : x_size(x), y_size(y)
	{
		matrix = new double*[x_size];
		for (int i = 0; i < x_size; ++i)
			matrix[i] = new double[y_size];

		for (int i = 0; i < x_size; ++i)
		{
			for (int j = 0; j < y_size; ++j)
			{
				matrix[i][j] = 0;
			}
		}
	}

	Matrix(const Matrix& m)
	{
		matrix = m.matrix;
		x_size = m.x_size;
		y_size = m.y_size;
	}

	~Matrix()
	{
		for (int j = 0; j < y_size; ++j)
			delete[]matrix[j];
		delete[]matrix;
	}

	void fillMatrix()
	{
		if (x_size == 0 && y_size == 0)
		{
			cerr << "ERROR net matix, vvedite new matrix";
			exit(0);
		}

		cout << "Vvedite matrix" << x_size << "x" << y_size << endl;
		for (int i = 0; i < x_size; ++i)
		{
			for (int j = 0; j < y_size; ++j)
			{
				cin >> matrix[i][j];
			}
		}
	}

	void printMatrix()const
	{
		cout << "Matrix " << x_size << "x" << y_size << endl;

		cout.setf(ios::fixed);
		cout.precision(3);

		for (int i = 0; i < x_size; i++)
		{
			for (int j = 0; j < y_size; j++)
			{
				cout << matrix[i][j] << " ";
			}
			cout << endl;
		}
	}

	void zeidel(double* vec)
	{
		const size_t MAX = 100;

		double* iterVector = nullptr;
		iterVector = new double[x_size];
		for (size_t i = 0; i < x_size; i++)
		{
			iterVector[i] = vec[i];
		}

		double** vector = nullptr;
		vector = new double*[x_size];
		for (size_t i = 0; i < x_size; i++)
		{
			vector[i] = new double[x_size];
		}

		for (size_t i = 0; i < x_size; i++)
			for (size_t j = 0; j < x_size; j++)
			{
				vector[i][j] = 0;
			}

		int n = 0;
		for (size_t i = 0; i < x_size; i++)
		{
			for (size_t j = 0; j < x_size; j++)
			{
				if (i == j)
				{
					vector[i][j] = 0;
				}
				else vector[i][j] = -matrix[i][j] / matrix[i][n];
			}

			iterVector[i] = vec[i] / matrix[i][n];
			n++;
		}


		cout << setw(15) << "\tNew Matrix A" << setw(15) << "\t\tVector free chlenov ֲ" << endl;
		for (size_t i = 0; i < x_size; i++) {
			for (size_t j = 0; j < x_size; j++)
			{
				cout << setw(8) << vector[i][j] << " ";
			}
			cout << setw(8) << " " << iterVector[i];
			cout << endl;
		}

		cout << endl << endl;

		double** mat = nullptr;
		mat = new double*[MAX];
		for (size_t j = 0; j < MAX; j++)
		{
			mat[j] = new double[x_size];
		}

		for (size_t i = 0; i < MAX; i++)
		{
			for (size_t j = 0; j < x_size; j++)
				mat[i][j] = 0;
		}

		cout.setf(ios::fixed);
		cout.precision(5);

		double max = 0;

		for (size_t i = 0; i < x_size; ++i)
		{
			mat[0][i] = iterVector[i];
		}

		cout << setw(5) << "N" << setw(10) << "X" << endl;
		cout << "     0: ";
		for (size_t i = 0; i < x_size; ++i)
			cout << setw(10) << mat[0][i] << " ";
		cout << endl;


		for (size_t i = 1; ; ++i)
		{
			cout << setw(5) << i << " : ";
			for (size_t j = 0; j < x_size; ++j)
			{
				mat[i][j] += iterVector[j];
				for (size_t k = 0; k < x_size; ++k)
				{
					mat[i][j] += vector[j][k] * mat[i - 1][k];
				}
				//iterVector[j] = mat[i][j];
				double k = fabs(mat[i][j] - mat[i - 1][j]);
				if (k > max) max = k;
				cout << setw(10) << mat[i][j] << " ";
			}
			cout << setw(6) << max;
			if (max < 0.0001)
			{
				cout << endl << "Complite" << endl;
				break;
			}
			else max = 0;
			cout << endl;
		}


		for (size_t i = 0; i < MAX; ++i)
		{
			delete[]mat[i];
		}
		delete[]mat;

		for (size_t i = 0; i < x_size; ++i)
		{
			delete[]vector[i];
		}
		delete[]vector;

		delete[]iterVector;

	}

};

int main()
{
	setlocale(LC_CTYPE, "");
	size_t M;

	cout << "Metod Zeidelya" << endl << endl;
	cout << "Kol-vo yravneniy: "; cin >> M;
	cout << "Svobodnie chleni: (" << M << " רע.): ";

	double* vec;
	vec = new double[M];
	for (size_t i = 0; i < M; ++i) cin >> vec[i];

	Matrix matrix(M, M);

	matrix.fillMatrix();

	steady_clock::time_point zeidel_time1 = steady_clock::now();
	matrix.zeidel(vec);
	steady_clock::time_point zeidel_time2 = steady_clock::now();
	duration<double> zeidel_span = duration_cast<duration<double>>(zeidel_time2 - zeidel_time1);
	//cout << "Check:\n 5    1   -1  2     2.97525   11.99996\n 0.5 -4    2 -1  X  0.55830 = 0.499955\n-1    0.2 -6  3    -0.31451  -6.60018\n 1   -0.5  3 -6    -1.87455   12.99987" << endl;
	cout << "Time: " << zeidel_span.count() << " sec" << endl;

	system("Pause");
	return 0;
}
