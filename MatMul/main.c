#include "MatMul.h"

int main(int argc, char* argv[])
{
	int numberOfFiles = argc - 1;
	int numberToPrint = numberOfFiles + 1;
	char** files = extractFiles(numberOfFiles, argv);
	Matrix* matrixes = createMatrixes(numberOfFiles, files);

	Matrix resultMatrix = multiplyMatrixes(numberOfFiles, matrixes);

	printf("the matrix: %s %i %i = %i %i %i %i\n", resultMatrix.name, resultMatrix.arr, resultMatrix.col, resultMatrix.arr[0], resultMatrix.arr[1], resultMatrix.arr[2], resultMatrix.arr[3]);

	printMatrixes(numberToPrint, matrixes, resultMatrix);

	// TODO: free everything that is declared by malloc
	// TODO: close all files
	return 0;
}