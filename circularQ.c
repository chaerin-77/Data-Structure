/*
 * circularQ.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element; // 자료형 char == element 로 지정
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType; // front와 rear가 포함 된 구조체 생성


QueueType *createQueue();
int freeQueue(QueueType *cQ); // 사용한 원형 큐를 해제하는 함수
int isEmpty(QueueType *cQ); // 원형큐가 비어있는지 확인하는 함수
int isFull(QueueType *cQ); // 원형큐가 포화상태인지 확인하는 함수
void enQueue(QueueType *cQ, element item); // rear를 이동시켜 데이터를 원형 큐에 저장하는 함수
void deQueue(QueueType *cQ, element* item); // front를 이동시켜 데이터를 삭제하는 함수
void printQ(QueueType *cQ); // 원형 큐 안에 들어있는 데이터들을 출력하는 함수
void debugQ(QueueType *cQ); // front와 rear의 위치를 출력하고, 각 데이터들의 위치도 알 수 있는 함수
element getElement();

int main(void)
{
	printf("[----- [Chaerin Jung] [2020039022] -----]\n");

	QueueType *cQ = createQueue(); // 원형 큐 생성
	element data;
	char command;

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			data = getElement(); // 데이터를 입력받고
			enQueue(cQ, data); // 원형큐에 데이터를 저장함
			break;
		case 'd': case 'D':
			deQueue(cQ, &data); // front의 위치를 옮겨 데이터를 삭제함
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ); // front와 rear의 위치를 확인
			break;
		case 'q': case 'Q':
   	        freeQueue(cQ); // 프로그램 종료 시 사용했던 원형큐 해제
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}

QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType)); // 동적할당을 통해 원형 큐 생성
	cQ->front = 0;
	cQ->rear = 0; // front와 rear를 0으로 초기화
	cQ->queue[0] = 0;
	return cQ; // 생성한 원형큐 포인터를 반환
}

int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1;
    free(cQ); // 원형큐 해제
    return 1;
}

element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item); // 데이터를 입력받음
	return item; // 입력받은 데이터를 반환
}


/* complete the function */
int isEmpty(QueueType *cQ)
{
	if(cQ->front == cQ->rear)
	printf("Circular Queue is Empty!"); // 원형큐의 front와 rear가 같으면 비어있다는 오류 문구 출력

    return 0;
}

/* complete the function */
int isFull(QueueType *cQ)
{
	if(cQ->front == ((cQ->rear + 1) % MAX_QUEUE_SIZE)) // 만약 원형 큐가 포화상태면 rear에 +1을 하면 front와 동일해짐. 또한 나머지 연산을 통해 값을 0~MAX_QUEUE_SIZE 로 고정
	{
		printf("Circular Queue is Full!"); // 따라서 rear에 +1을 한 것과 front가 동일하다면 원형큐는 포화상태임
		return 1;
	}

   else return 0;
}


/* complete the function */
void enQueue(QueueType *cQ, element item)
{
	if(isFull(cQ)) // 원형 큐가 포화상태인지 확인
		return;
	
	else
	{
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; // rear에 +1을 한 후 나머지 연산을 통해 rear의 범위를 0~MAX_QUEUE_SIZE 로 고정

		cQ->queue[cQ->rear] = item; // 1을 증가시킨 rear를 인덱스로 가지는 배열의 위치에 데이터를 저장
	}		

}

/* complete the function */
void deQueue(QueueType *cQ, element *item)
{
	if(isEmpty(cQ)) // 원형큐가 비어있는지 확인
		return;
	
	else
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE; // front의 위치를 이동시킴

    return;
}


void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE; // front가 가르키고 있는 위치는 공백이기 때문에 첫번째 요소를 출력하기 위해서는 하나 증가시켜야 함
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE; // 범위 설정을 위해 rear를 하나 증가시킴

	printf("Circular Queue : [");

	i = first;
	while(i != last) // 아까 rear를 하나 증가시켰기 때문에 rear는 데이터가 아닌 다른 곳을 가르키게 됨. 따라서 i가 last가 아닐때까지 반복
	{
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE; // i를 하나씩 증가시키며 나머지 연산을 통해 원형큐를 순환하게 함

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i); // front가 가르키고 있는 곳의 인덱스를 알 수 있음
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); // 각 인덱스 별 들어있는 데이터 출력

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); // front와 rear가 가르키는 곳을 출력
}