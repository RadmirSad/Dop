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

/** @brief Типы врагов */
enum EnTypes
{
	KID,
	BB,
	HELICOPTER,

	TEEN,
	BILLY,
	ADAM
};

/** @brief Типы аур */
enum Auras
{
	DAMAGE,
	SPEED,
	REGEN,
	HP
};

/** @brief Класс объекта типа "Логово"*/
class Lair
{
protected:
	MyVector<Enemy*> Enemies;	//!< Вектор указателей на врагов, которые выйдут из этого логова
	Tile Field;					//!< Клетка логова
public:
/** @brief Пустой конструктор */
	Lair() : Field() { ; };
/** @brief Деструктор */
	~Lair();
/**
@brief Метод для получения клетки логова
@return Клетка, на которой находится логово
*/
	Tile GetTile() const { return Field; }
/**
@brief Метод для получения координат логова
@param x1 Значение координаты по оси X
@param y1 Значение координаты по оси Y
*/
	void GetCoord(int& x1, int& y1) const { Field.GetCoord(x1, y1); }
/**
@brief Метод для смены координат логова
@param x1 Новое значение координаты по оси X
@param y1 Новое значение координаты по оси Y
*/
	void ChangeTile(int x1, int y1) { Field.ChangeTile(x1, y1); }

	friend class Map;
	friend int OnlyMonsters(Map& MyMap, int& flag_for_alive);
	friend int OnlyTowers(Map& MyMap, int& flag_for_monst);
};

/*=========================== Enemies ===========================*/

