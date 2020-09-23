#include <iostream>
#include <cstring>
#define SIZE 30

typedef struct pos
{
	int iX;
	int iY;
} Position;

class Rectangle
{
private:
	Position pLeftTop;
	Position pRightBottom;
public:
	Rectangle();
	void InputGrid(int, int, int, int);
	Position ReturnLT();
	Position ReturnRB();
	void MoveLeft();
	void MoveRight();
	void MoveTop();
	void MoveBottom();
	void ExpandToX();
	void ExpandToY();
	void ReduceToX();
	void ReduceToY();
	void Reset();
	~Rectangle();
};

Rectangle::Rectangle()
{
	Rectangle::Reset();
}

Rectangle::~Rectangle()
{

}

void Rectangle::InputGrid(int iLeft, int iTop, int iRight, int iBottom)
{
	Rectangle::pLeftTop.iX = iLeft;
	Rectangle::pLeftTop.iY = iTop;
	Rectangle::pRightBottom.iX = iRight;
	Rectangle::pRightBottom.iY = iBottom;
}

Position Rectangle::ReturnLT()
{
	return Rectangle::pLeftTop;
}

Position Rectangle::ReturnRB()
{
	return Rectangle::pRightBottom;
}

void Rectangle::MoveLeft()
{
	--Rectangle::pLeftTop.iX;
	--Rectangle::pRightBottom.iX;
}

void Rectangle::MoveRight()
{
	++Rectangle::pLeftTop.iX;
	++Rectangle::pRightBottom.iX;
}

void Rectangle::MoveTop()
{
	--Rectangle::pLeftTop.iY;
	--Rectangle::pRightBottom.iY;
}

void Rectangle::MoveBottom()
{
	++Rectangle::pLeftTop.iY;
	++Rectangle::pRightBottom.iY;
}

void Rectangle::ExpandToX()
{
	if (Rectangle::pRightBottom.iX < 30)
		++Rectangle::pRightBottom.iX;
	else
		--Rectangle::pLeftTop.iX;
}

void Rectangle::ExpandToY()
{
	if (Rectangle::pRightBottom.iY < 30)
		++Rectangle::pRightBottom.iY;
	else
		--Rectangle::pLeftTop.iY;
}

void Rectangle::ReduceToX()
{
	--Rectangle::pRightBottom.iX;
}

void Rectangle::ReduceToY()
{
	--Rectangle::pRightBottom.iY;
}

void Rectangle::Reset()
{
	Rectangle::pLeftTop = {};
	Rectangle::pRightBottom = {};
}

enum Command
{
	None, Reset, Quit
};

void Input();
void Draw(Position, Position);
int Interaction(Rectangle*);

int main()
{
	Input();
}

void Input()
{
	Rectangle rRectangle;
	char cInput[20];

	while (true)
	{
		std::cout << "사각형의 좌표 입력 : ";
		std::cin.getline(cInput, 20, '\n');

		char* cTok = strtok(cInput, " \n\t");
		int iGrid[4] = {};
		int iTemp = 0;

		while (cTok != NULL)
		{
			iGrid[iTemp++] = atoi(cTok);
			cTok = strtok(NULL, " \n\t");
		}

		rRectangle.InputGrid(iGrid[0], iGrid[1], iGrid[2], iGrid[3]);

		int iQuit;

		while (true)
		{
			Position LeftTop = rRectangle.ReturnLT();
			Position RightBottom = rRectangle.ReturnRB();
			Draw(LeftTop, RightBottom);
			iQuit = Interaction(&rRectangle);

			if (iQuit != None)
				break;
		}

		if (iQuit == Quit)
			break;
		else
		{
			while (getchar() != '\n');
			system("cls");
		}
	}
}

void Draw(Position LeftTop, Position RightBottom)
{
	char cBoard[SIZE][SIZE];

	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			cBoard[i][j] = '.';
		}
	}

	for (int i = LeftTop.iY - 1; i < RightBottom.iY; ++i)
	{
		for (int j = LeftTop.iX - 1; j < RightBottom.iX; ++j)
		{
			cBoard[i][j] = '#';
		}
	}

	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			std::cout << cBoard[i][j] << "\t";
		}

		std::cout << std::endl << std::endl;
	}
}

int Interaction(Rectangle *rRectangle)
{
	char cCommand;

	std::cout << "Input Command : ";
	std::cin >> cCommand;

	switch (cCommand)
	{
	case 'x':
	{
		(*rRectangle).MoveRight();
		break;
	}
	case 'X':
	{
		(*rRectangle).MoveLeft();
		break;
	}
	case 'y':
	{
		(*rRectangle).MoveBottom();
		break;
	}
	case 'Y':
	{
		(*rRectangle).MoveTop();
		break;
	}
	case 's':
	{
		(*rRectangle).ReduceToX();
		(*rRectangle).ReduceToY();
		break;
	}
	case 'S':
	{
		(*rRectangle).ExpandToX();
		(*rRectangle).ExpandToY();
		break;
	}
	case 'i':
	{
		(*rRectangle).ExpandToX();
		break;
	}
	case 'j':
	{
		(*rRectangle).ReduceToX();
		break;
	}
	case 'k':
	{
		(*rRectangle).ExpandToY();
		break;
	}
	case 'l':
	{
		(*rRectangle).ReduceToY();
		break;
	}
	case 'r':
	{
		(*rRectangle).Reset();
		return Reset;
	}
	case 'q':
	{
		return Quit;
	}
	default:
		break;
	}

	system("cls");

	return None;
}