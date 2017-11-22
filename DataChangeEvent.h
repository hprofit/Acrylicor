/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: DataAmountEvent.h
Purpose: Event that carries a (likely) numerical amount of some sort, type is indicated by Type()
Language: C++
Platform: Windows 8.1 / 10.0.15063.0  or  GCC 7.1.0
Project: CS529_holdenprofit_
Author: Holden Profit, holden.profit, 42833
Creation date: 11/09/17
- End Header --------------------------------------------------------*/

#pragma once

#ifndef DATA_CHANGE_EVENT_H
#define DATA_CHANGE_EVENT_H

#include "AcryEvent.h"

template <class T>
class DataChangeEvent :
	public AcryEvent
{
private:
	String dataType;
	T data;

public:
	DataChangeEvent(double time, String _dataType, T _data);
	virtual ~DataChangeEvent();

	String Type() const;
	T Data() const;
};

#include "DataChangeEvent.cpp"
#endif
