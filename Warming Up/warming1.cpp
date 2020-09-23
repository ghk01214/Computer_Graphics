#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <math.h>
#include <chrono>

//��� Ŭ����
class Matrix
{
private:
	int iMatrix1[4][4];							//2���� ��� �� ù ��° ����� ���� ������ �ִ� 2���� �迭
	int iMatrix2[4][4];							//2���� ��� �� �� ��° ����� ���� ������ �ִ� 2���� �迭
	int iResult[4][4];							//2���� ����� ���� ��� ����� ���� ������ �ִ� 2���� �迭
	int iDeterminant;							//�� ����� ��Ľ��� ��
	bool bTranspose;							//����� ��ġ ���θ� Ȯ���ϴ� �� ���
	bool bTransform;							//3x3 ����� 4x4 ��ķ��� ��ȯ ���θ� Ȯ���ϴ� �� ���
public:
	Matrix();									//Ŭ���� ������
	void Initialize();							//����� �ʱ�ȭ�ϴ� �Լ�
	void Add();									//����� ������ �����ϴ� �Լ�
	void Subtract();							//����� ������ �����ϴ� �Լ�
	void Multiply();							//����� ������ �����ϴ� �Լ�
	void PrintArithmetic(int);					//����� ��Ģ���� �� �� ����� ����ϴ� �Լ�
	void PrintDeterminant();					//����� ��Ľ� ���� ����ϴ� �Լ�
	int Determinant(int matrix[4][4], int);		//����� ��Ľ��� ���� ���ϴ� �Լ�
	void Transpose();							//����� ��ġ ����� ���ϴ� �Լ�
	void Transform();							//3x3 ����� 4x4 ��ķ� ��ȯ�ϴ� �Լ�
	~Matrix();
};

//����� ��Ģ���� ������ enumȭ
enum eArithmetic
{
	None, Add, Subtract, Multiply
};

//����� ��� ������ enumȭ
enum ePrint
{
	Non, Matrix1, Matrix2, Result
};

char PrintMenu();
void ExecuteMenu(Matrix, char, bool*);

int main()
{
	Matrix mMatrix;
	char cMenu;						//�޴� ������ ��Ÿ���� ������ ����
	bool bEnd = false;				//���α׷� ���� ���θ� �����ϴ� �� ���

	//mMatrix.Initialize();

	//���α׷��� �����ϱ� �������� ����� ���������� �����Ѵ�
	while (!bEnd)
	{
		//�޴� ���
		cMenu = PrintMenu();
		//�޴� ����
		ExecuteMenu(mMatrix, cMenu, &bEnd);
	}
}

//Ŭ���� ������
Matrix::Matrix()
{
	Matrix::Initialize();
}

//Ŭ���� �Ҹ���
Matrix::~Matrix()
{

}

//Ŭ������ �ʱ�ȭ�ϴ� Ŭ���� ��� �Լ� ������
void Matrix::Initialize()
{
	//0 �Ǵ� 1�� �������� �ʱ�ȭ�ϱ� ���� �����Լ� �̿�
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			//������ ����� 4��, 4���� 0���� �ʱ�ȭ
			if (i == 3 || j == 3)
			{
				Matrix::iMatrix1[i][j] = 0;
				Matrix::iMatrix2[i][j] = 0;
			}
			//������ ��Ŀ� 0 �Ǵ� 1�� �������� �ʱ�ȭ
			else
			{
				Matrix::iMatrix1[i][j] = (int)pow(rand() % 100, 3) % 2;
				Matrix::iMatrix2[i][j] = (int)pow(rand() % 100, 3) % 2;
			}

			//����� ���� ��� ����� 0���� �ʱ�ȭ
			Matrix::iResult[i][j] = 0;
		}
	}

	Matrix::iDeterminant = 0;

	//����� ���� ��ȯ ���δ� false�� �ʱ�ȭ
	Matrix::bTranspose = false;
	Matrix::bTransform = false;
}

