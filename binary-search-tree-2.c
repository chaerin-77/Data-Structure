/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20 // 스택의 최대 크기를 20으로 저장
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop(); // 스택을 pop하는 함수
void push(Node* aNode); // 스텍에 push하는 함수

/* for queue */
#define MAX_QUEUE_SIZE		20 // 큐의 최대 크기를 20으로 저장
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue(); // 큐에서 삭제하는 함수
void enQueue(Node* aNode); // 큐에 추가하는 함수


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	printf("[----- [Chaerin Jung] [2020039022] -----]");

	char command;
	int key;
	Node* head = NULL;

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head); // head의 주소를 넘겨 tree를 초기화 함
			break;
		case 'q': case 'Q':
			freeBST(head); // 사용했던 tree를 해제
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key); // 저장 할 키를 입력받아 삽입
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key); // 해당되는 노드 삭제
			break;
		case 'r': case 'R':
			recursiveInorder(head->left); // recursive 방식으로 중위순회
			break;
		case 't': case 'T':
			iterativeInorder(head->left); // iterative 방식으로 중위순회
			break;
		case 'l': case 'L':
			levelOrder(head->left); // leveloreder 방식 순회
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); // tree의 head 동적 할당
	(*h)->left = NULL; // head의 left를 root로 함
	(*h)->right = *h; // head의 right는 사용하지 않음
	(*h)->key = -9999;

	top = -1; // 전역변수인 top을 -1로 초기화

	front = rear = -1; // 전역변수인 front와 rear을 -1로 초기화

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	} // recursive 방식으로 ptr이 NULL이 될 때까지 실행
}

/**
 * textbook: p 224s
 */
