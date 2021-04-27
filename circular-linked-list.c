/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	printf("[----- [Chaerin Jung] [2020039022] -----]\n\n");
	
	char command;
	int key;
	listNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
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


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){

	listNode* p = h;
	listNode* prev = NULL;

	while(p != NULL) {
		prev = p; // 이전 노드를 p로 변경
		p = p->rlink; // p는 다음 노드를 가리키도록 변경
		free(prev); // 노드를 하나씩 해제
	}
	free(h); // 마지막으로 h도 해제

	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	listNode* n;
	n = h;
	node->key = key;
	node->rlink = h;

	if(h == NULL)
	{
		h = node; // 만약 리스트가 비어있을 때 처음 추가하게 되는 것이라면 바로 추가
		node->llink = node;
	}

	else
	{
		while(n->rlink != h) 
			n = n->rlink; // n의 rlink가 NULL 일 때까지, 즉 마지막 순서까지 n을 증가시킴
		
		n->rlink = node; // n의 rlink가 새로 추가할 node를 가리키게 함
		node->llink = n; // 새로 추가한 node의 llink가 n을 가리키게 함
		h->llink = node;
	}

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {

	listNode* n, *trail;
	n = h;
	trail = NULL;

	if(n == NULL)
		printf("Linked list is Empty!!\n\n"); // 리스트가 비어있으면 비어있다는 오류 문자열 출력
	
	else
	{
		if(h->rlink == h){ // 리스트에 노드가 하나 남아있다면
			h = NULL; // first가 가리키고 있는 값 NULL로 변경
			free(n); // n 해제

			return 0;
		}

		while(n->rlink != h){ // 리스트의 마지막 노드까지
			trail = n; // 이전 노드를 가리키는 trail의 값을 n으로 변경
			n = n->rlink; // n이 다음 노드를 가리키도록 변경
		}
		// 리스트의 마지막 노드라면
		trail->rlink = n->rlink;
		h->llink = trail;
		free(n); // 마지막 노드인 n 해제
	}

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	if(h == NULL)
	{
		h = node;
		node->rlink = h;
		node->llink = h;
	}

	else
	{	
		node->llink = h->llink;
		node->rlink = h;
		h->llink = node; // first가 가리키는 node의 llink가 새로 추가할 노드를 가리키도록 함
		h = node; // first가 새로 추가할 노드를 가리키도록 변경
	}

	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {

	listNode* n;
	n = h;

	if(n == NULL)
		printf("Linked list is Empty!!\n\n"); // 리스트가 비어있으면 비어있다는 오류 문자열 출력
	
	else
	{
		if(h->rlink == h){ // 리스트에 노드가 하나 남아있다면
			h = NULL; // first가 가리키고 있는 값 NULL로 변경
			free(n); // n 해제

			return 0;
		}

		h = n->rlink; // first가 가리키는 값을 n의 다음 노드 값으로 변경한 후
		h->llink = n->llink;
		free(n); // n의 메모리 해제
	}

	return 1;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {
	
	listNode* next, *trail, *n; // 다음 노드, 이전 노드, 현재 노드를 가리킬 포인터 선언
	next = trail = NULL;
	n = h;

	while(next != h){
		next = n->rlink; // next가 현재 노드의 다음 노드를 가리키도록 변경
		n->rlink = trail; // 현재 노드의 rlink는 이전 노드를 가리키도록 변경
		n->llink = next; // n의 llink는 다음 노드를 가리키도록 변경
		trail = n; // 이전 노드는 현재 노드를 가리키도록 변경
		n = next; // 현재 노드 n은 다음 노드를 가리키도록 변경
	}
	h->rlink = trail;
	h = trail; // 마지막으로 first가 마지막 노드를 가리키도록 함

	return 0;
}



/**
 *  리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 
 **/
int insertNode(listNode* h, int key) {

	listNode* n;
	listNode* trail = NULL;
	listNode* node = (listNode*)malloc(sizeof(listNode)); // 새로 추가할 노드
	n = h; // 처음 n의 값은 first가 가리키고 있는 노드
	node->key = key; // 새로 생성한 노드의 데이터 값에 입력받은 데이터값 대입

	if(n == NULL){
		h = node; // 만약 리스트가 비어있었다면 first가 가리키고 있는 노드를 node로 변경
		node->rlink = h; // node의 rlink는 NULL값으로 변경
		node->llink = h;
	}
	
	else{
		
		if(h->key >= node->key){// 만약 입력받은 키 값이 n이 가리키고 있는 키 값보다 작으면 바로 추가
			node->rlink = n; // 새로 추가할 node의 rlink가 n을 가리키도록 수정
			node->llink = h->llink;
			n->llink = node; // 원래 있던 node인 n의 llink가 새로 추가할 노드를 가리키도록 변경
			h = node; // first가 가리키는 노드를 node로 변경
		}

		else{
			
			while(n->key < node->key){ // 입력받은 키 값이 n이 가리키고 있는 키 값보다 클 때까지
				
				if (n->rlink == h && n->key <= node->key){ // 즉 새로 추가할 node의 키 값이 현재 리스트의 모든 키 값보다 클 경우
					node->rlink = n->rlink; // node의 rlink를 n의 링크 즉 NULL로 변경
					n->rlink = node; // n의 rlink를 node를 가리키도록 변경
					node->llink = n; // node의 llink가 n을 가리키도록 변경
					h->llink = node;

					return 0;
				}
				trail = n; // 비교할 노드 바로 전의 노드를 가리킬 포인터 trail의 값을 n으로 하나 증가
				n = n->rlink; // n은 뒤의 노드를 가리키도록 변경
			}
			// 리스트를 하나씩 비교하다 입력 받은 키 값보다 n이 가리키는 키 값이 더 클 경우

			trail->rlink = node; // 이전 노드의 rlink가 node를 가리키도록 변경
			node->rlink = n;// 새로 추가할 node의 rlink가 n을 가리키도록 변경
			n->llink = node; // n의 llink는 새로 추가할 노드를 가리키도록 변경
			node->llink = trail; // node의 llink는 이전 노드를 가리키도록 변경
		}
	}

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

	listNode* n;
	listNode* trail = NULL;
	n = h;

	if(n == NULL)
		printf("Linked list is Empty!!\n\n"); // 리스트가 비어있으면 비어있다는 오류 문자열 출력
	
	else
	{
		if(h->key == key) // 만약 첫번째 노드의 키 값이 삭제할 노드의 키 값과 같다면
		{
			if(h->rlink == h){ // 리스트에 노드가 하나 남아있다면
				h = NULL; // first가 가리키고 있는 값 NULL로 변경
				free(n); // n 해제
			}

			else
			{
				h = n->rlink; // first가 가리키는 노드를 n의 다음 노드로 변경 후
				free(n); // n 해제
			}
		}

		else
		{
			while(n->key != key) // n의 키 값이 삭제할 키값과 같지 않을 때까지
			{ 
				trail = n; // 이전 노드를 가리키는 trail 값을 n으로 변경
				n = n->rlink; // n은 n의 다음 노드를 가리키도록 변경

				if(trail->rlink == h) // n이 마지막 값인 NULL 까지 증가하였는데 해당되는 값이 없을 경우
				{
					printf("There is no such node!!\n\n"); // 해당되는 노드가 없다는 문자열 출력
					return 0;
				}

			}
			// n의 키 값이 삭제할 키 값과 같다면
			trail->rlink = n->rlink; // 이전 노드의 rlink 값을 n의 다음 노드를 가리키도록 변경
			n->rlink->llink = trail; // n의 다음 노드의 llink가 이전 노드를 가리키도록 변경 후
			free(n); //n 해제
		}
	}

	return 0;
}


