#include <iostream>
#include <cstring>
#include <cmath>

typedef struct coordinate
{
	int iX;
	int iY;
	int iZ;
} Position;

typedef struct set
{
	Position pPos;
	bool bIn;
	double iLength;
} Set;

bool Menu();
void Initialize(Set*);
void AddListTop(Set*, char*, int*, int*);
void AddListBottom(Set*, char*, int*, int*);
void DeleteList(Set*, int*, int*, bool);
void PrintList(Set*);
void ClearList(Set*, int*, int*);
void DistanceFromOriginPoint(Set*, int, bool);
void ReorderByDistance(Set*, int);

int main()
{
	Menu();
}

bool Menu()
{
	Set sSet[10];
	int iTop = 0;
	int iCount = 0;

	Initialize(sSet);

	while (true)
	{
		bool bDeleteBottom = false;
		bool bFindMax = false;
		char cCommand[20];
		std::cout << "Command : ";
		std::cin.getline(cCommand, 20, '\n');

		switch (cCommand[0])
		{
		case '+':
		{
			AddListTop(sSet, cCommand, &iTop, &iCount);
			break;
		}
		case '-':
		{
			DeleteList(sSet, &iTop, &iCount, bDeleteBottom);
			break;
		}
		case 'e':
		{
			AddListBottom(sSet, cCommand, &iTop, &iCount);
			break;
		}
		case 'd':
		{
			bDeleteBottom = true;
			DeleteList(sSet, &iTop, &iCount, bDeleteBottom);
			break;
		}
		case 'l':
		{
			std::cout << "리스트의 길이 : " << iTop << std::endl;
			break;
		}
		case 'c':
		{
			ClearList(sSet, &iTop, &iCount);
			break;
		}
		case 'm':
		{
			bFindMax = true;
			DistanceFromOriginPoint(sSet, iTop, bFindMax);
			break;
		}
		case 'n':
		{
			DistanceFromOriginPoint(sSet, iTop, bFindMax);
			break;
		}
		case 's':
		{
			ReorderByDistance(sSet, iTop);
			iTop = iCount;
			break;
		}
		case 'q':
		{
			return false;
			break;
		}
		default:
		{
			break;
		}
		}
	}
}

void Initialize(Set* sSet)
{
	for (int i = 0; i < 10; ++i)
	{
		sSet[i].pPos = {};
		sSet[i].bIn = false;
		sSet[i].iLength = 0;
	}
}

void AddListTop(Set* sSet, char* cCommand, int* iTop, int* iCount)
{
	char* cTok = strtok(cCommand, " \n\t");
	int iTemp = 0;

	while (cTok != NULL)
	{
		switch (iTemp)
		{
		case 1:
			sSet[*iTop].pPos.iX = atoi(cTok);
			break;
		case 2:
			sSet[*iTop].pPos.iY = atoi(cTok);
			break;
		case 3:
			sSet[*iTop].pPos.iZ = atoi(cTok);
			break;
		default:
			break;
		}

		cTok = strtok(NULL, " \n\t");
		++iTemp;
	}

	sSet[*iTop].bIn = true;

	if (*iCount == *iTop)
		++(*iTop);

	++(*iCount);

	PrintList(sSet);
}

void AddListBottom(Set* sSet, char* cCommand, int* iTop, int* iCount)
{
	int iBreakPoint = 0;

	for (int i = 0; i < *iTop; ++i)
	{
		if (!sSet[i].bIn)
		{
			iBreakPoint = i;
			break;
		}
		else if (i == *iTop - 1)
		{
			iBreakPoint = i;
		}
	}

	if (iBreakPoint != *iTop - 1)
	{
		for (int i = iBreakPoint - 1; i >= 0; --i)
		{
			sSet[i + 1].pPos = sSet[i].pPos;
			sSet[i + 1].bIn = sSet[i].bIn;
		}
	}
	else
	{
		for (int i = iBreakPoint; i >= 0; --i)
		{
			sSet[i + 1].pPos = sSet[i].pPos;
			sSet[i + 1].bIn = sSet[i].bIn;
		}
	}

	char* cTok = strtok(cCommand, " \n\t");
	int iTemp = 0;

	while (cTok != NULL)
	{
		switch (iTemp)
		{
		case 1:
			sSet[0].pPos.iX = atoi(cTok);
			break;
		case 2:
			sSet[0].pPos.iY = atoi(cTok);
			break;
		case 3:
			sSet[0].pPos.iZ = atoi(cTok);
			break;
		default:
			break;
		}

		cTok = strtok(NULL, " \n\t");
		++iTemp;
	}

	sSet[0].bIn = true;

	if (*iCount == *iTop)
		++(*iTop);

	++(*iCount);

	PrintList(sSet);
}

