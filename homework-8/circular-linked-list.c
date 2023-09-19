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
			initialize(&headnode); // 새로운 headnode 할당
			break;
		case 'p': case 'P':
			printList(headnode); // 각 노드의 주소를 포함한 key값 출력
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key); // key값을 오름차순으로 저장
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key); // key값을 입력받아 해당되는 노드 삭제
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key); // 리스트의 마지막에 노드 추가
			break;
		case 'e': case 'E':
			deleteLast(headnode); // 리스트의 마지막 노드 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key); // 리스트의 맨 앞에 노드 추가
			break;
		case 't': case 'T':
			deleteFirst(headnode); // 리스트의 첫 노드 삭제
			break;
		case 'r': case 'R':
			invertList(headnode); // 리스트를 역순으로 배열
			break;
		case 'q': case 'Q':
			freeList(headnode); // 종료 시 할당한 리스트 해제
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
	(*h)->rlink = *h; // headnode의 rlink가 자기 자신을 가리키도록 함
	(*h)->llink = *h; // headnode의 llink가 자기 자신을 가리키도록 함
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){

	listNode* p = h->rlink; // p가 headnode의 뒷 노드를 가리키도록 함
	listNode* prev = NULL;

	while(p != h) {
		prev = p; // 이전 노드를 p로 변경
		p = p->rlink; // p는 다음 노드를 가리키도록 변경
		free(prev); // 노드를 하나씩 해제
	}
	free(h); // 마지막으로 headnode 해제

	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n"); // print할 리스트가 없으면 오류 문자열 출력
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink; // p를 증가시키며 하나씩 출력
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink); // headnode의 주소와 rlink, llink 값 출력

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink); // 리스트의 주소와 rllink, llink 값 출력
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
	node->rlink = h; // 마지막에 노드를 추가하는 함수이기 때문에 rlink는 항상 headnode를 가리킴

	if(h->rlink == h) // 만약 리스트에 headnode만 존재하는 경우, 즉 리스트가 비어있을 경우
	{
		h->llink = node;
		h->rlink = node; // headnode의 rlink와 llink 모두 node를 가리키도록 함
		node->llink = h; // node의 llink는 헤드 노드를 가리키도록 함
	}

	else
	{
		while(n->rlink != h) 
			n = n->rlink; // n의 rlink가 headnode를 가리킬 때까지, 즉 마지막 순서까지 n을 증가시킴
		
		n->rlink = node; // n의 rlink가 새로 추가할 node를 가리키게 함
		node->llink = n; // 새로 추가한 node의 llink가 n을 가리키게 함
		h->llink = node; // headnode의 llink가 새로 추가한 node를 가리키게 함
	}

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {

	listNode* n, *trail;
	n = h->rlink; // n은 headnode의 뒷 노드를 가리키도록 함
	trail = NULL;

	if(h->rlink == h)
		printf("Linked list is Empty!!\n\n"); // 리스트에 headnode만 있다면 비어있다는 오류 문자열 출력
	
	else
	{
		if(n->rlink == h) // 리스트에 노드가 하나 남아있다면
		{
			h->rlink = h;
			h->llink = h; // headnode의 rlink와 llink가 자기 자신을 가리키도록 함
			free(n); // n 해제

			return 0;
		}

		while(n->rlink != h){ // 리스트의 마지막 노드까지
			trail = n; // 이전 노드를 가리키는 trail의 값을 n으로 변경
			n = n->rlink; // n이 다음 노드를 가리키도록 변경
		}
		// 리스트의 마지막 노드라면
		trail->rlink = n->rlink; // 이전 노드의 rlink를 n의 다음링크 즉 headnode를 가리키도록 함
		h->llink = trail; // headnode의 llink가 새로운 마지막 노드를 가리키도록 함
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

	if(h->rlink == h) // 리스트가 비어있을 경우
	{
		h->llink = node;
		h->rlink = node; // headnode의 모든 link가 새로 추가할 노드를 가리키도록 함
		node->rlink = h;
		node->llink = h; // node의 모든 link가 headnode를 가리키도록 함
	}

	else
	{	
		node->llink = h; // 처음에 추가하는 것이기 때문에 새로 추가할 node의 llink는 headnode를 가리키도록 함
		node->rlink = h->rlink; // node의 rlink는 headnode의 뒷 노드를 가리키도록 함
		h->rlink->llink = node; // headnode의 다음 노드의 llink가 새로 추가할 node를 가리키도록 함
		h->rlink = node; // headnode의 llink가 새로 추가할 노드를 가리키도록 변경
	}

	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {

	listNode* n;
	n = h->rlink; // n은 headnode의 다음 노드를 가리키도록 함

	if(h->rlink == h)
		printf("Linked list is Empty!!\n\n"); // 리스트에 headnode만 있다면 비어있다는 오류 문자열 출력
	
	else
	{
		if(n->rlink == h){ // 리스트에 노드가 하나 남아있다면
			h->rlink = h; 
			h->llink = h; // headnode의 모든 link가 자기 자신을 가리키도록 함
			free(n); // n 해제

			return 0;
		}

		h->rlink = n->rlink; // headnode의 rlink가 가리키는 값을 n의 다음 노드 값으로 변경한 후
		n->rlink->llink = h; // n의 다음노드의 llink가 headnode를 가리키도록 함
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
	h->rlink = trail; // headnode의 rlink가 마지막 노드를 가리키도록 함

	return 0;
}



/**
 *  리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 
 **/
int insertNode(listNode* h, int key) {

	listNode* n;
	listNode* trail = NULL;
	listNode* node = (listNode*)malloc(sizeof(listNode)); // 새로 추가할 노드
	n = h; // 처음 n의 값은 headnode가 가리키고 있는 노드
	node->key = key; // 새로 생성한 노드의 데이터 값에 입력받은 데이터값 대입

	if(h->rlink == h) // 리스트가 비어있다면
	{
		h->llink = node;
		h->rlink = node; // headnode의 모든 link가 새로 추가할 node를 가리키도록 함
		node->rlink = h;
		node->llink = h; // 새로 추가할 node의 모든 링크가 headnode를 가리키도록 함
	}
	
	else{
		
		if(h->key >= node->key){// 만약 입력받은 키 값이 n이 가리키고 있는 키 값보다 작으면 바로 추가
			node->rlink = n; // 새로 추가할 node의 rlink가 n을 가리키도록 수정
			node->llink = h; // 새로 추가할 node의 llink가 headnode를 가리키도록 함
			n->llink = node; // 원래 있던 노드인 n의 llink가 새로 추가할 노드를 가리키도록 변경
			h->rlink = node; // headnode가 가리키는 노드를 node로 변경
		}

		else{
			
			while(n->key < node->key){ // 입력받은 키 값이 n이 가리키고 있는 키 값보다 클 때까지
				
				if (n->rlink == h && n->key <= node->key){ // 즉 새로 추가할 node의 키 값이 현재 리스트의 모든 키 값보다 클 경우
					node->rlink = n->rlink; // node의 rlink를 n의 rlink로 변경
					n->rlink = node; // n의 rlink가 새로 추가할 node를 가리키도록 변경
					node->llink = n; // node의 llink가 n을 가리키도록 변경
					h->llink = node; // headnode의 llink가 마지막에 추가 된 node를 가리키도록 변경

					return 0;
				}
				trail = n; // trail의 값을 n으로 하나 증가
				n = n->rlink; // n은 뒤의 노드를 가리키도록 변경
			}
			// 리스트를 하나씩 비교하다 입력 받은 키 값보다 n이 가리키는 키 값이 더 클 경우

			trail->rlink = node; // 이전 노드의 rlink가 새로 추가할 node를 가리키도록 변경
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
	n = h->rlink; // n은 headnode 다음 노드를 가리키도록 함

	if(h->rlink == h)
		printf("Linked list is Empty!!\n\n"); // 리스트에 headnode만 있다면 비어있다는 오류 문자열 출력
	
	else
	{
		if(n->key == key) // 만약 첫번째 노드의 키 값이 삭제할 노드의 키 값과 같다면
		{
			if(n->rlink == h){ // 리스트에 노드가 하나 남아있다면
				h->rlink = h; 
				h->llink = h;// headnode의 모든 link가 자기자신을 가리키도록 변경
				free(n); // n 해제

			return 0;
		}

			else
			{
				h->rlink = n->rlink; // headnode의 rlink를 n의 다음 노드로 변경 후
				n->rlink->llink = h; // n의 다음 노드의 llink가 headnode를 가리키도록 변경
				free(n); // n 해제
			}
		}

		else
		{
			while(n->key != key) // n의 키 값이 삭제할 키값과 같지 않을 때까지
			{ 
				trail = n; // 이전 노드를 가리키는 trail 값을 n으로 변경
				n = n->rlink; // n은 n의 다음 노드를 가리키도록 변경

				if(trail->rlink == h) // trail이 마지막까지 증가하였는데 해당되는 값이 없을 경우
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


