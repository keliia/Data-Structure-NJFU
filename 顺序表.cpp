#include <stdio.h>
#include <stdlib.h>

#define maxsize 100
#define RIGHT 1
#define ERROR 0
typedef struct {
	int* elem;
	int last;
}SeqList;

void InitList(SeqList* l);
int Create(SeqList* l, int n);
void Visit(SeqList* l);
void Assign(SeqList* l);
int InsList1(SeqList* l, int X);
int InsList2(SeqList* l, int i, int a);
int DelList3(SeqList* l, int i, int* a);
int DelList4(SeqList* l, int n, int* a);
int DelList5(SeqList* l, int i, int k);
int Inverse7(SeqList* l);
void MergeList9(SeqList* la, SeqList* lb);
void Odd_Even(SeqList* l);
int DelList12(SeqList* l, int mink, int maxk);
int Bubble(SeqList* l);
void Choose(int* lobe);

int main()
{
	int* love = (int*)malloc(sizeof(int));
	int* a33 = (int*)malloc(sizeof(int));
	int* a44 = (int*)malloc(sizeof(int));
	int i, f, X, a22, n, k, mink, maxk;
	Choose(love);
	SeqList a1, a2;
	if (1 <= *love && *love <= 12) {
		Assign(&a1);
	}

	switch (*love) {
	case 1:
		printf("请输入你想要插入的元素X:");
		scanf("%d", &X);
		f = InsList1(&a1, X);
		if (f) {
			printf("在顺序表中的适当位置插入元素%d后的结果为:", X);
			Visit(&a1);
		}
		break;
	case 2:
		printf("请输入你想要插入的位置:");
		scanf("%d", &i);
		printf("请输入你想要插入的元素的数值:");
		scanf("%d", &a22);
		f = InsList2(&a1, i, a22);
		if (f) {
			printf("在顺序表的第%d个位置插入元素%d的结果为:", i, a22);
			Visit(&a1);
		}
		break;
	case 3:
		printf("请输入你想要删除的元素的位置:");
		scanf("%d", &i);
		f = DelList3(&a1, i, a33);
		if (f) {
			printf("删除第%d个数据元素后的结果为:", i);
			Visit(&a1);
			printf("被删掉的元素为:%d\n", *a33);
		}
		break;
	case 4:
		printf("请输入你想要删除的元素:");
		scanf("%d", &n);
		f = DelList4(&a1, n, a44);
		if (f) {
			printf("删除元素%d后的结果为:", n);
			Visit(&a1);
		}
		break;
	case 5:
		printf("请输入i:");
		scanf("%d", &i);
		printf("请输入k:");
		scanf("%d", &k);
		f = DelList5(&a1, i, k);
		if (f) {
			printf("删除自第%d个元素开始的%d个元素后的结果:", i, k);
			Visit(&a1);
		}
		break;
	case 6:
		printf("顺序表的长度为:%d", a1.last + 1);
		break;
	case 7:
		f = Inverse7(&a1);
		if (f) {
			printf("顺序表的逆置后的结果为:");
			Visit(&a1);
		}
		break;
	case 8:
		Bubble(&a1);
		printf("顺序表按值从小到大排序为:");
		Visit(&a1);
		break;
	case 9:
		printf("\n接下来的操作是生成第二个顺序表。\n");
		Assign(&a2);
		MergeList9(&a1, &a2);
		printf("合并两个顺序表成一个递增有序的顺序表的结果为:");
		Visit(&a1);
		break;
	case 10:
		printf("\n接下来的操作是生成第二个顺序表。\n");
		Assign(&a2);
		MergeList9(&a1, &a2);
		Inverse7(&a1);
		printf("合并两个顺序表成一个递减有序的顺序表的结果为:");
		Visit(&a1);
		break;
	case 11:
		Odd_Even(&a1);
		printf("对顺序表重新排序后的结果为:");
		Visit(&a1);
		break;
	case 12:
		printf("请输入mink:");
		scanf("%d", &mink);
		printf("请输入maxk:");
		scanf("%d", &maxk);
		f = DelList12(&a1, mink, maxk);
		if (f) {
			if (mink >= maxk) {
				printf("你什么也没有删除。\n");
			}
			printf("删除表中所有大于mink且小于maxk的元素后的顺序表为:");
			Visit(&a1);
		}
		break;
	case 0:
		printf("祝你幸福!");
	default:
		printf("祝你国庆快乐!\n");
	}

	return 0;
}

