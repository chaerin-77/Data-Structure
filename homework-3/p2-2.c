#include <stdio.h>

void print1 (int *ptr, int rows);

int main()
{
    printf("[----- [Chaerin Jung] [2020039022] -----]\n");

    int one[] = {0, 1, 2, 3, 4};

    printf("one     = %p\n", one);
    printf("&one    = %p\n", &one);
    printf("&one[0] = %p\n\n", &one[0]); // 위의 세 줄 모두 one 배열의 주소 출력

    print1(&one[0], 5); // one 배열의 주소값을 넘김

    return 0;

}

void print1 (int *ptr, int rows)
{
    int i;

    printf("Address \t Contents\n");

    for(i = 0; i < rows; i++)
        printf("%p \t  %5d\n", ptr + i, *(ptr + i)); // 각 자료들의 주소값 출력
    
    printf("\n");
}