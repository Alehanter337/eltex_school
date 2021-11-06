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
            int num = 1;
            matrix[i][j] = 1;
            if (i == 0 & j < 2)
            { 
                matrix[i][j] = 0;
            }           
            if (i == 1 & j == 0)
            {
                matrix[i][j] = 0;
            }
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

    return 0;
}
