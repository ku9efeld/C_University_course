#include <stdio.h>
#include <math.h>
#include <stdlib.h>
double function(double x, double a) {
double y, z;
z = 2 * a * (sin(x / a) + log(x));
y = 1 / z;
return y;
}
int main() {
int n = 0;
double d, a, x;
printf("Input a:");
scanf("%lf", &a);
printf("----------------------------------------------------------------\n");
printf("| N | X | A | Y |\n");
printf("|-----|--------|-------------------|---------------------------|\n");
if (((1000000 >= fabs(a)) && (fabs(a) >= 0.000001)) || (a == 0)) {
for (x = -10; x <= 5; x = x + 1.5) {
n++;
if (a != 0 && x > 0) {
d = function(x, a);
printf("| %-2d.", n);
printf(" | ");
printf(" %-5.1lf", x);
printf(" | ");
printf("%-17lf", a);
printf(" | %-26f|\n", d);
printf("----------------------------------------------------------------\n");
}
else {
printf("| %-2d.", n);
printf(" | ");
printf(" %-5.1lf", x);
printf(" | ");
printf("%-17lf", a);
printf(" | NV |\n");
printf("----------------------------------------------------------------\n");
}
}
}
else {
printf("No!\n");
}
system("pause");
return (0);
}