/** @brief Класс объекта типа "Враг"*/
class Enemy: public Destruct
{
protected:
	double DamPerSec = 0;			//!< Урон врага в секунду
	int Speed = 0;					//!< Скорость передвижения
	double SpeedOfRegen = 0;		//!< Скорость регенерации
	int TimeOfExit = 0;				//!< Время выхода из логова
	double coef[4]{ 1, 1, 1, 1 };	//!< Массив коэффициентов для улучшения
	MyVector<Tile> WayForEnemy;		//!< Путь врага
	MyVector<Enemy*> BrosWithAura;	//!< Вектор суперзлодеев, в радиус действия аур которых входит данный объект
public:
/** @brief Пустой конструктор */
	Enemy(): Destruct() { ; };
/** 
@brief Инициализирующий конструктор
@param MyDam Значение урона
@param Sp Значение скорости передвижения
@param Time Значение времени выхода из логова
@param NewHp Значение максимального здоровья
@param x Значение координаты по оси X
@param y Значение координаты по оси Y
@throw invalid_argument Если один из параметров меньше или равен 0
*/
	Enemy(double MyDam, int Sp, double Reg, int Time, double NewHp, int x = 0, int y = 0);
/** @brief Деструктор*/
	~Enemy();
	int TimeWithDam = 0; //!< Время без нанесения урона

/** 
@brief Метод для получения модифицированного урона
@return Урон, умноженный на соответствующий коэффициент
*/
	double GetDam() const { return coef[DAMAGE] * DamPerSec; }
/** 
@brief Метод для получения модифицированной скорости передвижения
@return Целочисленное значение скорости, умноженной на соответствующий коэффициент
*/
	int GetSpeed() const { return (int)(coef[SPEED] * (double)Speed); }
/**
@brief Метод для получения модифицированной скорости регенерации
@return Скорость регенерации, умноженная на соответствующий коэффициент
*/
	double GetReg() const { return coef[REGEN] * SpeedOfRegen; }
/**
@brief Метод для получения времени выхода
@return Целочисленное значение времени выхода врага из логова
*/
	int GetTime() const { return TimeOfExit; }
/**
@brief Метод для получения модифицированного здоровья врага
@return Здоровье врага в данный момент
*/
	double GetHealth() const { return Health; }
/**
@brief Метод для получения модифицированного максимального здоровья врага
@return Максимальное возможное значение здоровья врага
*/
	double GetMaxHealth() const { return MaxHealth; }

/**
@brief Метод для изменения пути врага
@param NewWay Новый путь, по которому будет идти враг
*/
	void ChangeWay(const MyVector<Tile>& NewWay) { WayForEnemy = NewWay; }
/**
@brief Метод для изменения времени выхода из логова
@param Newtume Новое значение времени
@throw invalid_argument Если новое значение времени меньше 0
@return Целочисленное значение кода операции
*/
	int ChangeTime(int NewTime);
/**
@brief Метод для принятия урона от других объектов
@param Dam Значение принимаемого урона
@return Целочисленное значение кода операции
*/
	int TakeDam(double Dam);
/** @brief Метод для регенерации врага */
	void Regen();
/**
@brief Метод для повышения коэффициентов
@param AurDam Значение коэффициента, который увеличивает предыдущее значение урона
@param AurSp Значение коэффициента, который увеличивает предыдущее значение скорости передвижения
@param AurReg Значение коэффициента, который увеличивает предыдущее значение скорости регенерации
@param AurHp Значение коэффициента, который увеличивает предыдущее значение максимального здоровья
@throw invalid_argument Если один из коэффициентов меньше 1
@return Целочисленное значение кода операции
*/
	int Increase(double AurDam, double AurSp, double AurReg, double AurHp);
/**
@brief Метод для повышения коэффициентов
@param AurDam Значение коэффициента, который уменьшает предыдущее значение урона
@param AurSp Значение коэффициента, который уменьшает предыдущее значение скорости передвижения
@param AurReg Значение коэффициента, который уменьшает предыдущее значение скорости регенерации
@param AurHp Значение коэффициента, который уменьшает предыдущее значение максимального здоровья
@throw invalid_argument Если один из коэффициентов меньше 1
@throw logic_error Если после уменьшения один из коэффициентов стал меньше 1
@return Целочисленное значение кода операции
*/
	int Reduce(double AurDam, double AurSp, double AurReg, double AurHp);

/**
@brief Метод для перерассчёта влияния суперзлодеев
Данная функция ищет среди всех живых злодеев суперзлодеев.
Затем идёт проверка расстояния между этим монстром и найденным:
Если расстояние между ними больше радиуса действия аур, то нужно этого монстра удалить из вектора указателей на суперзлодеев и исправить коэф-ты.
Если расстояние меньше радиуса, то нужно добавить суперзлодея в вектор, если он ещё там не находился.
@param MyMap Изменяемый объект типа "Карта"
@return Целочисленное значение кода операции
*/
	int Recalculation(Map& MyMap);
/**
@brief Вирутальный метод для выполнения действия врагом
@param MyMap Изменяемый объект типа "Карта"
@return Целочисленное значение кода операции
*/
	virtual int DoAction(Map& MyMap);
/** 
@brief Виртуальный метод для получения типа врага
@return Целочисленное значение типа врага
*/
	virtual int GetType() = 0;
/** 
@brief Виртуальный метод для получения символьного логотипа врага
@return Символьный рисунок врага
*/
	virtual const char* Print() const = 0;
/**
@brief Виртуальный метод для получения типа врага в виде слова
@return Символьное слово, обозначающее тип врага
*/
	virtual const char* Type() const = 0;
/**
@brief Виртуальный метод для получения коэффициентов аур суперзлодеев
@param AurDam Значение ауры урона
@param AurSp Значение ауры скорости
@param AurReg Значение ауры регенерации
@param AurHp Значение ауры здоровья
*/
	virtual void GetAuras(double& AurDam, double& AurSp, double& AurReg, double& AurHp) const { ; }
/**
@brief Виртуальный метод для получения радиуса действия аур суперзлодеев
@return Целочисленное значение радиуса действия
*/
	virtual int GetRad() const { return -1; }

	friend class Map;
};

/** @brief Класс объекта типа "Легкая пехота"*/
class Kid : public Enemy
{
public:
/** @brief Пустой конструктор*/
	Kid() : Enemy() { ; }
/**
@brief Инициализирующий конструктор
@param CoefOfLvl Коэффициент уровня сложности
@param time Время выхода из логова
@param Damage Урон объекта в секунду
@param Sp Скорость передвижения
@param Reg Скорость регенерации
@param NewHp Максимальное значение здоровья
@param x Значение координаты по оси X
@param y Значение координаты по оси Y
*/
	Kid(double CoefOfLvl, int time = 0, double Damage = 15, int Sp = 2, double Reg = 5, double NewHp = 50, int x = 0, int y = 0) :
		Enemy(CoefOfLvl* Damage, int(Sp* CoefOfLvl), Reg* CoefOfLvl, time, CoefOfLvl * NewHp, x, y) {}
/**
@brief Переопределённый виртуальный метод для получения типа врага
@return Целочисленное значение типа врага
*/
	virtual int GetType() override { return KID; }
/**
@brief Переопределённый виртуальный метод для получения символьного логотипа врага
@return Символьный рисунок врага
*/
	virtual const char* Print() const override { return " ' "; }
/**
@brief Переопределённый виртуальный метод для получения типа врага в виде слова
@return Символьное слово, обозначающее тип врага
*/
	virtual const char* Type() const override { return " Kid "; }
};

