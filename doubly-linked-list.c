/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 *
 */

// 깃허브 commit 기능 확인


#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
        - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	printf("[----- [Chaerin Jung] [2020039022] -----]\n\n");
	
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
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
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->first->rlink = *h;
	(*h)->first->llink = *h;
	(*h)->first->key = -9999;

	return 1;
}

int freeList(headNode* h){

	listNode* p = h->first;
	listNode* prev = NULL;

	while(p != NULL) {
		prev = p;
		p = p->rlink;
		free(prev); // h와 연결된 리스트 해제
	}
	free(h); // 마지막으로 h도 해제

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	listNode* n;
	n = h->first;
	node->key = key;
	node->rlink = NULL; 

	if(n == NULL)
	{
		h->first = node; 
	}

	else
	{
		while(n->rlink != NULL) 
			n = n->rlink;
		
		n->rlink = node; 
		node->llink = n;
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
		if(h->first->rlink == NULL){ // 리스트에 노드가 하나 남아있다면
			h->first = NULL; // first가 가리키고 있는 값 NULL로 변경
			free(n); // n 해제
			return 0;
		}

		while(n->rlink != NULL){ // 리스트의 마지막 노드까지
			trail = n; // 이전 노드를 가리키는 trail의 값을 n으로 변경
			n = n->rlink; // n이 다음 노드를 가리키도록 변경
		}
		// 리스트의 마지막 노드라면
		trail->rlink = NULL; // 이전 노드의 link를 NULL로 변경
		free(n); // 마지막 노드인 n 해제
	}

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->rlink = h->first;
	h->first = node;

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
		h->first = n->rlink; // 첫 번째 노드를 삭제하기 때문에 first가 가리키는 값을 n의 다음 노드 값으로 변경한 후
		free(n); // n의 메모리 해제
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
		next = n->rlink; // next가 현재 노드의 다음 노드를 가리키도록 변경
		n->rlink = trail; // 현재 노드의 link는 이전 노드를 가리키도록 변경
		trail = n; // 이전 노드는 현재 노드를 가리키도록 변경
		n = next; // 현재 노드 n은 다음 노드를 가리키도록 변경
	}
	h->first = trail; // 마지막으로 first가 가리키는 값을 trail로 변경


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
		node->rlink = NULL; // node의 link는 NULL값으로 변경
	}
	
	else{
		
		if(h->first->key >= node->key){// 만약 입력받은 키 값이 n이 가리키고 있는 키 값보다 작으면 바로 추가
			node->rlink = n; // 새로 추가할 node의 link를 n을 가리키도록 수정
			n->llink = node;
			h->first = node; // first가 가리키는 노드를 node로 변경
		}

		else{
			
			while(n->key < node->key){ // 입력받은 키 값이 n이 가리키고 있는 키 값보다 클 때까지
				
				if (n->rlink == NULL && n->key <= node->key){ // 즉 새로 추가할 node의 키 값이 현재 리스트의 모든 키 값보다 클 경우
					node->rlink = n->rlink; // node의 link를 n의 링크 즉 NULL로 변경
					n->rlink = node; // n의 link를 node를 가리키도록 변경
					node->llink = n;

					return 0;
				}
				trail = n; // 비교할 노드 바로 전의 노드를 가리킬 포인터 trail의 값을 n으로 하나 증가
				n = n->rlink; // n은 뒤의 노드를 가리키도록 변경
			}
			// 리스트를 하나씩 비교하다 입력 받은 키 값보다 n이 가리키는 키 값이 더 클 경우

			trail->rlink = node; // 이전 노드의 링크가 node를 가리키도록 변경
			node->rlink = n;// node의 link가 n을 가리키도록 변경
			n->llink = node;
			node->llink = trail;
		}
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
			h->first = n->rlink; // first가 가리키는 노드를 n의 다음 노드로 변경 후
			free(n); // n 해제
		}

		else
		{
			while(n->key != key){ // n의 키 값이 삭제할 키값과 같지 않을 때까지
				trail = n; // 이전 노드를 가리키는 trail 값을 n으로 변경
				n = n->rlink; // n은 n의 다음 노드를 가리키도록 변경
			}
			// n의 키 값이 삭제할 키 값과 같다면

			trail->rlink = n->rlink; // 이전 노드의 link 값을 n의 다음 노드를 가리키도록 변경
			n->rlink->llink = trail;
			free(n); //n 해제
		}
	}


	return 1;
}


