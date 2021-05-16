/**
 * @file matrix_transpose.c
 * @author Navid Shamszadeh
 * @brief Matrix transpose operation
 * @date 2021-05-15
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../printMatrix.h"


void printArray(int size, long int *arr) {
    printf("[");
    for (int i = 0; i < size; i++) {
        if (i != size - 1)
            printf("%ld, ", arr[i]);
        else
            printf("%ld]\n", arr[i]);
    }
}

/**
 * @brief Computes the transpose of matrix A. If A is not square (N != M) then it stores the result in A_t, otherwise the operation is done in-place.
 * 
 * @param N Number of rows of A
 * @param M Number of columns of A
 * @param A Matrix
 * @param A_t Matrix to store the transpose of A if A is not square
 */
void matrixTranspose(int N, int M, long int **A, long int **A_t) {
    if (N == M) {
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < M; j++) {
                // swap A[i][j] with A[j][i]
                long int temp = A[i][j];
                A[i][j] = A[j][i];
                A[j][i] = temp;
            }
        }
    }else {
        // store the transpose in A_t
        for (int i = 0; i < N; i++) {
            for (int j = i; j < M; j++) {
                // store A[i][j] in A_t[j][i]
                // store A[j][i] in A_t[i][j]
                A_t[i][j] = A[j][i];
                A_t[j][i] = A[i][j];
            }
        }
    }
}

/**
 * @brief Matrix transpose on strided matrix. Since A is strided, we can still perform the transpose in-place if N != M
 * 
 * @param N Number of rows of A
 * @param M Number of columns of A
 * @param A Input matrix 
 */
void matrixTransposeStrided(int N, int M, long int *A) {
    for (int k = 0; k < N * M; k++) {
        printArray(N * M, A);
        int idx = k;
        do // calculate index in the original array
        {
            idx = (idx % N) * M + (idx / N); // what the hell is this 
        } while (idx < k);
        // swap A[k] with A[idx]
        long int temp = A[k];
        A[k] = A[idx];
        A[idx] = temp;
    }
}

int main(int argc, char* argv[]) {
    int N = atoi(argv[1]);
    int M = atoi(argv[2]);

    srandom(time(NULL));

    long int *A = (long int *)malloc(N * M * sizeof(long int));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            A[j + M * i] = (long int)(j + M * i);
        }
    }

    printf("A:\n");
    printMatrixStrided(N, M, A);
    printf("\n");
    matrixTransposeStrided(N, M, A);
    printf("A_T:\n");
    printMatrixStrided(M, N, A);
    printf("\n");

    free(A);

    return 0;
}