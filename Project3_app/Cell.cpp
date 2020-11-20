#include "Cell.h"

Cell::Cell()
{
	this->number = 0;
	condition = EMPTY;
}

void Cell::set_number(int num)
{
	this->number = num;
}

void Cell::set_condition(Condition cond)
{
	condition = cond;
}

unsigned int Cell::get_number() const
{
	return this->number;
}

Condition Cell::get_condition() const
{
	return this->condition;
}