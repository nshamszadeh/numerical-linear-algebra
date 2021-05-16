#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printMatrix(int N, int M, long int **A) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%ld ", A[i][j]);
        }
        printf("\n");
    }
}

void matrixAdd(int N, int M, long int **A, long int **B, long int **C) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

int main(int argc, char* argv[]) {
    int N = atoi(argv[1]);
    int M = atoi(argv[2]);
    
    srandom(time(NULL));

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

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            A[i][j] = random() % 10;
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            B[i][j] = random() % 10;
        }
    }

    printMatrix(N, M, A);
    printf("\n");
    printMatrix(N, M, B);
    printf("\n");
    matrixAdd(N, M, A, B, C);
    printMatrix(N, M, C);


    free(A[0]);
    free(B[0]);
    free(C[0]);
    free(A);
    free(B);
    free(C);

    return 0;
}