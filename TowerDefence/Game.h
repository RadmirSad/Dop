#pragma once

#ifndef _GAME_H_
#define _GAME_H_

#include "Ptr.h"

template <class TypePtr>
class Tile
{
private:
	SmartPtr<TypePtr> Obj;
	int TypeOfLand;
public:
	Tile() : Obj(nullptr), 
};

template <class TypePtr>
class Map
{
private:
	Tile<TypePtr>** Field;
	int Dim;
public:

};

#endif