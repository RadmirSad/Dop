#pragma once

#ifndef _PTR_H_
#define _PTR_H_

#include <iostream>

template <class TypePtr>
class SmartPtr
{
private:
	TypePtr* ptr;
public:
	SmartPtr(TypePtr* MyPtr = nullptr) : ptr(MyPtr) { ; }
	SmartPtr(SmartPtr & dop_ptr);
	~SmartPtr()
	{
		delete ptr;
	}
	TypePtr& operator* () const { return *ptr; }
	TypePtr* operator-> () const { return ptr; }
	SmartPtr<TypePtr>& operator = (SmartPtr<TypePtr>& dop_dtr);

};

template <class TypePtr>
SmartPtr<TypePtr>::SmartPtr(SmartPtr<TypePtr> &dop_ptr)
{
	ptr = dop_ptr.ptr;
	dop_ptr = nullptr;
}

template <class TypePtr>
SmartPtr<TypePtr> &SmartPtr<TypePtr>:: operator = (SmartPtr<TypePtr> & dop_ptr)
{
	if (this == &dop_ptr)
		return *this;
	delete ptr;
	ptr = dop_ptr.ptr;
	dop_ptr.ptr = nullptr;
	return *this;
}

#endif