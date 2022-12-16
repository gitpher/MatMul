#include "MatMul.h"

int main(int argc, char* argv[])
{
	int numberOfFiles = argc - 1;
	int numberToPrint = numberOfFiles + 1;

	if (numberOfFiles < 2)
	{
		printf("ERROR: NOT ENOUGH INPUT FILES (YOU NEED TO GIVE AT LEAST 2 OR MORE FILES)\n");
		return 1;
	}

	char** files = extractFiles(numberOfFiles, argv);
	Matrix* matrixes = readMatrixes(numberOfFiles, files);
	Matrix resultMatrix = multiplyMatrixes(numberOfFiles, matrixes);
	validateResultMatrix(&resultMatrix);
	printMatrixes(numberToPrint, matrixes, &resultMatrix);

	freeAllMatrixes(matrixes, &resultMatrix);
	closeAllFiles(numberOfFiles);
	return 0;
}