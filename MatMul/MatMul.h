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

void validateNumberOfFiles(int numberOfFiles);
char** extractFiles(int numberOfFiles, char** argv);
Matrix* createMatrixes(int numberOfFiles, char** files);
FILE** openFiles(int numberOfFiles, char** files);
void validateFiles(FILE* fp);
Matrix multiplyMatrixes(int numberOfFiles, Matrix* matrixes);
void initializeMatrixArrToZero(int numberOfElements, Matrix* matrix);
bool isMatrixMultipliable(Matrix* matrix1, Matrix* matrix2);
void printMatrixes(int numberToPrint, Matrix* matrixes, Matrix resultMatrix);
void printMatrix(Matrix* matrix);

void closeAllFiles();


// 나중에 2개 이상의 파일을 읽어들이지 않으면 에러 내는 것 추가
// 나중에 bool isValidFiles() , bool isMatrixMultipliable() 추가
// 나중에 모든 메모리 할당 해제하고 파일 닫아주는 함수 추가 void freeAll() void closeAll()