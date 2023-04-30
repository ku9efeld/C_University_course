#include <iostream>
#include <string>
#include <cmath>
using namespace std;
bool check(long double year) {
int year1 = static_cast<int>(year);
long double x;
long double y;
y = modf(year,&x);
return ( (year1 == 0) || (y != 0) );
    }
int main() {

long double yearInput;
int colorIndex, animalIndex, n;
string animals[12] = { "Pig" , "Rat", "Cow", "Tiger",
"Rabbit", "Dragon", "Snake", "Horse", "Sheep","Monkey","Chicken","Dog" };
string colors[5] = { "Black", "Green","Red","Yellow","White" };
do {
cout << "Input year: ";
cin >> yearInput;
    } while (check(yearInput));
int year = static_cast<int>(yearInput);
if (year > 0) {
year = year + 2697;
animalIndex = (year % 60) % 12;
if (year % 2 == 1) {
year++;
    }
colorIndex = ((year % 60) / 2) % 5;
    }
else if (-2698 <= year && year <= -1) {
year = year + 2698;
animalIndex = (year % 60) % 12;
if (year % 2 == 1) {
year++;
    }
colorIndex = ((year % 60) / 2) % 5;
    }
else {
n = -1 * (year + 2699) / 60 + 1;
year = year + (60 * n) + 2698;
animalIndex = (year % 60) % 12;
if (year % 2 == 1) {
year++;
    }
colorIndex = ((year % 60) / 2) % 5;
    }
cout << colors[colorIndex] << " " << animals[animalIndex];
return 0;
}