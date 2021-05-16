/**
 * @file matrix_vector_multiply.c
 * @author Navid Shamszadeh 
 * @brief Serial matrix vector multiplication
 * @date 2021-05-15
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../printMatrix.h"

/**
 * @brief Matrix vector multiplication. 
 * 
 * @param N Number of rows of matrix A and number of rows of vector b
 * @param M Number of columns of matrix A and number of rows of vector x
 * @param A Matrix 
 * @param x Input vector.
 * @param b Output vector for the product Ax.
 */
void matrixVectorMultiply(int N, int M, long int **A, long int *x, long int *b) {
    for (int i = 0; i < N; i++) {
        b[i] = 0;
        for (int j = 0; j < M; j++) {
            b[i] += A[i][j] * x[j];
        }
    }
}

/**
 * @brief Strided matrix vector multiply.
 * 
 * @param N Number of rows of A and the number of rows of b
 * @param M Number of columns of A and the number of rows of x
 * @param A Matrix
 * @param x Input vector
 * @param b Output vector 
 */
void matrixVectorMultiplyStrided(int N, int M, long int *A, long int *x, long int *b) {
    for (int i = 0; i < N; i++) {
        b[i] = 0;
        for (int j = 0; j < M; j++) {
            b[i] += A[j + M * i] * x[j];
        }
    }
}

int main(int argc, char* argv[]) {
    int N = atoi(argv[1]);
    int M = atoi(argv[2]);

    // get a random seem
    srandom(time(NULL));

    // allocate memory for matrix and vectors
    long int **A = (long int **)malloc(N * sizeof(long int *));
    long int *x = (long int *)malloc(M * sizeof(long int));
    long int *b = (long int *)malloc(N * sizeof(long int));

    A[0] = (long int *)malloc(N * M * sizeof(long int));
    for (int i = 1; i < N; i++) {
        A[i] = A[0] + i * M;
    }

    // fill A and x with random numbers
    for (int i = 0; i < M; i++) {
        x[i] = random();
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            A[i][j] = random();
        }
    }

    // call the function and time its runtime
    clock_t start = clock();
    matrixVectorMultiply(N, M, A, x, b);
    clock_t end = clock();
    double cpu_time1 = (double)(end - start) / CLOCKS_PER_SEC;

    // allocate memory for strided matrix and its result vector
    long int *A_strided = (long int *)malloc(N * M * sizeof(long int));
    long int *b_strided = (long int *)malloc(N * sizeof(long int));

    // fill A_strided with the contents of A
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            A_strided[j + i * M] = A[i][j];
        }
    }

    // call strided matrix vector multiply function and time its runtime
    start = clock();
    matrixVectorMultiplyStrided(N, M, A_strided, x, b_strided);
    end = clock();
    double cpu_time2 = (double)(end - start) / CLOCKS_PER_SEC;

    // compare the outputs
    for (int i = 0; i < N; i++) {
        if (b[i] != b_strided[i]) {
            fprintf(stderr, "Error! b[%d] = %ld != b_strided[%d] = %ld.\n", i, b[i], i, b_strided[i]);
            free(A[0]);
            free(A);
            free(x);
            free(b);
            free(b_strided);
            exit(-1);
        }
    }

    // output the runtimes, free memory, and return
    printf("matrixVectorMultiply: %e \t matrixVectorMultiplyStrided: %e\n", cpu_time1, cpu_time2);
    free(A[0]);
    free(A);
    free(x);
    free(b);
    free(b_strided);
    return 0;
}