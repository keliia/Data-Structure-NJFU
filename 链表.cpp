#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define HANDSOME 1
typedef struct Node {
	char data;
	struct Node* next;
}Node, * LinkList;

void InitList(LinkList* L);
LinkList CreateFromTail(void);
LinkList CreateFromTail_a2(void);
int Insert(LinkList L, int i, char h);
int Delete(LinkList L, int i, char* h);
Node* Sort(LinkList L);
Node* Inverse(LinkList L);
int ListLength(LinkList L);
void Merge_list7(LinkList la, LinkList lb);
void Merge_list8(LinkList* la, LinkList lb);
void Merge_list9(LinkList la, LinkList lb);
Node* Position10(LinkList L, int K);
Node* Position11(LinkList L, int K);
void Visit(LinkList L);
void Choose(int* lobe);
void Reakmain(int* op);

int main()
{
	int* op = (int*)malloc(sizeof(int));
	Choose(op);
	Reakmain(op);


	return 0;
}

void InitList(LinkList* L) {
	(*L) = (Node*)malloc(sizeof(Node));
	(*L)->next = NULL;
}

LinkList CreateFromTail(void) {
	LinkList L;
	Node* s, * r;
	int flag = 1;
	InitList(&L);
	char c[2];
	c[0] = getchar();
	r = L;
	printf("请你输入一个字符类型单链表:");
	while (flag) {
		c[1] = getchar();
		if (c[1] != '\n') {
			s = (Node*)malloc(sizeof(Node));
			s->data = c[1];
			s->next = NULL;
			r->next = s;
			r = s;
		}
		else {
			flag = 0;
			r->next = NULL;
		}
	}
	return L;
}

LinkList CreateFromTail_a2(void) {
	LinkList L;
	Node* s, * r;
	int flag = 1;
	InitList(&L);
	char c;
	r = L;
	printf("请你输入一个字符类型单链表:");
	while (flag) {
		c = getchar();
		if (c != '\n') {
			s = (Node*)malloc(sizeof(Node));
			s->data = c;
			s->next = NULL;
			r->next = s;
			r = s;
		}
		else {
			flag = 0;
			r->next = NULL;
		}
	}
	return L;
}

int Insert(LinkList L, int i, char h) {
	if (i + 1 <= 0 || i - 1 > ListLength(L)) {
		return ERROR;
	}
	LinkList p = L;
	int count = 0;
	while (count < i - 1) {
		p = p->next;
		count++;
	}
	LinkList s;
	InitList(&s);
	s->data = h;
	s->next = p->next;
	p->next = s;
	return HANDSOME;
}

int Delete(LinkList L, int i, char* h) {
	LinkList p = L, r;
	int count = 0;
	while (p->next && count < i - 1) {
		p = p->next;
		count++;
	}
	if (count != i - 1 && !(p->next) || i <= 0 || i > ListLength(L)) {
		printf("删除位置不合理。\n");
		return ERROR;
	}
	r = p->next;
	p->next = p->next->next;
	*h = r->data;
	free(r);
	return HANDSOME;
}

Node* Sort(LinkList L) {
	LinkList p = NULL;
	LinkList q = L; 

	while (q != NULL) {
		LinkList next = q->next; 
		if (p == NULL || p->data >= q->data) {
			q->next = p;
			p = q;
		}
		else {
			LinkList temp = p;
			while (temp->next != NULL && temp->next->data < q->data) {
				temp = temp->next;
			}
			q->next = temp->next;
			temp->next = q;
		}
		q = next;
	}

	return p; 
}

Node* Inverse(LinkList L) {
	int i = ListLength(L), count = 0;
	LinkList p = L, q, s;
	InitList(&q);
	while (p->next) {
		s = (Node*)malloc(sizeof(Node));
		s->data = p->next->data;
		s->next = q->next;
		q->next = s;
		p = p->next;
	}
	return q;	
}

int ListLength(LinkList L) {
	LinkList P;
	InitList(&P);
	P = L;
	int len = 0;
	while (P->next != NULL) {
		len++;
		P = P->next;
	}
	return len;
}

void Merge_list7(LinkList la, LinkList lb) {
	LinkList pre = la, pa = la->next, pb = lb->next;
	while (pa && pb) {
		if (pa->data < pb->data) {
			pre->next = pa;
			pre = pa;
			pa = pa->next;
		}
		else {
			pre->next = pb;
			pre = pb;
			pb = pb->next;
		}
	}
	pre->next = pa ? pa : pb;
	free(lb);
}

void Merge_list8(LinkList* la, LinkList lb) {
	LinkList pre = *la, pa = (*la)->next, pb = lb->next;
	while (pa && pb) {
		if (pa->data < pb->data) {
			pre->next = pa;
			pre = pa;
			pa = pa->next;
		}
		else {
			pre->next = pb;
			pre = pb;
			pb = pb->next;
		}
	}
	pre->next = pa ? pa : pb;
	free(lb);
	LinkList sigh = Inverse(*la);
	*la = sigh;
}

