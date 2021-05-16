CC = gcc
MPICC = mpicc
CFLAGS = -g -Wall -o

matrixAddSerial:
	$(CC) $(CFLAGS) serial_matrix_add matrix_addition.c

matrixAddParallel:
	$(MPICC) $(CFLAGS) parallel_matrix_add matrix_addition_parallel.c

matrixMultiplySerial:
	$(CC) $(CFLAGS) serial_matrix_multiply matrix_multiply.c

matrixMultiplyParallel:
	$(MPICC) $(CFLAGS) parallel_matrix_multiply matrix_multiply_parallel.c 

matrixVectorMultiplySerial:
	$(CC) $(CFLAGS) serial_matrix_vector_multiply matrix_vector_multiply.c

matrixVectorMultiplyParallel:
	$(MPICC) $(CFLAGS) parallel_matrix_vector_multiply parallel_matrix_vector_multiply.c

matrixTransposeSerial:
	$(CC) $(CFLAGS) serial_matrix_transpose matrix_transpose.c

matrixTransposeParallel:
	$(MPICC) $(CFLAGS) parallel_matrix_transpose parallel_matrix_transpose.c

clean:
	rm -r serial_matrix_add parallel_matrix_add serial_matrix_multiply parallel_matrix_multiply \ 
		serial_matrix_vector_multiply parallel_matrix_vector_multiply serial_matrix_transpose parallel_matrix_transpose \
	

