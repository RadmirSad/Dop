#include "Game.h"

/*=============================== Methods for map ===============================*/

int Map::ChangeType(const int NewType, const int x, const int y)
{
	if ((NewType < ROAD) || (NewType > CASTLE)) return BAD;
	Tile[x][y] = NewType;
	return 0;
}

int Map::GetType(const Point& a) const
{
	int x, y;
	a.GetCoord(x, y);
	return Tile[x][y];
}

int Map::GenerStartMap()
{
	Fields = new Tile* [Dim];
	for (int i = 0; i < Dim; i++) {
		Fields[i] = new Tile[Dim];
		for (int j = 0; j < Dim; j++)
			Fields[i][j].ChangeType(VALLEY);
	}


	return 0;
}

void Map::CheckMap()
{
	for (int i = 0; i < Dim; i++)
	{
		for (int j = 0; j < Dim; j++)
		{
			std::cout << "  " << GetType(i, j);
			if (j + 1 == Dim) std::cout << std::endl;
		}
	}
}


/*=======================Methods for destructible objects========================*/

Destruct::Destruct(int MHp)
{
	if (MHp <= 0) throw std::invalid_argument("Impermissible amount of health.");
	MaxHealth = MHp;
	Health = MHp;
}

int Destruct::TakeDamage(const int Hp)
{
	Health -= Hp;
	if (Health <= 0)
	{
		Health = 0;
		return DEAD;
	}
	else return ALIVE;
}

int Destruct::SetMaxHealth(const int MHp)
{
	if (MHp <= MaxHealth) return BAD;
	MaxHealth = MHp;
	Health = MHp;
	return GOOD;
} 