/*
 * singly linked list
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key; // node의 data
	struct Node* link; // 다음 node를 가리키는 포인터
} listNode;

typedef struct Head {
	struct Node* first; // head 포인터인 first
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h); // first 포인터를 사용하여 리스트 초기화
int freeList(headNode* h); // 사용이 끝난 리스트 해제

int insertFirst(headNode* h, int key); // 데이터의 크기와 상관없이 리스트의 맨 앞에 노드 추가
int insertNode(headNode* h, int key); // 데이터의 크기를 비교하여 오름차순으로 노드 추가
int insertLast(headNode* h, int key); // 데이터의 크기와 상관없이 리스트의 맨 뒤에 노드 추가

int deleteFirst(headNode* h); // 맨 앞 노드 삭제
int deleteNode(headNode* h, int key); // 검색한 데이터와 같은 값을 가지고 있는 노드 삭제
int deleteLast(headNode* h); // 맨 뒤 노드 삭제
int invertList(headNode* h); // 리스트를 역순으로 정렬

void printList(headNode* h); // 리스트를 출력

int main()
{
	printf("[----- [Chaerin Jung] [2020039022] -----]\n\n");
	
	char command; // 선택한 메뉴를 받을 변수 선언
	int key; // 입력할 데이터를 받을 변수 선언
	headNode* headnode=NULL; // 맨 앞 노드를 null로 초기화

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode); // headnode를 사용하여 리스트 초기화
			break;
		case 'p': case 'P':
			printList(headnode); // 리스트 출력
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key); // 리스트에 추가할 데이터값을 입력받음
			insertNode(headnode, key); // 리스트에 오름차순으로 추가
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key); // 해당되는 데이터를 가진 노드를 삭제하기 위한 값을 입력받음
			deleteNode(headnode, key); // 리스트에 검색하여 해당되는 노드 삭제
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key); // 리스트에 추가할 데이터값을 입력받음
			insertLast(headnode, key); // 리스트의 마지막에 노드 추가
			break;
		case 'e': case 'E':
			deleteLast(headnode); // 리스트의 마지막 노드 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key); // 리스트에 추가할 데이터값을 입력받음
			insertFirst(headnode, key); // 리스트의 처음에 노드 추가
			break;
		case 't': case 'T':
			deleteFirst(headnode); // 리스트의 처음 노드 삭제
			break;
		case 'r': case 'R':
			invertList(headnode); // 리스트를 역순으로 정렬
			break;
		case 'q': case 'Q':
			freeList(headnode); // 종료 시 사용한 리스트 해제
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev); // h와 연결된 리스트 해제
	}
	free(h); // 마지막으로 h도 해제
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 입력된 데이터값을 가지는 노드를 만들기 위해 동적할당으로 노드 생성
	node->key = key; // 생성된 노드의 데이터 값에 입력받은 데이터 입력

	node->link = h->first; // 새로 추가된 노드의 link에 first가 가리키고 있는 노드의 주소값 대입
	h->first = node; // first가 가리키고 있는 노드를 새로 추가된 노드로 변경

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* n;
	listNode* trail = NULL;
	listNode* node = (listNode*)malloc(sizeof(listNode)); // 새로 추가할 노드
	n = h->first; // 처음 n의 값은 first가 가리키고 있는 노드
	node->key = key; // 새로 생성한 노드의 데이터 값에 입력받은 데이터값 대입

	if(n == NULL){
		h->first = node; // 만약 리스트가 비어있었다면 first가 가리키고 있는 노드를 node로 변경
		node->link = NULL; // node의 link는 NULL값으로 변경
	}
	
	else{
		
		if(h->first->key >= node->key){// 만약 입력받은 키 값이 n이 가리키고 있는 키 값보다 작으면 바로 추가
			node->link = n; // 새로 추가할 node의 link를 n을 가리키도록 수정
			h->first = node; // first가 가리키는 노드를 node로 변경
		}

		else{
			
			while(n->key < node->key){ // 입력받은 키 값이 n이 가리키고 있는 키 값보다 클 때까지
				if (n->link == NULL && n->key <= node->key){ // 즉 새로 추가할 node의 키 값이 현재 리스트의 모든 키 값보다 클 경우
					node->link = n->link; // node의 link를 n의 링크 즉 NULL로 변경
					n->link = node; // n의 link를 node를 가리키도록 변경
					return 0;
				}
				trail = n; // 비교할 노드 바로 전의 노드를 가리킬 포인터 trail의 값을 n으로 하나 증가
				n = n->link; // n은 뒤의 노드를 가리키도록 변경
			}
			// 리스트를 하나씩 비교하다 입력 받은 키 값보다 n이 가리키는 키 값이 더 클 경우

			trail->link = node; // 이전 노드의 링크가 node를 가리키도록 변경
			node->link = n;// node의 link가 n을 가리키도록 변경
		}
	}

	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	listNode* n;
	n = h->first;
	node->key = key;
	node->link = NULL; // 마지막에 추가할 노드이기 때문에 node의 링크는 항상 NULL 이다.

	if(n == NULL)
	{
		h->first = node; // 리스트가 비어있다면 바로 추가
	}

	else
	{
		while(n->link != NULL) // 즉, 현재 비교하고 있는 노드가 리스트의 끝이 아닐때까지 
			n = n->link; // n을 다음 노드로 변경
		
		n->link = node; // 현재 비교하는 노드가 끝이되었으면 뒤에 node 추가
	}

	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	
	listNode* n;
	n = h->first;

	if(n == NULL)
		printf("Linked list is Empty!!\n\n"); // 리스트가 비어있으면 비어있다는 오류 문자열 출력
	
	else{
		h->first = n->link; // 첫 번째 노드를 삭제하기 때문에 first가 가리키는 값을 n의 다음 노드 값으로 변경한 후
		free(n); // n의 메모리 해제
	}

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	
	listNode* n;
	listNode* trail = NULL;
	n = h->first;

	if(n == NULL)
		printf("Linked list is Empty!!\n\n"); // 리스트가 비어있으면 비어있다는 오류 문자열 출력
	
	else{
		if(n->key == key){ // 만약 첫번째 노드의 키 값이 삭제할 노드의 키 값과 같다면
			h->first = n->link; // first가 가리키는 노드를 n의 다음 노드로 변경 후
			free(n); // n 해제
		}

		else
		{
			while(n->key != key){ // n의 키 값이 삭제할 키값과 같지 않을 때까지
				trail = n; // 이전 노드를 가리키는 trail 값을 n으로 변경
				n = n->link; // n은 n의 다음 노드를 가리키도록 변경
			}
			// n의 키 값이 삭제할 키 값과 같다면

			trail->link = n->link; // 이전 노드의 link 값을 n의 다음 노드를 가리키도록 변경
			free(n); //n 해제
		}
	}

	return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	listNode* n, *trail;
	n = h->first;
	trail = NULL;

	if(n == NULL)
		printf("Linked list is Empty!!\n\n"); // 리스트가 비어있으면 비어있다는 오류 문자열 출력
	
	else{
		if(h->first->link == NULL){ // 리스트에 노드가 하나 남아있다면
			h->first = NULL; // first가 가리키고 있는 값 NULL로 변경
			free(n); // n 해제
			return 0;
		}

		while(n->link != NULL){ // 리스트의 마지막 노드까지
			trail = n; // 이전 노드를 가리키는 trail의 값을 n으로 변경
			n = n->link; // n이 다음 노드를 가리키도록 변경
		}
		// 리스트의 마지막 노드라면

		trail->link = NULL; // 이전 노드의 link를 NULL로 변경
		free(n); // 마지막 노드인 n 해제
	}

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	listNode* next, *trail, *n; // 다음 노드, 이전 노드, 현재 노드를 가리킬 포인터 선언
	next = trail = NULL;
	n = h->first;

	while(n){
		next = n->link; // next가 현재 노드의 다음 노드를 가리키도록 변경
		n->link = trail; // 현재 노드의 link는 이전 노드를 가리키도록 변경
		trail = n; // 이전 노드는 현재 노드를 가리키도록 변경
		n = next; // 현재 노드 n은 다음 노드를 가리키도록 변경
	}
	h->first = trail; // 마지막으로 first가 가리키는 값을 trail로 변경

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {// 헤드 포인터가 NULL이라면
		printf("Nothing to print....\n"); 
		return;
	}

	p = h->first;

	while(p != NULL) { // p가 가리키는 값이 NULL이 아닐 때 까지
		printf("[ [%d]=%d ] ", i, p->key); // 노드의 데이터 출력
		p = p->link; // p가 p의 다음 노드를 가리키도록 변경
		i++; // 데이터의 번호 하나 증가
	}

	printf("  items = %d\n", i); // 총 데이터의 갯수 출력
}
