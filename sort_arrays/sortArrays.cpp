#include <iostream>
#include<cmath>
#include <algorithm>
#include <string>
#include <ctime>
#include<iomanip>
using namespace std;


void inputMatrix(int A, int N, int **matrix) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < A; j++) {
			matrix[i][j] = rand() % 20 - 10; // rand() % (B-A) - A -> Необходимый диапозон рандомных чисел
			//cin >> matrix[i][j];
			cout << internal << setw(2) << matrix[i][j] << "\t";
		}
		cout << endl;
	}
}

void coppyMatrix(int **m0, int **m, int A, int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < A; j++) {
			m[i][j] = m0[i][j];
		}
	}
}

void selectSort(int j, int N, int **matrix, unsigned int &c, unsigned int &m) {	// при 4 элементах не дб 6 сравнений  // Сортировка простым выбором
	int ci = 0;
	int mi = 0;
	int smallestIndex;
	for (int i = 0; i < N - 1; i++) {
		smallestIndex = i;	
		for (int k = i + 1; k < N; k++) {
			
			if (abs(matrix[k][j]) < abs(matrix[smallestIndex][j])) {
				smallestIndex = k;
				ci++;
			}
			else ci++;
		}
		if (smallestIndex == i) continue;
		swap(matrix[i][j], matrix[smallestIndex][j]);
		mi++;
	}
	c = c + ci;
	m = m + mi;
}

void bubbleSort(int j,int N, int **matrix, unsigned int &c, unsigned int &m) {
	bool optimum;
	for (int i = 0; i < N - 1 ; i++) {
		optimum = false;
		for (int k = 0; k < N - i - 1 ; k++) {
			c++;// сравнения
			if (abs(matrix[k][j]) > abs(matrix [k+1][j])) {
				swap(matrix[k][j], matrix[k + 1][j]);// перестановка
				optimum = true;
				m++;
			}
	}
		if (optimum == false ) break;
	}

}

void insertSort(int j, int N, int  **matrix, unsigned int &c, unsigned int &m) { // Сортировка вставками
	int ci = 0;
	int mi = 0;
	int save = 1;
	for (int i = 1; i < N  ; i++) {//ST
		save = i;
		bool check = false;
		for (int k = i - 1; k >= 0 ; k--) {
			if (abs(matrix[k][j]) <= abs(matrix[save][j])) { //ST
				ci++;
				break;
			}
				swap(matrix[save][j], matrix[k][j]);
				save--;
				check = true;
				ci++;
			}
		if (check == true) mi++;
		}
	
	c = c + ci;
	m = m + mi;
}

void outputSortMatrix(int A, int N, int **matrix) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < A; j++) {
			cout << internal << setw (2) << matrix[i][j] << "\t";
		}
		cout << endl;
	}
}

void quickSort(int **matrix, int j, int firstIndex, int lastIndex, unsigned int &c, unsigned int &m) {
	if (firstIndex < lastIndex) {
		int ci = 0;
		int mi = 0;
		int left = firstIndex;
		int right = lastIndex;
		int privotIndex = (left + right + 1) / 2;
		int privot = abs(matrix[privotIndex][j]);
		c = c + (lastIndex - firstIndex);
		do {
			mi = 0;
			bool rightSortHand = false;
			bool leftSortHand = false;
			bool ptpLeft = false;
			bool ptpRight = false;
			while (abs(matrix[left][j]) < privot) left++;
			while (abs(matrix[right][j]) > privot) right--;
			if (right - left > 1 || left - right > 1) {
				if (left == privotIndex) leftSortHand = true;
				if (right == privotIndex) rightSortHand = true;
			}
			if (left == privotIndex) ptpLeft = true;
			if (right == privotIndex) ptpRight = true;
			if (left <= right) {
				swap(matrix[left][j], matrix[right][j]);
				if (ptpLeft  && abs(matrix[left][j]) != abs(matrix[right][j])) privotIndex = right;
				if (ptpRight && abs(matrix[left][j]) != abs(matrix[right][j]))	privotIndex = left;
				if ((left != right) && abs(matrix[left][j]) != abs(matrix[right][j])) mi++;
				left++;
				right--;
				if (!(ptpRight) && rightSortHand)
					right++;
				if (!(ptpLeft) && leftSortHand)
					left--;
			}
			m = m + mi;
		} while (left <= right);
		if (left == privotIndex) left++;
		if (right == privotIndex) right--;
		quickSort(matrix, j, firstIndex, right, c, m);
		quickSort(matrix, j, left, lastIndex, c, m);
	}
}

