#ifndef DATA_CHANGE_EVENT_CPP
#define DATA_CHANGE_EVENT_CPP
#include "DataChangeEvent.h"

template<class T>
DataChangeEvent<T>::DataChangeEvent(double time, String _dataType, T _data) :
	AcryEvent(EventType::DATA_AMOUNT, time),
	dataType(_dataType), data(_data) {}

template<class T>
DataChangeEvent<T>::~DataChangeEvent(){}

template<class T>
String DataChangeEvent<T>::Type() const
{
	return dataType;
}

template<class T>
T DataChangeEvent<T>::Data() const
{
	return data;
}

#endif
