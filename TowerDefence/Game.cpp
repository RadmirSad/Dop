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
			if ((type == ROAD) || (type == CASTLE) || (type == LAIR) || (type == BASIN)) return BAD;
		}
	return GOOD;
}


std::mutex mtx_for_tower_;
std::mutex mtx_for_monsters_;
std::mutex mtx_flag_;

// In progress

void StartGame(Map& MyMap)
{
	int flag_for_exit = 0;
	
	std::cout << "***********************  3  **************************" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(750));
	std::cout << "***********************  2  **************************" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(750));
	std::cout << "***********************  1  **************************" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(750));
	std::thread Monsters(OnlyMonsters, std::ref(MyMap), std::ref(flag_for_exit));
	std::thread Towers(OnlyTowers, std::ref(MyMap), std::ref(flag_for_exit));
	std::thread Menu(Waiting, std::ref(MyMap), std::ref(flag_for_exit));
	Towers.detach();
	Monsters.detach();
	mtx_flag_.lock();
	while (!flag_for_exit) {
		mtx_flag_.unlock();
		std::this_thread::sleep_for(std::chrono::microseconds(100));
		mtx_flag_.lock();
	}
	mtx_flag_.unlock();
	Menu.join();
	return;
}

void Waiting(Map& MyMap, int& flag_for_exit)
{
	while ((flag_for_exit == BAD) && (MyMap.GetHpCast() > 0))
	{
		std::cout << std::endl << "Enter something to bring up the menu " << std::endl;
		std::string res;
		getline(std::cin, res);
		mtx_for_tower_.lock();
		mtx_for_monsters_.lock();
		mtx_flag_.lock();
		if (flag_for_exit == BAD)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			GetMenu(MyMap, flag_for_exit);
			if (flag_for_exit != GOOD)
			{
				std::cout << "***********************  3  **************************" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(750));
				std::cout << "***********************  2  **************************" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(750));
				std::cout << "***********************  1  **************************" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(750));
			}
		}
		mtx_flag_.unlock();
		mtx_for_monsters_.unlock();
		mtx_for_tower_.unlock();
	}
}

int OnlyMonsters(Map& MyMap, int& flag_for_alive)
{
	int time = 0, count = 0;
	auto start = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now();
	mtx_flag_.lock();
	while (!flag_for_alive)
	{
		mtx_flag_.unlock();
		std::chrono::duration<float> dur = end - start;
		if (dur.count() >= 1)
		{
			start = std::chrono::high_resolution_clock::now();
			mtx_for_tower_.lock();
			mtx_for_monsters_.lock();

			system("cls");
			MyMap.PrintMap();
			std::cout << " Time  " << time / 60 << ":" << time % 60 << std::endl;
			std::cout << "Castle HP = " << MyMap.MyCast.GetHealth() << std::endl;

			mtx_for_monsters_.unlock();
			mtx_for_tower_.unlock();

			mtx_for_monsters_.lock();
			for (int i = 0; i < MyMap.Monsters.GetSize(); i++)
				if (MyMap.Monsters[i]->DoAction(MyMap) == DEAD)
				{
					mtx_flag_.lock();
					mtx_for_tower_.lock();
					flag_for_alive = 1;
					system("cls");
					MyMap.PrintMap();
					std::cout << " Time  " << time / 60 << ":" << time % 60 << std::endl;
					std::cout << "Castle HP = " << MyMap.MyCast.GetHealth() << std::endl;
					mtx_for_tower_.unlock();
					std::cout << std::endl << "Game over" << std::endl;
					break;
				}
			mtx_for_monsters_.unlock();
			if (flag_for_alive)
			{
				if (!MyMap.Monsters.GetSize())
					mtx_flag_.lock();
				break;
			}
			for (int i = 0; i < MyMap.Lairs.GetSize(); i++)
				for (int j = 0; j < MyMap.Lairs[i].Enemies.GetSize(); j++)
					if (MyMap.Lairs[i].Enemies[j]->GetTime() == time)
					{
						mtx_for_monsters_.lock();
						if(MyMap.Revive(i, j) == BAD)
							throw std::logic_error("Way wasn't found");
						mtx_for_monsters_.unlock();
					}
			time++;
		}
		end = std::chrono::high_resolution_clock::now();
		mtx_flag_.lock();
	}
	mtx_flag_.unlock();
	return GOOD;
}

