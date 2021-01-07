#include "Map.h"


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

int Castle::Upgrade(double coef)
{
	if (CashBalance - CostOfUpg < 0)
	{
		std::cout << "You don't have enough money for upgrade" << std::endl;
		return BAD;
	}
	CashBalance -= CostOfUpg;
	CostOfUpg += (int)(100 * coef);
	Revenue += (int)(15 * coef);
	CostOfRepair += (int)(75 * coef);
	MaxHealth += (60 * coef);
	Health = MaxHealth;
	return GOOD;
}

int Castle::BuySmth(double Cost)
{
	if (Cost <= 0)
		throw std::invalid_argument("Invalid value of cost");
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

void Castle::SetBasicParams()
{
	CashBalance = 50, Revenue = 15, CostOfUpg = 150;
	CostOfRepair = 100, HpIncrease = 100, MaxHealth = 250, Health = 250;
}

/*=============================== Methods for Tower ===============================*/

int Tower::ToDamage(Map& MyMap)
{
	if ((Tracker == nullptr) || (GetDist(Tracker->GetTile(), Field) > Radius))
	{
		Tracker = nullptr;
		Tracker = FindEnemy(MyMap);
	}
	if (Tracker != nullptr)
	{
		int result = Tracker->TakeDamage(DamPerSec);
		Tracker->TimeWithDam = 0;
		if (result == DEAD)
		{
			int index = 0;
			while ((index < MyMap.Monsters.GetSize()) && (MyMap.Monsters[index] != Tracker))
				index++; // Find index of dead monster
			if (index == MyMap.Monsters.GetSize()) throw std::logic_error("Index was more than available");
			index = MyMap.KillMonst(index);
			return index;
		}
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