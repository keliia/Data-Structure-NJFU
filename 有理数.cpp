#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

typedef struct {
	int son;
	int mom;
}ration;

void create(ration* p);
int commonmax(int a, int b);
ration plus(ration x, ration y);
ration minus(ration x, ration y);
ration mult(ration x, ration y);
ration divide(ration x, ration y);
void output(ration a);
void del_first(char* str);

int main()
{
	int choice;
	ration a1, a2, c1;
	create(&a1);
	create(&a2);
	
	do {
		printf("请选择你想要做的运算(输入数字)： 1.加法 2.减法 3.乘法 4.除法 0.退出:");
		scanf("%d", &choice);
		switch (choice) {
		case 1:c1 = plus(a1, a2);
			printf("有理数相加的结果为:");
			output(c1);
			break;
		case 2:c1 = minus(a1, a2);
			printf("有理数相减的结果为:");
			output(c1);
			break;
		case 3:c1 = mult(a1, a2);
			printf("有理数相乘的结果为:");
			output(c1);
			break;
		case 4:c1 = divide(a1, a2);
			printf("有理数相除的结果为:");
			output(c1);
			break;
		case 0:break;
		default:choice = 0;
		}	
	} while (choice);	

	return 0;
}

int commonmax(int a, int b)
{
	if (a == 0 || b == 0) {
		a = 1;
	}
	else {
		while (a != b) {
			if (a > b) {
				a = a - b;
			}
			else {
				b = b - a;
			}
		}
	}

	return a;
}

void create(ration* p)
{
	char str[100], num1[100], num2[100];
	double a;
	int i = 0, j = 0, k = 0, t = 1, r = 1;

	printf("请你用\"%%d/%%d\"或小数的形式输入一个有理数:");
	fgets(str, sizeof(str), stdin);
	for (; i < str[i]!='\0'; i++) {
		if (str[i] == '.') {
			t = 0;
			if (str[0] == '-') {
				del_first(str);
				r = -1;
			}
			a = atof(str);
			p->son = a * pow(10, strlen(str) - i - 1);
			p->mom = pow(10, strlen(str) - i - 1);
			int ch = commonmax(p->son, p->mom);
			p->son /= ch;
			p->mom /= ch;
			p->son *= r;
			break;
		}
		else if (str[i] == '/') {
			t = 0;
			if (str[0] == '-') {
				del_first(str);
				r = -1;
			}
			while (str[j] != '/' && str[j] != '\0') {
				num1[j] = str[j];
				j++;
			}
			num1[j] = '\0';
			j++;
			while (str[j] != '\0') {
				num2[k] = str[j];
				k++;
				j++;
			}
			num2[k] = '\0';
			p->son = atoi(num1);
			p->mom = atoi(num2);
			while (p->mom == 0) {
				printf("你输入了一个非法的有理数,");
				create(p);
			}
			int ch = commonmax(p->son, p->mom);
			p->son /= ch;
			p->mom /= ch;
			p->son *= r;
			break;
		}
		else if (!isdigit(str[i]) && str[i] != '\n' && str[i] != '-') {
			t = 0;
			printf("你输入了错误的字符，");
			create(p);
		}
	}

	if (t) {
		p->son = atoi(str);
		p->mom = 1;
	}
}

ration plus(ration x, ration y)
{
	ration z;
	z.son = x.son * y.mom + y.son * x.mom;
	z.mom = x.mom * y.mom;
	return z;
}

ration minus(ration x, ration y)
{
	ration z;
	z.son = x.son * y.mom - y.son * x.mom;
	z.mom = x.mom * y.mom;
	return z;
}

ration mult(ration x, ration y)
{
	ration z;
	z.son = x.son * y.son;
	z.mom = x.mom * y.mom;
	return z;
}

ration divide(ration x, ration y)
{
	ration z;
	z.son = x.son * y.mom;
	z.mom = x.mom * y.son;
	return z;
}

void output(ration a)
{
	if (a.son < 0 && a.mom < 0) {
		a.son = abs(a.son);
		a.mom = abs(a.mom);
	}
	else if (a.son < 0 && a.mom>0 || a.son > 0 && a.mom < 0) {
		a.son = abs(a.son);
		a.mom = abs(a.mom);
		printf("-");
	}

	int ch = commonmax(a.son, a.mom);
	a.son /= ch;
	a.mom /= ch;
	if (a.son == 0) {
		printf("0\n");
	}
	else if (a.mom == 0) {
		printf("Not A Number!\n");
	}
	else if (a.son == a.mom) {
		printf("1\n");
	}
	else if (a.son % a.mom == 0) {
		printf("%d\n", a.son / a.mom);
	}
	else {
		printf("%d/%d\n", a.son, a.mom);
	}
}

void del_first(char* str) {
	if (str == NULL || str[0] == '\0') {
		return;
	}
	char* new_str = str + 1;
	while (*new_str) {
		*str++ = *new_str++;
	}
	*str = '\0';
}