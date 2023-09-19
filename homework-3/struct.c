#include <stdio.h>

struct student1{
    char lastName;
    int studentId;
    char grade;
}; // typedef를 사용하지 않고 구조체 정의

typedef struct {
    char lastName;
    int studentId;
    char grade;
} student2; // typedef를 사용하여 구조체 정의

int main()
{
    printf("[----- [Chaerin Jung] [2020039022] -----]\n");

    struct student1 st1 = {'A', 100, 'A'}; // typedef를 사용하지 않았기 때문에 struct를 꼭 붙여야 함

    printf("st1.lastName = %c\n", st1.lastName);
    printf("st1.studentId = %d\n", st1.studentId);
    printf("st1.grade = %c\n", st1.grade); // 각 자료들을 출력

    student2 st2 = {'B', 200, 'B'};

    printf("\nst2.lastName = %c\n", st2.lastName);
    printf("st2.studentId = %d\n", st2.studentId);
    printf("st2.grade = %c\n", st2.grade); // 각 자료들을 출력

    student2 st3;

    st3 = st2; // st2를 st3에 복사

    printf("\nst3.lastName = %c\n", st3.lastName);
    printf("st3.studentId = %d\n", st3.studentId);
    printf("st3.grade = %c\n", st3.grade); // 출력하면 st2의 자료들과 같은 값이 출력됨

    /* equality test */
    /* if(st3==st2)
            printf("equal\n");
       else
            printf("not equal\n");  이렇게 동일성 여부를 판단하는 것은 불가능*/

    return 0;

}