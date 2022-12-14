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
5-1. 행렬곱 알고리즘 계산						(성공)
5-2. 행렬곱한 결과 출력						(성공)
6. 파일 닫기 w/ _fcloseall()					(성공)
7. 리팩터링 및 추가 요구사항 반영
  -1. Matrix에 init 없애고 수정하기
  -2. 차원 동적 배열을 선언하고 해제 꼭 하기
  -3. 명령행 인자로 텍스트 파일 몇 개가 들어오든 다 되게 하기
      - 고려사항: _fcloseall() , 뒤 2 없애기 배열 길이로 바꾸기
*/

/*
새로운 요구사항 반영
	
0. const int nof = argc - 1; // nof stands for "number of files"
1-1. 명령행 인자 ( nof 개의 파일 배열 순회하면서 파일 포인터 담기)
1-2. 파일 배열 안 파일 중에 NULL이 있는지 없는지 검사 (fvalidation)
2. 파일 배열마다 첫 줄 read한 뒤 matmulable한지 검사 ( nof 개의 파일 배열을 순회하면서 첫 줄을 검사 ) // 그러나, 어떻게? 알고리즘이 있나?
   >> int m, k를 files[0] 번째 m, k로 초기화
   >> for(int i=1, i<nof; i++)
   >> >> i번째 파일 k, n 추출
   >> >> k와 k가 같지 않으면 break; 
   >> >> k와 k가 같으면
   >> >> >> k에 n을 대입 (k = n)
3. 통과시, 파일 배열 돌면서 rewind(파일 포인터);   !!!! 이때 filename을 배열로 어떻게든 구해야 함
   >> nof만큼 파일 배열 돌면서 첫번째 줄에 적힌 행과 열 길이 matrix안에 넣어서 Matrix[]에 저장 후 반환
   통과하지 못할시, 빈 Matrix[] 반환

   typedef struct Matrix
   {
		char* name = " ";
		int row = 0;
		int col = 0;
   } Matrix;

4. matrices[i]와 files[i]의 인덱스가 같다는 것을 이용하여 2차원 동적 배열 ( filename[][] ) 을 만들어서 arr[]에 담고 반환 // 근데 이게 가능한가? --- 원하는 형식으로 데이터 가공
5. for (int i=0, j=1; i<arr[]-1의 길이; i++, j++) // A와 B비교랑 똑같음
	>> 2차원 동적 배열들을 
	for (int m = 0; m < matrices[i].row; m++)
	{
		for (int n = 0; n < matrices[j].col; n++)
		{
			for (int k = 0; k < matrices[i].col; k++)
			{
				AB[m][n] += A[m][k] * B[k][n];
			}
		}
	}
5. arr[] matrix들 출력
6. AB[][] 출력
7. 파일 닫기
*/

int rt(int n) 
{
	return n;
}

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
	// 이거 대신 FILE* 배열 만들기
	FILE* fpA, * fpB;
	fopen_s(&fpA, argv[1], "r");
	fopen_s(&fpB, argv[2], "r");

	// argc - 1 만큼 반복
	printf("%i\n", argc);


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

	const int Am = matrix.Am; 
	const int Ak = matrix.Ak; 
	const int Bk = matrix.Bk;
	const int Bn = matrix.Bn;

	// 임의로 만든 배열
	// 2차원 동적 배열 만들기
	int A[100][100] = {0}; // Am x Ak
	int B[100][100] = {0}; // Bk x Bn
	int AB[100][100] = {0}; // Am x Bn

	//
	char buf[512] = { 0 };
	printf("%s = \n", "A"); // 파일명으로 바꿔야 함
	for (int i = 0; i < Am; i++) // matrix.row
	{
		fgets(buf, sizeof(buf), fpA); 
		printf("%s", buf);
		char* rst = NULL;
		char* tok = strtok_s(buf, " ", &rst);
		for (int j = 0; j < Ak; j++) // matrix.col
		{
			A[i][j] = atoi(tok);
			tok = strtok_s(NULL, " ", &rst);
		}
	}
	memset(buf, 0, sizeof(buf));
	//
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
	for (int m = 0; m < Am; m++)
	{
		for (int n = 0; n < Bn; n++)
		{
			for (int k = 0; k < Ak; k++) 
			{
				AB[m][n] += A[m][k] * B[k][n]; 
			}
		}
	}
	puts("\nAB = ");
	for (int i = 0; i < Am; i++)
	{
		for (int j = 0; j < Bn; j++)
		{
			printf("%i ", AB[i][j]);
		}
		printf("\n");
	}	

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
// _fcloseall() 이 어떤 함수인지 왜 썼는지 해명
// fopen_s 작동방식 해명 그리고 fopen과 비교
// strtok()_s 쓰는 방식 해명
// const의 위치 왜 포인터로 넘겼는지 해명 // const int*와 int* const의 차이 그리고 const int와 int const의 차이
// 왜 Matrix struct를 썼는지 해명