void iterativeInorder(Node* node)
{
	int top = -1;
	Node stack[MAX_STACK_SIZE]; // 사용할 스택을 생성

	for(;;){ // 무한 루프
		for(;node;node = node->left) push(node); // node의 left로 이동하며 스택에 push
		node = pop(); // 스택에 저장된 포인터를 pop 즉, 가장 왼쪽의 값

		if(!node) break; // node가 NULL이 되면 break

		printf(" [%d] ", node->key); // pop한 node의 key값을 출력
		node = node->right; // 다음 출력인 right 값을 출력하기 위해 해당 node의 오른쪽 값으로 변경
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	Node queue[MAX_QUEUE_SIZE]; // 사용할 큐 생성

	if(!ptr) return; // ptr이 NULL이면 종료
	enQueue(ptr); // ptr을 큐에 저장

	for(;;){ // 무한 루프
		ptr = deQueue(); // 큐에 저장된 앞의 값 하나 받음
		
		if(ptr){ // ptr이 NULL이 아닐 때
			printf(" [%d] ", ptr->key); // ptr의 키값 출력
			if(ptr->left) enQueue(ptr->left); // ptr의 left가 NULL이 아니면 해당 값 큐에 저장
			if(ptr->right) enQueue(ptr->right); // ptr의 right가 NULL이 아니면 해당 값 큐에 저장
		}

		else break;
	}
	
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node)); // 새로 추가할 node 할당
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL; // 새로 할당받은 node의 키값, left, right 저장

	if (head->left == NULL) {
		head->left = newNode; // 만약 root node가 비어있다면 바로 추가
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left; // root node를 가리키는 포인터 생성
	Node* parentNode = NULL; // 부모노드를 가리키는 포인터 생성

	while(ptr != NULL) { // ptr이 NULL이 아닐 때까지

		if(ptr->key == key) return 1; // 해당되는 key값을 가진 node가 있을 경우 종료/

		parentNode = ptr; // 부모노드의 값을 ptr로 변경

		if(ptr->key < key)
			ptr = ptr->right; // ptr의 key값이 추가할 key값 보다 작을 경우 ptr의 값을 ptr의 right로 변경
		else
			ptr = ptr->left; // 그 외의 경우에는 ptr의 값을 ptr의 left로 변경
	}

	// 부모노드에 새로 생성한 newNode 연결
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
	Node *parent, *ptr, *del, *pdel; // 부모노드와 현재 노드를 확인하기 위한 포인터와 삭제를 위한 포인터 두 개
	parent = head; // parent가 root node를 가리키도록 함
	ptr = head->left;

	if(head->left == NULL)
		printf("Binary-search-tree is Empty!!\n"); // root node가 비어있을 경우 오류 문자열 출력
	
	else if (parent->left == NULL && parent->right == NULL) { // parent의 left와 right 모두가 NULL 일 경우 즉, root node만 존재할 경우
		head->left = NULL; // root node를 NULL로 변경
		free(parent); // root node 해제
	}
	
	else
	{
		while(ptr->key != key) // ptr의 key값이 삭제할 key값과 같아질 때 까지
		{
			parent = ptr; // 부모노드의 값을 현재노드로 변경

			if (parent->key > key) ptr = parent->left; // 부모노드의 key값이 입력받은 key값 보다 클 경우, 현재 노드를 부모노드의 left로 변경
			else if (parent->key < key) ptr = parent->right; // 부모노드의 key값이 입력방은 key값 보다 작을 경우, 현재 노드를 부모노드의 right로 변경

			if (ptr == NULL){ // 끝까지 비교했지만 해당 노드가 없을 경우
				printf("No node for key[%d]", key); // 해당되는 노드가 없다는 오류 문자열 출력
				return 0;
			}
		}

		if(ptr->left == NULL && ptr->right == NULL){ // 해당되는 node를 찾았지만 그 노드의 left나 right가 NULL일 경우

			if (parent->left == ptr) parent->left = NULL; // while문 종료 후 부모노드의 left가 ptr일 경우 left를 NULL로 변경
			else if (parent->right == ptr) parent->right = NULL; // 부모노드의 right가 ptr일 경우 right를 NULL로 변경

			free(ptr); // ptr 해제
		}

		else if(ptr->left != NULL && ptr->right == NULL){ // ptr의 left만 존재할 경우

			if (parent->left == ptr) parent->left = ptr->left; // parent의 left가 ptr일 경우 parent의 left를 ptr의 left로 변경
			else if (parent->right == ptr) parent->right = ptr->left; // parent의 right가 ptr일 경우 parent의 right를 ptr의 left로 변경

			free(ptr); // ptr 해제
		}

		else if(ptr->left == NULL && ptr->right != NULL){ // ptr의 right만 존재할 경우

			if (parent->left == ptr) parent->left = ptr->right; // parent의 left가 ptr일 경우 parent의 left를 ptr의 right로 변경
			else if (parent->right == ptr) parent->right = ptr->right; // parent의 right가 ptr일 경우 parent의 left를 ptr의 right로 변경

			free(ptr); // ptr 해제
		}

		else{

			del = ptr; // del이 ptr을 가리키도록 함
			pdel = parent; // pdel이 parent를 가리키도록 함
			ptr = ptr->right; // ptr의 값은 오른쪽 노드를 가리키도록 함

			if(ptr->left == NULL){ // ptr의 left 값이 비어있다면
				if (parent->left == del) parent->left->key = ptr->key; // 부모노드의 왼쪽 값이 del이라면 parent의 왼쪽 값의 key값을 ptr의 key값으로 변경
				else if (parent->right == del) parent->right->key = ptr->key; // 부모노드의 오른쪽 값이 del이라면 parent의 오른쪽 값의 key값을 ptr의 key값으로 변경

				del->right = NULL; // del의 right를 NULL로 변경
				free(ptr); // ptr 해제
				
				return 0;
			}

			while(ptr->left != NULL) { // ptr의 left가 NULL이 아닐 때까지
				pdel = ptr; // pdel의 값을 ptr로 변경
				ptr = ptr->left; // ptr의 값을 ptr의 left로 변경하여 가장 작은 값을 찾음
			}
			pdel->left = NULL; // pdel의 left를 NULL로 변경

			if (parent->left == del) parent->left->key = ptr->key; // 부모노드의 left가 del일 경우 parent의 left의 key를 ptr의 key값으로 변경
			else if (parent->right == del) parent->right->key = ptr->key; // 부모노드의 right가 del일 경우 parent의 right의 key를 ptr의 key값으로 변경

			free(ptr); // 그 후 ptr 해제
		}
		
	}
}


void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	} // 후위 순회 방식을 사용하여 트리 해제
}

int freeBST(Node* head)
{

	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p); // root node 해제

	free(head); // head node 해제
	return 1;
}



Node* pop()
{
	Node *p; // node를 가리키는 포인터 p 생성

	if(top == -1) return NULL; // stack이 비어있으면 바로 종료
	else p = stack[top--]; // 그렇지 않으면 p에 스택의 top 값을 받고 top의 값을 하나 감소시킴

	return p; // p반환
}

void push(Node* aNode)
{
	stack[++top] = aNode; // 스택의 top을 하나 증가시키면서 해당 값 저장
}



Node* deQueue()
{
	if (front == rear){
		return NULL; // 큐가 비어있으면 바로 종료
	}
	front = (front + 1) % MAX_QUEUE_SIZE; // front의 다음 인덱스 값을 저장
	return queue[front]; // 해당 인덱스의 큐 값 반환
}

void enQueue(Node* aNode)
{
	if (((rear+1)%MAX_QUEUE_SIZE) == front) { // rear의 다음 값이 front일 경우 즉, 큐가 포화상태일 경우
		printf(" There is an error!! (queue is full)"); // 오류 문자열 출력
		return;
	}
	rear = (rear + 1) % MAX_QUEUE_SIZE; // rear의 값을 한 칸 증가시킴
	queue[rear] = aNode; // 증가시킨 rear에 해당하는 큐에 저장
}