void DeleteList(Set* sSet, int* iTop, int* iCount, bool bDeleteBottom)
{
	int iBottom = 0;

	while (!sSet[iBottom].bIn)
		++iBottom;

	if (bDeleteBottom)
	{
		sSet[iBottom] = {};
		sSet[iBottom].bIn = false;
	}
	else
	{
		sSet[--(*iTop)] = {};
		sSet[*iTop].bIn = false;
	}

	--(*iCount);

	PrintList(sSet);
}

void PrintList(Set* sSet)
{
	std::cout << std::endl << "\t┏━━┳━━━━━━━━━━┓" << std::endl;
	for (int i = 9; i >= 0; --i)
	{
		std::cout << "\t┃ " << i << "┃";
		if (sSet[i].bIn)
		{
			std::cout << " (" << sSet[i].pPos.iX << ", " << sSet[i].pPos.iY << ", " << sSet[i].pPos.iZ << ")";
		}
		else
		{
			std::cout << "\t      ";
		}
		std::cout << "┃" << std::endl;

		if (i != 0)
			std::cout << "\t┃━━╋━━━━━━━━━━┃" << std::endl;
		else
			std::cout << "\t┗━━┻━━━━━━━━━━┛" << std::endl;
	}
}

void ClearList(Set* sSet, int* iTop, int* iCount)
{
	for (int i = 0; i < *iTop; ++i)
	{
		sSet[i] = {};
		sSet[i].bIn = false;
	}

	*iTop = 0;
	*iCount = 0;

	PrintList(sSet);
}

void DistanceFromOriginPoint(Set* sSet, int iTop, bool bFindMax)
{
	int j = 0;
	int k = 0;

	while (!sSet[j].bIn)
		++j;

	double iLength = sqrt(sSet[j].pPos.iX * sSet[j].pPos.iX + sSet[j].pPos.iY * sSet[j].pPos.iY + sSet[j].pPos.iZ * sSet[j].pPos.iZ);

	for (int i = j; i < iTop; ++i)
	{
		if (bFindMax == true)
		{
			if (iLength < sqrt(sSet[i].pPos.iX * sSet[i].pPos.iX + sSet[i].pPos.iY * sSet[i].pPos.iY + sSet[i].pPos.iZ * sSet[i].pPos.iZ) && sSet[i].bIn)
			{
				iLength = sqrt(sSet[i].pPos.iX * sSet[i].pPos.iX + sSet[i].pPos.iY * sSet[i].pPos.iY + sSet[i].pPos.iZ * sSet[i].pPos.iZ);
				k = i;
			}
		}
		else
		{
			if (iLength > sqrt(sSet[i].pPos.iX * sSet[i].pPos.iX + sSet[i].pPos.iY * sSet[i].pPos.iY + sSet[i].pPos.iZ * sSet[i].pPos.iZ) && sSet[i].bIn)
			{
				iLength = sqrt(sSet[i].pPos.iX * sSet[i].pPos.iX + sSet[i].pPos.iY * sSet[i].pPos.iY + sSet[i].pPos.iZ * sSet[i].pPos.iZ);
				k = i;
			}
		}
	}

	std::cout << "(" << sSet[k].pPos.iX << ", " << sSet[k].pPos.iY << ", " << sSet[k].pPos.iZ << ")" << std::endl;
}

void ReorderByDistance(Set* sSet, int iTop)
{
	for (int i = 0; i < 10; ++i)
	{
		if (sSet[i].bIn)
		{
			sSet[i].iLength = sqrt(sSet[i].pPos.iX * sSet[i].pPos.iX + sSet[i].pPos.iY * sSet[i].pPos.iY + sSet[i].pPos.iZ * sSet[i].pPos.iZ);
		}
	}

	for (int i = 0; i < iTop; ++i)
	{
		for (int j = 0; j < iTop - i; ++j)
		{
			if (sSet[j].iLength > sSet[j + 1].iLength && sSet[j + 1].bIn)
			{
				Set sTemp;

				sTemp = sSet[j];
				sSet[j] = sSet[j + 1];
				sSet[j + 1] = sTemp;
			}
		}
	}

	for (int i = 0; i < iTop; ++i)
	{
		if (!sSet[i].bIn)
		{
			for (int j = i; j < iTop; ++j)
			{
				sSet[j] = sSet[j + 1];
			}
		}
	}

	for (int i = iTop; i < 10; ++i)
	{
		sSet[i] = {};
		sSet[i].bIn = false;
	}

	PrintList(sSet);
}