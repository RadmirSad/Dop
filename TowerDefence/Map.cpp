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
			std::cout << "  " << GetCoordType(i, j);
			if (j + 1 == Dim) std::cout << std::endl;
		}
	}
}