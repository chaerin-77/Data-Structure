#include <stdio.h>
#include <stdlib.h>

void main()
{
    printf("[----- [Chaerin Jung] [2020039022] -----]\n");
    
    int **x;

    printf("sizeof(x) = %lu\n", sizeof(x)); // 주소를 저장하는 값이기 때문에 8bytes이다.
    printf("sizeof(*x) = %lu\n", sizeof(*x)); // 또한 주소를 저장하는 값이다.
    printf("sizeof(**x) = %lu\n", sizeof(**x)); // intger형을 저장하기 때문에 4bytes이다.

}