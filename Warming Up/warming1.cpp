#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <math.h>
#include <chrono>

//행렬 클래스
class Matrix
{
private:
	int iMatrix1[4][4];							//2개의 행렬 중 첫 번째 행렬의 값을 가지고 있는 2차원 배열
	int iMatrix2[4][4];							//2개의 행렬 중 두 번째 행렬의 값을 가지고 있는 2차원 배열
	int iResult[4][4];							//2개의 행렬의 연산 결과 행렬의 값을 가지고 있는 2차원 배열
	int iDeterminant;							//각 행렬의 행렬식의 값
	bool bTranspose;							//행렬의 전치 여부를 확인하는 불 대수
	bool bTransform;							//3x3 행렬을 4x4 행렬로의 변환 여부를 확인하는 불 대수
public:
	Matrix();									//클래스 생성자
	void Initialize();							//행렬을 초기화하는 함수
	void Add();									//행렬의 덧셈을 실행하는 함수
	void Subtract();							//행렬의 뺄셈을 실행하는 함수
	void Multiply();							//행렬의 곱셈을 실행하는 함수
	void PrintArithmetic(int);					//행렬의 사칙연산 식 및 결과를 출력하는 함수
	void PrintDeterminant();					//행렬의 행렬식 값을 출력하는 함수
	int Determinant(int matrix[4][4], int);		//행렬의 행렬식의 값을 구하는 함수
	void Transpose();							//행렬의 전치 행렬을 구하는 함수
	void Transform();							//3x3 행렬을 4x4 행렬로 변환하는 함수
	~Matrix();
};

//행렬의 사칙연산 종류를 enum화
enum eArithmetic
{
	None, Add, Subtract, Multiply
};

//행렬의 출력 종류를 enum화
enum ePrint
{
	Non, Matrix1, Matrix2, Result
};

char PrintMenu();
void ExecuteMenu(Matrix, char, bool*);

int main()
{
	Matrix mMatrix;
	char cMenu;						//메뉴 종류를 나타내는 문자형 변수
	bool bEnd = false;				//프로그램 종료 여부를 결정하는 불 대수

	//mMatrix.Initialize();

	//프로그램을 종료하기 전까지는 명령을 연속적으로 수행한다
	while (!bEnd)
	{
		//메뉴 출력
		cMenu = PrintMenu();
		//메뉴 실행
		ExecuteMenu(mMatrix, cMenu, &bEnd);
	}
}

//클래스 생성자
Matrix::Matrix()
{
	Matrix::Initialize();
}

//클래스 소멸자
Matrix::~Matrix()
{

}

//클래스를 초기화하는 클래스 멤버 함수 구현부
void Matrix::Initialize()
{
	//0 또는 1을 랜덤으로 초기화하기 위한 랜덤함수 이용
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			//각각의 행렬의 4행, 4열은 0으로 초기화
			if (i == 3 || j == 3)
			{
				Matrix::iMatrix1[i][j] = 0;
				Matrix::iMatrix2[i][j] = 0;
			}
			//각각의 행렬에 0 또는 1을 랜덤으로 초기화
			else
			{
				Matrix::iMatrix1[i][j] = (int)pow(rand() % 100, 3) % 2;
				Matrix::iMatrix2[i][j] = (int)pow(rand() % 100, 3) % 2;
			}

			//행렬의 연산 결과 행렬은 0으로 초기화
			Matrix::iResult[i][j] = 0;
		}
	}

	Matrix::iDeterminant = 0;

	//행렬의 형태 변환 여부는 false로 초기화
	Matrix::bTranspose = false;
	Matrix::bTransform = false;
}

//행렬의 덧셈을 구하는 클래스 멤버 함수 구현부
void Matrix::Add()
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			Matrix::iResult[i][j] = Matrix::iMatrix1[i][j] + Matrix::iMatrix2[i][j];
		}
	}

	//행렬의 사칙연산을 덧셈으로 설정
	Matrix::PrintArithmetic(eArithmetic::Add);
}

//행렬의 뺄셈을 구하는 클래스 멤버 함수 구현부
void Matrix::Subtract()
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			Matrix::iResult[i][j] = Matrix::iMatrix1[i][j] - Matrix::iMatrix2[i][j];
		}
	}

	//행렬의 사칙연산을 뺄셈으로 설정
	Matrix::PrintArithmetic(eArithmetic::Subtract);
}

//행렬의 곱셈을 구하는 클래스 멤버 함수 구현부
void Matrix::Multiply()
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			for (int k = 0; k < 3; ++k)
			{
				Matrix::iResult[i][j] += Matrix::iMatrix1[i][k] * Matrix::iMatrix2[k][j];
			}
		}
	}

	//행렬의 사칙연산을 곱셈으로 설정
	Matrix::PrintArithmetic(eArithmetic::Multiply);
}

