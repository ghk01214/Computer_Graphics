#include <iostream>
#include <cstring>

int main()
{
	FILE* fData = fopen("PLAYERUNKNOWN'S BATTLEGROUNDS Weapon List.txt", "r");

	if (fData != NULL)
	{
		char cBuffer[500] = {};

		fread(cBuffer, sizeof(cBuffer), 1, fData);

		std::cout << cBuffer << std::endl;

		char* cWeapon = strtok(cBuffer, " \n");

		int iWord = 0;
		int iNumber = 0;

		while (cWeapon != NULL)
		{
			int iLength = strlen(cWeapon);

			for (int i = 0; i < iLength; ++i)
			{
				if (cWeapon[i] > 47 && cWeapon[i] < 58)
				{
					++iNumber;
					break;
				}
				else if (i == iLength - 1)
					++iWord;
			}

			cWeapon = strtok(NULL, " \n");
		}

		std::cout << std::endl << "총 숫자 개수 = " << iNumber << std::endl << "총 문자 개수 = " << iWord << std::endl;
	}
	else
	{
		std::cout << "파일을 찾을 수 없습니다." << std::endl << "프로그램을 종료합니다." << std::endl;
	}

	fclose(fData);
}