
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <math.h>

using namespace std;
//"Вариант №13. Вычисление косеканса в квадрате."
//  Косеканс раскладывается в отрезках [-pi+e, -e] [e, pi-e] , где в программе e = 1e-6 " 
//  "В программе число П = 3.141592
void input(double &e,double &x0,double &x1,double &dx,double &a) {
	cout << "Введите точность эпсиллон(E): ";
	cin >> e;
	cout << "Введите начальную координату отрезка: ";
	cin >> x0;
	cout << "Введите конечную координату отрезка: ";
	cin >> x1;
	cout << "Введите значение вашего шага (dX): ";
	cin >> dx;
	cout << "Введите значение параметра:";
	cin >> a;
}
double sigma(double x, double y) {
	double a = sqrt(fabs((x*x - y * y)));
	return a;
}
constexpr auto PI = 3.141592;
int main() //  1 - параметр, 2 - х, 3 - точность 
{	//------------------------------//
	setlocale(LC_ALL, "Russian");
	string nameKimelfeld = { "cosec(x)*cosec(x)" };
	typedef double(*myf_1A)(double, double, double);
	typedef double(*myf_math)(double, double);
	typedef const char* (*Fname)();
	//------------------------------//
	string nameDll = "Dll1";
	if (!LoadLibraryExA(nameDll.c_str(), 0, LOAD_LIBRARY_AS_DATAFILE))
	{
		cout << "Ошибка в библиотеке" << endl;
		system("pause");
		return 0;
	}
	//
	HINSTANCE dll = LoadLibraryA("Dll1.dll");
	myf_1A cosec2 = (myf_1A)(GetProcAddress)(dll, "myf_3532703_00001");
	myf_math cosec2math = (myf_math)(GetProcAddress)(dll, "myf_math");
	Fname namevar = (Fname)(GetProcAddress)(dll, "FName");
	if (dll == NULL)
	{
		cout << "Ошибка библиотеки динамической компоновки!" << endl;
		system("pause");
		return 0;
	}
	if (!(cosec2 && cosec2math && namevar))
	{
		cout << "Ошибка в библиотеке" << endl;
		system("pause");
		return 0;
	}
	//-------------------------------//
	double epsilon, xStart, xFinish, dX, a;
	string ss1 = namevar();
	do {
		system("cls");
		
		input(epsilon, xStart, xFinish, dX,a); 
	} while ((xStart <= -1 * PI) || (xStart >= PI) || (xFinish <= -PI) || (xFinish >= PI) ||  (xStart > xFinish) || (epsilon <= 0.0) || (dX <= 0.0));
	if (ss1 != nameKimelfeld) cout << "Подключена не моя библиотека...." << endl;
	//-------------------------------//
	long double x = xStart;
	//-------------------------------//
	cout << " ----------------------------------------------------------------------------------" << endl;
	cout << " |" << setw (11) << "X" << "|" << "My " << setw(20)  << namevar()  << "|" <<  "math.h " << setw(21) << namevar() << "|" << setw (15) << "Sigma" << "|" << endl;
	cout << " ----------------------------------------------------------------------------------" << endl;
	while (x <= xFinish) {
		double myFun = cosec2(a, epsilon, x);
		double mathFun = cosec2math(a, x);
		if ((isnan(myFun)) || (isnan(mathFun)) || isinf(myFun) || isinf(mathFun)) {
			cout << " |" << setw(11) << x << "|" << setw(23) << "ERROR" << "|" << setw(28) << "ERROR" << "|" << setw(15) << "ERROR" << "|" << endl;
				cout << fixed;
				cout.precision(7);
				cout << " ----------------------------------------------------------------------------------" << endl;
				x = round((x + dX) * 10000000) / 10000000;
			continue;
		}	
		cout << fixed;
		cout << setprecision(7);
		cout << " |" << setw(11) << x << "|" << setw(23) << myFun << "|" << setw(28) << mathFun << "|" << setw(15) << sigma(myFun, mathFun) << "|" << endl;
		cout << " ----------------------------------------------------------------------------------" << endl;
		x = round((x + dX) * 10000000) / 10000000;
	}

	//-------------------------------//
	cout << endl << "Введите идеальный х: ";
	cin >> x;
	//-------------------------------//
	cout << " ----------------------------------------------------------------------------------" << endl;
	cout << " |" << setw(11) << "E" << "|" << "My " << setw(20) << namevar() << "|" << "math.h " << setw(21) << namevar() << "|" << setw(15) << "Sigma" << "|" << endl;
	cout << " ----------------------------------------------------------------------------------" << endl;

	for (double j = 0.1; j > 0.0000001; j /= 10) {
			double myFun = cosec2(a, j, x);
			double mathFun = cosec2math(a, x);
			if ((isnan(myFun)) || (isnan(mathFun)) ||isinf(myFun) || isinf(mathFun) || abs(x) >= PI ) {
				cout.precision(9);
				cout << " |" << setw(11) << x << "|" << setw(23) << "ERROR" << "|" << setw(28) << "ERROR" << "|" << setw(15) << "ERROR" << "|" << endl;
				cout << " ----------------------------------------------------------------------------------" << endl;
				continue;
			}
			cout << fixed;
			cout << setprecision(7);
			cout << " |" << setw(11) << j << "|" << setw(23) << myFun << "|" << setw(28) << mathFun << "|" << setw(15) << sigma(myFun, mathFun) << "|" << endl;
			cout << " ----------------------------------------------------------------------------------" << endl;
	}
	//-------------------------------//
	return 0;
}