int OnlyTowers(Map& MyMap, int& flag_for_monst)
{
	int time = 1, count = 0;
	auto start = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now();
	mtx_flag_.lock();
	while (!flag_for_monst)
	{
		mtx_flag_.unlock();
		std::chrono::duration<float> dur = end - start;
		if (dur.count() >= time)
		{
			start = std::chrono::high_resolution_clock::now();
			mtx_for_tower_.lock();
			mtx_for_monsters_.lock();

			count = MyMap.Towers.GetSize();
			for (int i = 0; i < count; i++)
				MyMap.Towers[i].ToDamage(MyMap);
			if (MyMap.Monsters.GetSize() == 0)
			{
				mtx_flag_.lock();
				flag_for_monst = 1;
				for (int i = 0; i < MyMap.Lairs.GetSize(); i++) // Check lists with Enemies
					if (MyMap.Lairs[i].Enemies.GetSize() != 0)	// if they are empty you win
					{
						flag_for_monst = 0;
						break;
					}

				if (flag_for_monst)
				{
					system("cls");
					MyMap.PrintMap();
					MyMap.PrintTable();
					std::cout << std::endl << "Congratulations!!!! You won!!!" << std::endl;
				}
				mtx_flag_.unlock();
			}

			mtx_for_monsters_.unlock();
			mtx_for_tower_.unlock();
			MyMap.MyCast.TakeMoney();
		}
		end = std::chrono::high_resolution_clock::now();
		mtx_flag_.lock();
	}
	mtx_flag_.unlock();
	return GOOD;
}


void GetMenu(Map& MyMap, int& quit)
{
	int flag = 0, num_of_act = 0;
	while (!flag)
	{
		std::cout << std::endl << "Choose one of the suggested actions:" << std::endl
			<< " 1. Check map" << std::endl
			<< " 2. Check table with information" << std::endl
			<< " 3. Build new tower" << std::endl
			<< " 4. Build new wall" << std::endl
			<< " 5. Upgrade one of your towers" << std::endl
			<< " 6. Upgrade your castle" << std::endl
			<< " 7. Repair castle" << std::endl
			<< " 8. Repair wall" << std::endl
			<< " 9. Continue the game" << std::endl
			<< " 10. Quit" << std::endl << std::endl;
		Get_num(num_of_act);
		switch (num_of_act)
		{
		case 1:
			MyMap.PrintMap();
			break;
		case 2:
			MyMap.PrintTable();
			break;
		case 3:
			NewObject(MyMap, TOWER);
			break;
		case 4:
			NewObject(MyMap, WALL);
			break;
		case 5:
			UpgradeTow(MyMap);
			break;
		case 6:
			MyMap.UpgCast();
			break;
		case 7:
			MyMap.RepCast();
			break;
		case 8:
			MyMap.RepWall();
			break;
		case 9:
			flag = 1;
			break;
		case 10:
			flag = 1;
			quit = GOOD;
			break;
		default:
			std::cout << std::endl << "Action with this number doesn't exist" << std::endl;
			break;
		}
	}
	
}

void UpgradeTow(Map& MyMap)
{
	int num = 0;
	if (MyMap.Towers.GetSize())
	{
		std::cout << "Write number of the tower that you want to upgrade from 1 to " <<MyMap.Towers.GetSize() << std::endl;
		Get_num(num);
		if ((num > 0) && (num <= MyMap.Towers.GetSize()))
			MyMap.Towers[num - 1].Upgrade(MyMap);
		else std::cout << "Tower with this number doesn't exist" << std::endl;
	}
	else std::cout << "You don't have any towers" << std::endl;
}

void NewObject(Map& MyMap, int type)
{
	int x = -1, y = -1;
	GetCoordinates(x, y, MyMap);
	if ((MyMap.GetCoordType(x, y) != CASTLE) && (MyMap.GetCoordType(x, y) != LAIR)
		&& (MyMap.GetCoordType(x, y) != TOWER) && (MyMap.GetCoordType(x, y) != WALL))
	{
		if (type == TOWER)
		{
			if (MyMap.GetCoordType(x, y) == VALLEY) {
				if(MyMap.BuildTow(x, y) == GOOD)
					MyMap.ChangeType(type, x, y);
			}
			else std::cout << "This cell is busy" << std::endl;
		}
		else
		{
			if(MyMap.BuildWall(x, y) == GOOD)
				MyMap.ChangeType(type, x, y);
		}
	}
	else
		std::cout << "This cell is busy" << std::endl;
}

void GetCoordinates(int& x, int& y, const Map& MyMap)
{
	int flag = 0;
	while (!flag)
	{
		std::cout << std::endl << "Enter the x coordinate in the range from 0 to " << MyMap.GetDim() - 1 << ":\n";
		Get_num(x);
		if ((x >= MyMap.GetDim()) || (x < 0))
		{
			std::cout << "Incorrect value" << std::endl;
			continue;
		}
		std::cout << "Enter the y coordinate in the range from 0 to " << MyMap.GetDim() - 1 << ":\n";
		Get_num(y);
		if ((y >= MyMap.GetDim()) || (y < 0))
		{
			std::cout << "Incorrect value" << std::endl;
			continue;
		}
		flag = 1;
	}
}

void clear_cmd() {
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}