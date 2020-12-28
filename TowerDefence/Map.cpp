#include "Map.h"
#include <cmath>

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

Map::~Map()
{
	CleanAll();
}

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

void Map::PrintMap(int flag_for_create)
{
	std::cout << std::endl;
	for (int i = 0; i <= Dim; i++)
		if (i == 0) std::cout << "   ";
		else std::cout << " " << i - 1 << " ";
	std::cout << " X " <<std::endl;
	for (int y = 0; y < Dim; y++)
	{
		std::cout << " " << y << " ";
		for (int x = 0; x < Dim; x++)
		{
			if ((Fields[x][y] == ROAD) || (Fields[x][y] == BASIN))
			{
				int ind = 0, x0 = -1, y0 = -1;
				while (ind < Monsters.GetSize())
				{
					Monsters[ind]->GetCoord(x0, y0);
					if ((x0 == x) && (y0 == y)) break;
					else ind++;
				}
				if (ind == Monsters.GetSize())
				{
					if(Fields[x][y] == ROAD)
						std::cout << "[=]";
					else std::cout << " ~ ";
				}
				else
					std::cout << Monsters[ind]->Print();
			}
			else
			{
				switch (Fields[x][y])
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
					std::cout << "&:&";
					break;
				case EMPTY:
					std::cout << " E ";
					break;
				default:
					std::cout << " error ";
					break;
				}
			}
			if (x + 1 == Dim) std::cout << std::endl;
		}
	}
	std::cout << " Y " << std::endl << std::endl;
	if (!flag_for_create)
	{
		for (int i = 0; i < Lairs.GetSize(); i++)
		{
			std::cout << "Lair ¹" << i + 1 << ":" << std::endl;
			if (!Lairs[i].Enemies.GetSize())
				std::cout << " This lair is empty " << std::endl;
			for (int j = 0; j < Lairs[i].Enemies.GetSize(); j++) 
			{
				Enemy* dop = Lairs[i].Enemies[j];
				std::cout << std::endl << "Type of enemy: " << dop->Type() << std::endl
					<< "Time of exit: " << dop->GetTime() << " Speed: " << dop->GetSpeed() << " Regen: " << dop->GetReg() << std::endl
					<< " Damage: " << dop->GetDam() << " MaxHealth :" << dop->GetMaxHealth() << std::endl;
				if (Lairs[i].Enemies[j]->GetType() >= TEEN)
				{
					double dam, sp, hp, reg;
					dop->GetAuras(dam, sp, reg, hp);
					std::cout << " Radius: " << dop->GetRad() << " Auras: " <<
						" AurDam = " << dam << " AurSpeed = " << sp << " AurRegen = " << reg << " AurHp = " << hp << std::endl;
				}
			}
		}
	}
	else
	{
		std::cout << std::endl << "My balance: " << MyCast.Cash() << std::endl;
	}
}

/*=============================== Creating map ================================*/

int Map::DialogMap()
{
	int Num = 0, flag = 0, fl_lv = 0;
	CleanMap();
	while (!flag)
	{
		std::cout << "Enter a new field size:" << std::endl;
		Get_num(Num);
		if (Num <= 5) std::cout << "New size should be more than 5" << std::endl;
		else flag = 1;
	}
	Dim = Num;
	Fields = new int* [Dim];
	for (int i = 0; i < Dim; i++)
	{
		Fields[i] = new int[Dim];
		for (int j = 0; j < Dim; j++)
			Fields[i][j] = EMPTY;
	}
	MyCast.ChangeTile(-1, -1);
	Level = 0;
	flag = 0;
	InstallLevel();
	while (!flag)
	{
		std::cout << std::endl << "Select a function number:" << std::endl
			<< "1. View map" << std::endl
			<< "2. Change the cell type" << std::endl
			<< "3. Add enemy" << std::endl
			<< "4. Create and save" << std::endl
			<< "5. Randomize fields (only when map hasn't lairs, castle and roads)" << std::endl
			<< "6. Map only with 'valley' (only when map hasn't lairs, castle and roads)"<< std::endl << std::endl;
		Num = 0;
		Get_num(Num);
		switch (Num)
		{
		case 1:
			PrintMap(0);
			break;
		case 2:
			ChangeCellType();
			break;
		case 3:
			if (Lairs.GetSize() != 0)
				AddEnemy();
			else std::cout << "At least one lair is needed" << std::endl;
			break;
		case 4:
			if ((CheckEmptyCells() == GOOD) && (CheckEmptyLairs() == GOOD))
			{
				if (IsRoadExist() == GOOD)
					flag = 1;
				else std::cout << "Not enough roads" << std::endl;
			}
			else std::cout << "There are empty cells or one of the lairs is empty" << std::endl;
			break;
		case 5:
			if (CheckCellsForRand(*this) == GOOD)
				RandGenerate();
			else std::cout << "Your map already has lair, or castle, or road" << std::endl;
			break;
		case 6:
			if (CheckCellsForRand(*this) == GOOD)
				FullValley();
			else std::cout << "Your map already has lair, or castle, or road" << std::endl;
			break;
		default:
			std::cout << "There is no function with this number" << std::endl;
			break;
		}
	}
	if (SaveMap()) return GOOD;
	else return BAD;
}

