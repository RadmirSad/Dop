#pragma once

#ifndef _DARK_H_
#define _DARK_H_

#include "Light.h"

class Enemy;
class Kid;
class BigBoy;
class Helicopter;
class Supervillain;
class Teenager;
class Billy;
class BlackAdam;
class Map;
class Tile;

enum EnTypes
{
	KID,
	BB,
	HELICOPTER,

	TEEN,
	BILLY,
	ADAM
};

enum Auras
{
	DAMAGE,
	SPEED,
	REGEN,
	HP
};

class Lair
{
protected:
	MyVector<Enemy*> Enemies;
	Tile Field;
public:
	Lair() : Field() { ; };
	~Lair();
	Tile GetTile() const { return Field; }
	void GetCoord(int& x1, int& y1) const { Field.GetCoord(x1, y1); }
	void ChangeTile(int x1, int y1) { Field.ChangeTile(x1, y1); }
	friend class Map;
};

/*=========================== Enemies ===========================*/

class Enemy: public Destruct
{
protected:
	double DamPerSec = 0;
	int Speed = 0;
	double SpeedOfRegen = 0;
	int TimeOfExit = 0;
	double coef[4]{ 1, 1, 1, 1 };
	MyVector<Tile> WayForEnemy;
	MyVector<Enemy*> BrosWithAura;
public:
	Enemy(): Destruct() { ; };
	Enemy(double MyDam, int Sp, double Reg, int Time, double NewHp, int x = 0, int y = 0);
	~Enemy();
	int TimeWithDam = 0;

	double GetDam() const { return coef[DAMAGE] * DamPerSec; }
	int GetSpeed() const { return (int)(coef[SPEED] * (double)Speed); }
	double GetReg() const { return coef[REGEN] * SpeedOfRegen; }
	int GetTime() const { return TimeOfExit; }
	double GetHealth() const { return coef[HP] * Health; }
	double GetMaxHealth() const { return coef[HP] * MaxHealth; }

	void ChangeWay(const MyVector<Tile>& NewWay) { WayForEnemy = NewWay; }
	int ChangeTime(int NewTime);
	int TakeDam(double Dam);
	void Regen();
	int Increase(double AurDam, double AurSp, double AurReg, double AurHp);
	int Reduce(double AurDam, double AurSp, double AurReg, double AurHp);

	int Recalculation(Map& MyMap);
	virtual int DoAction(Map& MyMap);
	virtual int GetType() = 0;
	virtual const char* Print() const = 0;
	virtual const char* Type() const = 0;
	virtual void GetAuras(double& AurDam, double& AurSp, double& AurReg, double& AurHp) const { ; }
	virtual int GetRad() const { return -1; }
};

class Kid : public Enemy
{
public:
	Kid() : Enemy() { ; }
	Kid(double CoefOfLvl, int time = 0, double Damage = 15, int Sp = 2, double Reg = 5, double NewHp = 50, int x = 0, int y = 0) :
		Enemy(CoefOfLvl* Damage, int(Sp* CoefOfLvl), Reg* CoefOfLvl, time, CoefOfLvl * NewHp, x, y) {}
	virtual int GetType() override { return KID; }
	virtual const char* Print() const override { return " ' "; }
	virtual const char* Type() const override { return " Kid "; }
};

class BigBoy : public Enemy
{
public:
	BigBoy() { ; }
	BigBoy(double CoefOfLvl, int time = 0, double Damage = 30, int Sp = 1, double Reg = 15, double NewHp = 100, int x = 0, int y = 0) :
		Enemy(CoefOfLvl* Damage, int(Sp* CoefOfLvl), Reg* CoefOfLvl, time, CoefOfLvl* NewHp, x, y) {}
	virtual int DoAction(Map& MyMap) override;
	virtual int GetType() override { return BB; }
	virtual const char* Print() const override { return " I "; }
	virtual const char* Type() const override { return " BigBoy "; }
};

