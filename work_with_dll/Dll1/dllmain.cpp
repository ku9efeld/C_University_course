// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"
#include "string"
#include <vector>
#include <math.h>

extern "C" __declspec(dllexport) double myf_math(double a, double x) {
	return (1/sin(x))*(1/sin(x));
}

extern "C" __declspec(dllexport) const char * FName() {
	return "cosec(x)*cosec(x)";

}


extern "C" __declspec(dllexport)  double Kimelfeld_cosec2(double a, double eps, double x) {
	double s = x, d = x;
	for (int n = 3; fabs(d) >= eps; n += 2){
		d *= -x * x / n / (n - 1);
		s += d;
	}
	return (1.0/s)*(1.0/s);
}
extern "C" __declspec(dllexport) double myf_3532703_00001(double a, double epsilon, double x) {
	return Kimelfeld_cosec2(a , epsilon, x);
}

