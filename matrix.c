#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col);
void print_matrix(int** matrix, int row, int col);
int free_matrix(int** matrix, int row, int col);
int fill_data(int** matrix, int row, int col);
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);

int main()
{

    char command;
    printf("[----- [Chaerin Jung]  [2020039022] -----]\n");

    int row, col;
    srand(time(NULL));

    printf("Input row and col : ");
    scanf("%d %d", &row, &col);
    int** matrix_a = create_matrix(row, col);
    int** matrix_b = create_matrix(row, col);
    int** matrix_a_t = create_matrix(col, row); // matrix_a, matrix_b, matrix_a_t를 초기화하지 않고 생성만 함

    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) {return -1;} // 두 matrix 중 하나라도 생성되지 않았을 경우 오류

    do{
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch(command) {
        case 'z': case 'Z':
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);
            fill_data(matrix_b, row, col); // 각 matrix를 초기화
            break;
        case 'p': case 'P':
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col); // 각 matrix를 출력
            break;
        case 'a': case 'A':
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);
            break;
        case 's': case 'S':
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
            break;
        case 't': case 'T':
            printf("Transpose matrix_a \n");
            printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row); // 전치행렬이기 때문에 행과 열을 반대로 입력
            print_matrix(matrix_a_t, col, row);
            break;
        case 'm': case 'M':
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col); 
            break;
        case 'q': case 'Q':
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col); // 프로그램 종료 후 사용했던 모든 배열 해제
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    }while(command != 'q' && command != 'Q');

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
    /* check pre conditions */
    if(row <= 0 || col <=0) 
    {
        printf("Check the sizes of row and col!\n");
        return NULL;
    }

    int k;
    int **matrix; // 행렬의 이중 포인터 생성
    matrix = (int**)malloc(sizeof(int*)*row); // 동적메모리 할당을 사용하여 행렬의 row 생성
    
    for(k=0 ; k<row ; k++)
    {
        matrix[k] = (int*)malloc(sizeof(int)*col); // col을 생성
    }

    /* check post conditions */
    if(matrix == NULL) 
    {
        /* proper actions for unexpected conditions */
        printf("Matrix is not created.\nThere is error.");
    }
    
    return matrix;

}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
    /* check pre conditions */
    if(row <= 0 || col <=0) 
    {
        printf("Check the sizes of row and col!\n");
        return NULL;
    }

    int i, j;
    
    for(i=0 ; i<row ; i++)
    {
        for(j=0 ; j<col ; j++)
        {
            printf("%4d", matrix[i][j]); // for문을 통해 각 요소들을 출력
        }
        
        printf("\n"); // 열이 한 줄 끝날때마다 아래줄로 내림
    }

    if(matrix == NULL) 
    {
        /* proper actions for unexpected conditions */
        printf("Matrix is not created.\nThere is error.");
    }

    return 1;

}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{
    /* check pre conditions */
    if(row <= 0 || col <=0) 
    {
        printf("Check the sizes of row and col!\n");
        return NULL;
    }

    int i;

    for(i=0; i<row ; i++)
    {
        free(matrix[i]); // 각 열들을 해제함
    }
    
    free(matrix); // 동적 메모리 할당을 통해 총 두번 선언했으므로 한 번 더 해제 해줘야 함

    if(matrix == NULL) 
    {
        /* proper actions for unexpected conditions */
        printf("Matrix is not created.\nThere is error.");
    }

    return 1;
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{
    /* check pre conditions */
    if(row <= 0 || col <=0) 
    {
        printf("Check the sizes of row and col!\n");
        return NULL;
    }

    int i, j;
    
    for(i=0; i<row; i++)
    {
        for(j=0 ; j<col ; j++) // 이중 for문을 통해 각 배열의 요소들에 접근
        {
            matrix[i][j] = rand()%20; // 행렬의 성분값의 범위가 0~19 이기 때문에 rand()%20으로 설정함
        }
    }

    /* check post conditions */
    if(matrix == NULL) 
    {
        /* proper actions for unexpected conditions */
        printf("Matrix is not created.\nThere is error.");
    }

    return matrix;
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    /* check pre conditions */
    if(row <= 0 || col <=0) 
    {
        printf("Check the sizes of row and col!\n");
        return NULL;
    }

    int** matrix_sum = create_matrix(row, col); // 행렬의 합을 저장할 새로운 행렬 생성
    int i, j;

    for(i=0 ; i<row ; i++)
    {
        for(j=0 ; j<col ; j++)
        {
            matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j]; // 행렬의 합 저장
        }
    }

    print_matrix(matrix_sum, row, col);

    /* check post conditions */
    if(matrix_a == NULL || matrix_b == NULL) 
    {
        /* proper actions for unexpected conditions */
        printf("Matrix is not created.\nThere is error.");
    }

    free_matrix(matrix_sum, row, col); // 사용이 끝난 후 행렬의 합을 저장한 배열 해제

    return 1;
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    /* check pre conditions */
    if(row <= 0 || col <=0) 
    {
        printf("Check the sizes of row and col!\n");
        return NULL;
    }

    int** matrix_sub = create_matrix(row, col); // 행렬의 차를 저장할 새로운 행렬 생성
    int i, j;

    for(i=0 ; i<row ; i++)
    {
        for(j=0 ; j<col ; j++)
        {
            matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j]; // 행렬의 차 저장
        }
    }

    print_matrix(matrix_sub, row, col);

    /* check post conditions */
    if(matrix_a == NULL || matrix_b == NULL) 
    {
        /* proper actions for unexpected conditions */
        printf("Matrix is not created.\nThere is error.");
    }

    free_matrix(matrix_sub, row, col); // 사용이 끝난 후 행렬의 차를 저장한 배열 해제

    return 1;
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
    /* check pre conditions */
    if(row <= 0 || col <=0) 
    {
        printf("Check the sizes of row and col!\n");
        return NULL;
    }

    int i, j;

    for(i=0 ; i<row ; i++)
    {
        for(j=0 ; j<col ; j++)
        {
            matrix_t[i][j] = matrix[j][i]; // 전치행렬은 행렬의 행과 열이 반대로 저장되는 것이므로 인덱스를 반대로 저장
        }
    }

    /* check post conditions */
    if( matrix == NULL || matrix_t == NULL) 
    {
        /* proper actions for unexpected conditions */
        printf("Matrix is not created.\nThere is error.");
    }

    return matrix_t;
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    /* check pre conditions */
    if(row <= 0 || col <=0) 
    {
        printf("Check the sizes of row and col!\n");
        return NULL;
    }

    int** matrix_axt = create_matrix(row, row); // matrix_a와 matrix_t의 곱을 저장할 행렬 생성
    int i, j, k;

    for(i=0 ; i<row ; i++)
    {
        for(j=0 ; j<row ; j++)
        {
            matrix_axt[i][j] = 0;

            for(k=0 ; k<col ; k++)
            {
                matrix_axt[i][j] += (matrix_a[i][k] * matrix_t[k][j]); // 행렬의 곱 연산식을 3개의 for문을 통해서 구현
            }
        }
    }

    print_matrix(matrix_axt, row, row); // row*row로 생성한 배열을 출력

    /* check post conditions */
    if(matrix_a == NULL || matrix_t == NULL) 
    {
        /* proper actions for unexpected conditions */
        printf("Matrix is not created.\nThere is error.");
    }

    free_matrix(matrix_axt, row, col); // 사용이 끝난 후 행렬의 곱을 저장했던 배열 해제

    return 1;
}
