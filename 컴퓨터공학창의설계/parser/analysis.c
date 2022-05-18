#include <stdio.h>

int g_value = 10;

void func1() {
	printf("I'm function 1\n");

}

void func2() {
  printf("I'm function 2\n");
}

double g_dbl_value = 20;

void main() {
  int data1 = 10;
  int data2 = 20;
  int data3 = data1 * data2;

  double dbl_data = 1.1;


  func1();
  func2();

	printf("%d %lf\n",data3, dbl_data);
}
