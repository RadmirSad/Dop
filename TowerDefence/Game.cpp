#include "Map.h"

int GetDist(const Tile& fir, const Tile& sec)
{
	int x1, y1, x2, y2;
	double res = 0;
	fir.GetCoord(x1, y1);
	sec.GetCoord(x2, y2);
	res += pow(x1 - x2, 2);
	res += pow(y1 - y2, 2);
	res = round(pow(res, 0.5));
	return (int)res;
}

int IsLevelsExist(int NewLevel)
{
	std::string res;
	std::stringstream str;
	for (int k = 1; k < NewLevel; k++)
	{
		str.clear();
		str.str("");
		res = "";
		str << "D:/Program/Lab/TowerDefence/Maps/";
		str << k;
		str << ".txt";
		str >> res;
		std::ifstream f(res);
		if (!f.is_open())
			return GOOD + k;
		f.close();
	}
	return GOOD;
}

int ThisLevelExist(int Lvl)
{
	std::string res;
	std::stringstream str;
	str.str("");
	str << "D:/Program/Lab/TowerDefence/Maps/";
	str << Lvl;
	str << ".txt";
	str >> res;
	std::ifstream f(res);
	if (!f.is_open())
		return BAD;
	f.close();
	return GOOD;
}

int DownloadDial(Map& MyMap)
{
	if (MyMap.InstallLevel(1) == GOOD)
		if (MyMap.DownloadMap(MyMap.Level) == GOOD)
			return GOOD;
	return BAD;
}

int CheckCellsForRand(const Map& MyMap)
{
	for (int i = 0; i < MyMap.GetDim(); i++)
		for (int j = 0; j < MyMap.GetDim(); j++)
		{
			int type = MyMap.GetCoordType(i, j);
			if ((type == ROAD) || (type == CASTLE) || (type == LAIR)) return BAD;
		}
	return GOOD;
}

void StartGame(Map& MyMap)
{
	std::cout << "***********************  3  **************************" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(750));
	std::cout << "***********************  2  **************************" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(750));
	std::cout << "***********************  1  **************************" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(750));
	std::thread Game(OnlyGame, MyMap);
	Game.detach();
	std::cout << std::endl << "Enter something to bring up the menu " << std::endl;
	std::string res;
	getline(std::cin, res);
	
}

int OnlyGame(Map& MyMap)
{
	int flag_for_alive = 1, time = 0;
	while (flag_for_alive)
	{


	}
}