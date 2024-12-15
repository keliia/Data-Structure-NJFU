#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX_NUM 20
typedef int QElemType;
#include "queue.h"
typedef char VRType;
typedef enum { DG, DN, UDG, UDN }GraphKind;
typedef struct {
	GraphKind kind;
	VRType vex[MAX_VERTEX_NUM];
	int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int vexnum, arcnum;
}MGraph;
typedef int WeightType;
typedef struct ArcNode {
	int adjvex;
	WeightType weight;
	struct ArcNode* nextarc;
}AreNode;
typedef struct VNode {
	VRType data;
	AreNode* firstarc;
}VNode, AdjList[MAX_VERTEX_NUM];
typedef struct {
	AdjList vertices;
	int vexnum, arcnum;
	GraphKind kind;
}ALGraph;

void Create_MGraph(MGraph* G);
int Locate_VRT(MGraph* G, VRType v);
void Printf_MGraph(MGraph* G);
void DFS(MGraph* G, int i, int* travel);
void DFS_MGraph(MGraph* G);
void BFS_MGraph(MGraph* G);
int Locate_ALGraph(ALGraph* G, VRType v);
void Create_ALGraph(ALGraph* G);
void Printf_ALGraph(ALGraph* G);
void DFS_A(ALGraph* G, int i, int* visited);
void DFS_ALGraph(ALGraph* G);
void BFS_ALGraph(ALGraph* G);
int main(int argc, char* argv[])
{
	MGraph G;
	ALGraph PD;
	int a;
	printf("1.邻接矩阵2.邻接表\n我想要创建:");
	(void)scanf("%d", &a);
	(void)getchar();
	if (a == 1) {
		Create_MGraph(&G);
		Printf_MGraph(&G);
		DFS_MGraph(&G);
		BFS_MGraph(&G);
		printf("\n");
	}
	else {
		Create_ALGraph(&PD);
		Printf_ALGraph(&PD);
		DFS_ALGraph(&PD);
		printf("\n");
		BFS_ALGraph(&PD);
		printf("\n");
	}

	return 0;
}

