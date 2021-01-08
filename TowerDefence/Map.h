#pragma once

#ifndef _MAP_H_
#define _MAP_H_

#include "Dark.h"
#include <sstream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <mutex>
#include <thread>
#include <Windows.h>

/**
@mainpage
Здравствуйте!
На данном сайте вы сможете найти документацию по всем классам, присутствующим в моей программе, кроме контейнерных.
*/

/** 
@brief Функция, вычисляющая расстояение между двумя клетками
@param fir Константная ссылка на первую клетку
@param sec Константная ссылка на вторую клетку
@return Целочисленное значение расстояния между клетками
*/
int GetDist(const Tile& fir, const Tile& sec);
/**
@brief Функция проверки существования уровней до переданного значения, не включая его
@param NewLevel Значение уровня, до которого будет идти проверка
@return Целочисленное значение кода ошибки
*/
int IsLevelsExist(int NewLevel);
/**
@brief Функция для проверки существования уровня с переданным значением
@param Lvl Значение уровня, которое нужно проверить
@return Целочисленное значение кода ошибки
*/
int ThisLevelExist(int Lvl);
/**
@brief Функция для запуска игры
@param MyMap Изменяемый объект типа "Карта"
*/
void StartGame(Map& MyMap);
/**
@brief Функция для установки нового уровня и загрузки соответсвующей карты
@param MyMap Изменяемый объект типа "Карта"
@return Целочисленное значение кода ошибки
*/
int DownloadDial(Map& MyMap);
/**
@brief Функция для проверки клеток на возможность случайной генерации карты
@param MyMap Константная ссылка на объект типа "Карта"
@return Целочисленное значение кода ошибки
*/
int CheckCellsForRand(const Map& MyMap);
/**
@brief Функция работы башен
@param MyMap Ссылка на объект типа "Карта"
@param flag_for_monst Ссылка на флаг для окончания игры
@return Целочисленное значение кода ошибки
*/
int OnlyTowers(Map& MyMap, int& flag_for_monst);
/**
@brief Функция действий врагов
@param MyMap Ссылка на объект типа "Карта"
@param flag_for_alive Ссылка на флаг для окончания игры
@return Целочисленное значение кода ошибки
*/
int OnlyMonsters(Map& MyMap, int& flag_for_alive);
/**
@brief Функция для вызова внутриигрового меню
@param MyMap Ссылка на объект типа "Карта"
@param quit Ссылка на флаг для окончания игры
*/
void GetMenu(Map& MyMap, int& quit);
/** @brief Функция очистки консоли */
void clear_cmd();
/**
@brief Функция постройки нового объекта
@param MyMap Ссылка на объект типа "Карта"
@param type Тип нового объекта
*/
void NewObject(Map& MyMap, int type);
/**
@brief Функция для ввода новых координат
@param x Переменная, в которую будет записано значение координаты по оси X
@param y Переменная, в которую будет записано значение координаты по оси Y
@param MyMap Ссылка на объект типа "Карта"
*/
void GetCoordinates(int& x, int& y, const Map& MyMap);
/**
@brief Функция для улучшения какой-либо башни
@param MyMap Ссылка на объект типа "Карта"
*/
void UpgradeTow(Map& MyMap);
/**
@brief Функция ожидания вызова меню пользователем
@param MyMap Ссылка на объект типа "Карта"
@param flag_for_exit Ссылка на флаг для окончания игры
*/
void Waiting(Map& MyMap, int& flag_for_exit);

/*=============================== Map ===============================*/

