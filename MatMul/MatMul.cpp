#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


/*
1. 명령행 인자								(성공)
2. .exe 파일									(성공)
3. 파일 단순 읽기 w/ fopen_s					(성공)
4-1. 파일 자체 유효성 검사					(성공)
4-2. 파일 내용 원하는 형태로 가공				(성공)
4-3. 파일 내용, 행열곱 가능 여부 유효성 검사	(성공)
5. 행렬곱 알고리즘
6. 파일 닫기 w/ _fcloseall()					(성공)
7. 리팩터링
*/

typedef struct Matrix
{
	int Am = 0;
	int Ak = 0;
	int Bk = 0;
	int Bn = 0;
	bool init = false;
} Matrix;
bool fvalidation(FILE* fpA, FILE* fpB);
Matrix matmulable(FILE* fpA, FILE* fpB);
void closeFiles();

int main(int argc, char* argv[])
{
	FILE* fpA, * fpB;
	fopen_s(&fpA, argv[1], "r");
	fopen_s(&fpB, argv[2], "r");

	if (!fvalidation(fpA, fpB))
	{
		closeFiles();
		return 1;
	}
	Matrix matrix = matmulable(fpA, fpB);
	if (matrix.init == false)
	{
		closeFiles();
		return 1;
	}

	int Am = matrix.Am; // Am 라인 만큼 읽고 [Am][]
	int Ak = matrix.Ak; // 한 라인당 Ak 번 만큼 넣고 [][Ak]
	int Bk = matrix.Bk;
	int Bn = matrix.Bn;

	// 임의로 만든 배열
	int A[2][2];
	int B[2][2] = {0};

	//왜 내가 가져온 matrix로 배열을 만들 수 없을까? 왜 상수가 아니면 배열의 크기를 초기화할 수 없을까?

	char buf[512] = { 0 };
	puts("A = ");
	for (int i = 0; i < Am; i++)
	{
		fgets(buf, sizeof(buf), fpA); 
		printf("%s", buf);
		char* rst = NULL;
		char* tok = strtok_s(buf, " ", &rst);
		for (int j = 0; j < Ak; j++)
		{
			A[i][j] = atoi(tok);
			tok = strtok_s(NULL, " ", &rst);
		}
	}
	memset(buf, 0, sizeof(buf));
	puts("\nB = ");
	for (int i = 0; i < Bk; i++)
	{
		fgets(buf, sizeof(buf), fpB);
		printf("%s", buf);
		char* rst = NULL;
		char* tok = strtok_s(buf, " ", &rst);
		for (int j = 0; j < Bn; j++)
		{
			B[i][j] = atoi(tok);
			tok = strtok_s(NULL, " ", &rst);
		}
	}
	// A와 B배열 출력
	printf("\n%i\n", A[0][0]);
	printf("%i\n", A[0][1]);
	printf("%i\n", A[1][0]);
	printf("%i\n", A[1][1]);
	printf("%i\n", B[0][0]);
	printf("%i\n", B[0][1]);
	printf("%i\n", B[1][0]);
	printf("%i\n", B[1][1]);
	puts("\nAB = ");
	// TODO: AB 계산
	// TODO: AB 출력

	closeFiles();
	return 0;
}

bool fvalidation(FILE* const fpA, FILE* const fpB)
{
	if ((fpA == NULL) && (fpB == NULL))
	{
		puts("\n\tERROR: FAILED TO OPEN BOTH FILE A.txt AND B.txt\n");
		return false;
	} 
	else if (fpA == NULL)
	{
		puts("\n\tERROR: FAILED TO OPEN FILE A.txt\n");
		return false;
	} 
	else if (fpB == NULL)
	{
		puts("\n\tERROR: FAILD TO OPEN FILE B.txt\n");
		return false;
	}
	else
	{
		return true;
	}
}

Matrix matmulable(FILE* const fpA, FILE* const fpB)
{
	char bufA[512] = { 0 };
	char bufB[512] = { 0 };
	fgets(bufA, sizeof(bufA), fpA);
	fgets(bufB, sizeof(bufB), fpB);

	char* tmpAk = NULL;
	char* tmpAm = strtok_s(bufA, " ", &tmpAk);
	char* tmpBn = NULL;
	char* tmpBk = strtok_s(bufB, " ", &tmpBn);
	
	int Ak = atoi(tmpAk);
	int Bk = atoi(tmpBk);

	Matrix matrix;

	if (Ak == Bk)
	{
		matrix.Am = atoi(tmpAm);
		matrix.Ak = Ak;
		matrix.Bk = Bk;
		matrix.Bn = atoi(tmpBn);
		matrix.init = true;
		return matrix;
	}
	else
	{
		printf("\n\tERROR: A AND B MATRIXES ARE NOT MULTIPLIABLE\n");
		return matrix;
	}
}

void closeFiles()
{
	printf("\n\t%i OUT OF %i FILE(S) CLOSED\n", _fcloseall(), 2);
}

// 왜 [512]만큼의 크기인지 해명
// _fcloseall() 이 어떤 함수인지 