void InitList(SeqList* l) {
	l->elem = (int*)malloc(maxsize * sizeof(int));
	if (l->elem == NULL) {
		printf("\n分配内存失败。\n");
		exit(EXIT_FAILURE);
	}
	l->last = -1;
}

int Create(SeqList* l, int n) {
	if (n < 0) {
		printf("\nERROR\n");
		return 0;
	}
	printf("请输入一个长度为%d的顺序表:", n);
	l->last = n - 1;
	for (int i = 0; i < n; i++) {
		scanf("%d", &(l->elem[i]));
	}
	return 1;
}

void Visit(SeqList* l) {
	if (l->last == -1) {
		printf("EMPTY\n");
	}
	else {
		for (int i = 0; i <= l->last; i++) {
			printf("%d ", l->elem[i]);
		}
		printf("\n");
	}
}

void Assign(SeqList* l) {
	InitList(l);
	int sad;
	printf("请输入你期望的顺序表长度:");
	scanf("%d", &sad);
	Create(l, sad);
}

int InsList1(SeqList* l, int X) {
	if (l->last > maxsize) {
		printf("\n表已满，无法插入。\n");
		return ERROR;
	}
	int k = l->last;
	if (X >= l->elem[k]) {
		l->elem[k + 1] = X;
		l->last++;
		return RIGHT;
	}
	for (int i = 0; i < l->last; i++) {
		if (X < l->elem[0]) {
			for (; k >= 0; k--) {
				l->elem[k + 1] = l->elem[k];
			}
			l->elem[0] = X;
			l->last++;
			break;
		}
		if (l->elem[i] <= X && X <= l->elem[i + 1]) {
			for (; k > i; k--) {
				l->elem[k + 1] = l->elem[k];
			}
			l->elem[i + 1] = X;
			l->last++;
			break;
		}
	}
	return RIGHT;
}

int InsList2(SeqList* l, int i, int a) {
	int k = l->last;
	if (i<1 || i>l->last + 2) {
		printf("\n插入位置不合法。\n");
		return ERROR;
	}
	if (l->last > maxsize) {
		printf("\n表已满，无法插入。\n");
		return ERROR;
	}
	for (; k >= i - 1; k--) {
		l->elem[k + 1] = l->elem[k];
	}
	l->elem[i - 1] = a;
	l->last++;
	return RIGHT;
}

int DelList3(SeqList* l, int i, int* a) {
	if (i<1 || i>l->last + 1) {
		printf("\n栓除位置不合法。\n");
		return ERROR;
	}
	*a = l->elem[i - 1];
	for (int k = i - 1; k <= l->last; k++) {
		l->elem[k] = l->elem[k + 1];
	}
	l->last--;
	return RIGHT;
}

int DelList4(SeqList* l, int n, int* a) {
	for (int i = 0; i <= l->last; i++) {
		if (l->elem[i] == n) {
			for (int j = i; j < l->last; j++) {
				l->elem[j] = l->elem[j + 1];
			}
			l->last--;
			break;
		}
		if (i == l->last) {
			printf("\n该元素不在顺序表中。\n");
			return ERROR;
		}
	}
	return RIGHT;
}

int DelList5(SeqList* l, int i, int k) {
	if (i + k > l->last + 2) {
		printf("\n删除了不存在的元素。\n");
		return ERROR;
	}
	else {
		for (int j = i - 1; j <= l->last; j++) {
			l->elem[j] = l->elem[j + k];
		}
		l->last -= k;
		return RIGHT;
	}
}

