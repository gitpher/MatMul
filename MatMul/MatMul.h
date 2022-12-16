#pragma once
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct
{
	char* name;
	int row;
	int col;
	int* arr;
} Matrix;

char** extractFiles(int numberOfFiles, char** argv);
Matrix* readMatrixes(int numberOfFiles, char** files, FILE** openedFiles);
Matrix readMatrix(char* file, FILE* openedFile, Matrix* matrix);
FILE** openFiles(int numberOfFiles, char** files);
bool isValidFile(FILE* fp);
Matrix multiplyMatrixes(int numberOfFiles, Matrix* matrixes);

// multiplyMatrix();

void initializeMatrixArrToZero(int numberOfElements, Matrix* matrix);
bool isMatrixMultipliable(Matrix* matrix1, Matrix* matrix2);
void printMatrixes(int numberToPrint, Matrix* matrixes, Matrix* resultMatrix);
void printMatrix(Matrix* matrix);
void freeAllMatrixes(Matrix* matrixes, Matrix* resultMatrix);
void closeAllFiles(int numberOfFiles);