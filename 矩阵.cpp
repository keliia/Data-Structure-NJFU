#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAXSIZE 20
#define ElemType int
typedef struct {
	int row, col;
	ElemType e;
}Triple;
typedef struct {
	Triple data[MAXSIZE + 1];
	int m, n, len;
}TSMatrix;
void Input(TSMatrix* a);
void Output(TSMatrix* a);
void Simple(TSMatrix g, TSMatrix* pd);
void Fast(TSMatrix g, TSMatrix* pd);
void Quick(TSMatrix g, TSMatrix* pd);
int Plus(TSMatrix g, TSMatrix p, TSMatrix* d);
void BODY(void);
int main(int argc, char* argv[])
{
	BODY();
	return 0;
}
void Input(TSMatrix* a) {
	int i, j, p = 1;
	ElemType x;
	printf("请输入矩阵的行和列:");
	scanf("%d%d", &a->m, &a->n);
	for (i = 1; i <= a->m; i++) {
		for (j = 1; j <= a->n; j++) {
			scanf("%d", &x);
			if (x) {
				a->data[p].row = i;
				a->data[p].col = j;
				a->data[p].e = x;
				p++;
			}
		}
	}
	a->len = p - 1;
}
void Output(TSMatrix* a) {
	int i, j, k = 1;
	for (i = 1; i <= a->m; i++) {
		for (j = 1; j <= a->n; j++) {
			if (k <= a->len && i == a->data[k].row && j == a->data[k].col) {
				printf("%d ", a->data[k++].e);
			}
			else {
				printf("0 ");
			}
		}
		printf("\n");
	}
}
void Simple(TSMatrix g, TSMatrix* pd) {
	pd->m = g.n;
	pd->n = g.m;
	pd->len = g.len;
	if (pd->len) {
		int q = 1;
		for (int i = 1; i < g.len; i++) {
			pd->data[i].row = 0;
			pd->data[i].col = 0;
			pd->data[i].e = 0;
		}
		for (int i = 1; i <= g.n; i++) {
			for (int p = 1; p <= g.len; p++) {
				if (g.data[p].col == i) {
					pd->data[q].col = g.data[p].row;
					pd->data[q].row = g.data[p].col;
					pd->data[q].e = g.data[p].e;
					q++;
				}
			}
		}
	}
}
void Fast(TSMatrix g, TSMatrix* pd) {
	pd->m = g.n;
	pd->n = g.m;
	pd->len = g.len;
	int num[MAXSIZE + 1] = { 0 };
	int pos[MAXSIZE + 1] = { 0 };
	int col, t, p, q;
	if (pd->len) {
		for (t = 1; t <= g.len; t++) {
			++num[g.data[t].col];
		}
		pos[1] = 1;
		for (col = 2; col <= g.n; col++) {
			pos[col] = pos[col - 1] + num[col - 1];
		}
		for (p = 1; p <= g.len; p++) {
			col = g.data[p].col;
			q = pos[col];
			pd->data[q].row = g.data[p].col;
			pd->data[q].col = g.data[p].row;
			pd->data[q].e = g.data[p].e;
			++pos[col];
		}
	}
}
void Quick(TSMatrix g, TSMatrix* pd) {
	pd->m = g.n;
	pd->n = g.m;
	pd->len = g.len;
	int num_pos[MAXSIZE + 1] = { 0 }, col, t, p, q;
	if (pd->len) {
		for (t = 1; t <= g.len; t++) {
			num_pos[g.data[t].col + 1]++;
		}
		num_pos[1] = 1;
		for (col = 2; col <= g.n; col++) {
			num_pos[col] = num_pos[col - 1] + num_pos[col];
		}
		for (p = 1; p <= g.len; p++) {
			col = g.data[p].col;
			q = num_pos[col];
			pd->data[q].row = g.data[p].col;
			pd->data[q].col = g.data[p].row;
			pd->data[q].e = g.data[p].e;
			num_pos[col]++;
		}
	}
}
int Plus(TSMatrix g, TSMatrix p, TSMatrix* d) {
	if (g.m != p.m || g.n != p.n) {
		return 0;
	}
	d->m = g.m;
	d->n = p.n;
	if (g.len == 0 && p.len == 0) {
		d->len = 0;
		return 1;
	}
	int i = 1, j = 1, k = 1;
	while (i <= g.len && j <= p.len) {
		if (g.data[i].row < p.data[j].row) {
			d->data[k++] = g.data[i++];
		}
		else {
			if (g.data[i].row > p.data[j].row) {
				d->data[k++] = p.data[j++];
			}
			else {
				if (g.data[i].col < p.data[j].col) {
					d->data[k++] = g.data[i++];
				}
				else {
					if (g.data[i].col > p.data[j].col) {
						d->data[k++] = p.data[j++];
					}
					else {
						d->data[k].row = g.data[i].row;
						d->data[k].col = p.data[j].col;
						d->data[k++].e = g.data[i++].e + p.data[j++].e;
					}
				}
			}
		}
	}
	for (; i <= g.len; i++, k++) {
		d->data[k] = g.data[i];
	}
	for (; j <= p.len; j++, k++) {
		d->data[k] = p.data[j];
	}
	d->len = k - 1;
	return 1;
}
void BODY(void) {
	TSMatrix a, b, c;
	printf("你想要做什么呢:"
		"1.矩阵简单转置\n"
		"               2.矩阵快速转置\n"
		"               3.矩阵快速转置(num_pos)\n"
		"               4.矩阵相加\n"
		"               0.Life is boundless\n"
		"我的选择是:");
	int g, p;
	scanf("%d", &g);
	if (g)	Input(&a);
	switch (g) {
	case 0:printf("感谢赏玩!\n");
		break;
	case 1:Simple(a, &b);
		printf("简单转置的结果为:\n");
		Output(&b);
		break;
	case 2:Fast(a, &b);
		printf("快速转置的结果为:\n");
		Output(&b);
		break;
	case 3:Quick(a, &b);
		printf("快速转置的结果为:\n");
		Output(&b);
		break;
	case 4:Input(&b);
		p = Plus(a, b, &c);
		if (p) {
			printf("矩阵相加的结果为:\n");
			Output(&c);
		}
		else {
			printf("矩阵大小并不相同,无法相加!");
		}break;
	}
}