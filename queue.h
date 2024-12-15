#define QUEUE_SIZE 50
#define TRUE 1
#define FALSE 0
typedef struct {
	QElemType elem[QUEUE_SIZE];
	int front;
	int rear;
}SeqQueue;

void InitQueue(SeqQueue* Q) {
	Q->front = 0;
	Q->rear = 0;
}
int IsEmpty2(SeqQueue* Q) {
	if (Q->front == Q->rear) {
		return 1;
	}
	else {
		return 0;
	}
}
int IsFull2(SeqQueue* Q) {
	if ((Q->rear + 1) % QUEUE_SIZE == Q->front) {
		return 1;
	}
	else {
		return 0;
	}
}
int EnterQueue(SeqQueue* Q, QElemType a) {
	if (IsFull2(Q)) {
		return FALSE;
	}
	else {
		Q->elem[Q->rear] = a;
		Q->rear = (Q->rear + 1) % QUEUE_SIZE;
		return TRUE;
	}
}
int DeleteQueue(SeqQueue* Q, QElemType* a) {
	if (IsEmpty2(Q)) {
		return FALSE;
	}
	else {
		*a = Q->elem[Q->front];
		Q->front = (Q->front + 1) % QUEUE_SIZE;
		return TRUE;
	}
}
int GetHead(SeqQueue* Q, QElemType* a) {
	if (IsFull2(Q)) {
		return FALSE;
	}
	else {
		*a = Q->elem[Q->front];
		return TRUE;
	}
}
int GetTail(SeqQueue* Q, QElemType* a) {
	if (IsEmpty2(Q)) {
		return FALSE;
	}
	else {
		*a = Q->elem[(Q->rear - 1 + QUEUE_SIZE) % QUEUE_SIZE];
		return TRUE;
	}
}