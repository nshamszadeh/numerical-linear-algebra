/**
 * @file matrix_addition_parallel.c
 * @author Navid Shamszadeh
 * @brief Implementation of parallel matrix addition algorithms using open-mpi.
 * @date 2021-05-14
 */

#include <stdio.h>
#include <stdlib.h>
#include <openmpi-x86_64/mpi.h>

/**
 * @brief Adds matrices matrix_A and matrix_B in parallel and stores the result in matrix_C
 * @param N Number of rows 
 * @param M Number of columns
 * @param matrix_A First matrix summand
 * @param matrix_B Second matrix summand
 * @param matrix_C Matrix to store the sum of matrix_A and matrix_B
 */
void matrixAddParallel(int N, int M, long int **matrix_A, long int **matrix_B, long int **matrix_C) {

}

/**
 * @brief Adds matrices matrix_A and matrix_B in parallel and stores the result in matrix_C.
 * @details The input matrices are strided arrays, i.e., they are allocated as 1-dimensional NxM sized arrays indexed by A[i][j] = A[j + N * i]
 * @param N Number of rows
 * @param M Number of columns
 * @param matrix_A First matrix summand
 * @param matrix_B Second matrix summand
 * @param matrix_C Matrix to store the sum of matrix_A and matrix_B
 */
void matrixAddParallelStrided(int N, int M, long int *matrix_A, long int *matrix_B, long int *matrix_C) {

}

int main(int argc, char* argv[]) {
    
    return 0;
}