int Locate_VRT(MGraph* G, VRType v) {
	int i;
	for (i = 0; i < G->vexnum; i++) {
		if (G->vex[i] == v) {
			return i;
		}
	}
	return -1;
}
void Create_MGraph(MGraph* G) {
	int i, j, k;
	VRType v1, v2;
	G->kind = UDG;
	printf("请输入图的顶点数和弧数:");
	(void)scanf("%d%d", &(G->vexnum), &(G->arcnum));
	(void)getchar();
	for (i = 0; i < G->vexnum; i++) {
		for (j = 0; j < G->vexnum; j++) {
			G->arcs[i][j] = 0;
		}
	}
	printf("请输入图的各个顶点:");
	for (i = 0; i < G->vexnum; i++) {
		(void)scanf("%c", &(G->vex[i]));
	}
	(void)getchar();
	printf("请以\"%%c %%c\"的形式输入各条边:\n");
	for (k = 0; k < G->arcnum; k++) {
		(void)scanf("%c %c", &v1, &v2);
		(void)getchar();
		i = Locate_VRT(G, v1);
		j = Locate_VRT(G, v2);
		if (i == -1 || j == -1) {
			printf("你输入了错误的数值");
			return;
		}
		G->arcs[i][j] = 1;
		G->arcs[j][i] = 1;
	}
}
void Printf_MGraph(MGraph* G) {
	int i, j;
	printf("图的种类为:");
	printf("无向图(UDG)\n图中各个顶点为:");
	for (i = 0; i < G->vexnum; i++) {
		printf("%c ", G->vex[i]);
	}
	printf("\n无向图的邻接矩阵为:\n");
	for (i = 0; i < G->vexnum; i++) {
		for (j = 0; j < G->vexnum; j++) {
			printf("%d ", G->arcs[i][j]);
		}
		printf("\n");
	}
}
void DFS(MGraph* G, int i, int* travel) {
	int g;
	printf("%c", G->vex[i]);
	travel[i] = 1;
	for (g = 0; g < G->vexnum; g++) {
		if (G->arcs[i][g]) {
			if (!travel[g]) {
				DFS(G, g, travel);
			}
		}
	}
}
void DFS_MGraph(MGraph* G) {
	int i, travel[MAX_VERTEX_NUM] = { 0 };
	printf("图的深度优先遍历序列为:");
	for (i = 0; i < G->vexnum; i++) {
		if (travel[i] == 0) {
			DFS(G, i, travel);
		}
	}
	printf("\n");
}
void BFS_MGraph(MGraph* G) {
	int i, j, visited[MAX_VERTEX_NUM] = { 0 }, a;
	SeqQueue Q;
	InitQueue(&Q);
	printf("图的广度优先遍历序列为:");
	for (i = 0; i < G->vexnum; i++) {
		if (!visited[i]) {
			printf("%c", G->vex[i]);
			visited[i] = 1;
			EnterQueue(&Q, i);
			while (!IsEmpty2(&Q)) {
				DeleteQueue(&Q, &a);
				for (j = 0; j < G->vexnum; j++) {
					if (G->arcs[a][j] && !visited[j]) {
						visited[j] = 1;
						printf("%c", G->vex[j]);
						EnterQueue(&Q, j);
					}
				}
			}
		}
	}
}
int Locate_ALGraph(ALGraph* G, VRType v) {
	int i;
	for (i = 0; i < G->vexnum; i++) {
		if (G->vertices[i].data == v) {
			return i;
		}
	}
	return -1;
}
void Create_ALGraph(ALGraph* G) {
	int i, j, p;
	VRType vx, vy;
	WeightType weight;
	AreNode* d;
	G->kind = DN;
	printf("请输入图的顶点数和弧数:");
	(void)scanf("%d%d", &(G->vexnum), &(G->arcnum));
	(void)getchar();
	printf("请输入图的各个顶点:");
	for (i = 0; i < G->vexnum; i++) {
		(void)scanf("%c", &(G->vertices[i].data));
		G->vertices[i].firstarc = NULL;
	}
	(void)getchar();
	printf("请以\"%%c %%c %%d\"的形式输入每条弧的弧尾结点、弧头结点、权值:\n");
	for (p = 0; p < G->arcnum; p++) {
		(void)scanf("%c %c %d", &vx, &vy, &weight);
		(void)getchar();
		i = Locate_ALGraph(G, vx);
		j = Locate_ALGraph(G, vy);
		d = (AreNode*)malloc(sizeof(AreNode));
		d->adjvex = j;
		d->weight = weight;
		d->nextarc = G->vertices[i].firstarc;
		G->vertices[i].firstarc = d;
	}
}
void Printf_ALGraph(ALGraph* G) {
	int i, j;
	AreNode* p;
	printf("图的种类为:DN\n图的邻接表为:\n");
	for (i = 0; i < G->vexnum; i++) {
		printf("%c ", G->vertices[i].data);
		if (G->vertices[i].firstarc == NULL) {
			printf("^\n");
		}
		else {
			for (p = G->vertices[i].firstarc; p != NULL; p = p->nextarc) {
				printf("->%d,%d ", p->adjvex, p->weight);
			}
			printf("\n");
		}
	}
}
void DFS_A(ALGraph* G, int i, int* visited) {
	int g;
	AreNode* p;
	printf("%c", G->vertices[i].data);
	visited[i] = 1;
	for (p = G->vertices[i].firstarc; p != NULL; p = p->nextarc) {
		g = p->adjvex;
		if (visited[g] == 0) {
			DFS_A(G, g, visited);
		}
	}
}
void DFS_ALGraph(ALGraph* G) {
	int i, visited[MAX_VERTEX_NUM] = { 0 };
	printf("图的深度优先遍历序列为:");
	for (i = 0; i < G->vexnum; i++) {
		if (visited[i] == 0) {
			DFS_A(G, i, visited);
		}
	}
}
void BFS_ALGraph(ALGraph* G) {
	int i, visited[MAX_VERTEX_NUM] = { 0 }, u, w;
	AreNode* p;
	printf("图的广度优先遍历序列:");
	SeqQueue Q;
	InitQueue(&Q);
	for (i = 0; i < G->vexnum; i++) {
		if (!visited[i]) {
			visited[i] = 1;
			printf("%c ", G->vertices[i].data);
			EnterQueue(&Q, i);
			while (!IsEmpty2(&Q)) {
				DeleteQueue(&Q, &u);
				for (p = G->vertices[u].firstarc; p != NULL; p = p->nextarc) {
					w = p->adjvex;
					if (!visited[w]) {
						visited[w] = 1;
						printf("%c ", G->vertices[w].data);
						EnterQueue(&Q, w);
					}
				}
			}
		}
	}
}