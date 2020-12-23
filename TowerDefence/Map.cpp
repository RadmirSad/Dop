#include "Map.h"
#include "Light.h"

/*======================= Methods for Tile ========================*/

Tile::Tile(int x0, int y0)
{
	if((x0 < 0) || (y0 < 0)) throw std::invalid_argument("Invalid coordinate value");
	X = x0;
	Y = y0;
}

Tile::Tile(const Tile& NewTile)
{
	int x, y;
	NewTile.GetCoord(x, y);
	X = x;
	Y = y;
}

/*=============================== Methods for Map ===============================*/

int Map::ChangeType(int NewType, int x, int y)
{
	if ((NewType < ROAD) || (NewType > CASTLE)) return BAD;
	Fields[x][y] = NewType;
	return GOOD;
}

int Map::GetCoordType(const Tile& a) const
{
	int x, y;
	a.GetCoord(x, y);
	return Fields[x][y];
}

int Map::GenerStartMap()
{
	Fields = new int* [Dim];
	for (int i = 0; i < Dim; i++) {
		Fields[i] = new int[Dim];
		for (int j = 0; j < Dim; j++)
			Fields[i][j] = VALLEY;
	}


	return 0;
}

void Map::CheckMap()
{
	for (int i = 0; i < Dim; i++)
	{
		for (int j = 0; j < Dim; j++)
		{
			if ((Fields[i][j] == ROAD) || (Fields[i][j] == BASIN))
			{
				int ind = 0, x = -1, y = -1;
				while (ind < Monsters.GetSize())
				{
					Monsters[ind]->ChangeTile(x, y);
					if ((x == i) && (y == j)) break;
					else ind++;
				}
				if (ind == Monsters.GetSize())
				{
					if(Fields[i][j] == ROAD)
						std::cout << " = ";
					else std::cout << " ~ ";
				}
				else
				{
					switch (Monsters[ind]->GetType())
					{
					case KID:
						std::cout << " ' ";
						break;
					case BB:
						std::cout << " I ";
						break;
					case HELICOPTER:
						std::cout << " + ";
						break;
					case TEEN:
						std::cout << " * ";
						break;
					case BILLY:
						std::cout << " $ ";
						break;
					case ADAM:
						std::cout << " @ ";
						break;
					default:
						std::cout << " error ";
						break;
					}
				}
			}
			else
			{
				switch (Fields[i][j])
				{
				case VALLEY:
					std::cout << " x ";
					break;
				case MOUNTAIN:
					std::cout << " A ";
					break;
				case TOWER:
					std::cout << " T ";
					break;
				case WALL:
					std::cout << " # ";
					break;
				case CASTLE:
					std::cout << "ITI";
					break;
				case LAIR:
					std::cout << "(*)";
					break;
				case EMPTY:
					std::cout << " E ";
					break;
				default:
					std::cout << " error ";
					break;
				}
			}
			if (j + 1 == Dim) std::cout << std::endl;
		}
	}
}

/*=============================== Creating map ================================*/

int Map::CreateMap()
{
	int Num = 0, flag = 0, fl_lv = 0;
	for (int i = 0; i < Dim; i++)
		for (int j = 0; j < Dim; j++)
			Fields[i][j] = EMPTY;
	MyCast.ChangeTile(-1, -1);
	Level = 0;
	while (!flag)
	{
		std::cout << "Select a function number:" << std::endl
			<< "1. View map" << std::endl
			<< "2. Change the cell type" << std::endl
			<< "3. Add enemy" << std::endl
			<< "4. Change level" << std::endl
			<< "5. Create" << std::endl;
		Num = 0;
		Get_num(Num);
		switch (Num)
		{
		case 1:
			CheckMap();
			break;
		case 2:
			ChangeCellType();
			break;
		case 3:
			if(fl_lv)
				AddEnemy();
			break;
		case 4:
			if (!fl_lv)
			{
				InstallLevel();
				fl_lv = 1;
			}
			break;
		case 5:
			if (CheckEmpty() == GOOD)
			{
				if (IsRoadExist() == GOOD)
					flag = 1;
				else std::cout << "Not enough roads" << std::endl;
			}
			else std::cout << "There are empty cells" << std::endl;
			break;
		default:
			std::cout << "There is no function with this number" << std::endl;
			break;
		}
	}
}

void Map::InstallLevel()
{
	int Num = 0, flag = 0;
	while (!flag)
	{
		std::cout << "Enter a new value:" << std::endl;
		Get_num(Num);
		if (ChangeLevel(Num) == GOOD)
		{
			int dop = IsLevelsExist();
			if (dop == GOOD) flag = 1;
			else std::cout << "Maximum permissible level = " << dop - GOOD << std::endl;
		}
	}
}

