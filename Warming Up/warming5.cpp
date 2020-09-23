#include <iostream>
#include <random>
#define SIZE 5

typedef struct position
{
	int iX;
	int iY;
} Position;

class Movement
{
private:
	char cBoard[SIZE][SIZE];
	Position pPos;
	int iMove;
	int iDirection;
	bool bLeft;
	bool bRight;
	bool bUp;
	bool bDown;
public:
	Movement();
	void ChangeDirection();
	void Foodprint();
	char Return(int, int);
	~Movement();
};

enum Direction
{
	Left, Right, Up, Down
};

Movement::Movement()
{
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			Movement::cBoard[i][j] = '1';
		}
	}

	Movement::pPos = { 0, 0 };
	Movement::cBoard[pPos.iY][pPos.iX] = '0';

	Movement::iMove = 0;
	Movement::iDirection = Right;
	Movement::bLeft = false;
	Movement::bRight = false;
	Movement::bUp = false;
	Movement::bDown = false;
}

Movement::~Movement()
{

}

void Movement::Foodprint()
{
	while (Movement::cBoard[SIZE - 1][SIZE - 1] != '0')
	{
		std::random_device rRandom;
		std::mt19937 mGen(rRandom());
		std::uniform_int_distribution<int> uDis(1, 5);

		if (Movement::iMove == 0 || Movement::pPos.iX == 0 || Movement::pPos.iX == SIZE - 1 || Movement::pPos.iY == 0 || Movement::pPos.iY == SIZE - 1)
		{
			Movement::iMove = uDis(mGen);
			Movement::ChangeDirection();
		}

		for (int i = 0; i < Movement::iMove; ++i)
		{
			switch (Movement::iDirection)
			{
			case Left:
			{
				--Movement::pPos.iX;
				break;
			}
			case Right:
			{
				++Movement::pPos.iX;
				break;
			}
			case Up:
			{
				--Movement::pPos.iY;
				break;
			}
			case Down:
			{
				++Movement::pPos.iY;
				break;
			}
			default:
				break;
			}

			if (Movement::pPos.iX == 0 || Movement::pPos.iX == SIZE - 1 || Movement::pPos.iY == 0 || Movement::pPos.iY == SIZE - 1)
				break;

			--Movement::iMove;
			Movement::cBoard[Movement::pPos.iY][Movement::pPos.iX] = '0';
		}
	}
}

void Movement::ChangeDirection()
{
	std::random_device rRandom;
	std::mt19937 mGen(rRandom());
	std::uniform_int_distribution<int> uDis(0, 1);

	int iTemp = uDis(mGen);

	switch (Movement::iDirection)
	{
	case Left: case Right:
	{
		if (Movement::pPos.iY == 0)
		{
			Movement::iDirection = Down;
			Movement::bDown = true;
		}
		else if (Movement::pPos.iY == SIZE - 1)
		{
			Movement::iDirection = Up;
			Movement::bUp = true;
		}
		else
		{
			if (iTemp == 0)
			{
				Movement::iDirection = Down;
				Movement::bDown = true;
			}
			else
			{
				Movement::iDirection = Up;
				Movement::bUp = true;
			}
		}

		break;
	}
	case Up: case Down:
	{
		if (Movement::pPos.iX == 0)
		{
			Movement::iDirection = Right;
			Movement::bRight = true;
		}
		else if (Movement::pPos.iX == SIZE - 1)
		{
			Movement::iDirection = Left;
			Movement::bLeft = true;
		}
		else
		{
			if (iTemp == 0)
			{
				Movement::iDirection = Right;
				Movement::bRight = true;
			}
			else
			{
				Movement::iDirection = Left;
				Movement::bLeft = true;
			}
		}

		break;
	}
	default:
		break;
	}
}

char Movement::Return(int i, int j)
{
	return Movement::cBoard[i][j];
}

void Draw();

int main()
{
	Draw();
}

void Draw()
{
	Movement mMove;

	mMove.Foodprint();

	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			std::cout << mMove.Return(i, j) << " ";
		}

		std::cout << std::endl;
	}
}