#include "header.h"

using namespace std;

double iterMethod(double firstX, double accuracy, double(*iterFunc)(double), double(*f)(double))
{
	int i = 1;
	double prevX, nextX = firstX;


	cout << "X" << 0 << " = " << firstX << endl;
	do
	{
		prevX = nextX;
		nextX = iterFunc(prevX);
		cout << "X" << i << " = " << nextX << endl;
		i++;
	} while (abs(f(nextX)) > accuracy);

	return nextX;
}

double combMethod(double horda, double kasat, double accuracy,
	double(*chordsFunc)(double, double), double(*tangentsFunc)(double), double(*f)(double))
{
	int i = 1;

	cout << "A" << 0 << " = " << horda << " "
		<< "B" << 0 << " = " << kasat << endl;
	do
	{
		if (horda == kasat)return horda;
		horda = chordsFunc(horda, kasat);
		kasat = tangentsFunc(kasat);
		cout << "A" << i << " = " << horda << " "
			<< "B" << i << " = " << kasat << endl;
		i++;
	} while (abs(f(abs(horda + kasat) / 2.)) > accuracy);

	return horda;
}
