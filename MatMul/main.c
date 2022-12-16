#include "MatMul.h"

int main(int argc, char* argv[])
{
	int numberOfFiles = argc - 1;
	int numberToPrint = numberOfFiles + 1;

	if (numberOfFiles < 2)
	{
		printf("ERROR: NOT ENOUGH INPUT FILES (YOU NEED TO GIVE AT LEAST 2 OR MORE FILES)\n");
		return 1; // 나중에 할당 해제 추가
	}

	char** files = extractFiles(numberOfFiles, argv);
	Matrix* matrixes = createMatrixes(numberOfFiles, files);
	Matrix resultMatrix = multiplyMatrixes(numberOfFiles, matrixes);

	if (resultMatrix.row == 0 && resultMatrix.col == 0)
	{
		printf("ERROR: MATRIXES ARE NOT MULTIPLIABLE (YOU MIGHT WANT TO CHECK FILE %s)\n", resultMatrix.name);
		return 1; // 나중에 할당 해제 추가
	}

	printMatrixes(numberToPrint, matrixes, resultMatrix);

	// TODO: free everything that is declared by malloc
	// TODO: close all files
	return 0;
}