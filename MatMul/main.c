#include "MatMul.h"

int main(int argc, char* argv[])
{
	int numberOfFiles = argc - 1;
	int numberToPrint = numberOfFiles + 1;
	char** files = extractFiles(numberOfFiles, argv);
	Matrix* matrixes = createMatrixes(numberOfFiles, files);

	// 확인용
	for (int i = 0; i < numberOfFiles; i++)
	{
		printf("matrixes[i]: %s %i %i = %i %i %i %i\n", matrixes[i].name, matrixes[i].row, matrixes[i].col, matrixes[i].arr[0], matrixes[i].arr[1], matrixes[i].arr[2], matrixes[i].arr[3]);
	}

	Matrix resultMatrix = multiplyMatrixes(numberOfFiles, matrixes);

	if (resultMatrix.row == 0 && resultMatrix.col == 0)
	{
		printf("ERROR: MATRIXES ARE NOT MULTIPLIABLE (YOU MIGHT WANT TO CHECK FILE %s)\n", resultMatrix.name);
		return 1;
	}

	// 확인용
	printf("resultMatrix: %s %i %i = %i %i %i %i\n", resultMatrix.name, resultMatrix.row, resultMatrix.col, resultMatrix.arr[0], resultMatrix.arr[1], resultMatrix.arr[2], resultMatrix.arr[3]);

	printMatrixes(numberToPrint, matrixes, resultMatrix);

	// TODO: free everything that is declared by malloc
	// TODO: close all files
	return 0;
}