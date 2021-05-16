/**
 * @file matrix_addition.c
 * @author Navid Shamszadeh
 * @brief Implementation of serial addition algorithms in C.
 * @date 2021-05-13
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../printMatrix.h"

/**
 * @brief Serially adds matrices matrix_A and matrix_B and stores the result in matrix_C
 * 
 * @param N number of rows 
 * @param M number of columns
 * @param matrix_A First matrix summand
 * @param matrix_B Second matrix summand
 * @param matrix_C Matrix to store the sum of matrix_A and matrix_B.
 */
void matrixAddSerial(int N, int M, long int **matrix_A, long int **matrix_B, long int **matrix_C) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            matrix_C[i][j] = matrix_A[i][j] + matrix_B[i][j];
        }
    }
}

/**
 * @brief Serially adds matrices matrix_A and matrix_B and stores the result in matrix_C.
 * @details The input matrices are strided arrays, i.e., they are allocated as 1-dimensional NxM sized arrays indexed by A[i][j] = A[j + N * i]
 * @param N Number of rows 
 * @param M Number of columns 
 * @param matrix_A First matrix summand
 * @param matrix_B Second matrix summand
 * @param matrix_C Matrix to store the sum of matrix_A and matrix_B
 */
void matrixAddSerialStrided(int N, int M, long int *matrix_A, long int *matrix_B, long int *matrix_C) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            matrix_C[j + M * i] = matrix_A[j + M * i] + matrix_B[j + M * i];
        }
    }
}

int main(int argc, char* argv[]) {
    int N = atoi(argv[1]);
    int M = atoi(argv[2]);
    srandom(time(NULL));

    // allocate memory for the non strided matrices
    long int **A = (long int **)malloc(N * sizeof(long int *));
    long int **B = (long int **)malloc(N * sizeof(long int *));
    long int **C = (long int **)malloc(N * sizeof(long int *));

    A[0] = (long int *)malloc(N * M * sizeof(long int));
    B[0] = (long int *)malloc(N * M * sizeof(long int));
    C[0] = (long int *)malloc(N * M * sizeof(long int));
    
    for (int i = 1; i < N; i++) {
        A[i] = A[0] + i * M;
        B[i] = B[0] + i * M;
        C[i] = C[0] + i * M;
    }

    // fill the summand matrices with random integers
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            A[i][j] = random() % 1000;
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            B[i][j] = random() % 1000;
        }
    }

    // printing matrices for debugging purposes
    // printMatrix(N, M, A);
    // printf("\n");
    // printMatrix(N, M, B);
    // printf("\n");

    // declare timer variables
    clock_t start, end;
    double cpu_time_used1, cpu_time_used2;

    // time the execution of serial matrix sum
    start = clock();
    matrixAddSerial(N, M, A, B, C);
    end = clock();
    cpu_time_used1 = (double)(end - start) / CLOCKS_PER_SEC;

    // allocate memory for the strided matrices
    long int *A_strided = (long int *)malloc(N * M * sizeof(long int));
    long int *B_strided = (long int *)malloc(N * M * sizeof(long int));
    long int *C_strided = (long int *)malloc(N * M * sizeof(long int));

    // copy the data from the original summand arrays to the strided arrays
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            A_strided[j + M * i] = A[i][j];
            B_strided[j + M * i] = B[i][j];
        }
    }

    // printing strided matrices for debugging purposes
    // printMatrixStrided(N, M, A_strided);
    // printf("\n");
    // printMatrixStrided(N, M, B_strided);
    // printf("\n\n");
    
    // time the execution of serial matrix strided sum
    start = clock();
    matrixAddSerialStrided(N, M, A_strided, B_strided, C_strided);
    end = clock();
    cpu_time_used2 = (double)(end - start) / CLOCKS_PER_SEC;

    // printf sum matrices for debugging purposes
    // printMatrix(N, M, C);
    // printf("\n");
    // printMatrixStrided(N, M, C_strided);
    // printf("\n");

    // output the result
    printf("matrixAddSerial: %e \t matrixAddSerialStrided: %e.\n", cpu_time_used1, cpu_time_used2);
    // verify the results
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (C[i][j] != C_strided[j + M * i]) {
                fprintf(stderr, "Error: C[%d][%d] = %ld != C_strided[%d + %d * %d] = %ld!\n", i, j, C[i][j], j, N, i, C_strided[j + M * i]);
                free(A[0]);
                free(A);
                free(B[0]);
                free(B);
                free(A_strided);
                free(B_strided);
                free(C[0]);
                free(C);
                free(C_strided);
                exit(-1);
            }
        }
    }

    free(A[0]);
    free(A);
    free(B[0]);
    free(B);
    free(A_strided);
    free(B_strided);
    free(C[0]);
    free(C);
    free(C_strided);
    return 0;
}