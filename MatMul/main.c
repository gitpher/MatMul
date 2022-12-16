#include "MatMul.h"

int main(int argc, char* argv[])
{
	int numberOfFiles = argc - 1;
	int numberToPrint = numberOfFiles + 1;

	validateNumberOfFiles(numberOfFiles);
	char** files = extractFiles(numberOfFiles, argv);
	Matrix* matrixes = createMatrixes(numberOfFiles, files);
	Matrix resultMatrix = multiplyMatrixes(numberOfFiles, matrixes);
	validateResultMatrix(&resultMatrix);
	printMatrixes(numberToPrint, matrixes, resultMatrix);

	// TODO: free everything that is declared by malloc
	// TODO: close all files
	return 0;
}