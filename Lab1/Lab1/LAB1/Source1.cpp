#include <iostream>
#include <cmath>
#include "header.h"
#include <windows.h>

#define PI 3.141592

using namespace std;

double f1(double x) { return pow(x, 3) + pow(x, 2) - 3; }
double iterFunc1(double x) { return x - f1(x) / 8; }

double f2(double x) { return 3 * x + cos(x) + 1; }
double iterFunc2(double x) { return x - f2(x) / 11; }

double f3(double x) { return tan(x) - 7 / (2 * x + 6); }
double chordsIterFunc3(double x) { return x - f3(x)*(x - 1) / (f3(x) - f3(1)); }

double f4(double x) { return pow(x, 3) + 3 * pow(x, 2) + 9 * x + 2; }
double tangentsIterFunc4(double x) { return x - f4(x) / (3 * pow(x, 2) + 6 * x + 9); }

double f5(double x) { return pow(x, 3) + 3 * pow(x, 2) - 24 * x - 10; }
double chordsIterFunc5(double x, double fixedX)
{
	return x - f5(x)*(fixedX - x) / (f5(fixedX) - f5(x));
}
double tangentsIterFunc5(double x) { return x - f5(x) / (3 * pow(x, 2) + 6 * x - 24); }

int main()
{
	cout << "Nomer 2.1\n";
	double e1 = iterMethod(0, 0.001, iterFunc1, f1);
	cout << "Priblizitelniy koren x = " << e1 << endl;
	cout << "f(x) = " << f1(e1) << endl;

	cout << "Nomer 2.2\n";
	double e2 = iterMethod(0, 0.001, iterFunc2, f2);
	cout << "Priblizitelniy koren x = " << e2 << endl;
	cout << "f(x) = " << f2(e2) << endl;

	cout << "Nomer 3.1\n";
	double e3 = iterMethod(0.75, 0.0001, chordsIterFunc3, f3);
	cout << "Priblizitelniy koren x = " << e3 << endl;
	printf("f(x) = %lf\n", f3(e3));

	cout << "Nomer 3.2\n";
	double e4 = iterMethod(0, 0.001, tangentsIterFunc4, f4);
	cout << "Priblizitelniy koren x = " << e4 << endl;
	cout << "f(x) = " << f4(e4) << endl;

	cout << "Nomer 3.3\n";
	double e5 = combMethod(0, 4, 0.001, chordsIterFunc5, tangentsIterFunc5, f5);
	cout << "Priblizitelniy koren x = " << e5 << endl;
	printf("f(x) = %lf\n", f5(e5));
	system("pause");
	return 0;
}
