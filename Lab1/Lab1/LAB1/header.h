#include <iostream>
#include <cmath>

double iterMethod(double firstX, double accuracy, double(*iterFunc)(double), double(*f)(double));

double combMethod(double horda, double kasat, double accuracy,
	double(*chordsIterFunc)(double, double), double(*tangentsFunc)(double), double(*f)(double));
