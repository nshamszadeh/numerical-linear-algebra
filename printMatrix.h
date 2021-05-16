/**
 * @file printMatrix.c
 * @author Navid Shamszadeh
 * @brief Helper functions to print 2D arrays.
 * @date 2021-05-14
 */
#include <stdio.h>

void printMatrix(int N, int M, long int **A) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%ld ", A[i][j]);
        }
        printf("\n");
    }
}

void printMatrixStrided(int N, int M, long int *A) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%ld ", A[j + M * i]);
        }
        printf("\n");
    }
}