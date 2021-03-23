#include <stdio.h>
#include <stdlib.h>

void main()
{
    printf("[----- [Chaerin Jung] [2020039022] -----]\n");
    
    int list[5];
    int *plist[5] = {NULL,}; // 정수형 포인터 배열

    plist[0] = (int *)malloc(sizeof(int));

    list[0] = 1;
    list[1] = 100;

    *plist[0] = 200;

    printf("value of list[0] = %d\n", list[0]);
    printf("address of list[0]      = %p\n", &list[0]); // list[0]의 주소
    printf("value of list           = %p\n", list); // list 출력 = list 배열의 첫번째 값의 주소
    printf("address of list (&list) = %p\n", &list); // list의 주소
               /* 세 값이 모두 동일 */

    printf("-------------------------------------------\n\n");
    printf("value of list[1]    = %d\n", list[1]); 
    printf("address of list[1]  = %p\n", &list[1]); // list[1]의 주소
    printf("value of *(list+1)  = %p\n", *(list + 1)); // list 주소에서 하나 더한 곳의 자료값 출력
    printf("address of list+1   = %p\n", list+1); // list+1 한 곳의 주소
    
    printf("-------------------------------------------\n\n");

    printf("value of *plist[0]  = %d\n", *plist[0]); // plist[0]이 가르키고 있는 값
    printf("&plist[0]           = %p\n", &plist[0]); // 0번째 요소의 주소
    printf("&plist              = %p\n", &plist); // plist의 주소
    printf("plist               = %p\n", plist); // plist = 배열의 첫번째 값의 주소
    printf("plist[0]            = %p\n", plist[0]); // plist[0]이 가르키고 있는 곳의 주소
    printf("plist[1]            = %p\n", plist[1]);
    printf("plist[2]            = %p\n", plist[2]);
    printf("plist[3]            = %p\n", plist[3]);
    printf("plist[4]            = %p\n", plist[4]); // list[1]부터는 모두 NULL 값이 출력됨
    
    free(plist[0]);

}