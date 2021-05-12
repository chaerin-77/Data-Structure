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
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


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
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;
		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;
		case 'l': case 'L':
			levelOrder(head->left);
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
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224s
 */
void iterativeInorder(Node* node)
{
	int top = -1;
	Node stack[MAX_STACK_SIZE];

	for(;;){
		for(;node;node = node->left) push(node);
		node = pop();

		if(!node) break;

		printf(" [%d] ", node->key);
		node = node->right;
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	Node queue[MAX_QUEUE_SIZE];

	if(!ptr) return;
	enQueue(ptr);

	for(;;){
		ptr = deQueue();
		
		if(ptr){
			printf(" [%d] ", ptr->key);
			if(ptr->left) enQueue(ptr->left);			
			if(ptr->right) enQueue(ptr->right);
		}

		else break;
	}
	
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
	Node *parent, *ptr, *del, *pdel; // 부모노드와 현재 노드를 확인하기 위한 포인터
	parent = head->left; // parent가 root node를 가리키도록 함
	ptr = parent;

	if(head->left == NULL)
		printf("Binary-search-tree is Empty!!\n"); // root node가 비어있을 경우
	
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

		else if(ptr->left != NULL && ptr->right == NULL){

			if (parent->left == ptr) parent->left = ptr->left;
			else if (parent->right == ptr) parent->right = ptr->left;

			free(ptr);
		}

		else if(ptr->left == NULL && ptr->right != NULL){

			if (parent->left == ptr) parent->left = ptr->right;
			else if (parent->right == ptr) parent->right = ptr->right;

			free(ptr);
		}

		else{

			del = ptr;
			pdel = parent;
			ptr = ptr->right;

			if(ptr->left == NULL){
				if (parent->left == del) parent->left->key = ptr->key;
				else if (parent->right == del) parent->right->key = ptr->key;

				del->right = NULL;
				free(ptr);
				
				return 0;
			}

			while(ptr->left != NULL) {
				pdel = ptr;
				ptr = ptr->left;
			}
			pdel->left = NULL;

			if (parent->left == del) parent->left->key = ptr->key;
			else if (parent->right == del) parent->right->key = ptr->key;

			free(ptr);
		}
		
	}
}


void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()
{
	Node *p;

	if(top == -1) return NULL;
	else p = stack[top--];

	return p;
}

void push(Node* aNode)
{
	stack[++top] = aNode;
}



Node* deQueue()
{
	if (front == rear){
		return NULL;
	}
	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];
}

void enQueue(Node* aNode)
{
	if (((rear+1)%MAX_QUEUE_SIZE) == front) {
		printf(" There is an error!! (enqueue) ");
		return;
	}
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	queue[rear] = aNode;
}





