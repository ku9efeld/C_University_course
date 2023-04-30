using namespace std;
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>
#include <Windows.h>
#include <iomanip>
// Сделать хэширование
struct stringTable {
	string firstName; // Фамилия
	string middleName; // Имя
	string lastName; // Отчество
	long hash;
	int number;
};
long hashFunction(stringTable personality) {
	string *arr[3] = { &personality.firstName, &personality.middleName, &personality.lastName };
	long  hash = 0;
	for (int i = 0; i < 3; i++) {
		string a = *arr[i];
		for (int j = 0; (j < a.size()) && (i == 0) ; j++) hash += (-1)*int(a[j]) ;
		if (i != 0 ) hash += (-1)*a[0] ;
	}
	return hash % 100000 ;
};
void seperation(const string &text, stringTable &personality){
	istringstream instr(text);
	char I, O;
	instr >> personality.firstName >> personality.middleName >> personality.lastName;
	if (personality.middleName.size() == 4 && personality.lastName == "") {
		I = personality.middleName[0];
		O = personality.middleName[2];
		personality.middleName = I;
		personality.lastName = O;

	}
};
bool checkInput(stringTable &key) {
	for (int i = 0; i < key.middleName.size(); i++) if (key.middleName[i] == '.')  key.middleName.erase(i);
	for (int i = 0; i < key.lastName.size(); i++) if (key.lastName[i] == '.')  key.lastName.erase(i);
	return 0;
}
void sortArray(vector <stringTable> &array, int n) {
	for (int i = 0; i < n - 1; i++) {
		int smallestIndex = i;
		for (int j = i + 1; j < n; j++) if (array[smallestIndex].hash > array[j].hash) smallestIndex = j;
		swap(array[smallestIndex], array[i]);
	}
}
void binarySearch(vector <stringTable> &array, stringTable key, int &sumBinary,int n , int index[]) {
	sortArray(array,n);
	int sum = 0;
	int left = 0;
	int right = size(array) - 1;
	int mid = 0;
	while (1) {
		mid = (left + right) / 2;
		if (key.hash < array[mid].hash) right = mid - 1;
		else if (key.hash > array[mid].hash) left = mid + 1;
		else { // ключ найден
			int save = mid + 1;
			while (array[mid].hash == key.hash && mid > 0) {
				index[sum] = mid;
				sum++;
				mid--;
			}
			if (array[0].hash == key.hash) {
				index[sum] = 0;
				sum++;
			}
			while (array[save].hash == key.hash && save < size(array) - 1) {
				index[sum] = save;
				sum++;
				save++;
			}
			if (array[size(array) - 1].hash == key.hash) {
				index[sum] = array.size() - 1;
				sum++;
			}
			sumBinary = sum;
			break;
		}
		if (left > right) break;
	}
}
void checkCollision(int arrInd[], vector <stringTable> p, stringTable key, int &n, int &C) {
	bool IO = false;
	if (key.middleName.size() == 1 && key.lastName.size() == 1) IO = true;
	for (int i = 0; i < n  && !IO; i++) {
		if (p[arrInd[i]].firstName == key.firstName && p[arrInd[i]].middleName == key.middleName && p[arrInd[i]].lastName == key.lastName ) {
			continue;
		}
		else {
			arrInd[i] = -1;
			C++;
		}
	}
	for (int i = 0; i < n && IO; i++) {
		if (p[arrInd[i]].firstName == key.firstName && p[arrInd[i]].middleName[0] == key.middleName[0] && p[arrInd[i]].lastName[0] == key.lastName[0]) {
			continue;
		}
		else {
			arrInd[i] = -1;
			C++;
		}
	}
}
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ifstream data("база данных.txt");
	char end = '0';
	string field;
	int n = 0;
	vector < stringTable > personality;
	cout << setw (13) <<"\tФамилия" << setw(17) << "\tИмя " << setw(20) << " \tОтчество" << setw (10) << "\tХэш" << endl;
	do {
		getline(data, field);
		if (field.size() > 0) {
			stringTable p0;
			p0.number = n + 1;
			seperation(field, p0);
			p0.hash = hashFunction(p0);
			personality.push_back(p0);
		}
		end = data.get();
		data.putback(end);
		cout << setw(20) << personality[n].firstName << setw(20) << personality[n].middleName << setw(20) << personality[n].lastName << setw(10) << personality[n].hash << endl;
		n++;
		field = "";
	} while (end != EOF);
	//ввод на поиск по массиву, сверка коллизий, а затем вывод всей работы ( разница с колизией и найденные по запросу)
	stringTable key;
	string input;
	do { 
		cout << "Введите полное ФИО или полную фамилию и инициалы (Фамилия И. О.) для осуществления поиска по исходной таблице:" << endl;
		getline(cin, input);
		seperation(input,key);
	} while (checkInput(key));
	key.hash = hashFunction(key);
	int sumBinary = 0;
	int collisionIndex[100];
	int C = 0;
	binarySearch(personality, key, sumBinary, n, collisionIndex);
	// Всего совпадений по хэшу
	cout << "Количество совпадений по хэшу в бинарном поиске: " <<  sumBinary << endl;
	// Индексы возможного ответа
	if (!sumBinary) {
		cout << "увы, такого человека здесь нет....";
		return 0;
	}
	cout << "Номера строк этих совпадений в исходной таблице: ";
	for (int i = 0; i < sumBinary; i++) {
		if (i == sumBinary - 1) {
			cout << personality[collisionIndex[i]].number;
			break;
		}
		cout << personality[collisionIndex[i]].number << ",  ";
	}
	// Исключений коллизий
	checkCollision(collisionIndex,personality,key,sumBinary,C);
	// sumBinary - совпадения, С - кол-во коллизии
	cout << endl << "Количество коллизии в совпадениях: " << C;
	cout << endl << "Итоговый ответ (номер(а) строки в исходной таблице): ";
	for (int i = 0; i < sumBinary; i++)
	{
		int sum = sumBinary - C;
		if (collisionIndex[i] < 0) continue;
		sum--;
		if (i == sumBinary - 1 || sum == 0) {
			cout << personality[collisionIndex[i]].number;
			break;
		}
		cout << personality[collisionIndex[i]].number << ",  ";
	}
	system("pause");
	return 0;
}