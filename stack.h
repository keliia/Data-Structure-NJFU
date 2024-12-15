#define Stack_size 50
#define TRUE 1
#define FALSE 0
typedef struct {
	SElemType elem[Stack_size];
	int top;
}SeqStack;

void InitStack(SeqStack* s) {
	s->top = -1;
}
int IsEmpty(SeqStack* s) {
	if (s->top == -1) {
		return 1;
	}
	else {
		return 0;
	}
}
int IsFull(SeqStack* s) {
	if (s->top == Stack_size - 1) {
		return 1;
	}
	else {
		return 0;
	}
}
int Push(SeqStack* s, SElemType a) {
	if (IsFull(s)) {
		return FALSE;
	}
	else {
		s->elem[++s->top] = a;
		return TRUE;
	}
}
int Pop(SeqStack* s, SElemType* a) {
	if (IsEmpty(s)) {
		return FALSE;
	}
	else {
		*a = s->elem[s->top--];
		return TRUE;
	}
}
int GetTop(SeqStack* s, SElemType* a) {
	if (IsEmpty(s)) {
		return FALSE;
	}
	else {
		*a = s->elem[s->top];
	}
	return TRUE;
}