void shellsSort(int j, int N,int **matrix,unsigned int &c, unsigned int &m){
	int buff;
	int s;
	for (int step = N / 2; step > 0; step = step / 2) {
		
		for (int rInsert = step; rInsert < N; rInsert++) {
			buff = matrix[rInsert][j];
			bool check = false;
			for (s = rInsert; s >= step; s -= step) {
				c++;
				if (abs(buff) < abs(matrix[s - step][j])) {	
					matrix[s][j] = matrix[s - step][j];
					check = true;
				}
				else {
					break;
				}
			}
			if (check == true) m++;
			matrix[s][j] = buff;
		}
	}
}
 
int main() {
	setlocale(LC_ALL, "Russian");
	int A, N;
	srand(time(NULL));
	cout << "\\\\Сортировка элементов по модулю в столбцах матрицы в порядке неубывания\\\\" << endl;
	cout << "Введите кол-во строк в матрице: ";
	cin >> N; 
	cout << endl << "Введите кол-во столбцов в матрице: ";
	cin >> A;
	//cout << endl << endl << "Изначальный массив" << endl;
	// Формирование массивов в памяти
	int **matrix = new int*[N];
		int **matrixCoppy = new int*[N];
		for (int i = 0; i < N; i++) {
			matrix[i] = new int[A];
			matrixCoppy[i] = new int[A];
		}	
	// Создание массивов счетчиков
		unsigned int C[5];
		unsigned int M[5];
		for (int i = 0; i < 5; i++) {
			C[i] = 0;
			M[i] = 0;
		}
	// Заполнение одного из массивов, а затем копирование
	string s[] = { "Сортировка 'пузырьком'","Сортировка простым выбором","Сортировка вставками","Быстрая сортировка","Сортировка Шелла"};
	inputMatrix(A,N,matrix);
	coppyMatrix(matrix,matrixCoppy,A,N);
	// Сортировка 
	for (int sortingType = 0; sortingType < 5; sortingType++) {
		if (N == 1) continue;
		for (int j = 0; j < A && sortingType == 0; j++)  bubbleSort(j, N, matrix,C[sortingType],M[sortingType]);
		for (int j = 0; j < A && sortingType == 1; j++) selectSort(j, N, matrix,C[sortingType],M[sortingType]);
		for (int j = 0; j < A && sortingType == 2; j++) insertSort(j, N, matrix,C[sortingType],M[sortingType]);
		for (int j = 0; j < A && sortingType == 3; j++) quickSort(matrix,j,0,N-1,C[sortingType], M[sortingType]);
		for (int j = 0; j < A && sortingType == 4; j++) shellsSort(j,N,matrix, C[sortingType], M[sortingType]); 
		cout << s[sortingType] << endl;
		outputSortMatrix(A, N, matrix);
		coppyMatrix(matrixCoppy, matrix, A, N);
	}
	// Табличка
	for (int i = -1; i < 5; i++, cout << endl) {
		if (i == -1) {
			cout << endl << "|__________________________|______________|______________|" << endl << "#      Тип сортировки      #  Сравнения   # Перестановки #" << endl << "#__________________________#______________#______________#";
		}
		else
		{
			cout << "|" << setw (26) << s[i] << "|" << setw(14) << C[i] << "|" << setw(14) << M[i] << "|";
		}
	}
	cout <<  "#__________________________#______________#______________#";


	// Чистим память =)
	for (int i = 0; i < N ; i++) {
		delete[] matrix[i];
		delete[] matrixCoppy[i];
	}
	delete[] matrix;
	delete[] matrixCoppy;
	//
	system("pause");
	return 0;
}