/** @brief Класс объекта типа "Тяжёлая пехота"*/
class BigBoy : public Enemy
{
public:
/** @brief Пустой конструктор*/
	BigBoy() { ; }
/**
@brief Инициализирующий конструктор
@param CoefOfLvl Коэффициент уровня сложности
@param time Время выхода из логова
@param Damage Урон объекта в секунду
@param Sp Скорость передвижения
@param Reg Скорость регенерации
@param NewHp Максимальное значение здоровья
@param x Значение координаты по оси X
@param y Значение координаты по оси Y
*/
	BigBoy(double CoefOfLvl, int time = 0, double Damage = 30, int Sp = 1, double Reg = 15, double NewHp = 100, int x = 0, int y = 0) :
		Enemy(CoefOfLvl* Damage, int(Sp* CoefOfLvl), Reg* CoefOfLvl, time, CoefOfLvl* NewHp, x, y) {}
/**
@brief Переопределённый вирутальный метод для выполнения действия врагом
@param MyMap Изменяемый объект типа "Карта"
@return Целочисленное значение кода операции
*/
	virtual int DoAction(Map& MyMap) override;
/**
@brief Переопределённый виртуальный метод для получения типа врага
@return Целочисленное значение типа врага
*/
	virtual int GetType() override { return BB; }
/**
@brief Переопределённый виртуальный метод для получения символьного логотипа врага
@return Символьный рисунок врага
*/
	virtual const char* Print() const override { return " I "; }
/**
@brief Переопределённый виртуальный метод для получения типа врага в виде слова
@return Символьное слово, обозначающее тип врага
*/
	virtual const char* Type() const override { return " BigBoy "; }
};

/** @brief Класс объекта типа "Авиация"*/
class Helicopter : public Enemy
{
public:
/** @brief Пустой конструктор*/
	Helicopter() { ; }
/**
@brief Инициализирующий конструктор
@param CoefOfLvl Коэффициент уровня сложности
@param time Время выхода из логова
@param Damage Урон объекта в секунду
@param Sp Скорость передвижения
@param Reg Скорость регенерации
@param NewHp Максимальное значение здоровья
@param x Значение координаты по оси X
@param y Значение координаты по оси Y
*/
	Helicopter(double CoefOfLvl, int time = 0, double Damage = 20, int Sp = 2, double Reg = 5, double NewHp = 70, int x = 0, int y = 0) :
		Enemy(CoefOfLvl* Damage, int(Sp* CoefOfLvl), Reg* CoefOfLvl, time, CoefOfLvl* NewHp, x, y) {}
/**
@brief Переопределённый виртуальный метод для получения типа врага
@return Целочисленное значение типа врага
*/
	virtual int GetType() override { return HELICOPTER; }
/**
@brief Переопределённый виртуальный метод для получения символьного логотипа врага
@return Символьный рисунок врага
*/
	virtual const char* Print() const override { return " + "; }
/**
@brief Переопределённый виртуальный метод для получения типа врага в виде слова
@return Символьное слово, обозначающее тип врага
*/
	virtual const char* Type() const override { return " Helicopter "; }
};

/*================================ Supervillains ==============================*/

