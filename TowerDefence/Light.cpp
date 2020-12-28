#include "Map.h"

/*============================ Methods for Destruct ================================*/

Destruct::Destruct(double MHp, const Tile& NewTile): Field(NewTile)
{
	if (MHp <= 0) throw std::invalid_argument("Impermissible amount of health.");
	MaxHealth = MHp;
	Health = MHp;
}

Destruct::Destruct(double MHp, int x0, int y0): Field(x0, y0)
{
	if (MHp <= 0) throw std::invalid_argument("Impermissible amount of health.");
	MaxHealth = MHp;
	Health = MHp;
}

int Destruct::TakeDamage(double Hp)
{
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

Building::Building(int Cost, double Inc, double MHp, const Tile& NewField): Destruct(MHp, NewField)
{
	if (Cost <= 0) throw std::invalid_argument("Impossible cost of repair.");
	if (Inc <= 0) throw std::invalid_argument("Impossible value of added health.");
	CostOfRepair = Cost;
	HpIncrease = Inc;
}

Building::Building(int Cost, double Inc, double MHp, int x0, int y0): Destruct(MHp, x0, y0)
{
	if (Cost <= 0) throw std::invalid_argument("Impossible cost of repair.");
	if (Inc <= 0) throw std::invalid_argument("Impossible value of added health.");
	CostOfRepair = Cost;
	HpIncrease = Inc;
}

void Building::Repair()
{
	if (Health + HpIncrease > MaxHealth) Health = MaxHealth;
	else Health += HpIncrease;
}

/*================================ Methods for Castle ================================*/

Castle::Castle(double coef, int x, int y): Building((int)(100 * coef), 100 * coef, 250 * coef, x, y), 
	Revenue((int)(coef * 15)), CashBalance(50 * coef), CostOfUpg((int)(150 * coef))
{
	if (coef < 1) throw std::invalid_argument("Impossible value of level");
}

int Castle::ChangeRevenue(int NewRev)
{
	if (NewRev <= 0) {
		std::cout << "New revenue should be more than 0" << std::endl;
		return BAD;
	}
	Revenue = NewRev;
	return GOOD;
}

void Castle::Upgrade(double coef)
{
	CashBalance -= CostOfUpg;
	CostOfUpg += (int)(100 * coef);
	Revenue += (int)(15 * coef);
	CostOfUpg += (int)(75 * coef);
}

int Castle::BuySmth(double Cost)
{
	if (Cost <= 0) {
#ifdef DEBUG
		std::cout << "Invalid value of cost" << std::endl;
#endif
		return BAD;
	}
	if (CashBalance - Cost < 0) {
		std::cout << "You don't have enough money" << std::endl;
		return BAD;
	}
	CashBalance -= Cost;
	return GOOD;
}

void Castle::Multiply(double coef)
{
	CashBalance *= coef; CostOfUpg = (int)(coef * CostOfUpg);
	Health *= coef; CostOfRepair = (int)(coef * CostOfRepair);
	HpIncrease *= coef; MaxHealth *= coef; Revenue = (int)(coef * Revenue);
}

/*=============================== Methods for Tower ===============================*/

int Tower::ToDamage(Map& MyMap)
{
	if ((Tracker == nullptr) || (GetDist(Tracker->GetTile(), Field) > Radius))
	{
		Tracker = nullptr;
		Tracker = FindEnemy(MyMap);
	}	
	if ((Tracker != nullptr) && (Tracker->TakeDamage(DamPerSec) == DEAD))
	{
		int index = 0;
		while ((index < MyMap.Monsters.GetSize()) && (MyMap.Monsters[index] != Tracker)) index++;
		return MyMap.KillMonst(index);
	}
	return GOOD;
}

Enemy* Tower::FindEnemy(const Map& MyMap)
{
	int MySize = MyMap.Monsters.GetSize(), dist;
	for (int i = 0; i < MySize; i++)
	{
		Tile Sec(MyMap.Monsters[i]->GetTile());
		dist = GetDist(Field, Sec);
		if (dist <= Radius) return MyMap.Monsters[i];
	}
	return nullptr;
}

int Tower::Upgrade(Map& MyMap)
{
	if (MyMap.MyCast.Cash() < CostOfUp) {
		std::cout << "You don't have enough money for upgrade this tower" << std::endl;
		return BAD;
	}
	CostOfUp += 10;
	DamPerSec += 5 * MyMap.GetCoef();
	Radius += 1;
	MyMap.MyCast.BuySmth(CostOfUp);
	return GOOD;
}