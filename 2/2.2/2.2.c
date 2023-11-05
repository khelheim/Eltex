#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double sum(double arg1, double arg2) { // сложение
	return arg1 + arg2;
}

double dif(double arg1, double arg2) { // вычитание
	return arg1 - arg2;
}

double mult(double arg1, double arg2) { // умножение
	return arg1 * arg2;
}

double divide(double arg1, double arg2) { // деление
	if (arg2 == 0) { // проверка на деление на 0
		printf("Zero dividing is prohibited\n");
		return 0;
	}
	return arg1 / arg2;
}

int main() {
	int choice = '0';
	double arg1, arg2, res;
	int init = 0;
	printf("----Calculator with operations of two type double arguments----\n"); 
	while (1) {
		printf("Available actions:\n(0) - exit\n(1) - sum\n(2) - reduct\n(3) - multiply\n(4) - divide\n(8) - return previous result\n(9) - use previous result as argument 1\n(10) - use previous result as argument 2\nPreffered action: ");
		scanf_s("%d", &choice); // выбор действия
		switch (choice) {
		case 0: // выход из программы
			return 0;
		case 1: // сложение
			if (init != 2) {
				printf("Enter argument 1: ");
				scanf_s("%lf", &arg1);
			}
			if (init != 3) {
				printf("Enter argument 2: ");
				scanf_s("%lf", &arg2);
			}
			init = 1;
			res = sum(arg1, arg2);
			printf("\n%lf + %lf = %lf\n", arg1, arg2, res);
			break;
		case 2: // вычитание
			if (init != 2) {
				printf("Enter argument 1: ");
				scanf_s("%lf", &arg1);
			}
			if (init != 3) {
				printf("Enter argument 2: ");
				scanf_s("%lf", &arg2);
			}
			init = 1;
			res = dif(arg1, arg2);
			printf("\n%lf - %lf = %lf\n", arg1, arg2, res);
			break;
		case 3: // умножение
			if (init != 2) {
				printf("Enter argument 1: ");
				scanf_s("%lf", &arg1);
			}
			if (init != 3) {
				printf("Enter argument 2: ");
				scanf_s("%lf", &arg2);
			}
			init = 1;
			res = mult(arg1, arg2);
			printf("\n%lf x %lf = %lf\n", arg1, arg2, res);
			break;
		case 4: // деление
			if (init != 2) {
				printf("Enter argument 1: ");
				scanf_s("%lf", &arg1);
			}
			if (init != 3) {
				printf("Enter argument 2: ");
				scanf_s("%lf", &arg2);
			}
			init = 1;
			res = divide(arg1, arg2);
			if (arg2 != 0)
				printf("\n%lf / %lf = %lf\n", arg1, arg2, res);
			else
				init = 0;
			break;
		case 8: // вывод предыдущего результата
			if (init != 0) // проверка на инициализацию res
				printf("Prev result: %lf\n", res);
			else
				printf("No previous result\n");
			break;
		case 9: // использование предыдущего результата, как arg1
			if (init != 0) { // проверка на инициализацию res
				init = 2;
				arg1 = res;
				printf("Argument 1 = %lf\n", res);
			}
			else
				printf("No previous result\n");
			break;
		case 10: // использование предыдущего результата, как arg2
			if (init != 0) { // проверка на инициализацию res
				init = 3;
				arg2 = res;
				printf("Argument 2 = %lf\n", res);
			}
			else
				printf("No previous result\n");
			break;
		default: // если нет такого действия
			printf("No such actions\n");
		}
	}
}