void Map::FullValley()
{
	for (int i = 0; i < Dim; i++)
		for (int j = 0; j < Dim; j++)
			Fields[i][j] = VALLEY;
}

void Map::RandGenerate()
{
	srand(time(0));
	for (int i = 0; i < Dim; i++)
		for (int j = 0; j < Dim; j++)
			Fields[i][j] = rand() % 3;
}

int Map::CheckEmptyLairs() const
{
	for (int i = 0; i < Lairs.GetSize(); i++)
		if (Lairs[i].Enemies.GetSize() == 0) return BAD;
	return GOOD;
}

void Map::CleanMap()
{
	for (int i = 0; i < Dim && Fields != nullptr; i++)
		delete[] Fields[i];
	delete[] Fields;
	Fields = nullptr;
}

void Map::CleanAll()
{
	CleanMap();
	for (int i = 0; i < Monsters.GetSize(); i++)
		delete Monsters[i];
	Monsters.Clear();
	Lairs.Clear();
	Towers.Clear();
	Walls.Clear();
	Ways.Clear();
}

int Map::InstallLevel(int flag) // flag for download
{
	int Num = 0, DopFlag = 0;
	while (!DopFlag)
	{
		std::cout << std::endl << "Enter a new value of level." << std::endl;
		if(!flag) std::cout << "Be carefully. You won't change level of the map again." << std::endl;
		Get_num(Num);
		int buf = Level;
		if (ChangeLevel(Num) == GOOD)
		{
			int dop;
			if (flag)
			{
				dop = IsLevelsExist(Level + 1); // if we trying to download file we should check all levels to the correct level including it
				if (dop == GOOD)
					DopFlag = 1;
				else {
					if (dop - GOOD == 1)
					{
						std::cout << std::endl << "No files have been created before now" << std::endl;
						return BAD;
					}
					std::cout << std::endl << "Maximum permissible level = " << dop - GOOD - 1 << std::endl;
					Level = buf;
				}
			}
			else
			{
				dop = IsLevelsExist(Level);
				if (dop == GOOD) DopFlag = 1;
				else
				{
					std::cout << std::endl << "Maximum permissible level = " << dop - GOOD << std::endl;
					Level = buf;
				}
			}
		}
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

void Map::AddEnemy(int base_type, int base_time, int num_of_lair)
{
	int type = -1, flag = 0;
	Enemy* ptr = nullptr;
	while (!flag)
	{
		if (base_type == -1)
		{
			std::cout << "Select enemy type:" << std::endl
				<< "1. Kid" << std::endl
				<< "2. BigBoy" << std::endl
				<< "3. Helicopter" << std::endl
				<< "4. Teenager" << std::endl
				<< "5. Billy" << std::endl
				<< "6. BlackAdam" << std::endl;
			Get_num(type);
		}
		else type = base_type + 1;
		flag = 1;
		double coef = GetCoef();
		switch (type)
		{
		case 1:
			ptr = new Kid(coef);
			break;
		case 2:
			ptr = new BigBoy(coef);
			break;
		case 3:
			ptr = new Helicopter(coef);
			break;
		case 4:
			ptr = new Teenager(coef);
			break;
		case 5:
			ptr = new Billy(coef);
			break;
		case 6:
			ptr = new BlackAdam(coef);
			break;
		default:
			std::cout << " error ";
			flag = 0;
			break;
		}
	}
	flag = 0;
	if (base_time == -1)
	{
		while (!flag)
		{
			std::cout << "Enter the exit time in seconds" << std::endl;
			Get_num(type);
			if (type <= 0) std::cout << "Exit time must be greater than 0" << std::endl;
			else flag = 1;
		}
	}
	else type = base_time;
	ptr->ChangeTime(type);
	flag = 0;
	if (num_of_lair == -1)
	{
		while (!flag)
		{
			std::cout << "Enter the number of Lair from 1 to " << Lairs.GetSize() << std::endl;
			Get_num(type);
			if ((type > Lairs.GetSize()) || (type < 1)) std::cout << "A lair with this number does not exist" << std::endl;
			else flag = 1;
		}
	}
	else type = num_of_lair + 1;
	ConstIter<Enemy*> it = Lairs[type - 1].Enemies.cend();
	Lairs[type - 1].Enemies.Insert(it, ptr);
}

int Map::ChangeCellType()
{
	int x = -1, y = -1, flag = 0, type = -1, flag_for_cast = 0;
	while (!flag)
	{
		std::cout << "Enter the x coordinate in the range from 0 to " << Dim - 1 << ":\n";
		Get_num(x);
		if ((x >= Dim) || (x < 0))
		{
			std::cout << "Incorrect value" << std::endl;
			continue;
		}
		std::cout << "Enter the y coordinate in the range from 0 to " << Dim - 1 << ":\n";
		Get_num(y);
		if ((y >= Dim) || (y < 0))
		{
			std::cout << "Incorrect value" << std::endl;
			continue;
		}
		if ((Fields[x][y] != CASTLE) && (Fields[x][y] != LAIR) && (Fields[x][y] != ROAD))
			flag = 1;
		else
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
			AddPoint(x, y);
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
			if (!flag_for_cast)
			{
				type = CASTLE;
				MyCast.ChangeTile(x, y);
				MyCast.Multiply(GetCoef());
				AddPoint(x, y);
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
			NL.Field.ChangeTile(x, y);
			Lairs.Insert(it, NL);
			AddPoint(x, y);
			break;
		}
		default:
			std::cout << "There is no type of the cell with this number" << std::endl;
			flag = 0;
			break;
		}
	}
	Fields[x][y] = type;
	return GOOD;
}

void Map::AddPoint(int x, int y)
{
	auto it = Ways.cend();
	Node ptr(x, y); // Create Node and insert it
	if ((Ways.GetSize() != 0) && (Ways.GetSize() % 10 == 0)) // If memory will be reallocated we should copy all information about pointers and then paste it into the vector
	{
		int** DopMatrix = new int* [Ways.GetSize()];
		for (int i = 0; i < Ways.GetSize(); i++)
			DopMatrix[i] = new int[Ways.GetSize()]{};
		for(int i = 0; i < Ways.GetSize(); i++)
			for (int j = 0; j < Ways[i].GetSize(); j++)
			{
				int ind = 0;
				while ((ind < Ways.GetSize()) && (Ways[i].GetPoint(j)->GetTile() != Ways[ind].GetTile()))
					ind++;
				DopMatrix[i][ind] = 1;
			}
		Ways.Insert(it, ptr);
		for (int i = 0; i < Ways.GetSize() - 1; i++)
		{
			Ways[i].Clear();
			for (int j = 0; j < Ways.GetSize() - 1; j++)
				if (DopMatrix[i][j] == 1)
					Ways[i].Insert(Ways[i].cend(), &Ways[j]);
		}
		for (int i = 0; i < Ways.GetSize() - 1; i++)
			delete[] DopMatrix[i];
		delete[] DopMatrix;
	}
	else
		Ways.Insert(it, ptr);
	if ((x + 1 < Dim) && ((Fields[x + 1][y] == ROAD) || (Fields[x + 1][y] == CASTLE) || (Fields[x + 1][y] == LAIR)))
		AddEdges(x + 1, y);
	if ((y + 1 < Dim) && ((Fields[x][y + 1] == ROAD) || (Fields[x][y + 1] == CASTLE) || (Fields[x][y + 1] == LAIR)))
		AddEdges(x, y + 1);
	if ((x - 1 >= 0) && ((Fields[x - 1][y] == ROAD) || (Fields[x - 1][y] == CASTLE) || (Fields[x - 1][y] == LAIR)))
		AddEdges(x - 1, y);
	if ((y - 1 >= 0) && ((Fields[x][y - 1] == ROAD) || (Fields[x][y - 1] == CASTLE) || (Fields[x][y - 1] == LAIR)))
		AddEdges( x, y - 1);
}

void Map::AddEdges(int xsec, int ysec)
{
	int index = 0, x = 0, y = 0, num = Ways.GetSize() - 1;
	while (index < Ways.GetSize()) // Finding the right cell to create links with
	{
		Ways[index].GetCoord(x, y);
		if ((xsec == x) && (ysec == y)) break;
		index++;
	}
	if (index == Ways.GetSize())
	{
		std::cout << "Error. Tile with corresponding coordinates wasn't found" << std::endl;
		return;
	}
	auto it = Ways[num].cend();
	if(CheckPointers(&(Ways[index]), num) < 0)
		Ways[num].Insert(it, &(Ways[index])); // link MyTile -> adjacent Tile
	if(CheckPointers(&(Ways[num]), index) < 0)
		Ways[index].Insert(Ways[index].cend(), &(Ways[num])); // link adjacent Tile -> MyTile
}

int Map::CheckPointers(Node* MyNode, int index) const
{
	for (int i = 0; i < Ways[index].GetSize(); i++)
		if (MyNode == Ways[index].GetPoint(i)) return i;
	return -1;
}

int Map::CheckEmptyCells() const
{
	for (int i = 0; i < Dim; i++)
		for (int j = 0; j < Dim; j++)
			if (Fields[i][j] == EMPTY) return BAD;
	return GOOD;
}

int Map::IsRoadExist() const
{
	int count = 0, xCast = 0, yCast = 0, xLair = 0, yLair = 0, MySize = Lairs.GetSize();
	MyVector<Tile> dop;
	for (int ind = 0; ind < MySize; ind++)
		count += Dijkstra(Lairs[ind].GetTile(), MyCast.GetTile(), dop);
	if (count == (MySize * GOOD))
		return GOOD;
	else return BAD;
}

int Map::Dijkstra(const Tile& start, const Tile& end, MyVector<Tile>& way) const
{
	way.Clear();
	way.Insert(way.cend(), start);
	int x = 0, st = 0, en = 0, MySize = Ways.GetSize() , * visited = new int[MySize]{}, 
		* dist = new int[MySize], index = 0;
	while ((st < MySize) && (en < MySize)) // Find index of start and end point
	{
		if (start != Ways[st].GetTile()) st++;
		if (end != Ways[en].GetTile()) en++;
		else if (start == Ways[st].GetTile()) break;
	}
	if ((st == MySize) || (en == MySize))
	{
#ifdef DEBUG
		std::cout << "Start or end point wasn't found" << std::endl;
#endif
		return BAD;
	}
	for (int i = 0; i < MySize; i++) // Initialize distance
		dist[i] = INT_MAX;
	dist[st] = 0;
	for(int dop = 0; dop < MySize; dop++)
	{
		index = -1;
		for (int j = 0; j < MySize; j++)
			if ((!visited[j]) && ((index == -1) || (dist[index] > dist[j]))) index = j; // Find vertex with minimal distance
		if (dist[index] == INT_MAX)
			break;
		visited[index] = 1;
		for (int i = 0; i < Ways[index].GetSize(); i++) // Check all pointers
		{
			x = 0;
			while ((x < Ways.GetSize()) && (Ways[index].GetPoint(i)->GetTile() != Ways[x].GetTile()))
			{// Find corresponding node
				std::cout << Ways[index].GetSize() << " - size" << std::endl;
				x++;
			}
			if (x == Ways.GetSize())
			{
				std::cout << "ERROR" << std::endl;
				return BAD;
			}
			if (dist[x] > 1 + dist[index])
			{
				dist[x] = 1 + dist[index];
				way.Insert(way.cend(), Ways[x].GetTile());
			}
		}
	}
	delete[] visited;
	if (dist[en] == INT_MAX)
	{
		way.Clear();
		delete[] dist;
		std::cout << "Way wasn't build" << std::endl;
		return BAD;
	}
	delete[] dist;
	return GOOD;
}

/*================================ Downloading and saving map ================================*/

int Map::SaveMap()
{
	int size = 0, x = 0, y = 0, time = 0;
	std::string res;
	res = ".txt";
	std::stringstream str;
	str << "D:/Program/Lab/TowerDefence/Maps/";
	str << Level;
	str << res;
	res = "";
	str >> res;
	std::ofstream MyFile(res);
	if (MyFile.is_open())
	{
		MyFile << Level << " " << Dim << std::endl; // write level and dimension of map
		MyCast.GetCoord(x, y);
		MyFile << x << " " << y << std::endl; // write coordinate of castle
		size = Lairs.GetSize();
		MyFile << size << std::endl; // write number of lairs
		for (int i = 0; i < size; i++) // write number of monsters and their types from corresponding lair
		{
			Lairs[i].GetCoord(x, y);
			MyFile << x << " " << y << " "; // write coordinates of the lair
			int CountOfMonst = Lairs[i].Enemies.GetSize();
			MyFile << CountOfMonst << " ";
			for (int j = 0; j < CountOfMonst; j++) // write types and times of every monster from this lair
				MyFile << Lairs[i].Enemies[j]->GetType() << " " << Lairs[i].Enemies[j]->GetTime() << " ";
			MyFile << std::endl;
		}
		for (int i = 0; i < Dim; i++) // write map
		{
			for (int j = 0; j < Dim; j++)
				MyFile << Fields[i][j] << " ";
			MyFile << std::endl;
		}
		size = Ways.GetSize(); // write number of nodes
		MyFile << size << std::endl;
		for (int i = 0; i < size; i++)
		{
			Ways[i].GetCoord(x, y);
			MyFile << x << " " << y << " " << Ways[i].GetPrior() << " "; // write coordinates of the node
			MyFile << std::endl;
		}
		for (int i = 0; i < size; i++)
		{
			int CountOfPtr = Ways[i].GetSize();
			for (int j = 0; j < CountOfPtr; j++) // write coordinates of pointers
			{
				Ways[i].GetPoint(j)->GetCoord(x, y);
				MyFile << CountOfPtr << " " << x << " " << y << " ";
			}
			MyFile << std::endl;
		}
		std::cout << "New level has been created" << std::endl;
		return GOOD;
	}
	else {
		std::cout << "File didn't open" << std::endl;
		return BAD;
	}
}

int Map::DownloadMap(int lvl)
{
	int size = 0, x = 0, y = 0, time = 0, type = 0;
	std::string res;
	res = ".txt";
	std::stringstream str;
	str << "D:/Program/Lab/TowerDefence/Maps/";
	str << lvl;
	str << res;
	res = "";
	str >> res;
	std::ifstream MyFile(res);
	if (MyFile.is_open())
	{
		CleanAll();
		getline(MyFile, res); str.str(res); str.clear(); // read level and dimension
		str >> Level >> Dim;
		str.clear();
		getline(MyFile, res); str.str(res); str.clear();// read coordinates of the castle
		str >> x >> y;
		MyCast.ChangeTile(x, y);
		MyCast.Multiply(GetCoef());
		getline(MyFile, res); str.str(res); str.clear();// read number of lairs
		str >> size;
		for (int i = 0; i < size; i++)
		{
			int CountOfPtr;
			getline(MyFile, res); str.str(res); str.clear(); // read coordinates of lair
			str >> x >> y;

			Lair dop;
			dop.ChangeTile(x, y);
			Lairs.Insert(Lairs.cend(), dop);
			str >> CountOfPtr; // read number of monsters in this lair
			for (int j = 0; j < CountOfPtr; j++) // read types and times of every monster from this lair
			{
				str >> type >> time;
				AddEnemy(type, time, i);
			}
		}
		Fields = new int* [Dim];
		for (int i = 0; i < Dim; i++) // read map
		{
			Fields[i] = new int[Dim];
			getline(MyFile, res); str.str(res); str.clear();
			for (int j = 0; j < Dim; j++)
				str >> Fields[i][j];
		}
		getline(MyFile, res); str.str(res); str.clear(); // read number of nodes
		str >> size;
		for (int i = 0; i < size; i++) 
		{
			getline(MyFile, res); str.str(res); str.clear(); // read information about I node
			str >> x >> y >> type;
			Node dop(x, y, type);
			Ways.Insert(Ways.cend(), dop);
		}
		for (int i = 0; i < size; i++)
		{
			int count;
			getline(MyFile, res); str.str(res); str.clear();
			str >> count;
			for (int j = 0; j < count; j++) // add pointers to the corresponding node
			{
				str >> x >> y;
				int ind = 0;
				Node dop(x, y, type);
				for (; (ind < Ways.GetSize()) && (dop.GetTile() == Ways[ind].GetTile()); ind++);
				Ways[i].Insert(Ways[i].cend(), &(Ways[ind]));
			}
		}
		return GOOD;
	}
	else {
		std::cout << "File didn't open" << std::endl;
		return BAD;
	}
}

/*=================================== Ingame functions ==================================*/

int Map::Revive(int IndOfLair, int IndOfEnemy)
{
	if ((IndOfLair < 0) || (IndOfLair > Lairs.GetSize()))
	{
#ifdef DEBUG
		std::cout << "Index of lair is out of range" << std::endl;
#endif
		return BAD;
	}
	if ((IndOfEnemy < 0) || (IndOfEnemy > Lairs[IndOfLair].Enemies.GetSize()))
	{
#ifdef DEBUG
		std::cout << "Index of enemy is out of range" << std::endl;
#endif
			return BAD;
	}
	Enemy* buf = Lairs[IndOfLair].Enemies[IndOfEnemy]; ConstIter<Enemy*> it(&Lairs[IndOfLair].Enemies[IndOfEnemy]);
	Lairs[IndOfLair].Enemies.Erase(it, it + 1);
	Monsters.Insert(Monsters.cend(), buf);
	MyVector<Tile> NewWay;
	if (Dijkstra(Lairs[IndOfLair].Field, MyCast.GetTile(), NewWay) == GOOD)
	{
		int MyInd = Monsters.GetSize() - 1;
		Monsters[MyInd]->ChangeWay(NewWay);
		Monsters[MyInd]->ChangeTile(NewWay[0]);
	}
	else
		return BAD;
	return GOOD;
}

int Map::KillMonst(int IndOfEnemy)
{
	if ((IndOfEnemy < 0) || (IndOfEnemy >= Monsters.GetSize()))
	{
#ifdef DEBUG
		std::cout << "Index of enemy is out of range" << std::endl;
#endif
		return BAD;
	}
	if (Monsters[IndOfEnemy]->GetHealth() == 0)
	{
		delete Monsters[IndOfEnemy];
		ConstIter<Enemy*> it(&Monsters[IndOfEnemy]);
		Monsters.Erase(it, it + 1);
		return GOOD;
	}
	else {
		std::cout << "This enemy was still alive" << std::endl;
		return BAD;
	}
}

int Map::BreakWall(int IndOfWall)
{
	if ((IndOfWall < 0) || (IndOfWall >= Walls.GetSize()))
	{
#ifdef DEBUG
		std::cout << "Index of wall if out of range" << std::endl;
#endif
		return BAD;
	}
	if (Walls[IndOfWall].GetHealth() == 0)
	{
		ConstIter<Wall> it(&Walls[IndOfWall]);
		int x, y;
		(*it).GetCoord(x, y);
		Fields[x][y] = ROAD;
		Walls.Erase(it, it + 1);
		return GOOD;
	}
	else {
		std::cout << "This wall wasn't broken" << std::endl;
		return BAD;
	}
}

int Map::BuildWall(int x0, int y0)
{
	Wall Dop(GetCoef(), x0, y0);
	if (MyCast.Cash() < Dop.GetPr()) {
		std::cout << "You don't have enough money for build new wall" << std::endl;
		return BAD;
	}
	int type = Fields[x0][y0];
	if ((type == ROAD) && (CheckMonst(x0, y0) == GOOD))
	{
		Fields[x0][y0] = WALL;
		MyCast.BuySmth(Dop.GetPr());
		Walls.Insert(Walls.cend(), Dop);
	}
	else {
		std::cout << "This tile is busy" << std::endl;
		return BAD;
	}
	return GOOD;
}

int Map::BuildTow(int x0, int y0)
{
	Tower Dop(GetCoef(), x0, y0);
	if (MyCast.Cash() < Dop.GetPr()) {
		std::cout << "You don't have enough money for build new tower" << std::endl;
		return BAD;
	}
	int type = Fields[x0][y0];
	if ((type == VALLEY) && (CheckMonst(x0, y0) == GOOD))
	{
		Fields[x0][y0] = TOWER;
		MyCast.BuySmth(Dop.GetPr());
		Towers.Insert(Towers.cend(), Dop);
	}
	else {
		std::cout << "This tile is busy" << std::endl;
		return BAD;
	}
	return GOOD;
}

int Map::CheckMonst(int x0, int y0)
{
	int x, y, flag = GOOD;
	for (int i = 0; i < Monsters.GetSize(); i++)
	{
		Monsters[i]->GetCoord(x, y);
		if ((x == x0) && (y == y0)) {
			flag = BAD; i = Monsters.GetSize();
		}
	}
	return flag;
}