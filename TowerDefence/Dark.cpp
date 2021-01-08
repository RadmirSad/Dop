#include "Map.h"

Lair::~Lair()
{
	int ind = 0;
	while (ind < Enemies.GetSize())
	{
		delete Enemies[ind];
		ind++;
	}
	Enemies.Clear();
}

/*========================================= Methods for 'Enemy' =======================================*/

Enemy::~Enemy()
{
	WayForEnemy.Clear();
	BrosWithAura.Clear();
}

Enemy::Enemy(double MyDam, int Sp, double Reg, int Time, double NewHp, int x, int y)
{
	if((MyDam <= 0) || (Sp <= 0) || (Reg <= 0) || (NewHp <= 0) || (x < 0) || (y < 0))
		throw std::invalid_argument("One of parameters had invalid value");
	DamPerSec = MyDam, Speed = Sp, SpeedOfRegen = Reg, TimeOfExit = Time, Health = NewHp, MaxHealth = NewHp, Field.ChangeTile(x, y);
}

int Enemy::TakeDam(double Dam)
{
	TimeWithDam = 0;
	return TakeDamage(Dam);
}

int Enemy::ChangeTime(int NewTime)
{
	if (NewTime < 0) {
		std::invalid_argument("Time was less then 0");
		return BAD;
	}
	TimeOfExit = NewTime;
	return GOOD;
}

void Enemy::Regen()
{
	if (Health + SpeedOfRegen > MaxHealth) Health = MaxHealth;
	else Health += SpeedOfRegen;
}

int Enemy::Increase(double AurDam, double AurSp, double AurReg, double AurHp)
{
	if ((AurDam < 1) || (AurSp < 1) || (AurReg < 1) || (AurHp < 1)) {
		throw std::invalid_argument("The coefficient must be greater than 1");
		return BAD;
	}
	coef[DAMAGE] *= AurDam, coef[SPEED] *= AurSp, coef[REGEN] *= AurReg, coef[HP] *= AurHp;
	Health *= AurHp; MaxHealth *= AurHp;
	return GOOD;
}

int Enemy::Reduce(double AurDam, double AurSp, double AurReg, double AurHp)
{
	if ((AurDam < 1) || (AurSp < 1) || (AurReg < 1) || (AurHp < 1)) {
		throw std::invalid_argument("The coefficient must be greater than 1");
		return BAD;
	}
	coef[DAMAGE] /= AurDam, coef[SPEED] /= AurSp, coef[REGEN] /= AurReg, coef[HP] /= AurHp;
	Health /= AurHp; MaxHealth /= AurHp;
	if ((coef[DAMAGE] < 1) || (coef[SPEED] < 1) || (coef[REGEN] < 1) || (coef[HP] < 1))
	{
		throw std::logic_error("Critical error. One of the coefficients were less than 1");
		return BAD;
	}
	return GOOD;
}

/*=================================== Methods for Enemies ==================================*/

int Enemy::DoAction(Map& MyMap)
{
	if (TimeWithDam < 5) TimeWithDam++;
	else Regen();
	int index = WayForEnemy.find(Field), flag_for_cast = 0, cycle = 1;
	while (cycle <= (int)(Speed * coef[SPEED]))
	{
		int type = MyMap.GetCoordType(WayForEnemy[index + cycle]);
		Field = WayForEnemy[index + cycle - 1];
		if (type == CASTLE)
		{
			flag_for_cast = MyMap.TDamCast(DamPerSec);
			if (flag_for_cast == DEAD)
				return DEAD;
			break;
		}
		else if (type == WALL)
			break;
		else
		{
			Field = WayForEnemy[index + cycle];
			cycle++;
		}
		if (Recalculation(MyMap) == BAD) {
			std::cout << "Error of calculation" << std::endl;
			return BAD;
		}
	}
	return GOOD;
}

