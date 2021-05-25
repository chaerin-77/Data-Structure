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

typedef struct Vertex{ // 간선의 정보와 정점의 정보를 저장하기 위한 구조체
	int data;
	struct Vertex *link;
} Vertex;

typedef struct Graph { //그래프를 구성하기 위한 구조체
	Vertex *Head;
} Graph;

/* for queue */
#define MAX_QUEUE_SIZE 20 // 큐의 최대 크기를 20으로 저장
Vertex* queue[MAX_QUEUE_SIZE]; 
int front = -1;
int rear = -1;

Vertex* deQueue(); // 큐에서 삭제하는 함수
void enQueue(Vertex* v); // 큐에 추가하는 함수

int visitInfo[MAX_VERTEX]; // 방문 정보를 확인하는 배열
int VisitVertex(int visitV); // 방문 정보를 저장해주는 함수

Graph* initialize(Graph *G); // 처음 그래프를 초기화 해주는 함수
int freeGraph(Graph *G); // 사용한 그래프를 해제하는 함수
int insertVertex(Graph *G, int v); // 정점을 삽입하는 함수
int insertEdge(Graph *G, int u, int v); // 간선을 삽입하는 함수
int DepthFS(Graph *G, int v); // DFS 실행하는 함수
int BreathFS(Graph *G, int v); // BFS 실행하는 함수
void printGraph(Graph *G); // 그래프를 출력하는 함수
int CheckV(Graph *G, int v); // 해당 정점이 생성되었는지 확인하는 함수
void initVist(); // 방문 정보들을 초기화하는 함수

int main()
{
	printf("[----- [Chaerin Jung] [2020039022] -----]");

	char command;
	int u, v;
	Graph* graph = NULL; // 그래프를 할당할 포인터 선언

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
			graph = initialize(graph); // 그래프 초기화
			break;
		case 'q': case 'Q':
			freeGraph(graph); // 종료 시 사용한 그래프 해제
			break;
		case 'v': case 'V':
			printf("Your Num = ");
			scanf("%d", &v);
			insertVertex(graph, v); // 생성할 정점을 입력받아 저장
			break;
		case 'd': case 'D':
			printf("Your Num = ");
			scanf("%d", &v);
			initVist(); // 시작하기 전 방문기록 초기화
			DepthFS(graph, v); // 입력받은 정점에 대한 DFS 실행
			break;
		case 'p': case 'P':
			printGraph(graph); // 그래프 출력
			break;
		case 'e': case 'E':
			printf("Your Num = ");
			scanf("%d %d", &u, &v);
			insertEdge(graph, u, v); // 두 정점을 입력받아 간선 삽입
			insertEdge(graph, v, u); // 무방향 그래프이기 때문에 양쪽에 삽입되어야 해서 반대로 두번 실행
			break;
		case 'b': case 'B':
			printf("Your Num = ");
			scanf("%d", &v);
			BreathFS(graph, v); // 입력받은 정점에 대한 BFS 실행
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
	if(G != NULL) freeGraph(G); // 그래프가 비어있지 않다면 해제함

	Graph *temp = (Graph*)malloc(sizeof(Graph)*MAX_VERTEX); // 임시 포인터에 graph 구조체 배열을 할당함

	for(int i = 0; i < MAX_VERTEX; i++){
		temp[i].Head = NULL; // 각 배열의 head 포인터를 NULL로 초기화
	}

	initVist(); // 방문 기록들을 초기화

	return temp; // 할당된 그래프를 반환
}

int freeGraph(Graph *G)
{
	Vertex *n, *trail; // 그래프를 해제하기 위한 포인터 선언

	for(int i = 0; i < MAX_VERTEX; i++){
		n = G[i].Head; // n을 G[i]의 head 포인터로 초기화

		if(n != NULL) { // n이 NULL이 아니라면
			while(n != NULL){ // n이 NULL이 될 때까지
				trail = n; // 이전 포인터를 n으로 변경하고
				n = n->link; // n은 n의 다음 포인터를 가리키도록 함
				free(trail); // 이전 포인터가 가리키는 노드 해제	
			}
		}
	}
	free(G); // for문 종료 후 그래프 배열 해제
}

int insertVertex(Graph *G, int v)
{
	Vertex *new = (Vertex*)malloc(sizeof(Vertex)); // 입력된 정점을 삽입하기 위한 노드 생성
	new->data = v;
	new->link = NULL;

	if (v > MAX_VERTEX){
		printf("[%d] is out of range!!\n"); // 입력된 정점이 범위보다 클 경우 오류 문자열 출력
		return 0;
	}

	else if(G[v].Head != NULL){
		printf("The Vertex of [%d] already exists!!\n", v); // 해당 정점이 삽입 될 배열의 위치가 NULL이 아닐 경우 오류 문자열 출력
		return 0;
	}

	else{
		G[v].Head = new; // 이 외의 경우에는 해당 인덱스의 배열의 head에 해당 번호 노드 추가
		return 0;
	}
}

