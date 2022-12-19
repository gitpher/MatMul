#include "MatMul.h"

Matrix* readMatrixes(const int numberOfFiles, const char** const fileNames, const FILE** const openedFiles)
{	
	Matrix* matrixes = (Matrix*)malloc(sizeof(Matrix)*numberOfFiles);
	for (int m = 0; m < numberOfFiles; m++)
	{
		matrixes[m] = readMatrix(fileNames[m], openedFiles[m]);
	}
	return matrixes;
}

Matrix readMatrix(const char* const fileName, const FILE* const openedFile)
{
	char buf[BUFFERLENGTH] = { 0 };
	fgets(buf, sizeof(buf), openedFile);
	char* rest = NULL;
	char* token = strtok_s(buf, " ", &rest);
	int col = atoi(rest);
	int row = atoi(token);
	int numberOfElements = col * row;
	int* arr = (int*)malloc(sizeof(int) * numberOfElements);
	for (int i = 0; i < row; i++)
	{
		fgets(buf, sizeof(buf), openedFile);
		char* rest = NULL;
		char* token = strtok_s(buf, " ", &rest);
		for (int j = 0; j < col; j++)
		{
			int k = col * i + j;
			arr[k] = atoi(token);
			token = strtok_s(NULL, " ", &rest);
		}
	}
	Matrix readedMatrix = { fileName , row, col, arr };
	return readedMatrix;
}

FILE** openFiles(const int numberOfFiles, const char** const fileNames)
{
	FILE** openedFiles = (FILE**)malloc(sizeof(FILE*) * numberOfFiles);
	for (int i = 0; i < numberOfFiles; i++)
	{
		FILE* fp = NULL;
		fopen_s(&fp, fileNames[i], "r");
		if (isValidFile(fp)) 
		{
			openedFiles[i] = fp;
		}
		else
		{
			return NULL;
		}
	}
	return openedFiles;
}

bool isValidFile(const FILE* const fp)
{
	if (fp == NULL)
	{
		return false;
	}
	else
	{
		return true;
	}
}

Matrix multiplyMatrixes(const int numberOfFiles, const Matrix* const matrixes)
{
	Matrix matrixAB;
	for (int i = 0; i < numberOfFiles - 1; i++)
	{
		Matrix matrixA;
		if (i == 0)
		{
			matrixA = matrixes[i];
		}
		else
		{
			matrixA = matrixAB;
		}
		Matrix matrixB = matrixes[i + 1];

		matrixAB.name = matrixB.name;
		matrixAB.row = matrixA.row;
		matrixAB.col = matrixB.col;
		int numberOfElements = matrixAB.row * matrixAB.col;
		matrixAB.arr = (int*)malloc(sizeof(int) * numberOfElements);
		initializeMatrixArrToZero(numberOfElements, &matrixAB);

		if (isMatrixMultipliable(&matrixA, &matrixB))
		{
			multiplyMatrix(&matrixAB, &matrixA, &matrixB);
		}
		else
		{
			matrixAB.row = 0;
			matrixAB.col = 0;
			initializeMatrixArrToZero(numberOfElements, &matrixAB);
			return matrixAB;
		}
	}
	return matrixAB;
}

void multiplyMatrix(Matrix* const matrixAB, const Matrix* const matrixA, const Matrix* const matrixB)
{
	int newRow = matrixA->row;
	int newCol = matrixB->col;

	for (int m = 0; m < newRow; m++)
	{
		for (int n = 0; n < newCol; n++)
		{
			for (int k = 0; k < matrixA->col; k++)
			{
				int indexOfMatrixA = matrixA->col * m + k;
				int indexOfMatrixB = matrixB->col * k + n;
				int indexOfMatrixAB = newCol * m + n;
				matrixAB->arr[indexOfMatrixAB] += ((matrixA->arr[indexOfMatrixA]) * (matrixB->arr[indexOfMatrixB]));
			}
		}
	}
}

bool isMatrixMultipliable(const Matrix* const matrixA, const Matrix* const matrixB)
{
	if (matrixA->col == matrixB->row)
	{
		return true; 
	}
	else
	{
		return false; 
	}
}

void initializeMatrixArrToZero(const int numberOfElements, Matrix* const matrix)
{
	for (int i = 0; i < numberOfElements; i++)
	{
		matrix->arr[i] = 0;
	}
}

void printMatrixes(const int numberToPrint, const Matrix* const matrixes, Matrix* const resultMatrix)
{
	for (int i = 0; i < numberToPrint-1; i++)
	{
		Matrix matrix = matrixes[i];
		printMatrix(&matrix);
	}
	resultMatrix->name = "result";
	printMatrix(resultMatrix);
}

void printMatrix(const Matrix* const matrix)
{
	char* name = matrix->name;
	int row = matrix->row;
	int col = matrix->col;
	int* arr = matrix->arr;

	printf("%s = \n", name);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			int k = col * i + j;
			printf("%i ", arr[k]);
		}
		printf("\n");
	}
}

void freeAllMatrixes(const Matrix* const matrixes, const Matrix* const resultMatrix)
{
	int numberOfMatrixes = _msize(matrixes) / sizeof(matrixes[0]);
	for (int i = 0; i < numberOfMatrixes; i++)
	{
		free(matrixes[i].arr);
	}
	free(resultMatrix->arr);
	free(matrixes);
}

void closeAllFiles(const int numberOfFiles)
{
	int numberOfFilesClosed = _fcloseall();
	printf("*** %i OUT OF %i FILES CLOSED ***\n", numberOfFilesClosed, numberOfFiles);
}