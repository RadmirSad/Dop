#include "Map.h"

int main()
{
	int flag = 0, num = 0, flag_for_map = 0;
	Map NewMap;
	while (!flag)
	{
		std::cout << std::endl << " Main Menu:" << std::endl
			<< " 1. Start game" << std::endl
			<< " 2. Download level" << std::endl
			<< " 3. Create level" << std::endl
			<< " 4. Exit" << std::endl 
			<< " 5. Print map" << std::endl << std::endl;
		Get_num(num);
		switch (num)
		{
		case 1:
			if (flag_for_map)
				StartGame(NewMap);
			else
				std::cout << std::endl << "Before starting the game you should create new map or download it" << std::endl << std::endl;
			break;
		case 2:
			if (DownloadDial(NewMap) == GOOD) flag_for_map = 1;
			break;
		case 3:
			if (NewMap.DialogMap() == GOOD) flag_for_map = 1;
			break;
		case 4:
			flag = 1;
			break;
		case 5:
			if(flag_for_map)
				NewMap.PrintMap(0);
			else std::cout << std::endl << "Before checking map you should create new map or download it" << std::endl << std::endl;
			break;
		default:
			std::cout << std::endl;
			break;
		}
	}
	return 0;
}