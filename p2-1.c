#define MAX_SIZE 100

float sum(float list[], int);
float input[MAX_SIZE], answer;

int i;

void main(void)
{
    printf("[----- [Chaerin Jung] [2020039022] -----]\n");

    for(i = 0; i < MAX_SIZE; i++)
        input[i] = i; // input 배열의 자료들의 값 지정
    
    printf("address of input = %p\n", input); // 참조에 의한 호출 확인

    answer = sum(input, MAX_SIZE); // input의 주소값을 넘김
    printf("The sum is: %f\n", answer);
}

float sum(float list[], int n)
{
    printf("value of list = %p\n", list); // list에 넘어온 값 출력 (input 주소값)
    printf("address of list = %p\n\n", &list); // list의 주소
    
    int i;
    float tempsum = 0;

    for(i = 0; i < n; i++)
        tempsum += list[i]; // list 배열의 자료들을 하나씩 더함
    
    return tempsum;
}