//행렬의 사칙연산 식 및 결과를 출력하는 클래스 멤버 함수 구현부
void Matrix::PrintArithmetic(int iType)
{
	int iSize = 3;

	if (Matrix::bTransform == true)
		iSize = 4;

	std::cout << std::endl;

	for (int i = 0; i < iSize; ++i)
	{
		//첫 번째 행렬 출력
		std::cout << " ┃";

		for (int j = 0; j < iSize; ++j)
		{
			std::cout << "  " << Matrix::iMatrix1[i][j];
		}

		std::cout << " ┃";

		//연산 기호를 연산 종류에 맞춰 출력
		if (i == 1)
		{
			switch (iType)
			{
			case eArithmetic::Add:
			{
				std::cout << "  +";
				break;
			}
			case eArithmetic::Subtract:
			{
				std::cout << "  -";
				break;
			}
			case eArithmetic::Multiply:
			{
				std::cout << "  x";
				break;
			}
			default:
			{
				std::cout << "\t";
				break;
			}
			}
		}
		else
		{
			std::cout << "\t";
		}

		//두 번째 행렬 출력
		std::cout << " ┃";

		for (int j = 0; j < iSize; ++j)
		{
			std::cout << "  " << Matrix::iMatrix2[i][j];
		}

		std::cout << " ┃";

		//등호 출력
		if (i == 1)
			std::cout << "  =";
		else
			std::cout << "\t";

		//연산 결과 행렬 출력
		std::cout << " ┃";

		for (int j = 0; j < iSize; ++j)
		{
			std::cout << "  " << Matrix::iResult[i][j];
		}

		std::cout << " ┃" << std::endl;
	}

	std::cout << std::endl;

	system("pause");
	system("cls");
}

