#include <cmath>
#include <iostream>
#include <Windows.h>
#include <iomanip>
using namespace std;
int main() {
HANDLE console;
WORD reform;
CONSOLE_SCREEN_BUFFER_INFO turn;
console = GetStdHandle(STD_OUTPUT_HANDLE);
GetConsoleScreenBufferInfo(console, &turn);
reform = turn.wAttributes;
setlocale(LC_ALL, "");
double size, N0, H, ostatok;
do {
cout << "Введите размер массива: ";
cin >> size;
system("cls");
} while (size <= 0 || modf(size,&ostatok ) != 0);
SetConsoleTextAttribute(console,reform);
do {
cout << "Введите количество элементов в строке: ";
cin >> N0;
system("cls");
} while (N0 <= 0 || modf(N0,&ostatok)!=0);
int sizeNormal = static_cast<int>(size);
int N = static_cast<int>(N0);
if (sizeNormal % N == 0) {
H = size / N;
}
else H = sizeNormal / N + 1; // H+1 - количество строк , N - количество элементов в строке
if ((N - 1 == sizeNormal) && (H = 1)) {
sizeNormal++;
}
int **matrix = new int*[sizeNormal]; //
int *numbers = new int [sizeNormal];
for (int i = 0; i < size; i++) {
SetConsoleTextAttribute(console, BACKGROUND_GREEN | 0);
numbers [i] = rand()%2000;
}
SetConsoleTextAttribute(console, reform);
cout << endl << endl << "Матрица (" << N << " X " << H <<"):" << endl << endl;
for (int i = 0; i < H ; i++) {
matrix[i] = new int[N];
}
for (int i = 0; i < H; i++) {
for (int j = 0; j < N; j++) {
matrix[i][j] = 0;
}
}
int k = 0;
for (int i = 0 ; i < H ; i++) {
for (int j = 0 ; j < N; j++) {
if (k >= size) {
break;
}
matrix[i][j] = numbers[k];
k++;
}
}

for (int i = 0; i < H; i++) {
if (i % 3 == 2 || i == 2) { // Красный
SetConsoleTextAttribute(console, FOREGROUND_RED | BACKGROUND_GREEN );
}
if (i % 3 == 1 || i == 1) { // Синий // Работа с цветом текста
SetConsoleTextAttribute(console, FOREGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY );
}
if (i % 3 == 0 || i == 0) { // Белый
SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | BACKGROUND_GREEN );
}
for (int j = 0; j < N; j++) {
double l0 = sizeNormal % N;
int l = static_cast<int>(l0);
if ((sizeNormal % N != 0) && (i == H - 1) && (j >= l) ) {
for (l = l + 1; l < N ; l++) {
SetConsoleTextAttribute(console, BACKGROUND_RED | 0); // Выделение нулей в красный цвет и назначение тексту черного цвета
cout << setw(5) << matrix[i][l] << "\t";
break;
}
}
else {
if ((N - 1 == size) && (H == 1) && (j == N - 1 )) {
SetConsoleTextAttribute(console, BACKGROUND_RED | 0);
}
cout << setw(5) << matrix[i][j] << "\t";
}
}
SetConsoleTextAttribute(console, reform);
cout << endl;
}
delete [] matrix;
return 0;
}