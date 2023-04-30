#include <iostream>
using namespace std;
struct Pair
{
int x;
int y;
};
int main() {
setlocale(LC_ALL, "Russian");
int n; // m - строк , n - столбцов
int m;
int P;
int i0, j0;
cout << "Введите количество строк в массиве: ";
cin >> m;
cout << endl << "Введите количнство столбцов в массиве: ";
cin >> n;
cout << endl << "Введите вероятность генерации новой бактерии в клетке: ";
cin >> P;
cout << endl << "Введите координаты изначальной бактерии: ";
cin >> i0 >> j0;
int **matrix = new int*[m];
Pair *points = new Pair[m*n]; // points [0].x; points[0].y
for (int i = 0; i < m; i++) {
matrix[i] = new int[m];
}
for (int i = 0; i < m; i++) {
for (int j = 0; j < n; j++, cout << "\t") {
matrix[i][j] = 0;
cout << matrix[i][j];
}
cout << endl;
}
cout << endl;
int k = 1; // Следующая память под точку из массива
int g = 0;
int limit = 1;
points[0].x = i0;
points[0].y = j0;
matrix[points[0].x][points[0].y] = 1;
for (int i = 0; i < m; i++) {
for (int j = 0; j < n; j++, cout << "\t") {
cout << matrix[i][j];
}
cout << endl;
}
if (P == 0) {
return 0;
}
int size = (m * n) - 1;
int it = 0;
while (size != 0) { // Заполнение матрицы
it++;
for (int pointer = 0 ; pointer < limit; pointer++ ) { // Проход по массиву точек
i0 = points[pointer].x;
j0 = points[pointer].y;
for (int i = i0 - 1; i <= i0 + 1; ++i) { // Заполнение бактериями

for (int j = j0 - 1; j <= j0 + 1; ++j) {
if ((0 <= i) && (i < m ) && (0 <= j) && (j < n) && (i != i0 || j != j0)) {
if (((rand() % 100) <= P) && (matrix[i][j] != 1)) {
matrix[i][j] = 1;
size--;
points[k].x = i; // Запоминает точки, заполненные единицами
points[k].y = j; // от 1 до p
k++;
g++;
}
}
}
}
}
cout << endl;
for (int i = 0; i < m; i++) {
for (int j = 0; j < n; j++, cout << "\t") {
cout << matrix[i][j];
}
cout << endl;
}
limit +=g ;
g = 0;
}
cout << endl << "Количество итераций:" << it;
return 0;
}