int BigBoy::DoAction(Map& MyMap)
{
	if (TimeWithDam < 5) TimeWithDam++;
	else Regen();
	int index = WayForEnemy.find(Field), flag_for_cast = 0, flag_for_wall = 0, cycle = 1;
	while (cycle <= (int)(Speed * coef[SPEED])) // Check all tiles before the right one
	{
		int type = MyMap.GetCoordType(WayForEnemy[index + cycle]); // Save type of the next tile for further actions
		Field = WayForEnemy[index + cycle - 1]; // Do step on the next tile from way
		if (type == CASTLE) // If the castle is on this cell monster should stop and inflict damage
		{
			flag_for_cast = MyMap.TDamCast(DamPerSec);
			if (flag_for_cast == DEAD)
				return DEAD;
			break;
		}
		else if (type == WALL)
		{
			int MyInd = 0;
			while ((MyInd < MyMap.Walls.GetSize()) && (WayForEnemy[index + cycle] != (MyMap.Walls[MyInd].GetTile())))
				MyInd++;
			flag_for_wall = MyMap.TDamWall(DamPerSec, MyInd);
			if (flag_for_wall == DEAD)
				MyMap.BreakWall(MyInd);
			break;
		}
		else
		{
			Field = WayForEnemy[index + cycle];
			cycle++;
		}
		if (Recalculation(MyMap) == BAD) {
			std::cout << "Error of calculation" << std::endl;
			return BAD;
		}
	}
	return GOOD;
}

int Enemy::Recalculation(Map& MyMap)
{
	int MonstInt = 0, BroInt = 0;
	for ( ; MonstInt < MyMap.Monsters.GetSize(); MonstInt++)
	{		
		if ((MyMap.Monsters[MonstInt]->GetType() < TEEN) || (MyMap.Monsters[MonstInt] == this))
			continue;
		BroInt = 0;
		Enemy* buf = MyMap.Monsters[MonstInt];				 // Check vector of monsters and find supervillains without "this" monster
		if (GetDist(buf->GetTile(), Field) <= buf->GetRad()) // Check distance between "this" monster and monster from vector
		{													 // if distance between them less then radius of monster from vector					 
			while (BroInt < BrosWithAura.GetSize())			 // we should put this monster in our BroVect if it won't be there before
			{												 // and increase our coef
				if (buf == BrosWithAura[BroInt]) break;
				BroInt++;
			}
			if (BroInt == BrosWithAura.GetSize())
			{
				BrosWithAura.Insert(BrosWithAura.cend(), MyMap.Monsters[MonstInt]);
				double dam, sp, reg, hp;
				buf->GetAuras(dam, sp, reg, hp);
				Increase(dam, sp, reg, hp);
			}
		}
		else												// Otherwise we should check our BroVect for monster from vector
		{													// and if it will be here we must delete him from there and return our coef
			while (BroInt < BrosWithAura.GetSize())
			{
				if (buf == BrosWithAura[BroInt])
				{
					ConstIter<Enemy*> fir(&BrosWithAura[BroInt]), sec;
					if (BroInt + 1 < BrosWithAura.GetSize()) sec = &BrosWithAura[BroInt + 1];
					else sec = BrosWithAura.cend();
					BrosWithAura.Erase(fir, sec);
					double dam, sp, reg, hp;
					buf->GetAuras(dam, sp, reg, hp);
					Reduce(dam, sp, reg, hp);
					break;
				}
				BroInt++;
			}
		}
	}
	return GOOD;
}

/*================================= Methods for Supervillains ====================================*/

Supervillain::Supervillain(int Rad, double DopDam, double DopSp, double DopReg, double DopHp)
{
	if ((Rad <= 0) || (DopDam < 1) || (DopSp < 1) || (DopReg < 1) || (DopHp < 1))
		throw std::invalid_argument("One of parameters had invalid value");
	RadOfAuras = Rad; AurasRatio[DAMAGE] = DopDam; AurasRatio[SPEED] = DopSp; AurasRatio[REGEN] = DopReg; AurasRatio[HP] = DopHp;
}

int Supervillain::ChangeRad(int NewRad)
{
	if (NewRad <= 0) {
		std::cout << "New radius should be more than 0" << std::endl;
		return BAD;
	}
	RadOfAuras = NewRad;
	return GOOD;
}

int Supervillain::ChangeAur(int Num, double NewAurRat)
{
	if ((Num > 3) || (Num < 0) || (NewAurRat <= 1))
	{
		std::cout << "Invalid values" << std::endl;
		return BAD;
	}
	AurasRatio[Num] = NewAurRat;
	return GOOD;
}
