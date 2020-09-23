#include <iostream>
#include <chrono>
#include <random>
#include <stdlib.h>
#include <math.h>

typedef struct Position
{
	int iX;
	int iY;
} Pos;

class Rectangle
{
private:
	Pos pStart;
	Pos pEnd;
	int iMove;
public:
	Rectangle();
	void Print(int);
	void Move();
	Pos StartPos();
	Pos EndPos();
	~Rectangle();
};

Rectangle::Rectangle()
{
	std::random_device rRandom;
	std::mt19937 mGen(rRandom());
	std::uniform_int_distribution<int> uDis(0, 500);

	Rectangle::pStart.iX = uDis(mGen);
	Rectangle::pStart.iY = uDis(mGen);

	do
	{
		Rectangle::pEnd.iX = uDis(mGen) + Rectangle::pStart.iX;
		Rectangle::pEnd.iY = uDis(mGen) + Rectangle::pStart.iY;
	} while (Rectangle::pEnd.iX > 500 || Rectangle::pEnd.iY > 500 || Rectangle::pStart.iX == Rectangle::pEnd.iX || Rectangle::pStart.iY == Rectangle::pEnd.iY);

	Rectangle::iMove = 50;
}
Rectangle::~Rectangle()
{

}

void Rectangle::Print(int iNumber)
{
	std::cout << iNumber << "�� �簢�� : (" << Rectangle::pStart.iX << ", " << Rectangle::pStart.iY << "), (" << Rectangle::pEnd.iX << ", " << Rectangle::pEnd.iY << ")" << std::endl;
}

void Rectangle::Move()
{
	char cCommand;

	std::cout << std::endl << "Command : ";
	std::cin >> cCommand;

	switch (cCommand)
	{
	case 'W': case 'w':
	{
		if (Rectangle::pStart.iY - Rectangle::iMove < 0)
		{
			std::cout << "������ ��ǥ�� ����Ƿ� �̵����� �ʽ��ϴ�." << std::endl;
		}
		else
		{
			Rectangle::pStart.iY -= Rectangle::iMove;
			Rectangle::pEnd.iY -= Rectangle::iMove;
		}

		break;
	}
	case 'A': case 'a':
	{
		if (Rectangle::pStart.iX - Rectangle::iMove < 0)
		{
			std::cout << "������ ��ǥ�� ����Ƿ� �̵����� �ʽ��ϴ�." << std::endl;
		}
		else
		{
			Rectangle::pStart.iX -= Rectangle::iMove;
			Rectangle::pEnd.iX -= Rectangle::iMove;
		}

		break;
	}
	case 'S': case 's':
	{
		if (Rectangle::pEnd.iY + Rectangle::iMove > 500)
		{
			std::cout << "������ ��ǥ�� ����Ƿ� �̵����� �ʽ��ϴ�." << std::endl;
		}
		else
		{
			Rectangle::pStart.iY += Rectangle::iMove;
			Rectangle::pEnd.iY += Rectangle::iMove;
		}

		break;
	}
	case 'D': case 'd':
	{
		if (Rectangle::pEnd.iX + Rectangle::iMove > 500)
		{
			std::cout << "������ ��ǥ�� ����Ƿ� �̵����� �ʽ��ϴ�." << std::endl;
		}
		else
		{
			Rectangle::pStart.iX += Rectangle::iMove;
			Rectangle::pEnd.iX +=Rectangle::iMove;
		}

		break;
	}
	case 'C': case 'c':
	{
		system("cls");
		break;
	}
	default:
	{
		std::cout << "�߸��� Ű�� �Է��Ͽ����ϴ�." << std::endl << "�ٽ� �Է��� �ֽʽÿ�." << std::endl;
		system("pause");
		system("cls");
		break;
	}
	}

	std::cout << std::endl;
}

Pos Rectangle::StartPos()
{
	return Rectangle::pStart;
}

Pos Rectangle::EndPos()
{
	return Rectangle::pEnd;
}

void crash(Pos pR1StartPos, Pos pR1EndPos, Pos pR2StartPos, Pos pR2EndPos)
{
	//1�� �簢���� 2�� �簢������ �� �����ʿ� �ִ� ���
	if (pR1StartPos.iX > pR2EndPos.iX)
	{
		//1�� �簢���� 2�� �簢������ �� �Ʒ��� �ִ� ���
		if (pR1StartPos.iY > pR2EndPos.iY)
		{
			if (pR2EndPos.iX > pR1StartPos.iX && pR2EndPos.iY > pR1StartPos.iY)
				std::cout << "1�� �簢���� 2�� �簢���� ���� �浹�մϴ�." << std::endl;
		}
		//2�� �簢���� 1�� �簢������ �� �Ʒ��� �ִ� ���
		else if (pR2StartPos.iY > pR1EndPos.iY)
		{
			if (pR2EndPos.iX - pR1StartPos.iX > 0 && pR1EndPos.iY - pR2StartPos.iY > 0)
				std::cout << "1�� �簢���� 2�� �簢���� ���� �浹�մϴ�." << std::endl;
		}
	}
	//2�� �簢���� 1�� �簢������ �� �����ʿ� �ִ� ���
	else if (pR2StartPos.iX > pR1EndPos.iX)
	{
		//1�� �簢���� 2�� �簢������ �� �Ʒ��� �ִ� ���
		if (pR1StartPos.iY > pR2EndPos.iY)
		{
			if (pR2StartPos.iX > pR1EndPos.iX && pR2StartPos.iY > pR1EndPos.iY)
				std::cout << "1�� �簢���� 2�� �簢���� ���� �浹�մϴ�." << std::endl;
		}
		//2�� �簢���� 1�� �簢������ �� �Ʒ��� �ִ� ���
		else if (pR2StartPos.iY > pR1EndPos.iY)
		{
			if (pR2StartPos.iX > pR1EndPos.iX && pR1StartPos.iY > pR2EndPos.iY)
				std::cout << "1�� �簢���� 2�� �簢���� ���� �浹�մϴ�." << std::endl;
		}
	}
}

int main()
{
	Rectangle rRect1;
	Rectangle rRect2;
	Pos pR1StartPos = {};
	Pos pR1EndPos = {};
	Pos pR2StartPos = {};
	Pos pR2EndPos = {};

	while (true)
	{
		pR1StartPos = rRect1.StartPos();
		pR1EndPos = rRect1.EndPos();
		pR2StartPos = rRect2.StartPos();
		pR2EndPos = rRect2.EndPos();
		crash(pR1StartPos, pR1EndPos, pR2StartPos, pR2EndPos);
		rRect1.Print(1);
		rRect2.Print(2);
		rRect2.Move();
	}
}