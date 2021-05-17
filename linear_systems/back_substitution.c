/**
 * @file back_substitution.c
 * @author Navid Shamszadeh
 * @brief Back substitution algorithm for solving linear N x N systems.
 * @date 2021-05-16
 */

#include <stdio.h>
#include <stdlib.h>
#include "../printMatrix.h"

/**
 * @brief Back substitution algorithm for solving a linear system.
 * 
 * @param N Dimensions of U and x and b
 * @param U Upper triangular matrix allocated as a 1-dimensional array
 * @param b Input vector
 * @param x Output vector
 */
void backSubstitution(const int N, float *U, float *b, float *x) {
    x[N - 1] = b[N - 1] / U[N*N - 1];
    for (int i = N - 2; i >= 0; i--) {
        x[i] = b[i];
        for (int j = i + 1; j < N; i++) {
            x[i] -= U[j + N * i] * x[j];
        }
        x[i] /= U[i + N * i];
    }
}