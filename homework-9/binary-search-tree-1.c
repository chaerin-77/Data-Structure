/*
 * Binary Search Tree #1
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

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	printf("[----- [Chaerin Jung] [2020039022] -----]");
	
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // command 변수에 해당 메뉴를 실행 할 수 있도록 입력받음

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head); // head변수의 주소를 넘겨 tree 초기화
			break;
		case 'q': case 'Q':
			freeBST(head); // 종료 시 사용했던 tree 해제
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key); // 추가할 key를 입력받음
			insert(head, key); // insert 함수를 통해 tree에 추가
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key); // 삭제할 key를 입력받음
			deleteLeafNode(head, key); // delete함수를 통해 해당 leaf node 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key); // iteragive 방식으로 검색하고 싶은 key를 입력받음
			ptr = searchIterative(head, key); // 해당되는 key를 가진 node의 주소를 ptr에 받음
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr); // ptr이 NULL이 아니라면 해당되는 주소 출력
			else
				printf("\n Cannot find the node [%d]\n", key); // ptr이 NULL이라면 찾을 수 없다는 오류 문자열 출력
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key); // recursive 방식으로 검색하고 싶은 key를 입력받음
			ptr = searchRecursive(head->left, key); // 해당되는 key를 가진 node의 주소를 받음
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr); // ptr이 NULL이 아니라면 해당되는 주소 출력
			else
				printf("\n Cannot find the node [%d]\n", key); // ptr이 NULL이라면 찾을 수 없다는 오류 문자열 출력
			break;

		case 'i': case 'I':
			inorderTraversal(head->left); // 중위 순회 방식으로 tree 출력
			break;
		case 'p': case 'P':
			preorderTraversal(head->left); // 전위 순회 방식으로 tree 출력
			break;
		case 't': case 'T':
			postorderTraversal(head->left); // 후위 순회 방식으로 tree 출력
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); // 메뉴에 지정해 놓은 선택지가 아닐 경우 오류 문자열 출력
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h); // head가 가리키는 곳이 NULL이 아니라면 할당되었던 tree 해제

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL; // h의 left를 root node로 사용
	(*h)->right = *h; // h의 right는 자기 자신을 가리킴
	(*h)->key = -9999; // head의 key값 초기화
	return 1;
}



void inorderTraversal(Node* ptr)
{
	if(ptr)
	{
		inorderTraversal(ptr->left);
		printf("[%d]   ", ptr->key);
		inorderTraversal(ptr->right);
	} // 중위 순회는 왼쪽 자식, 뿌리, 오른쪽 자식 순
	

}

void preorderTraversal(Node* ptr)
{
	if(ptr)
	{
		printf("[%d]   ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	} // 전위 순회는 뿌리, 왼쪽자식, 오른쪽 자식 순

}

void postorderTraversal(Node* ptr)
{
	if(ptr)
	{
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf("[%d]   ", ptr->key);
	} // 후위 순회는 왼쪽 자식, 오른쪽 자식, 뿌리 순
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node)); // 입력 받은 key를 저장하는 새로운 노드 생성
	newNode->key = key; // 새로운 노드에 key 값에 입력받은 값 대입
	newNode->left = NULL;
	newNode->right = NULL; // 새로운 노드의 left, right의 값을 NULL로 초기화
	
	Node *parent, *ptr; // 부모 노드와 현재 노드를 확인하기 위한 포인터

	if(head->left == NULL)
		head->left = newNode; // 만약에 head의 left 즉, root 노드가 비어있다면 root 노드를 newNode로 변경
	
	else
	{
		parent = head->left; // parent의 값을 root 노드로 설정
		ptr = parent;

		while(ptr != NULL) // 현재 노드가 NULL이 될 때 까지
		{
			parent = ptr; // parent의 값을 현재 노드로 변경, tree의 leaf 부분에 저장해야 하기 때문

			if (parent->key > newNode->key) ptr = parent->left; // 새로 추가할 노드의 key가 부모 노드의 key보다 작다면 현재 노드를 left로 변경
			else if (parent->key < newNode->key) ptr = parent->right; // 새로 추가할 노드의 key가 부모 노드의 key보다 크다면 현재 노드를 right로 변경
		}

		//while문 종료 후 부모노드의 key 값과 새로운 노드의 key 값을 비교하여 해당 되는 위치에 저장
		if (parent->key > newNode->key) parent->left = newNode; // 부모노드의 key값이 더 클 경우 left가 새로운 노드를 가리키도록 함
		else if (parent->key < newNode->key) parent->right = newNode; // 부모노드의 key값이 더 작을 경우 right가 새로운 노드를 가리키도록 함
	}
}

int deleteLeafNode(Node* head, int key)
{
	Node *parent, *ptr; // 부모노드와 현재 노드를 확인하기 위한 포인터
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
				printf("There is no such node!!"); // 해당되는 노드가 없다는 오류 문자열 출력
				return 0;
			}
		}

		if(ptr->left != NULL || ptr->right != NULL){ // 해당되는 node를 찾았지만 그 노드의 left나 right가 NULL이 아닐 경우
			printf("the node [%d] is not a leaf", ptr->key); // 해당 노드는 leaf node가 아님
			return 0;
		}

		else if (parent->left == ptr) parent->left = NULL; // while문 종료 후 부모노드의 left가 ptr일 경우 left를 NULL로 변경
		else if (parent->right == ptr) parent->right = NULL; // 부모노드의 right가 ptr일 경우 right를 NULL로 변경

		free(ptr); // ptr 해제
	}
}

Node* searchRecursive(Node* ptr, int key) // recursive 방식으로 search
{
	if (ptr == NULL) return NULL; // 해당 노드가 비어있을 경우 NULL 반환
	else if (key == ptr->key) return ptr; // 검색할 key와 ptr의 key값이 같을 경우 해당 노드의 주소 반환
	else if (key < ptr->key) return searchRecursive(ptr->left, key); // 검색할 key보다 ptr의 key값이 더 클 경우 ptr의 left를 searchRecursive함수의 인자로 반환
	else if (key > ptr->key) return searchRecursive(ptr->right, key); // 검색할 key보다 ptr의 key값이 더 작을 경우 ptr의 right를 searchRecursive함수의 인자로 반환
}

Node* searchIterative(Node* head, int key) // iterative 방식으로 search
{
	Node *ptr = head->left; // ptr이 root node를 가리키도록 함

	while(ptr)
	{
		if (ptr->key == key) return ptr; // 해당되는 key값을 찾았을 경우 ptr의 값 반환
		else if (key < ptr->key) ptr = ptr->left; // 검색 할 key값 보다 ptr의 key값이 더 클 경우 ptr의 값을 ptr의 left로 변경
		else if (key > ptr->key) ptr = ptr->right; // 검색 할 key값 보다 ptr의 key값이 더 작을 경우 ptr의 값을 ptr의 right로 변경
	}

	if (ptr == NULL) return NULL; // ptr이 NULL이 되었을 경우 NULL값을 반환
}


int freeBST(Node* head)
{
	if(head)
	{
		freeBST(head->left);
		freeBST(head->right);
		free(head);
	} // root node를 마지막에 접근하는 후위 순회의 방식을 활용하여 할당한 tree 해제
}