void Merge_list9(LinkList la, LinkList lb) {
	LinkList pre = la, pa = la->next, pb = lb->next;
	int count = 0;
	while (pa && pb) {
		if (count % 2 == 0) {
			pre->next = pa;
			pre = pa;
			pa = pa->next;
		}
		else {
			pre->next = pb;
			pre = pb;
			pb = pb->next;
		}
		count++;
	}
	pre->next = pa ? pa : pb;
	free(lb);
}

Node* Position10(LinkList L, int K) {
	if (K <= 0) {
		return NULL;
	}
	LinkList P = L;
	int count = 0;
	while (P->next != NULL && count < K) {
		P = P->next;
		count++;
	}
	if (count == K) {
		return P;
	}
	return NULL;
}

Node* Position11(LinkList L, int K) {
	if (ListLength(L) < K || K <= 0) {
		return NULL;
	}
	LinkList P = L;
	int count = 0;
	while (count < ListLength(L) - K + 1) {
		count++;
		P = P->next;
	}
	return P;
}

void Visit(LinkList L) {
	Node* p = L->next;
	if (!p) {
		printf("链表为空。\n");
		return;
	}
	while (p) {
		printf("%c", p->data);
		p = p->next;
	}
	printf("\n");
}

void Choose(int* lobe) {
	printf("请输入你想要进行的操作:\n");
	printf("1.在单链表的第i个位置插入字符元素h\n");
	printf("2.删除单链表的第i个元素\n");
	printf("3.输出单链表内各元素\n");
	printf("4.求单链表的长度\n");
	printf("5.实现单链表中数据节点的按值排序\n");
	printf("6.单链表的逆置\n");
	printf("7.合并两个单链表成一个递增有序的单链表\n");
	printf("8.合并两个单链表成一个递减有序的单链表   (第8题)\n");
	printf("9.交替合并两个单链表，多余的元素放在末尾   (第10题)\n");
	printf("10.查找第K个元素\n");
	printf("11.查找倒数第K个元素   (第13题)\n");
	printf("0.我不想做任何运算\n");
	printf("\n请输入你想要进行的操作的序号:");
	scanf("%d", lobe);
}

void Reakmain(int* op) {
	LinkList a1, a2;
	InitList(&a2);
	a1 = CreateFromTail();
	int K, len, f, i;
	char h[2], * H = (char*)malloc(sizeof(char));
	Node* b1;
	switch (*op) {
	case 1:
		printf("请输入i:");
		scanf("%d", &i);
		h[0] = getchar();
		printf("请输入h:");
		h[1] = getchar();
		f = Insert(a1, i, h[1]);
		if (f) {
			printf("数据元素插入的结果为:");
			Visit(a1);
			printf("\n");
		}
		else {
			printf("插入位置出错。\n");
		}
		break;
	case 2:
		printf("请输入i:");
		scanf("%d", &i);
		f = Delete(a1, i, H);
		if (f) {
			printf("数据元素删除后的结果为:");
			Visit(a1);
			printf("被删除的元素的值为%c。\n", *H);
		}
		break;
	case 3:
		printf("单链表内的各个元素为:");
		Visit(a1);
		break;
	case 4:
		len = ListLength(a1);
		printf("链表长度为%d", len);
		break;
	case 5:
		b1 = Sort(a1);
		printf("按值排序后的链表为:");
		Visit(b1);
		break;
	case 6:
		b1 = Inverse(a1);
		printf("链表逆置后的结果为:");
		Visit(b1);
		break;
	case 7:
		a2 = CreateFromTail_a2();
		Merge_list7(a1, a2);
		printf("合并结果为:");
		Visit(a1);
		break;
	case 8:
		a2 = CreateFromTail_a2();
		Merge_list8(&a1, a2);
		printf("合并结果为:");
		Visit(a1);
		break;
	case 9:
		a2 = CreateFromTail_a2();
		Merge_list9(a1, a2);
		printf("合并结果为:");
		Visit(a1);
		break;
	case 10:
		printf("请输入K:");
		scanf("%d", &K);
		b1 = Position10(a1, K);
		if (b1 != NULL) {
			printf("链表第%d个元素是%c\n", K, b1->data);
		}
		else {
			printf("链表中没有第%d个元素\n", K);
		}
		break;
	case 11:
		printf("请输入K:");
		scanf("%d", &K);
		b1 = Position11(a1, K);
		if (b1 != NULL) {
			printf("链表倒数第%d个元素是%c\n", K, b1->data);
		}
		else {
			printf("链表中没有倒数第%d个元素\n", K);
		}
		break;
	case 0:printf("\nHappy National Day!\n");
	}
}