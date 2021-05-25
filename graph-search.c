/*
 * Graph Search
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 10

typedef struct Vertex{
	int data;
	struct Vertex *link;
} Vertex;

typedef struct Graph {
	Vertex *Head;
} Graph;

/* for queue */
#define MAX_QUEUE_SIZE		20 // 큐의 최대 크기를 20으로 저장
Vertex* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Vertex* deQueue(); // 큐에서 삭제하는 함수
void enQueue(Vertex* v); // 큐에 추가하는 함수

int visitInfo[MAX_VERTEX];
int VisitVertex(int visitV);

Graph* initialize(Graph *G);
int freeGraph(Graph *G);
int insertVertex(Graph *G, int v);
int insertEdge(Graph *G, int u, int v);
int DepthFS(Graph *G, int v);
int BreathFS(Graph *G, int v);
void printGraph(Graph *G);
int CheckV(Graph *G, int v);
void initVist();

int main()
{
	printf("[----- [Chaerin Jung] [2020039022] -----]");

	char command;
	int u, v;
	Graph* graph = NULL;

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                         Graph Searches                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph     = z                                       \n");
		printf(" Insert Vertex        = v      Insert Edge                  = e \n");
		printf(" Depth First Search   = d      Breath First Search          = b \n");
		printf(" Print Graph          = p      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			graph = initialize(graph);
			break;
		case 'q': case 'Q':
			freeGraph(graph);
			break;
		case 'v': case 'V':
			printf("Your Num = ");
			scanf("%d", &v);
			insertVertex(graph, v);
			break;
		case 'd': case 'D':
			printf("Your Num = ");
			scanf("%d", &v);
			initVist();
			DepthFS(graph, v);
			break;
		case 'p': case 'P':
			printGraph(graph);
			break;
		case 'e': case 'E':
			printf("Your Num = ");
			scanf("%d %d", &u, &v);
			insertEdge(graph, u, v);
			insertEdge(graph, v, u);
			break;
		case 'b': case 'B':
			printf("Your Num = ");
			scanf("%d", &v);
			BreathFS(graph, v);
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}
Graph* initialize(Graph *G)
{
	if(G != NULL) freeGraph(G);

	Graph *temp = (Graph*)malloc(sizeof(Graph)*MAX_VERTEX);

	for(int i = 0; i < MAX_VERTEX; i++){
		temp[i].Head = NULL;
		visitInfo[i] = 0;
	}

	initVist();

	return temp;
}

int freeGraph(Graph *G)
{
	Vertex *n, *trail;

	for(int i = 0; i < MAX_VERTEX; i++){
		n = G[i].Head;

		if(n != NULL) {
			while(n != NULL){
				trail = n;
				n = n->link;
				free(trail);				
			}
		}
	}
	free(G);
}

int insertVertex(Graph *G, int v)
{
	Vertex *new = (Vertex*)malloc(sizeof(Vertex));
	new->data = v;
	new->link = NULL;

	if (v > MAX_VERTEX){
		printf("[%d] is out of range!!\n");
		return 0;
	}

	else if(G[v].Head != NULL){
		printf("The Vertex of [%d] already exists!!\n", v);
		return 0;
	}

	else{
		G[v].Head = new;
		return 0;
	}
}

int insertEdge(Graph *G, int u, int v)
{
	Vertex *new = (Vertex*)malloc(sizeof(Vertex));
	new->data = v;
	new->link = NULL;

	Vertex *n, *trail;
	n = G[u].Head;
	trail = n;

	if(CheckV(G, u) != 1 || CheckV(G, v) != 1) {
		printf("There is an error!!");
		return 0;
	}

	if (n->link == NULL) {
		n->link = new;
		return 0;
	}
	n = n->link;
		/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {
		if(n->data > v) {
				/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == G[u].Head->link) {
				new->link = G[u].Head->link;
				G[u].Head->link = new;				
			} 
			else { /* 중간이거나 마지막인 경우 */
				new->link = trail->link;
				trail->link = new;
			}
			return 0;
		}
		else if(n->data == v) return 0;
		trail = n;
		n = n->link;
	}
		/* 마지막 노드까지 찾지 못한 경우 , 마지막에 삽입 */
	trail->link = new;
	return 0;
}

int DepthFS(Graph *G, int v)
{
	Vertex *w;

	printf("%d ", v);
	VisitVertex(v);

	for(w = G[v].Head->link; w; w = w->link)
		if(visitInfo[w->data] == 0)
			DepthFS(G, w->data);
	
	return 0;
}

int BreathFS(Graph *G, int v)
{
	int i;
	Vertex *m, *n;
	initVist();

	if(G == NULL) return 0;
	else if(CheckV(G, v) == 0) return 0;
	else{
		enQueue(G[v].Head);
		VisitVertex(v);
		printf("%d ", v);

		while(front != rear){
			m = deQueue();
			for(n = G[m->data].Head; n; n = n->link)
				if(visitInfo[n->data] == 0){
					VisitVertex(n->data);
					printf("%d ", n->data);
					enQueue(n);
				}
		}			
	}

}

int CheckV(Graph *G, int v)
{
	if(v > MAX_VERTEX) return 0;

	else if(G[v].Head == NULL) return 0;

	else return 1;
}

int VisitVertex(int visitV)
{
	if(visitInfo[visitV] == 0){
		visitInfo[visitV] = 1;
		return 0; // 방문한 적이 없으면 0 반환
	}
	return 1; // 방문했었으면 1 반환
}

void initVist()
{
	for(int i = 0; i<MAX_VERTEX; i++) visitInfo[i] = 0;	
	for(int j = 0; j<MAX_QUEUE_SIZE; j++) queue[j] = NULL;
	front = rear = -1;
}

void printGraph(Graph *G)
{
	Vertex *p, *n;

	printf("\n---PRINT\n");

	if(G == NULL){
		printf("Nothing to print....\n");
		return;
	}

	for(int i = 0; i < MAX_VERTEX; i++){
		p = G[i].Head;

		if(p != NULL){
			printf("Adjacent list of [%d]", i);
			n = p->link;

			while(n != NULL){				
				printf("-> %d", n->data);
				n = n->link;
			}
			printf("\n");
		}
	}
	return;
}

Vertex* deQueue()
{
	if (front == rear){
		return NULL; // 큐가 비어있으면 바로 종료
	}
	front = (front + 1) % MAX_QUEUE_SIZE; // front의 다음 인덱스 값을 저장
	return queue[front]; // 해당 인덱스의 큐 값 반환
}

void enQueue(Vertex* v)
{
	if (((rear+1)%MAX_QUEUE_SIZE) == front) { // rear의 다음 값이 front일 경우 즉, 큐가 포화상태일 경우
		printf(" There is an error!! (queue is full)"); // 오류 문자열 출력
		return;
	}
	rear = (rear + 1) % MAX_QUEUE_SIZE; // rear의 값을 한 칸 증가시킴
	queue[rear] = v; // 증가시킨 rear에 해당하는 큐에 저장
}