class Helicopter : public Enemy
{
public:
	Helicopter() { ; }
	Helicopter(double CoefOfLvl, int time = 0, double Damage = 20, int Sp = 2, double Reg = 5, double NewHp = 70, int x = 0, int y = 0) :
		Enemy(CoefOfLvl* Damage, int(Sp* CoefOfLvl), Reg* CoefOfLvl, time, CoefOfLvl* NewHp, x, y) {}
	virtual int GetType() override { return HELICOPTER; }
	virtual const char* Print() const override { return " + "; }
	virtual const char* Type() const override { return " Helicopter "; }
};

/*================================ Supervillains ==============================*/

class Supervillain
{
protected:
	int RadOfAuras = 0;
	double AurasRatio[4]{};
	int ChangeRad(int NewRad);
	int ChangeAur(int Num, double NewAurRat);
public:
	Supervillain() { ; }
	Supervillain(int Rad, double DopDam = 1.5, double DopSp = 1.5, double DopReg = 1.5, double DopHp = 1.5);
	int GetRadius() const { return RadOfAuras; }
	void GetMyAuras(double& AurDam, double& AurSp, double& AurReg, double& AurHp) const
	{ AurDam = AurasRatio[DAMAGE]; AurSp = AurasRatio[SPEED]; AurReg = AurasRatio[REGEN]; AurHp = AurasRatio[HP]; }
};

class Teenager: public Supervillain, public Kid
{
public:
	Teenager() : Supervillain(), Kid() { ; }
	Teenager(double CoefOfLvl, int time = 0, int RadOfAur = 3, double DopDam = 1.2, double DopSp = 2, double DopReg = 1.1, double DopHp = 1.2,
		double Damage = 15, int Sp = 2, double Reg = 5, double NewHp = 50, int x = 0, int y = 0) :
		Supervillain(RadOfAur, DopDam, DopSp, DopReg, DopHp), Kid(CoefOfLvl, time, Damage, Sp, Reg, NewHp, x, y) { ; }
	virtual int GetType() override { return TEEN; }
	virtual const char* Print() const override { return " * "; }
	virtual void GetAuras(double& AurDam, double& AurSp, double& AurReg, double& AurHp) const override
	{ GetMyAuras(AurDam, AurSp, AurReg, AurHp); }
	virtual int GetRad() const override { return GetRadius(); }
	virtual const char* Type() const override { return " Teenager "; }
};

class Billy: public Supervillain, public BigBoy
{
public:
	Billy() : Supervillain(), BigBoy() { ; }
	Billy(double CoefOfLvl, int time = 0, int RadOfAur = 5, double DopDam = 1.8, double DopSp = 1, double DopReg = 1.5, double DopHp = 1.4,
		double Damage = 30, int Sp = 1, double Reg = 15, double NewHp = 100, int x = 0, int y = 0) :
		Supervillain(RadOfAur, DopDam, DopSp, DopReg, DopHp), BigBoy(CoefOfLvl, time, Damage, Sp, Reg, NewHp, x, y) {}
	virtual int GetType() override { return BILLY; }
	virtual const char* Print() const override { return " $ "; }
	virtual void GetAuras(double& AurDam, double& AurSp, double& AurReg, double& AurHp) const override
	{ GetMyAuras(AurDam, AurSp, AurReg, AurHp); }
	virtual int GetRad() const override { return GetRadius(); }
	virtual const char* Type() const override { return " Billy "; }
};

class BlackAdam : public Supervillain, public Helicopter
{
public:
	BlackAdam() : Supervillain(), Helicopter() { ; }
	BlackAdam(double CoefOfLvl, int time = 0, int RadOfAur = 5, double DopDam = 1.5, double DopSp = 1.5, double DopReg = 1.3, double DopHp = 1.3,
		double Damage = 20, int Sp = 2, double Reg = 5, double NewHp = 70, int x = 0, int y = 0) :
		Supervillain(RadOfAur, DopDam, DopSp, DopReg, DopHp), Helicopter(CoefOfLvl, time, Damage, Sp, Reg, NewHp, x, y) {}
	virtual int GetType() override { return ADAM; }
	virtual const char* Print() const override { return " @ "; }
	virtual void GetAuras(double& AurDam, double& AurSp, double& AurReg, double& AurHp) const override
	{ GetMyAuras(AurDam, AurSp, AurReg, AurHp); }
	virtual int GetRad() const override { return GetRadius(); }
	virtual const char* Type() const override { return " Adam "; }
};

#endif