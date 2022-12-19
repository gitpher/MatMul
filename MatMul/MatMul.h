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

Matrix* readMatrixes(const int numberOfFiles, const char** const files, const FILE** const openedFiles);
Matrix readMatrix(const char* const file, const FILE* const openedFile);
FILE** openFiles(const int numberOfFiles, const char** const files);
bool isValidFile(const FILE* const fp);
Matrix multiplyMatrixes(const int numberOfFiles, const Matrix* const matrixes);
void multiplyMatrix(Matrix* const matrixAB, const Matrix* const matrixA, const Matrix* const matrixB);
void initializeMatrixArrToZero(const int numberOfElements, Matrix* const matrix);
bool isMatrixMultipliable(const Matrix* const matrix1, const Matrix* const matrix2);
void printMatrixes(const int numberToPrint, const Matrix* const matrixes, Matrix* const resultMatrix);
void printMatrix(const Matrix* const matrix);
void freeAllMatrixes(const Matrix* const matrixes, const Matrix* const resultMatrix);
void closeAllFiles(const int numberOfFiles);