/** @brief Класс объекта типа "Суперзлодей"*/
class Supervillain
{
protected:
	int RadOfAuras = 0;							//!< Радиус действия аур
	double AurasRatio[4]{};						//!< Ауры данного суперзлодея
/**
@brief Метод для изменения радиуса действия
@param NewRad Новое значение радиуса
@return Целочисленное значение кода ошибки
*/
	int ChangeRad(int NewRad);
/**
@brief Метод для изменения одной из 4 аур
@param Num Индекс ауры
@param NewAurRat Новое значение ауры
@return Целочисленное значение кода ошибки
*/
	int ChangeAur(int Num, double NewAurRat);
public:
/** @brief Пустой конструктор */
	Supervillain() { ; }
/**
@brief Инициализирующий конструктор
@param Rad Значение радиуса действия аур
@param DopDam Аура урона
@param DopSp Аура скорости передвижения
@param DopReg Аура регенерации
@param DopHp Аура здоровья
@throw invalid_argument Если радиус был меньше или равен 0 или если одна из аур была меньше 1
*/
	Supervillain(int Rad, double DopDam = 1.5, double DopSp = 1.5, double DopReg = 1.5, double DopHp = 1.5);
/**
@brief Метод для получения радиуса действия
@return Значение радиуса действия аур
*/
	int GetRadius() const { return RadOfAuras; }
/**
@brief Метод для получения значений всех аур
@param AurDam Аура урона
@param AurSp Аура скорости
@param AurReg Аура регенерации
@param AurHp Аура здоровья
*/
	void GetMyAuras(double& AurDam, double& AurSp, double& AurReg, double& AurHp) const
	{ AurDam = AurasRatio[DAMAGE]; AurSp = AurasRatio[SPEED]; AurReg = AurasRatio[REGEN]; AurHp = AurasRatio[HP]; }
};

/** @brief Класс объекта типа "Суперзлодей лёгкой пехоты"*/
class Teenager: public Supervillain, public Kid
{
public:
/** @brief Пустой конструктор */
	Teenager() : Supervillain(), Kid() { ; }
/**
@brief Инициализирующий конструктор
@param CoefOfLvl Коэффициент уровня сложности
@param RadOfAur Значение радиуса действия аур
@param DopDam Аура урона
@param DopSp Аура скорости передвижения
@param DopReg Аура регенерации
@param DopHp Аура здоровья
@param time Время выхода из логова
@param Damage Урон объекта в секунду
@param Sp Скорость передвижения
@param Reg Скорость регенерации
@param NewHp Максимальное значение здоровья
@param x Значение координаты по оси X
@param y Значение координаты по оси Y
*/
	Teenager(double CoefOfLvl, int time = 0, int RadOfAur = 3, double DopDam = 1.2, double DopSp = 2, double DopReg = 1.1, double DopHp = 1.2,
		double Damage = 15, int Sp = 2, double Reg = 5, double NewHp = 50, int x = 0, int y = 0) :
		Supervillain(RadOfAur, DopDam, DopSp, DopReg, DopHp), Kid(CoefOfLvl, time, Damage, Sp, Reg, NewHp, x, y) { ; }
/**
@brief Переопределённый виртуальный метод для получения типа врага
@return Целочисленное значение типа врага
*/
	virtual int GetType() override { return TEEN; }
/**
@brief Переопределённый виртуальный метод для получения символьного логотипа врага
@return Символьный рисунок врага
*/
	virtual const char* Print() const override { return " * "; }
/**
@brief Переопределённый виртуальный метод для получения коэффициентов аур суперзлодеев
@param AurDam Значение ауры урона
@param AurSp Значение ауры скорости
@param AurReg Значение ауры регенерации
@param AurHp Значение ауры здоровья
*/
	virtual void GetAuras(double& AurDam, double& AurSp, double& AurReg, double& AurHp) const override
	{ GetMyAuras(AurDam, AurSp, AurReg, AurHp); }
/**
@brief Переопределённый виртуальный метод для получения радиуса действия аур суперзлодеев
@return Целочисленное значение радиуса действия
*/
	virtual int GetRad() const override { return GetRadius(); }
/**
@brief Переопределённый виртуальный метод для получения типа врага в виде слова
@return Символьное слово, обозначающее тип врага
*/
	virtual const char* Type() const override { return " Teenager "; }
};

