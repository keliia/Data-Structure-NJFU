#include <stdio.h>
#include <stdlib.h>

typedef char TElemType;
typedef struct Node {
	TElemType data;
	struct Node* LChild, * RChild;
}BiTNode, * BiTree;
#define SElemType BiTree
#include "stack.h"
typedef BiTree QElemType;
#include "queue.h"

BiTree Create(void);
void PreOrder(BiTree root);
void InOrder(BiTree root);
void PostOrder(BiTree root);
int Height(BiTree root);
int Count_All(BiTree root);
int Count_Leaf(BiTree root);
void PreOrder2(BiTree root);
void InOrder2(BiTree root);
void Level(BiTree root);
int main(int argc, char* argv[])
{
	
	int ch, pd;
	void(*p[])(BiTree) = { PreOrder,InOrder,PostOrder,PreOrder2,InOrder2,Level };
	int (*q[])(BiTree) = { Height,Count_All,Count_Leaf };
	printf("你想要做什么呢:1.二叉树前序递归遍历\n"
		"               2.二叉树中序递归遍历\n"
		"               3.二叉树后续递归遍历\n"
		"               4.二叉树前序非递归遍历\n"
		"               5.二叉树中序非递归遍历\n"
		"               6.二叉树层序遍历\n"
		"               7.统计二叉树的高度\n"
		"               8.统计二叉树结点数\n"
		"               9.统计二叉树叶子结点数\n");
	printf("我的选择是:");
	scanf("%d", &ch);
	getchar();
	printf("请按前序输入一棵二叉树:");
	BiTree g = Create();
	if (1 <= ch && ch <= 6) {
		(*p[ch - 1])(g);
	}
	else if (7 <= ch && ch <= 9) {
		pd = (*q[ch - 7])(g);
		printf("%d", pd);
	}

	return 0;
}

BiTree Create(void) {
	TElemType b;
	scanf("%c", &b);
	if (b == '#') {
		return NULL;
	}
	else {
		BiTree Cloud = (BiTree)malloc(sizeof(BiTNode));
		if (Cloud == NULL) {
			printf("空间分配失败");
			exit(EXIT_FAILURE);
		}
		Cloud->data = b;
		Cloud->LChild = Create();
		Cloud->RChild = Create();
		return Cloud;
	}
}
void PreOrder(BiTree root) {
	if (root != NULL) {
		printf("%c", root->data);
		PreOrder(root->LChild);
		PreOrder(root->RChild);
	}
}
void InOrder(BiTree root) {
	if (root != NULL) {
		InOrder(root->LChild);
		printf("%c", root->data);
		InOrder(root->RChild);
	}
}
void PostOrder(BiTree root) {
	if (root != NULL) {
		PostOrder(root->LChild);
		PostOrder(root->RChild);
		printf("%c", root->data);
	}
}
int Height(BiTree root) {
	int h1, h2, h;
	if (root != NULL) {
		h1 = Height(root->LChild);
		h2 = Height(root->RChild);
		h = h1 > h2 ? h1 + 1 : h2 + 1;
	}
	else {
		h = 0;
	}
	return h;
}
int Count_All(BiTree root) {
	int n;
	if (root != NULL) {
		n = 1 + Count_All(root->LChild) + Count_All(root->RChild);
	}
	else {
		n = 0;
	}
	return n;
}
int Count_Leaf(BiTree root) {
	int n;
	if (root != NULL) {
		if (root->LChild == NULL && root->RChild == NULL) {
			n = 1;
		}
		else {
			n = Count_Leaf(root->LChild) + Count_Leaf(root->RChild);
		}
	}
	else {
		n = 0;
	}
	return n;
}
void PreOrder2(BiTree root) {
	SElemType a;
	SeqStack s;
	InitStack(&s);
	while (root != NULL || !IsEmpty(&s)) {
		if (root != NULL) {
			printf("%c", root->data);
			Push(&s, root);
			root = root->LChild;
		}
		else {
			Pop(&s, &a);
			root = a->RChild;
		}
	}
}
void InOrder2(BiTree root) {
	SElemType a;
	SeqStack s;
	InitStack(&s);
	while (root != NULL || !IsEmpty(&s)) {
		if (root != NULL) {
			Push(&s, root);
			root = root->LChild;
		}
		else {
			Pop(&s, &a);
			printf("%c", a->data);
			root = a->RChild;
		}
	}
}
void Level(BiTree root) {
	QElemType Q;
	SeqQueue a;
	InitQueue(&a);
	printf("%c", root->data);
	EnterQueue(&a, root);
	while (!IsEmpty2(&a)) {
		DeleteQueue(&a, &Q);
		if (Q->LChild != NULL) {
			printf("%c", Q->LChild->data);
			EnterQueue(&a, Q->LChild);
		}
		if (Q->RChild != NULL) {
			printf("%c", Q->RChild->data);
			EnterQueue(&a, Q->RChild);
		}
	}
}