//����� ������ ���ϴ� Ŭ���� ��� �Լ� ������
void Matrix::Add()
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			Matrix::iResult[i][j] = Matrix::iMatrix1[i][j] + Matrix::iMatrix2[i][j];
		}
	}

	//����� ��Ģ������ �������� ����
	Matrix::PrintArithmetic(eArithmetic::Add);
}

//����� ������ ���ϴ� Ŭ���� ��� �Լ� ������
void Matrix::Subtract()
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			Matrix::iResult[i][j] = Matrix::iMatrix1[i][j] - Matrix::iMatrix2[i][j];
		}
	}

	//����� ��Ģ������ �������� ����
	Matrix::PrintArithmetic(eArithmetic::Subtract);
}

//����� ������ ���ϴ� Ŭ���� ��� �Լ� ������
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

	//����� ��Ģ������ �������� ����
	Matrix::PrintArithmetic(eArithmetic::Multiply);
}

//����� ��Ģ���� �� �� ����� ����ϴ� Ŭ���� ��� �Լ� ������
void Matrix::PrintArithmetic(int iType)
{
	int iSize = 3;

	if (Matrix::bTransform == true)
		iSize = 4;

	std::cout << std::endl;

	for (int i = 0; i < iSize; ++i)
	{
		//ù ��° ��� ���
		std::cout << " ��";

		for (int j = 0; j < iSize; ++j)
		{
			std::cout << "  " << Matrix::iMatrix1[i][j];
		}

		std::cout << " ��";

		//���� ��ȣ�� ���� ������ ���� ���
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

		//�� ��° ��� ���
		std::cout << " ��";

		for (int j = 0; j < iSize; ++j)
		{
			std::cout << "  " << Matrix::iMatrix2[i][j];
		}

		std::cout << " ��";

		//��ȣ ���
		if (i == 1)
			std::cout << "  =";
		else
			std::cout << "\t";

		//���� ��� ��� ���
		std::cout << " ��";

		for (int j = 0; j < iSize; ++j)
		{
			std::cout << "  " << Matrix::iResult[i][j];
		}

		std::cout << " ��" << std::endl;
	}

	std::cout << std::endl;

	system("pause");
	system("cls");
}

//����� ��Ľ��� ����ϴ� Ŭ���� ��� �Լ� ������
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
		//ù ��° ��� ���
		std::cout << " ��";

		for (int j = 0; j < iTimes; ++j)
		{
			std::cout << "  " << iTempMatrix[i][j];
		}

		std::cout << " ��";

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
		//ù ��° ��� ���
		std::cout << " ��";

		for (int j = 0; j < iTimes; ++j)
		{
			std::cout << "  " << iTempMatrix[i][j];
		}

		std::cout << " ��";

		if (i == 1)
		{
			std::cout << " = " << Determinant(iTempMatrix, iTimes);
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;
}

//����� ��Ľ��� ���ϴ� Ŭ���� ��� �Լ� ������
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

//����� ��ġ ����� ���ϴ� Ŭ���� ��� �Լ� ������
void Matrix::Transpose()
{
	//����� ��ġ��Ų��.
	Matrix::bTranspose = true;
	Matrix::PrintDeterminant();
	//��ġ��Ų ����� �� ���·� ������Ų��.
	Matrix::bTranspose = false;
}

//3x3 ����� 4x4 ��ķ� ��ȯ�ϴ� Ŭ���� ��� �Լ� ������
void Matrix::Transform()
{
	//3x3 ����� 4x4 ��ķ� ��ȯ.
	Matrix::bTransform = true;
	Matrix::iMatrix1[3][3] = 1;
	Matrix::iMatrix2[3][3] = 1;

	//��ȯ�� ����� ��Ľ� ���� ���Ѵ�.
	Matrix::PrintDeterminant();

	//4x4 ����� �ٽ� 3x3 ��ķ� ��ȯ.
	Matrix::bTransform = false;
}