//행령의 행렬식을 출력하는 클래스 멤버 함수 구현부
void Matrix::PrintDeterminant()
{
	int iTimes = 3;
	int iTempMatrix[4][4];

	if (Matrix::bTransform)
		iTimes = 4;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (Matrix::bTranspose)
				iTempMatrix[i][j] = Matrix::iMatrix1[j][i];
			else
				iTempMatrix[i][j] = Matrix::iMatrix1[i][j];
		}
	}

	std::cout << std::endl;

	for (int i = 0; i < iTimes; ++i)
	{
		//첫 번째 행렬 출력
		std::cout << " ┃";

		for (int j = 0; j < iTimes; ++j)
		{
			std::cout << "  " << iTempMatrix[i][j];
		}

		std::cout << " ┃";

		if (i == 1)
		{
			std::cout << " = " << Determinant(iTempMatrix, iTimes);
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (Matrix::bTranspose)
				iTempMatrix[i][j] = Matrix::iMatrix2[j][i];
			else
				iTempMatrix[i][j] = Matrix::iMatrix2[i][j];
		}
	}

	for (int i = 0; i < iTimes; ++i)
	{
		//첫 번째 행렬 출력
		std::cout << " ┃";

		for (int j = 0; j < iTimes; ++j)
		{
			std::cout << "  " << iTempMatrix[i][j];
		}

		std::cout << " ┃";

		if (i == 1)
		{
			std::cout << " = " << Determinant(iTempMatrix, iTimes);
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;
}

//행렬의 행렬식을 구하는 클래스 멤버 함수 구현부
int Matrix::Determinant(int iTempMatrix[4][4], int iTimes)
{
	int iTemp[4][4];

	if (iTimes == 2)
	{
		return ((iTempMatrix[0][0] * iTempMatrix[1][1]) - (iTempMatrix[1][0] * iTempMatrix[0][1]));
	}
	else
	{
		for (int i = 0; i < iTimes; ++i)
		{
			int subi = 0;

			for (int j = 1; j < iTimes; ++j)
			{
				int subj = 0;

				for (int k = 0; k < iTimes; ++k)
				{
					if (i == k)
						continue;

					iTemp[subi][subj] = iTempMatrix[j][k];
					++subj;
				}

				++subi;
			}

			Matrix::iDeterminant += (pow(-1, i) * iTempMatrix[0][i] * Matrix::Determinant(iTemp, iTimes - 1));
		}
	}

	return Matrix::iDeterminant;
}

//행렬의 전치 행렬을 구하는 클래스 멤버 함수 구현부
void Matrix::Transpose()
{
	//행렬을 전치시킨다.
	Matrix::bTranspose = true;
	Matrix::PrintDeterminant();
	//전치시킨 행렬을 원 상태로 복구시킨다.
	Matrix::bTranspose = false;
}

//3x3 행렬을 4x4 행렬로 변환하는 클래스 멤버 함수 구현부
void Matrix::Transform()
{
	//3x3 행렬을 4x4 행렬로 변환.
	Matrix::bTransform = true;
	Matrix::iMatrix1[3][3] = 1;
	Matrix::iMatrix2[3][3] = 1;

	//변환한 행렬의 행렬식 값을 구한다.
	Matrix::PrintDeterminant();

	//4x4 행렬을 다시 3x3 행렬로 변환.
	Matrix::bTransform = false;
}

//명령어 선택 메뉴를 출력하는 함수
char PrintMenu()
{
	while (true)
	{
		char* cMenu = new char[100];

		std::cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << std::endl;
		std::cout << "┃ a: 각각의 행렬을 더한다" << "\t\t\t\t\t\t    ┃" << std::endl;
		std::cout << "┃\t\t\t\t\t\t\t\t\t    ┃" << std::endl;
		std::cout << "┃ s: 각각의 행렬을 뺀다" << "\t\t\t\t\t\t\t    ┃" << std::endl;
		std::cout << "┃\t\t\t\t\t\t\t\t\t    ┃" << std::endl;
		std::cout << "┃ m: 각각의 행렬을 곱한다" << "\t\t\t\t\t\t    ┃" << std::endl;
		std::cout << "┃\t\t\t\t\t\t\t\t\t    ┃" << std::endl;
		std::cout << "┃ d: 각각의 행렬식의 값을 출력한다" << "\t\t\t\t\t    ┃" << std::endl;
		std::cout << "┃\t\t\t\t\t\t\t\t\t    ┃" << std::endl;
		std::cout << "┃ t: 각각의 행렬을 전치시키고 전치시킨 행렬의 행렬식의 값을 출력한다" << "\t    ┃" << std::endl;
		std::cout << "┃\t\t\t\t\t\t\t\t\t    ┃" << std::endl;
		std::cout << "┃ h: 3x3 행렬을 4x4 행렬로 변환시키고 변환시킨 행렬의 행렬식의 값을 출력한다" << "┃" << std::endl;
		std::cout << "┃\t\t\t\t\t\t\t\t\t    ┃" << std::endl;
		std::cout << "┃ r: 각각의 행렬을 새로 랜덤하게 초기화시킨다" << "\t\t\t\t    ┃" << std::endl;
		std::cout << "┃\t\t\t\t\t\t\t\t\t    ┃" << std::endl;
		std::cout << "┃ q: 프로그램 종료" << "\t\t\t\t\t\t\t    ┃" << std::endl;
		std::cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << std::endl << std::endl;

		std::cout << "실행할 명령어를 입력 : ";
		std::cin >> cMenu;

		if (strlen(cMenu) == 1)
		{
			switch (*cMenu)
			{
			case 'a': case 's': case 'm': case 'd': case 't': case 'h': case 'r': case 'q':
			{
				return *cMenu;
				break;
			}
			default:
			{
				std::cout << std::endl << "잘못된 명령를 입력했습니다." << std::endl << "명령을 다시 입력해 주십시오." << std::endl << std::endl;
				system("pause");
				system("cls");
				break;
			}
			}
		}
		else
		{
			std::cout << std::endl << "잘못된 명령를 입력했습니다." << std::endl << "명령을 다시 입력해 주십시오." << std::endl << std::endl;
			system("pause");
			system("cls");
		}

		delete[] cMenu;
	}
}

//선택된 명령어를 실행하는 함수
void ExecuteMenu(Matrix mMatrix, char cMenu, bool* bEnd)
{
	switch (cMenu)
	{
	//행렬의 덧셈을 실행
	case 'a':
	{
		mMatrix.Add();
		break;
	}
	//행렬의 뺄셈을 실행
	case 's':
	{
		mMatrix.Subtract();
		break;
	}
	//행렬의 곱셈을 실행
	case 'm':
	{
		mMatrix.Multiply();
		break;
	}
	//행렬의 행렬식의 값을 연산
	case 'd':
	{
		mMatrix.PrintDeterminant();
		break;
	}
	//행렬의 전치 행렬과 행렬식의 값을 연산
	case 't':
	{
		mMatrix.Transpose();
		break;
	}
	//3x3 행렬을 4x4 행렬로 변환하고 행렬식의 값을 연산
	case 'h':
	{
		mMatrix.Transform();
		break;
	}
	//행렬의 값을 새로 랜덤하게 초기화
	case 'r':
	{
		mMatrix.Initialize();
		std::cout << "초기화 완료" << std::endl;
		system("pause");
		system("cls");
		break;
	}
	//프로그램 종료
	case 'q':
	{
		*bEnd = true;
		break;
	}
	default:
		break;
	}
}