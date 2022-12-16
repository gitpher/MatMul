#include "MatMul.h"

int main(int argc, char* argv[])
{
	int numberOfFiles = argc - 1;
	char** fileNames = &argv[1];
	int numberToPrint = numberOfFiles + 1;

	if (numberOfFiles < 2)
	{
		printf("ERROR: NOT ENOUGH INPUT FILES (YOU NEED TO GIVE AT LEAST 2 OR MORE FILES)\n");
		return 1;
	}

	FILE** openedFiles = openFiles(numberOfFiles, fileNames); 

	if (openedFiles == NULL)
	{
		printf("ERROR: INVALID FILE(S) DETECTED (MAKE SURE ALL OF YOUR FILES ARE SAFE TO READ)\n");
		closeAllFiles(numberOfFiles);
		return 1;
	}

	Matrix* matrixes = readMatrixes(numberOfFiles, fileNames, openedFiles); 
	Matrix resultMatrix = multiplyMatrixes(numberOfFiles, matrixes);
	
	if (resultMatrix.row == 0 || resultMatrix.col == 0)
	{
		printf("ERROR: MATRIXES ARE NOT MULTIPLIABLE (YOU MIGHT WANT TO CHECK FILE %s)\n", resultMatrix.name);
		freeAllMatrixes(matrixes, &resultMatrix);
		closeAllFiles(numberOfFiles);
		return 1;
	}

	printMatrixes(numberToPrint, matrixes, &resultMatrix);

	freeAllMatrixes(matrixes, &resultMatrix);
	closeAllFiles(numberOfFiles);
	return 0;
}