//��ɾ� ���� �޴��� ����ϴ� �Լ�
char PrintMenu()
{
	while (true)
	{
		char* cMenu = new char[100];

		std::cout << "����������������������������������������������������������������������������������������������������������������������������������������������������������" << std::endl;
		std::cout << "�� a: ������ ����� ���Ѵ�" << "\t\t\t\t\t\t    ��" << std::endl;
		std::cout << "��\t\t\t\t\t\t\t\t\t    ��" << std::endl;
		std::cout << "�� s: ������ ����� ����" << "\t\t\t\t\t\t\t    ��" << std::endl;
		std::cout << "��\t\t\t\t\t\t\t\t\t    ��" << std::endl;
		std::cout << "�� m: ������ ����� ���Ѵ�" << "\t\t\t\t\t\t    ��" << std::endl;
		std::cout << "��\t\t\t\t\t\t\t\t\t    ��" << std::endl;
		std::cout << "�� d: ������ ��Ľ��� ���� ����Ѵ�" << "\t\t\t\t\t    ��" << std::endl;
		std::cout << "��\t\t\t\t\t\t\t\t\t    ��" << std::endl;
		std::cout << "�� t: ������ ����� ��ġ��Ű�� ��ġ��Ų ����� ��Ľ��� ���� ����Ѵ�" << "\t    ��" << std::endl;
		std::cout << "��\t\t\t\t\t\t\t\t\t    ��" << std::endl;
		std::cout << "�� h: 3x3 ����� 4x4 ��ķ� ��ȯ��Ű�� ��ȯ��Ų ����� ��Ľ��� ���� ����Ѵ�" << "��" << std::endl;
		std::cout << "��\t\t\t\t\t\t\t\t\t    ��" << std::endl;
		std::cout << "�� r: ������ ����� ���� �����ϰ� �ʱ�ȭ��Ų��" << "\t\t\t\t    ��" << std::endl;
		std::cout << "��\t\t\t\t\t\t\t\t\t    ��" << std::endl;
		std::cout << "�� q: ���α׷� ����" << "\t\t\t\t\t\t\t    ��" << std::endl;
		std::cout << "����������������������������������������������������������������������������������������������������������������������������������������������������������" << std::endl << std::endl;

		std::cout << "������ ��ɾ �Է� : ";
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
				std::cout << std::endl << "�߸��� ��ɸ� �Է��߽��ϴ�." << std::endl << "����� �ٽ� �Է��� �ֽʽÿ�." << std::endl << std::endl;
				system("pause");
				system("cls");
				break;
			}
			}
		}
		else
		{
			std::cout << std::endl << "�߸��� ��ɸ� �Է��߽��ϴ�." << std::endl << "����� �ٽ� �Է��� �ֽʽÿ�." << std::endl << std::endl;
			system("pause");
			system("cls");
		}

		delete[] cMenu;
	}
}

//���õ� ��ɾ �����ϴ� �Լ�
void ExecuteMenu(Matrix mMatrix, char cMenu, bool* bEnd)
{
	switch (cMenu)
	{
	//����� ������ ����
	case 'a':
	{
		mMatrix.Add();
		break;
	}
	//����� ������ ����
	case 's':
	{
		mMatrix.Subtract();
		break;
	}
	//����� ������ ����
	case 'm':
	{
		mMatrix.Multiply();
		break;
	}
	//����� ��Ľ��� ���� ����
	case 'd':
	{
		mMatrix.PrintDeterminant();
		break;
	}
	//����� ��ġ ��İ� ��Ľ��� ���� ����
	case 't':
	{
		mMatrix.Transpose();
		break;
	}
	//3x3 ����� 4x4 ��ķ� ��ȯ�ϰ� ��Ľ��� ���� ����
	case 'h':
	{
		mMatrix.Transform();
		break;
	}
	//����� ���� ���� �����ϰ� �ʱ�ȭ
	case 'r':
	{
		mMatrix.Initialize();
		std::cout << "�ʱ�ȭ �Ϸ�" << std::endl;
		system("pause");
		system("cls");
		break;
	}
	//���α׷� ����
	case 'q':
	{
		*bEnd = true;
		break;
	}
	default:
		break;
	}
}