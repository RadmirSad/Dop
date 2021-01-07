#include "Map.h"

/*============================ Methods for Destruct ================================*/

Destruct::Destruct(double MHp, const Tile& NewTile) : Field(NewTile)
{
	if (MHp <= 0) throw std::invalid_argument("Impermissible amount of health.");
	MaxHealth = MHp;
	Health = MHp;
}

Destruct::Destruct(double MHp, int x0, int y0) : Field(x0, y0)
{
	if (MHp <= 0) throw std::invalid_argument("Impermissible amount of health.");
	MaxHealth = MHp;
	Health = MHp;
}

int Destruct::TakeDamage(double Hp)
{
	if (Hp <= 0)
		throw std::invalid_argument("Damage must be more than 0");
	Health -= Hp;
	if (Health <= 0)
	{
		Health = 0;
		return DEAD;
	}
	else return ALIVE;
}

int Destruct::SetMaxHealth(double MHp)
{
	if (MHp <= 0) return BAD;
	MaxHealth = MHp;
	return GOOD;
}

/*========================= Methods for Building ====================*/

Building::Building(int Cost, double Inc, double MHp, const Tile& NewField) : Destruct(MHp, NewField)
{
	if (Cost <= 0) throw std::invalid_argument("Impossible cost of repair.");
	if (Inc <= 0) throw std::invalid_argument("Impossible value of added health.");
	CostOfRepair = Cost;
	HpIncrease = Inc;
}

Building::Building(int Cost, double Inc, double MHp, int x0, int y0) : Destruct(MHp, x0, y0)
{
	if (Cost <= 0) throw std::invalid_argument("Impossible cost of repair.");
	if (Inc <= 0) throw std::invalid_argument("Impossible value of added health.");
	CostOfRepair = Cost;
	HpIncrease = Inc;
}

int Building::Repair(Castle& MyCast)
{
	if (MyCast.Cash() - CostOfRepair < 0)
	{
		std::cout << "You don't have enough money" << std::endl;
		return BAD;
	}
	if (Health + HpIncrease > MaxHealth) Health = MaxHealth;
	else Health += HpIncrease;
	MyCast.BuySmth(CostOfRepair);
	return GOOD;
}