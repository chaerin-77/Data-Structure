#include <stdio.h>

struct student {
    char lastName[13];  // 13bytes
    int studentId;      // 4bytes
    short grade;        // 2bytes
}; // 모두 합하면 19bytes이다.

int main()
{
    printf("[----- [Chaerin Jung] [2020039022] -----]\n");

    struct student pst;

    printf("size of student = %ld\n", sizeof(struct student)); // 하지만 출력해보면 24bytes가 나오는 것으로 보아 padding이 되었음을 알 수 있다.
    printf("size of int = %ld\n", sizeof(int));
    printf("size of short = %ld\n", sizeof(short));

    return 0;
}