/** @brief Класс объекта типа "Суперзлодей тяжёлой пехоты"*/
class Billy: public Supervillain, public BigBoy
{
public:
/** @brief Пустой конструктор*/
	Billy() : Supervillain(), BigBoy() { ; }
/**
@brief Инициализирующий конструктор
@param CoefOfLvl Коэффициент уровня сложности
@param RadOfAur Значение радиуса действия аур
@param DopDam Аура урона
@param DopSp Аура скорости передвижения
@param DopReg Аура регенерации
@param DopHp Аура здоровья
@param time Время выхода из логова
@param Damage Урон объекта в секунду
@param Sp Скорость передвижения
@param Reg Скорость регенерации
@param NewHp Максимальное значение здоровья
@param x Значение координаты по оси X
@param y Значение координаты по оси Y
*/
	Billy(double CoefOfLvl, int time = 0, int RadOfAur = 5, double DopDam = 1.8, double DopSp = 1, double DopReg = 1.5, double DopHp = 1.4,
		double Damage = 30, int Sp = 1, double Reg = 15, double NewHp = 100, int x = 0, int y = 0) :
		Supervillain(RadOfAur, DopDam, DopSp, DopReg, DopHp), BigBoy(CoefOfLvl, time, Damage, Sp, Reg, NewHp, x, y) {}
/**
@brief Переопределённый виртуальный метод для получения типа врага
@return Целочисленное значение типа врага
*/
	virtual int GetType() override { return BILLY; }
/**
@brief Переопределённый виртуальный метод для получения символьного логотипа врага
@return Символьный рисунок врага
*/
	virtual const char* Print() const override { return " $ "; }
/**
@brief Переопределённый виртуальный метод для получения коэффициентов аур суперзлодеев
@param AurDam Значение ауры урона
@param AurSp Значение ауры скорости
@param AurReg Значение ауры регенерации
@param AurHp Значение ауры здоровья
*/
	virtual void GetAuras(double& AurDam, double& AurSp, double& AurReg, double& AurHp) const override
	{ GetMyAuras(AurDam, AurSp, AurReg, AurHp); }
/**
@brief Переопределённый виртуальный метод для получения радиуса действия аур суперзлодеев
@return Целочисленное значение радиуса действия
*/
	virtual int GetRad() const override { return GetRadius(); }
/**
@brief Переопределённый виртуальный метод для получения типа врага в виде слова
@return Символьное слово, обозначающее тип врага
*/
	virtual const char* Type() const override { return " Billy "; }
};

/** @brief Класс объекта типа "Суперзлодей авиации"*/
class BlackAdam : public Supervillain, public Helicopter
{
public:
/** @brief Пустой конструктор*/
	BlackAdam() : Supervillain(), Helicopter() { ; }
/**
@brief Инициализирующий конструктор
@param CoefOfLvl Коэффициент уровня сложности
@param RadOfAur Значение радиуса действия аур
@param DopDam Аура урона
@param DopSp Аура скорости передвижения
@param DopReg Аура регенерации
@param DopHp Аура здоровья
@param time Время выхода из логова
@param Damage Урон объекта в секунду
@param Sp Скорость передвижения
@param Reg Скорость регенерации
@param NewHp Максимальное значение здоровья
@param x Значение координаты по оси X
@param y Значение координаты по оси Y
*/
	BlackAdam(double CoefOfLvl, int time = 0, int RadOfAur = 5, double DopDam = 1.5, double DopSp = 1.5, double DopReg = 1.3, double DopHp = 1.3,
		double Damage = 20, int Sp = 2, double Reg = 5, double NewHp = 70, int x = 0, int y = 0) :
		Supervillain(RadOfAur, DopDam, DopSp, DopReg, DopHp), Helicopter(CoefOfLvl, time, Damage, Sp, Reg, NewHp, x, y) {}
/**
@brief Переопределённый виртуальный метод для получения типа врага
@return Целочисленное значение типа врага
*/
	virtual int GetType() override { return ADAM; }
/**
@brief Переопределённый виртуальный метод для получения символьного логотипа врага
@return Символьный рисунок врага
*/
	virtual const char* Print() const override { return " @ "; }
/**
@brief Переопределённый виртуальный метод для получения коэффициентов аур суперзлодеев
@param AurDam Значение ауры урона
@param AurSp Значение ауры скорости
@param AurReg Значение ауры регенерации
@param AurHp Значение ауры здоровья
*/
	virtual void GetAuras(double& AurDam, double& AurSp, double& AurReg, double& AurHp) const override
	{ GetMyAuras(AurDam, AurSp, AurReg, AurHp); }
/**
@brief Переопределённый виртуальный метод для получения радиуса действия аур суперзлодеев
@return Целочисленное значение радиуса действия
*/
	virtual int GetRad() const override { return GetRadius(); }
/**
@brief Переопределённый виртуальный метод для получения типа врага в виде слова
@return Символьное слово, обозначающее тип врага
*/
	virtual const char* Type() const override { return " Adam "; }
};

#endif