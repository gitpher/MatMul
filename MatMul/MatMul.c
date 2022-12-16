#include "MatMul.h"

void validateNumberOfFiles(int numberOfFiles)
{
	if (numberOfFiles < 2)
	{
		printf("ERROR: NOT ENOUGH INPUT FILES (YOU NEED TO GIVE AT LEAST 2 OR MORE FILES)\n");
		exit(1);
	}
}

char** extractFiles(int numberOfFiles, char** argv)
{
	char** files = (char**)malloc(_msize(argv) * numberOfFiles);
	for (int i = 0; i < numberOfFiles; i++)
	{
		files[i] = argv[i + 1];
	}
	return files;
}

Matrix* createMatrixes(int numberOfFiles, char** files)
{	
	FILE** openedFiles = openFiles(numberOfFiles, files);
	Matrix* matrixes = (Matrix*)malloc(sizeof(Matrix)*numberOfFiles);
	for (int m = 0; m < numberOfFiles; m++)
	{
		char buf[512] = { 0 };
		fgets(buf, sizeof(buf), openedFiles[m]);
		char* rest = NULL;
		char* token = strtok_s(buf, " ", &rest);
		int col = atoi(rest); 
		int row = atoi(token); 
		int numberOfElements = col * row;  
		int* arr = (int*)malloc(sizeof(int) * numberOfElements);
		for (int i = 0; i < row; i++) 
		{
			fgets(buf, sizeof(buf), openedFiles[m]);
			char* rest = NULL;
			char* token = strtok_s(buf, " ", &rest);
			for (int j = 0; j < col; j++) 
			{
				int k = col * i + j;
				arr[k] = atoi(token);
				token = strtok_s(NULL, " ", &rest);
			}
		}
		Matrix matrix = { files[m], row, col, arr }; 
		matrixes[m] = matrix;
	}
	return matrixes;
}

FILE** openFiles(int numberOfFiles, char** files)
{
	FILE** openedFiles = (FILE**)malloc(sizeof(FILE*) * numberOfFiles);
	for (int i = 0; i < numberOfFiles; i++)
	{
		FILE* fp = NULL;
		fopen_s(&fp, files[i], "r");
		validateFile(fp);
		openedFiles[i] = fp;
	}
	return openedFiles;
}

void validateFile(FILE* fp)
{
	if (fp == NULL)
	{
		printf("ERROR: INVALID FILE(S) DETECTED (MAKE SURE ALL OF YOUR FILES ARE SAFE TO READ)");
		exit(1);
	}
}

Matrix multiplyMatrixes(int numberOfFiles, Matrix* matrixes)
{
	Matrix matrix;
	for (int i = 0; i < numberOfFiles - 1; i++)
	{
		Matrix matrixA;
		if (i == 0)
		{
			matrixA = matrixes[i];
		}
		else
		{
			matrixA = matrix;
		}
		Matrix matrixB = matrixes[i + 1];

		char* newName = matrixB.name;
		int newRow = matrixA.row;
		int newCol = matrixB.col;
		int numberOfElements = newRow * newCol;
		int* newArr = (int*)malloc(sizeof(int) * numberOfElements);

		matrix.name = newName;
		matrix.row = newRow;
		matrix.col = newCol;
		matrix.arr = newArr;
		initializeMatrixArrToZero(numberOfElements, &matrix);

		if (isMatrixMultipliable(&matrixA, &matrixB))
		{
			for (int m = 0; m < newRow; m++)
			{
				for (int n = 0; n < newCol; n++)
				{
					for (int k = 0; k < matrixA.col; k++)
					{
						int indexOfMatrixA = matrixA.col * m + k;		
						int indexOfMatrixB = matrixB.col * k + n;			
						int indexOfNewMatrix = newCol * m + n;
						matrix.arr[indexOfNewMatrix] += ((matrixA.arr[indexOfMatrixA]) * (matrixB.arr[indexOfMatrixB]));
					}
				}
			}
		}
		else
		{
			matrix.row = 0;
			matrix.col = 0;
			initializeMatrixArrToZero(numberOfElements, &matrix);
			return matrix;
		}
	}
	return matrix;
}

bool isMatrixMultipliable(Matrix* matrixA, Matrix* matrixB)
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

void validateResultMatrix(Matrix* resultMatrix)
{
	if (resultMatrix->row == 0 && resultMatrix->col == 0)
	{
		printf("ERROR: MATRIXES ARE NOT MULTIPLIABLE (YOU MIGHT WANT TO CHECK FILE %s)\n", resultMatrix->name);
		exit(1);
	}
}

void initializeMatrixArrToZero(int numberOfElements, Matrix* matrix)
{
	for (int i = 0; i < numberOfElements; i++)
	{
		matrix->arr[i] = 0;
	}
}

void printMatrixes(int numberToPrint, Matrix* matrixes, Matrix* resultMatrix)
{
	for (int i = 0; i < numberToPrint-1; i++)
	{
		Matrix matrix = matrixes[i];
		printMatrix(&matrix);
	}
	resultMatrix->name = "result";
	printMatrix(resultMatrix);
}

void printMatrix(Matrix* matrix)
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

void freeAllMatrixes(Matrix* matrixes, Matrix* resultMatrix)
{
	int numberOfMatrixes = _msize(matrixes);
	for (int i = 0; i < numberOfMatrixes; i++)
	{
		free(matrixes[i].arr);
		free(matrixes);
	}
}

void closeAllFiles()
{
}




