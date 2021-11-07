#include "stdio.h"

void PrintMatrix()
{
    int N = 3;
    int a[N][N];
    int num = 1;

    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++)

        {   
            a[i][j] = num++;   
            printf("%d",a[i][j]);
        }
        printf("\n");
    }

}

void PrintReverseArray()
{
    int N = 5;
    int array[] = {1, 2, 3, 4, 5};

    for (int i = 0; i < N/2; i++)
    {
        int temp = array[i];
        array[i] = array[N - i - 1];
        array[N - i - 1] = temp;
    }

    for (int i = 0; i < N; i++)
    {
        printf("%d ", array[i]);
    }   

}

void TriangleMatrix()
{
    int N = 3;
    int matrix[N][N];
    
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        { 
            matrix[i][j] = 1;
        }
            for (int j = 0; j < N - i - 1; j++)
        {
            matrix[i][j] = 0;
        }
        for (int j = 0; j < N; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");

    }


}


void MatrixUlitka()
{
    int N = 5;
    int matrix[N][N];
    int num = 1;    
    
    
    for (int i = 0; i < N/2; i++)
    {
        for (int j = i; j < N - i; j++)
            matrix[i][j] = num++;

        for (int j = i + 1; j < N - i; j++)
            matrix[j][N - 1 - i] = num++;
        
        for (int j = N - 2 - i; j >= i; j--) 
            matrix[N - 1 - i][j] = num++;
        
        for (int j = N - 2 - i; j > i; j--)
            matrix[j][i] = num++;
    }
    matrix[N/2][N/2] = N*N;    
 
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
                printf("%d ", matrix[i][j]);
        }
        printf("\n");
    } 

}



int main()
{
    PrintMatrix();
    printf("\n"); 
    PrintReverseArray();
    printf("\n");
    printf("\n");
    TriangleMatrix();
    printf("\n");
    MatrixUlitka();
    return 0;
}
