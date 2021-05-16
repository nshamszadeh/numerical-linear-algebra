/**
 * @file matrix_multiply.c
 * @author Navid Shamszadeh
 * @brief Serial matrix multiplication functions.
 * @date 2021-05-14
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../printMatrix.h"

/**
 * @brief Matrix multiplication of matrices A and B, result stored in matrix C
 * 
 * @param N Number of rows for matrix A
 * @param M Number of columns for matrix A and rows for matrix B
 * @param K Number of columns for matrix B
 * @param matrix_A Should be of size N x M 
 * @param matrix_B Should be of size M x K
 * @param matrix_C Should be of size  N x K
 */
void matrixMultiply(int N, int M, int K, long int **matrix_A, long int **matrix_B, long int **matrix_C) {
    // C[i][j] == A[i][] * B[][j] (dot product of row i of A with column j of B)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < K; j++) {
            matrix_C[i][j] = 0;
            for (int k = 0; k < M; k++) {
                matrix_C[i][j] += matrix_A[i][k] * matrix_B[k][j];
            }
        }
    }
}

/**
 * @brief Matrix multiplication of strided matrices (one dimensional arrays of size N x M and M x K)
 * 
 * @param N Number of rows for matrix A
 * @param M Number of columns for matrix A and rows for matrix B
 * @param K Number of columns for matrix B
 * @param matrix_A Should be a one-dimensional array of size N x M
 * @param matrix_B Should be a one-dimensional array of size M x K
 * @param matrix_C Should be a one-dimensional array of size N x K
 */
void matrixMultiplyStrided(int N, int M, int K, long int *matrix_A, long int *matrix_B, long int *matrix_C) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < K; j++) {
            matrix_C[j + K * i] = 0;
            for (int k = 0; k < M; k++) {
                matrix_C[j + K * i] += matrix_A[k + i * M] * matrix_B[j + k * K]; 
            }
        }
    }
}

int main(int argc, char* argv[]) {
    // gather the matrix dimensions from user input
    int N = atoi(argv[1]);
    int M = atoi(argv[2]);
    int K = atoi(argv[3]);

    // generate a random seed
    srandom(time(NULL));

    // allocate memory for the non strided matrices
    long int **A = (long int **)malloc(N * sizeof(long int *));
    long int **B = (long int **)malloc(M * sizeof(long int *));
    long int **C = (long int **)malloc(N * sizeof(long int *));

    A[0] = (long int *)malloc(N * M * sizeof(long int));
    B[0] = (long int *)malloc(M * K * sizeof(long int));
    C[0] = (long int *)malloc(N * K * sizeof(long int));

    for (int i = 1; i < N; i++) {
        A[i] = A[0] + i * M;
    }
    for (int i = 1; i < M; i++) {
        B[i] = B[0] + i * K;
    }
    for (int i = 1; i < N; i++) {
        C[i] = C[0] + i * K;
    }

    // fill matrices A and B with random integers before computing their product
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            A[i][j] = random() % 1000;
        }
    }
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < K; j++) {
            B[i][j] = random() % 1000;
        }
    }

    // call the matrix multiply function and time its runtime
    clock_t start = clock();
    matrixMultiply(N, M, K, A, B, C);
    clock_t end = clock();
    double cpu_time1 = (double)(end - start) / CLOCKS_PER_SEC;

    // allocate memory for the strided matrices
    long int *A_strided = (long int *)malloc(N * M * sizeof(long int));
    long int *B_strided = (long int *)malloc(M * K * sizeof(long int));
    long int *C_strided = (long int *)malloc(N * K * sizeof(long int));

    // copy the values of A and B into the strided versions
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            A_strided[j + M * i] = A[i][j];
        }
    }
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < K; j++) {
            B_strided[j + K * i] = B[i][j];
        }
    }

    // call the strided matrix multiply function and time the runtime
    start = clock();
    matrixMultiplyStrided(N, M, K, A_strided, B_strided, C_strided);
    end = clock();
    double cpu_time2 = (double)(end - start) / CLOCKS_PER_SEC;

    // compare the values of C and C_strided to make sure they are equal, if not then safely abort the program
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < K; j++) {
            if (C[i][j] != C_strided[j + i * K]) {
                fprintf(stderr, "Error: C[%d][%d] = %ld != C_strided[%d + %d * %d] = %ld!\n", i, j, C[i][j], j, K, i, C_strided[j + K * i]);
                free(A[0]);
                free(A);
                free(B[0]);
                free(B);
                free(C[0]);
                free(C);
                free(A_strided);
                free(B_strided);
                free(C_strided);
                exit(-1);
            }
        }
    }

    // print the results of the timers
    printf("matrixMultiply: %e \t matrixMultiplyStided: %e\n", cpu_time1, cpu_time2);
    
    // free all allocated memory and exit
    free(A[0]);
    free(A);
    free(B[0]);
    free(B);
    free(C[0]);
    free(C);
    free(A_strided);
    free(B_strided);
    free(C_strided);
    return 0;
}