/** @brief Класс объекта типа "Карта"*/
class Map
{
private:
	int** Fields = nullptr;		//!< Целочисленные значения типов клеток карты
	int Dim = 10;				//!< Размер карты
	int Level = 1;				//!< Уровень карты
	Castle MyCast;				//!< Замок
	MyVector<Lair> Lairs;		//!< Вектор логов
	MyVector<Enemy*> Monsters;	//!< Вектор указателей живых врагов
	MyVector<Wall> Walls;		//!< Вектор поставленных стен
	MyVector<Tower> Towers;		//!< Вектор установленных башен
	MyVector<Node> Ways;		//!< Вектор узлов графа для построения путей

/**
@brief Метод для ввода и установки нового значения уровня с проверками на возможность установки
@param flag Флаг для работы при загрузке уровня из файла
@return Целочисленное значение кода ошибки
*/
	int InstallLevel(int flag = 0);
/**
@brief Метод для изменения значение уровня
@param NewLvl Новое значение уровня карты
@throw invalid_argument Если значение уровня меньше или равно 0
@return Целочисленное значение кода ошибки
*/
	int ChangeLevel(int NewLvl);

/** 
@brief Метод для выбора нового значения типа выбранной клетки
@return Целочисленное значение кода ошибки
*/
	int ChangeCellType();
/**
@brief Метод для проверки карты на наличие пустых клеток
@return Целочисленное значение кода ошибки
*/
	int CheckEmptyCells() const;
/**
@brief Метод для проверки карты на наличие пустых логов
@return Целочисленное значение кода ошибки
*/
	int CheckEmptyLairs() const;
/**
@brief Метод для проверки существования путей от логов до замка
@return Целочисленное значение кода ошибки
*/
	int IsRoadExist() const;
/**
@brief Метод для добавления узла в граф путей
@param x Значение координаты по оси X
@param y Значение координаты по оси Y
*/
	void AddPoint(int x, int y);
/**
@brief Метод для добавления нового врага в логово
@param base_type Тип врага
@param base_time Время выхода из логова
@param num_of_lair Индекс логова
*/
	void AddEnemy(int base_type = -1, int base_time = -1, int num_of_lair = -1);
/** @brief Метод для очистки типов клеток */
	void CleanMap();
/**
@brief Метод установки указателей между последним вставленным узлом и узлом, расположенным по указанным координатам
@param xsec Значение координаты по оси X
@param ysec Значение координаты по оси Y
*/
	void AddEdges(int xsec, int ysec);
/**
@brief Метод для нахождения кратчайшего пути между двумя вершинами графа путей
@param start Начальная клетка
@param end Конечная клетка
@param way Ссылка на вектор клеток, в который будет записан конечный путь
@param IsFly Флаг для построения путей для сухопутных врагов и летающих
@return Целочисленное значение кода ошибки
*/
	int Dijkstra(const Tile& start, const Tile& end, MyVector<Tile>& way, int IsFly) const;

/**
@brief Метод для выпуска врага из логова
@param IndOfLair Индекс логова
@param IndOfEnemy Индекс врага
@return Целочисленное значение кода ошибки
*/
	int Revive(int IndOfLair, int IndOfEnemy);
/**
@breif Метод для удаления врага, который был уничтожен
@param IndOfEnemy Индекс врага
@return Целочисленное значение кода ошибки
*/
	int KillMonst(int IndOfEnemy);
/**
@breif Метод для удаления уничтоженной стены
@param IndOfWall Индекс стены
@return Целочисленное значение кода ошибки
*/
	int BreakWall(int IndOfWall);
/**
@breif Метод для загрузки карты из файла
@param lvl Уровень карты, которую нужно загрузить
@return Целочисленное значение кода ошибки
*/
	int DownloadMap(int lvl);
/**
@brief Метод для сохранения карты в файл
@return Целочисленное значение кода ошибки
*/
	int SaveMap();
/** @brief Метод для случайной генерации карты */
	void RandGenerate();
/** @brief Метод для изменения типов незанятых клеток на тип Равнина*/
	void FullValley();
/**
@brief Метод для проверки наличия монстра на клетке с указанными координатами
@param x0 Значение координаты по оси X
@param y0 Значение координаты по оси Y
*/
	int CheckMonst(int x0, int y0) const;
/**
@brief Метод для поиска индекса переданного узла у узла с переданным индексом
@param MyNode Указатель на узел, индекс которого будет в поиске
@param index Индекс узла, в указателях которого будет искаться индекс
@return Целочисленное значение кода ошибки
*/
	int CheckPointers(Node* MyNode, int index) const;

public:
/** @brief Пустой конструктор*/
	Map() { ; }
/** @brief Деструктор*/
	~Map();
/**
@brief Метод для вывода карты на экран
@param flag_for_create Флаг проверки вывода дополнительной информации, нужной при создании карты
*/
	void PrintMap(int flag_for_create = 1);
/** @brief Метод для вывода таблицы с информацией о замке, башнях, стенах*/
	void PrintTable();
/**
@brief Метод для получения размера
@return Размер карты
*/
	int GetDim() const { return Dim; };
/**
@brief Метод для получения типа клетки по существующей клетке
@param a Клетка, тип которой нужно получить
@throw out_of_range Если одна из координат клетки меньше нуля или не меньше размера карты
@return Целочисленное значение кода ошибки
*/
	int GetCoordType(const Tile& a) const;
/**
@brief Метод для получения типа клетки по координатам
@param x Значение координаты по оси X
@param y Значение координаты по оси Y
@throw out_of_range Если одна из координат клетки меньше нуля или не меньше размера карты
@return Целочисленное значение кода ошибки
*/
	int GetCoordType(int x, int y) const;
/**
@brief Метод для изменения типа клетки
@param NewType Новое значение типа клетки
@param x Значение координаты по оси X
@param y Значение координаты по оси Y
@throw out_of_range Если одна из координат клетки меньше нуля или не меньше размера карты
@return Целочисленное значение кода ошибки
*/
	int ChangeType(int NewType, int x, int y);
/** @brief Метод для полной очистки объекта типа "Карта"*/
	void CleanAll();

/**
@brief Метод для создания пользователем новой карты
@return Целочисленное значение кода ошибки
*/
	int DialogMap();
/**
@brief Метод для нанесения урона замку
@param Dam Значение урона
@return Целочисленное значение кода ошибки
*/
	int TDamCast(double Dam) { return MyCast.TakeDamage(Dam); }
/**
@brief Метод для нанесения урона определённой стене
@param Dam Значение урона
@param index Индекс стены
@return Целочисленное значение кода ошибки
*/
	int TDamWall(double Dam, int index) { return Walls[index].TakeDamage(Dam); }
/**
@brief Метод для построения новой стены
@param x0 Значение координаты по оси X
@param y0 Значение координаты по оси Y
@return Целочисленное значение кода ошибки
*/
	int BuildWall(int x0, int y0);
/**
@brief Метод для построения новой башни
@param x0 Значение координаты по оси X
@param y0 Значение координаты по оси Y
@return Целочисленное значение кода ошибки
*/
	int BuildTow(int x0, int y0);
/**
@brief Метод для улучшения замка
@return Целочисленное значение кода ошибки
*/
	int UpgCast() { return MyCast.Upgrade(GetCoef()); }
/**
@brief Метод для починки замка
@return Целочисленное значение кода ошибки
*/
	int RepCast() { return MyCast.Repair(MyCast); }
/**
@brief Метод для получения количества здоровья замка
@return Значение здоровья замка
*/
	double GetHpCast() const { return MyCast.GetHealth(); }
/** @brief Метод для починки одной из стен */
	void RepWall();
/**
@brief Метод для получения коэффициента уровня
@return Коэффициент уровня сложности
*/
	double GetCoef() const { return (double)(Level + 9) / 10; }

