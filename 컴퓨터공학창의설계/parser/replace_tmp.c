#include <stdio.h>

double g_value = 10;

void func1() {
	printf("I'm function 1\n");

}

void func2() {
	printf("I'm function 2\n");
}

double g_dbl_value = 20;

void main() {
	double data1 = 10;
	double data2 = 20;
	double data3 = data1 * data2;

	double dbl_data = 1.1;


	func1();
	func2();
	
	printf("%d %lf\n",data3, dbl_data);
}
