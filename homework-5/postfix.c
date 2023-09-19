/*
 * postfix.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

/* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum{
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	/* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];		/* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;	   /* evalStack용 top */

int evalResult = 0;	   /* 계산 결과를 저장 */

void postfixpush(char x); // postfix로 변환하기 위해 스택에 저장하는 함수
char postfixPop(); // postfix를 만들기 위해 스택에서 pop을 하는 함수
void evalPush(int x); // postfix를 계산하기 위해 스택에 저장하는 함수
int evalPop(); // postfix를 계산하기 위해 스택에서 pop을 하는 함수
void getInfix(); // 계산 할 수식을 입력받는 함수
precedence getToken(char symbol); // 지정해놓은 열거형에 따라 연산자를 token으로 변환하는 함수
precedence getPriority(char x); // 연산자 우선순위를 판단하는 함수
void charCat(char* c); // 문자 하나를 전달받아 postfixExp에 저장하는 함수
void toPostfix(); // postfix로 전환하기 위한 함수
void debug(); // 입력받은 수식, postrix로 전환된 수식, 계산 결과, postfixStack을 출력하는 함수
void reset(); // 모든 내용을 초기화 시키는 함수
void evaluation(); // postfix 를 계산하는 함수

int main()
{
	printf("[----- [Chaerin Jung] [2020039022] -----]\n\n");

	char command;

	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			getInfix(); // 수식을 입력받음
			break;
		case 'p': case 'P':
			toPostfix(); // postfix로 전환
			break;
		case 'e': case 'E':
			evaluation(); // postfix를 계산
			break;
		case 'd': case 'D':
			debug(); // 모든 값들을 출력
			break;
		case 'r': case 'R':
			reset(); // 모든 값들을 초기화
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x; // stack에 top을 증가시켜 문자 저장
}

char postfixPop()
{
    char x;
    if(postfixStackTop == -1)
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--]; // top을 인덱스로 가지는 배열의 요소를 x에 반환한 후 top을 하나 감소시킴
    }
    return x;
}

void evalPush(int x)
{
    evalStack[++evalStackTop] = x; // stack에 top을 증가시켜 정수 저장
}

int evalPop()
{
    if(evalStackTop == -1)
        return -1;
    else
        return evalStack[evalStackTop--]; // top을 인덱스로 가지는 배열의 요소를 반환 한 후 top을 하나 감소시킴
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp); // 계산 할 수식을 입력받음
}

precedence getToken(char symbol)
{
	switch(symbol) {
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;
	} // 각 연산자들을 case문을 통하여 열거형에 정의된 숫자로 변환
}

precedence getPriority(char x)
{
	return getToken(x); // getToken 함수로 반환
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1); // 문자열이 비어있으면 들어온 문자 C를 복사로 저장
	else
		strncat(postfixExp, c, 1); // 그렇지 않으면 postfixExp 뒤에 c를 붙여 저장
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp;
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while(*exp != '\0')
	{
		/* 필요한 로직 완성 */
		if(getToken(*exp) == operand) // 만약 exp포인터로 읽은 문자가 피연산자라면 postfixExp에 바로 저장
		{
			charCat(exp);
		}

		else if(getPriority(*exp) == rparen)  
		{
			while(getPriority(postfixStack[postfixStackTop]) != lparen)
			{							
				x = postfixPop();
				charCat(&x); // 만약 exp포인터로 읽은 문자가 오른쪽 괄호라면 postfixStack에서 왼쪽 괄호가 나올 때까지 postfixExp에 저장	
			}
			
			if(postfixStack[postfixStackTop] == '(')
			{
				postfixStackTop--; // 왼쪽 괄호는 postfixExp에 저장하지 않음
			}
		}

		else
		{
			if(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp)) // 만약 postfixStack의 top에 저장된 연산자의 우선순위가 현재 비교중인 연산자보다 높거나 같을 경우
			{
				if(getToken(*exp) == lparen)
				{
					postfixPush(*exp); // 왼쪽 괄호는 우선 순위에 상관없이 stack에 push
				}
				
				else
				{
					x = postfixPop();
					charCat(&x); // 왼쪽 괄호를 제외한 경우 postfixStack의 top에 저장된 연산자를 pop하여 postfixExp에 저장

					postfixPush(*exp); // top에 있던 연산자를 pop한 후 현재 연산자 push
				}
			}

			else postfixPush(*exp); // 만약 postfixStack의 top에 저장된 연산자의 우선순위가 현재 비교중인 연산자보다 작을 경우 stack에 push
			
		}
		exp++;
	}
	
	while(postfixStackTop != -1)
	{
		x = postfixPop();
		charCat(&x); // stack에 남아있는 연산자 모두 출력
	}
}

void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp); // 입력 받은 수식 출력
	printf("postExp =  %s\n", postfixExp); // postfix로 변환된 수식 출력
	printf("eval result = %d\n", evalResult); // 계산 한 값 출력

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]); // 마지막으로 스택에 저장된 연산자들 출력

	printf("\n");

}

void reset()
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';
         
	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0; // 모든 스택과 변수들의 값을 처음과 같이 변경함
}

void evaluation()
{
	/* postfixExp, evalStack을 이용한 계산 */
	int ev1, ev2, i;
	int length = strlen(postfixExp); // postfixExp 길이를 저장하는 변수
	char *evp = postfixExp; // postfixExp 배열을 하나씩 읽을 변수
	char x;

	for(i=0 ; i < length ; i++)
	{
		x = *evp; // evp 포인터가 가리키는 값을 받는 변수 x

		if(getToken(x) == operand){ evalPush(x - '0');} // x가 피연산자 일 경우 evalStack에 push, -'0'을 하는 이유는 문자를 정수로 변환하기 위해서

		else{
			ev2 = evalPop(); // 스택에 가장 마지막으로 저장된 정수
			ev1 = evalPop(); // 그 다음으로 스택에 마지막으로 저장된 정수

			switch(getToken(x)) // x의 토큰 값으로 수식을 계산한 후 ev1과 ev2를 연산한 값을 스택에 다시 push
			{			
         	case times: evalPush(ev1 * ev2); break;
			case divide: evalPush(ev1 / ev2); break;	
			case plus: evalPush(ev1 + ev2); break;
         	case minus: evalPush(ev1 - ev2); break;			
         	default: break;
			}
		}
		evp++; // evp가 가리키고 있는 값을 증가시킴
	}
	evalResult = evalPop(); // 마지막에 스택에 남아있는 정수가 계산의 결과 값임
}