int Inverse7(SeqList* l) {
	if (l->last == -1) {
		printf("\nEMPTY\n");
		return ERROR;
	}
	int i = 0, temp7, h = l->last;
	for (; i < h / 2; i++) {
		temp7 = l->elem[i];
		l->elem[i] = l->elem[h - i];
		l->elem[h - i] = temp7;
	}
	return RIGHT;
}

void MergeList9(SeqList* la, SeqList* lb) {
	SeqList lc;
	InitList(&lc);
	int i = 0, j = 0, k = 0;
	while (i <= la->last && j <= lb->last) {
		if (la->elem[i] <= lb->elem[j]) {
			lc.elem[k++] = la->elem[i++];
		}
		else {
			lc.elem[k++] = lb->elem[j++];
		}
	}
	while (i <= la->last) {
		lc.elem[k++] = la->elem[i++];
	}
	while (j <= lb->last) {
		lc.elem[k++] = lb->elem[j++];
	}
	lc.last = k - 1;
	for (i = 0; i <= lc.last; i++) {
		la->elem[i] = lc.elem[i];
	}
	la->last = lc.last;
}

void Odd_Even(SeqList* l) {
	SeqList lb;
	InitList(&lb);
	int t = 0, u = l->last;
	for (int j = 0; j <= l->last; j++) {
		if (l->elem[j] % 2 == 1) {
			lb.elem[t++] = l->elem[j];
		}
		else {
			lb.elem[u--] = l->elem[j];
		}
	}
	for (int j = 0; j <= l->last; j++) {
		l->elem[j] = lb.elem[j];
	}
}

int DelList12(SeqList* l, int mink, int maxk) {
	int b, c = 0, d = 0;
	if (maxk <= mink) {
		return RIGHT;
	}
	for (b = 0; b <= l->last; b++) {
		if (l->elem[b] <= mink) {
			c++;
		}
		else {
			break;
		}
	}
	for (b = 0; b <= l->last; b++) {
		if (l->elem[b] < maxk) {
			d++;
		}
		else {
			break;
		}
	}
	for (int j = c; j <= l->last; j++) {
		l->elem[j] = l->elem[j + d - c];
	}
	l->last -= (d - c);
	return RIGHT;
}

int Bubble(SeqList* l) {
	if (l->last == -1) {
		printf("ERROR");
		return NULL;
	}
	int i = 1, j = 0, t;
	for (; i <= l->last; i++) {
		for (j = 0; j <= l->last - 1; j++) {
			if (l->elem[j] > l->elem[j + 1]) {
				t = l->elem[j];
				l->elem[j] = l->elem[j + 1];
				l->elem[j + 1] = t;
			}
		}
	}
	return ERROR;
}

void Choose(int* lobe) {
	printf("请输入你想要进行的操作:\n");
	printf("1.在顺序表中的适当位置插入元素X   (第3题)\n");
	printf("2.在顺序表的第i个位置插入元素a\n");
	printf("3.删除第i个数据元素\n");
	printf("4.删除值为n数据元素\n");
	printf("5.删除自第i个元素开始的k个元素   (第4题)\n");
	printf("6.求顺序表的长度\n");
	printf("7.顺序表的逆置\n");
	printf("8.顺序表按值从小到大排序\n");
	printf("9.合并两个顺序表成一个递增有序的顺序表\n");
	printf("10.合并两个顺序表成一个递减有序的顺序表   (第5题)\n");
	printf("11.对顺序表重新排序，奇数全部放在前面，偶数全部放在后面   (第6题)\n");
	printf("12.删除表中所有大于mink且小于maxk的元素   (第7题)\n");
	printf("0.我不想做任何运算\n");
	printf("请输入你想要进行的操作的序号:");
	scanf("%d", lobe);
	if (1 <= *lobe && *lobe <= 12) {
		printf("\n接下来的操作是输入整型的顺序表。\n");
	}
	else {
		printf("\n");
	}
}