	friend void StartGame(Map& MyMap);
	friend int DownloadDial(Map& MyMap);
	friend int OnlyMonsters(Map& MyMap, int& flag_for_alive);
	friend int OnlyTowers(Map& MyMap, int& flag_for_monst);
	friend void UpgradeTow(Map& MyMap);

	friend class BigBoy;
	friend class Enemy;
	friend class Tower;
};


/**
@brief Функция для получения числа
@param a Переменная, в который будет введено число
@return Целочисленное значение кода ошибки
*/
template <class number>
int Get_info(number& a)
{
	int flag = 0;
	std::string dop;
	getline(std::cin, dop);
	if (dop.length() == 0) return 0;
	for (size_t i = 0; i < dop.length(); i++)
		if ((dop[i] < '0') || (dop[i] > '9')) flag = 1;
	if (flag) return 0;
	std::stringstream ss;
	ss << dop;
	ss >> a;
	return 1;
}

/**
@brief Диалоговая функция для гарантированного ввода числа
@param Переменная, в которую будет передано числовое значение
*/
template <class number>
void Get_num(number& num)
{
	int flag = 0;
	while (!flag)
		if (Get_info(num) > 0) flag = 1;
		else std::cout << "Incorrect symbols. Try again:" << std::endl;
}

#endif