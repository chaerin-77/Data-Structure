/*
 * hw12-sorting-hashing.c
 *
 *  Created on: May 22, 2021
 *
 *  Homework 12: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	printf("[----- [Chaerin Jung] [2020039022] -----]");

	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1; // 사용할 변수와 포인터들 생성 후 초기화

	srand(time(NULL)); // 난수 생성

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array); // 배열 초기화
			break;
		case 'q': case 'Q':
			freeArray(array); // 사용한 배열 해제
			break;
		case 's': case 'S':
			selectionSort(array); // 선택 정렬
			break;
		case 'i': case 'I':
			insertionSort(array); // 삽입 정렬
			break;
		case 'b': case 'B':
			bubbleSort(array); // 버블 정렬
			break;
		case 'l': case 'L':
			shellSort(array); // 쉘 정렬
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE); // 퀵 정렬
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable); // 해싱
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key); // 해시 테이블에서 해당되는 키 찾기
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array); // 배열 출력
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)
{
	if(a != NULL)
		free(a); // 사용한 배열 해제
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) {
		printf("nothing to print.\n"); // 배열이 생성되지 않았다면 오류 문자열 출력
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i); // 인덱스 번호 출력
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]); // 인덱스에 해당되는 값 출력
	printf("\n");
}


int selectionSort(int *a)
{
	int min; // 선택 정렬은 가장 작은 값부터 정렬하기 때문에 최소값을 저장할 변수가 필요함
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 정렬을 하기 전에 생성된 배열 출력

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i; // 최소값의 인덱스를 i로 설정
		min = a[i]; // 배열 a의 i번째 값을 최소값으로 설정
		for(j = i+1; j < MAX_ARRAY_SIZE; j++) // i의 다음 번호부터 비교 시작
		{
			if (min > a[j]) // 만약 최소값보다 작은 값이 존재한다면
			{
				min = a[j]; // 최소값을 j번째 값으로 변경 후
				minindex = j; // 최소값의 인덱스도 j로 번경
			}
		}
		a[minindex] = a[i]; // 최소값이 들어있던 위치의 값을 i번째 값과 변경
		a[i] = min; // a의 i번째 값을 최소값으로 변경
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬된 배열 출력
	return 0;
}

int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 정렬 전 배열 출력

	for(i = 1; i < MAX_ARRAY_SIZE; i++) // 맨 앞을 정렬되었다고 보고 1부터 시작
	{
		t = a[i]; // i번째 값으로 설정
		j = i; // j를 이동시켜서 비교하기 위해 i값으로 초기화
		while (a[j-1] > t && j > 0) // a의 j-1번째 값이 a의 i번째 값보다 작거나 같고, j가 0이 되면 종료
		{
			a[j] = a[j-1]; // a의 j번째 값을 a의 j-1번째 값으로 변경
			j--; // j값을 하나 감소시킴
		}
		a[j] = t; // a의 j번째 값을 i번째 값으로 변경
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬된 배열 출력

	return 0;
}

int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 정렬 전 배열 출력

	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j-1] > a[j]) // a의 j번째와 그 앞의 값 두개를 비교한 후 만약 앞의 값이 더 크다면
			{
				t = a[j-1]; 
				a[j-1] = a[j];
				a[j] = t; // 두 값을 교환
			}
		}
	} // 두개씩 비교하며 가장 큰 값이 뒤에서부터 정렬됨

	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬된 배열 출력

	return 0;
}

int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 정렬 전 배열 출력

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) // 처음 h의 값을 전체 배열의 절반으로 설정함. 반복 할 수록 h의 값을 절반으로 변경함
	{
		for (i = 0; i < h; i++) // i가 0부터 h보다 작을 때 까지 하나씩 증가
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h) // j는 i로부터 h만큼 떨어져 있는 곳부터 시작하여 배열의 끝까지 비교
			{
				v = a[j]; // v의 값을 a의 j번째 값으로 설정
				k = j; // k를 j로 설정
				while (k > h-1 && a[k-h] > v) // k가 h-1보다 크고, a의 k-h번째 값이 v 즉 a의 j번째 값보다 클 동안
				{
					a[k] = a[k-h]; // k번째 값을 k-h번째 값으로 변경
					k -= h; // k = k-h
				}
				a[k] = v; // a의 k번째 값을 a의 j번째 값으로 변경
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬 된 배열 출력

	return 0;
}

int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1) // n은 인자로 넘어옴
	{
		v = a[n-1]; // 기준점인 v를 a의 n-1번째 값으로 설정
		i = -1; // i는 맨 앞 인덱스를 가리키기 위해 -1로 설정
		j = n - 1; // j는 배열의 마지막 인덱스로 설정

		while(1)
		{
			while(a[++i] < v); // v보다 큰 값이 나올 때까지 i 증가
			while(a[--j] > v); // v보다 작은 값이 나올 때까지 j 감소

			if (i >= j) break; // 만약 i가 j보다 크거나 같으면 while문 종료

			t = a[i];
			a[i] = a[j];
			a[j] = t; // a의 i번째 값과 j번째 값을 교환
		}
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t; // a의 i번째 값과 기준 값을 교환

		quickSort(a, i); // i번째를 기준으로 앞부분 퀵정렬
		quickSort(a+i+1, n-i-1); // i번째 뒷부분 퀵정렬
	}


	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key);
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)
		{
			hashtable[hashcode] = key;
		} else 	{

			index = hashcode;

			while(hashtable[index] != -1)
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key);

	if(ht[index] == key)
		return index;

	while(ht[++index] != key)
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;
}