int Map::IsLevelsExist()
{
	std::string res;
	std::stringstream str;
	for (int k = 1; k < Level; k++)
	{
		str.str("");
		str << k;
		str << ".txt";
		str >> res;
		std::ifstream f(res);
		if (f.good())
			return GOOD + k;
		f.close();
	}
	return GOOD;
}

int Map::ChangeLevel(int NewLvl)
{
	if (NewLvl <= 0) {
		std::cout << "Incorrect value of new level" << std::endl;
		return BAD;
	}
	Level = NewLvl;
	return GOOD;
}

void Map::AddEnemy()
{
	int type = -1, flag = 0;
	ConstIter<Enemy*> it = Monsters.cend();
	Enemy* ptr = nullptr;
	while (!flag)
	{
		std::cout << "Select enemy type:" << std::endl
			<< "1. Kid" << std::endl
			<< "2. BigBoy" << std::endl
			<< "3. Helicopter" << std::endl
			<< "4. Teenager" << std::endl
			<< "5. Billy" << std::endl
			<< "6. BlackAdam" << std::endl;
		Get_num(type);
		flag = 1;
		switch(type)
		{
		case KID:
			ptr = new Kid;
			break;
		case BB:
			ptr = new BigBoy;
			break;
		case HELICOPTER:
			ptr = new Helicopter;
			break;
		case TEEN:
			ptr = new Teenager;
			break;
		case BILLY:
			ptr = new Billy;
			break;
		case ADAM:
			ptr = new BlackAdam;
			break;
		default:
			std::cout << " error ";
			flag = 0;
			break;
		}
	}
	flag = 0;
	while (!flag)
	{
		std::cout << "Enter the exit time in seconds" << std::endl;
		Get_num(type);
		if (type <= 0) std::cout << "Exit time must be greater than 0" << std::endl;
		else flag = 1;
	}
	ptr->ChangeTime(type);
	Monsters.Insert(it, ptr);
}

int Map::ChangeCellType()
{
	int x = -1, y = -1, flag = 0, type = -1;
	while (!flag)
	{
		std::cout << "Enter the coordinates in the range from 0 to " << Dim << ":\n";
		Get_num(x);
		if ((x >= Dim) || (x < 0))
		{
			std::cout << "Incorrect value" << std::endl;
			continue;
		}
		Get_num(y);
		if ((y >= Dim) || (y < 0))
		{
			std::cout << "Incorrect value" << std::endl;
			continue;
		}
		if((Fields[x][y] != CASTLE) || (Fields[x][y] != LAIR))
			flag = 1;
		std::cout << "This cell is busy" << std::endl;
	}
	flag = 0;
	while(!flag)
	{
		std::cout << "Choose type of the cell:" << std::endl
			<< "1. Road" << std::endl
			<< "2. Valley" << std::endl
			<< "3. Basin" << std::endl
			<< "4. Mountain" << std::endl
			<< "5. Castle" << std::endl
			<< "6. Lair" << std::endl;
		Get_num(type);
		flag = 1;
		switch (type)
		{
		case 1:
			type = ROAD;
			break;
		case 2:
			type = VALLEY;
			break;
		case 3:
			type = BASIN;
			break;
		case 4:
			type = MOUNTAIN;
			break;
		case 5:
			if (CheckCast() == BAD)
			{
				type = CASTLE;
				MyCast.ChangeTile(x, y);
			}
			else
			{
				std::cout << "The castle is already on the map" << std::endl;
				flag = 0;
			}
			break;
		case 6:
		{
			type = LAIR;
			ConstIter<Lair> it = Lairs.cend();
			Lair NL;
			NL.ChangeTile(x, y);
			Lairs.Insert(it, NL);
			break;
		}
		deafult:
			std::cout << "There is no type of the cell with this number" << std::endl;
			flag = 0;
			break;
		}
	}
	Fields[x][y] = type;
	return GOOD;
}

int Map::CheckEmpty()
{
	for (int i = 0; i < Dim; i++)
		for (int j = 0; j < Dim; j++)
			if (Fields[i][j] == EMPTY) return BAD;
	return GOOD;
}

int Map::CheckCast()
{
	int x0 = 0, y0 = 0;
	MyCast.GetCoord(x0, y0);
	if ((x0 >= Dim) || (x0 < 0) || (y0 >= Dim) || (y0 < 0)) return BAD;
	return GOOD;
}

int Map::IsRoadExist()
{
	return GOOD;
}

/*================================================================*/