int insertEdge(Graph *G, int u, int v)
{
	Vertex *new = (Vertex*)malloc(sizeof(Vertex)); // 새로운 간선을 추가하기 위한 노드 생성
	new->data = v;
	new->link = NULL;

	Vertex *n, *trail; // 현재 노드와 이전 노드를 가리킬 포인터 생성
	n = G[u].Head; // n이 u번째 배열의 head를 가리키도록 함
	trail = n;

	if(CheckV(G, u) != 1 || CheckV(G, v) != 1) { // 해당 정점이 생성되었는지 확인
		printf("There is an error!!"); // 생성되지 않았으면 오류 문자열 출력
		return 0;
	}

	if (n->link == NULL) { // head의 다음 노드가 NULL이면 정점만 생성되고 간선이 없는 것이기 때문에
		n->link = new; // 새로운 노드 추가
		return 0;
	}
	n = n->link; // if문을 빠져나왔다면 NULL이 아니므로 n을 head의 다음 노드로 변경

	while(n != NULL) { // n이 NULL이 되기 전까지
		if(n->data > v) {
				
			if(n == G[u].Head->link) {// 첫 노드에 삽입해야할 경우
				new->link = G[u].Head->link; // 새로 추가할 노드의 link를 head의 link로 변경
				G[u].Head->link = new; // head의 link가 새로운 노드를 가리키도록 함
			} 
			else { // 중간이거나 마지막인 경우 
				new->link = trail->link; // 새로운 노드의 link를 이전 노드의 link로 변경
				trail->link = new; // 이전 노드의 link가 새로운 노드를 가리키도록 변경
			}
			return 0;
		}
		else if(n->data == v) return 0; // 만약 해당되는 노드가 이미 있다면 그냥 종료
		trail = n;
		n = n->link;
	}		
	trail->link = new;// 마지막 노드까지 찾지 못한 경우 , 마지막에 삽입
	return 0;
}

int DepthFS(Graph *G, int v)
{
	// DFS 함수는 재귀적으로 사용할 것이기 때문에 함수 사용 전 방문기록을 초기화했음
	Vertex *w;

	if(G == NULL) return 0; // 해당 그래프가 없을 경우 종료
	else if(CheckV(G, v) == 0) return 0; // 정점의 생성 확인 후 생성되지 않았으면 종료

	VisitVertex(v); // 해당 정점을 방문했다는 표시
	printf("%d ", v); // 입력받은 정점 출력

	for(w = G[v].Head->link; w; w = w->link)
		if(visitInfo[w->data] == 0) // 해당 인덱스에 방문한 적이 없을 경우
			DepthFS(G, w->data); // 재귀적으로 DFS 함수 호출
	
	return 0;
}

int BreathFS(Graph *G, int v)
{
	Vertex *m, *n;
	initVist(); // 함수 호출 전 방문기록들 초기화

	if(G == NULL) return 0; // 해당 그래프가 없을 경우 종료
	else if(CheckV(G, v) == 0) return 0; // 정점의 생성 확인 후 생성되지 않았으면 종료
	
	enQueue(G[v].Head); // 큐에 G의 v번째 head를 추가
	VisitVertex(v); // 해당 정점을 방문했다는 표시
	printf("%d ", v); // 입력받은 정점 출력

	while(front != rear){ // 큐가 빌 때까지
		m = deQueue(); // 큐에서 하나를 꺼내옴
		for(n = G[m->data].Head; n; n = n->link)
			if(visitInfo[n->data] == 0){ //해당 인덱스에 방문한 적이 없다면
				VisitVertex(n->data); // 방문했다는 표시를 한 후
				printf("%d ", n->data); // 해당 인덱스 번호 출력
				enQueue(n); // 큐에 추가
			}
	}

}

int CheckV(Graph *G, int v)
{
	if(v > MAX_VERTEX) return 0; // v가 10이 넘어갈 경우 0반환

	else if(G[v].Head == NULL) return 0; // 해당 정점이 생성되지 않았으면 0반환

	else return 1; // 정상적으로 생성되어있는 경우 1반환
}

int VisitVertex(int visitV)
{
	if(visitInfo[visitV] == 0){ // 방문한 적이 없으면
		visitInfo[visitV] = 1; // 해당 번호의 배열에 1로 변경
		return 0; // 방문한 적이 없으면 0 반환
	}
	return 1; // 방문했었으면 1 반환
}

void initVist()
{
	for(int i = 0; i<MAX_VERTEX; i++) visitInfo[i] = 0;	// 방문 기록을 저장하는 배열 초기화
	for(int j = 0; j<MAX_QUEUE_SIZE; j++) queue[j] = NULL; // 사용한 큐 초기화
	front = rear = -1; // 큐의 front와 rear도 초기화
}

void printGraph(Graph *G)
{
	Vertex *p, *n;

	printf("\n---PRINT\n");

	if(G == NULL){ // 그래프가 비어있다면
		printf("Nothing to print....\n"); // 오류 문자열 출력
		return;
	}

	for(int i = 0; i < MAX_VERTEX; i++){ // i가 10보다 작을 때까지
		p = G[i].Head; // p를 G의 i번째 head로 변경

		if(p != NULL){ // p가 NULL이 아닐 때까지
			printf("Adjacent list of [%d]", i);
			n = p->link; // 출력 후 p의 link로 변경

			while(n != NULL){ // n이 NULL이 아닐 때까지		
				printf("-> %d", n->data);
				n = n->link; // 출력 후 n을 n의 다음 노드로 변경
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