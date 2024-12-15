#include <stdio.h>
#include <string.h>

#define SElemType char
#include "stack.h"
typedef int QElemType;
#include "queue.h"

int match(char a, char b);
int BracketMatch(char* str);
void YangHuiTriangle(int a);
int main()
{
	int t, a, ch;
	SElemType arr[50];
	printf("请输入你的选择:1.括弧匹配\n");
	printf("               2.杨辉三角\n");
	printf("我的选择是:");
	scanf("%d", &ch);
	switch (ch) {
	case 1:
		printf("请输入一串带有括弧的表达式:");
		scanf("%49s", arr, (unsigned)49);
		t=BracketMatch(arr);
		if(t){
			printf("括弧匹配。\n");
		}
		break;
	case 2:
		printf("请输入杨辉三角的层数:");
		scanf("%d", &a);
		YangHuiTriangle(a);
		break;
	}

	return 0;
}

int match(char a, char b) {
	int flag = 0;
	switch (a) {
	case '(':if (b == ')') {
		flag = 1;
	}
			break;
	case '[':if (b == ']') {
		flag = 1;
	}
			break;
	case '{':if (b == '}') {
		flag = 1;
	}
			break;
	}
	return flag;
}
int BracketMatch(char* str) {
	SeqStack m;
	InitStack(&m);
	SElemType n;
	int flag = 1, count = 0, i = 0;
	for (; str[i] != '\0'; i++) {
		switch (str[i]) {
		case '(':
		case '[':
		case '{':
			Push(&m, str[i]);
			count++;
			break;
		case ')':
		case ']':
		case '}':count++;
			if (IsEmpty(&m)) {
				printf("第%d个%c多余。\n", count, str[i]);
				flag = 0;
			}
			else {
				Pop(&m, &n);
				if (!match(n, str[i])) {
					printf("第%d个%c与%c不匹配。\n", count, str[i], n);
					flag = 0;
				}
			}
			break;
		}
	}
	if (!IsEmpty(&m)) {
		printf("左括弧多余。\n");
		flag = 0;
	}
	return flag;
}
void YangHuiTriangle(int a) {
	SeqQueue Q;
	int i, j, k, temp, ui;
	InitQueue(&Q);
	EnterQueue(&Q, 1);
	for (i = 2; i <= a; i++) {
		for (k = a; k >= i; k--) {
			printf("   ");
		}
		EnterQueue(&Q, 1);
		for (j = 0; j < i - 2; j++) {
			DeleteQueue(&Q, &temp);
			printf("%-6d", temp);
			GetHead(&Q, &ui);
			temp += ui;
			EnterQueue(&Q, temp);
		}
		DeleteQueue(&Q, &temp);
		printf("%-6d\n", temp);
		EnterQueue(&Q, 1);
	}
	while (!IsEmpty2(&Q)) {
		DeleteQueue(&Q, &temp);
		printf("%-6d", temp);
	}
	printf("\n");
}
