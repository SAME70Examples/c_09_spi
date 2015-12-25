#include "same70.h"                     // Device header

int a = 1;
int b = 3;
float a_f;
float b_f;
double a_d;
double b_d;

int c;
float c_f;
double c_d;

int main(){
	double total = 0;
	SystemCoreClockUpdate();
	int core_clock = SystemCoreClock;
	c = a +b;
	c_f = a_f + b_f;
	c_d = a_d + b_d;
	total += c;
	total += c_f;
	total += c_d;
	return 0;
}
