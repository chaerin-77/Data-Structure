#include <stdio.h>
#include <stdlib.h>

void main()
{
    printf("[----- [Chaerin Jung] [2020039022] -----]\n");
    
    int list[5];
    int *plist[5];

    list[0] = 10;
    list[1] = 11;

    plist[0] = (int*)malloc(sizeof(int));

    printf("list[0] \t= %d\n", list[0]); // list[0]의 값 출력
    printf("address of list \t= %p\n", list); // list 출력 = 배열의 첫번째 요소의 주소
    printf("address of list[0] \t= %p\n", &list[0]); // 따라서 list 출력값이랑 동일
    printf("address of list + 0 \t= %p\n", list+0); // list + 0 = list 이므로 위의 값과 동일
    printf("address of list + 1 \t= %p\n", list+1); 
    printf("address of list + 2 \t= %p\n", list+2);
    printf("address of list + 3 \t= %p\n", list+3);
    printf("address of list + 4 \t= %p\n", list+4); // 4bytes 씩 증가
    printf("address of list[4] \t= %p\n", &list[4]); // list[4]의 주소와 list + 4 의 값이 동일

    free(plist[0]);

}