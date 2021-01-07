#include "Tile.h"

/*======================= Methods for Tile ========================*/

Tile::Tile(int x0, int y0)
{
	if ((x0 < 0) || (y0 < 0)) throw std::invalid_argument("Invalid coordinate value");
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

std::ostream& operator << (std::ostream& out, const Tile& dop)
{
	out << "  [" << dop.X << ", " << dop.Y << "]  ";
	return out;
}