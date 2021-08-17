#pragma once

#include "structures/heap_monitor.h"

template<typename T>
class VytvaracMatic {

public:
	VytvaracMatic();
	virtual ~VytvaracMatic();

	virtual Matica<T>* vytvorMaticu(int pocetRiadkov, int pocetStlpcov, T hodnota) const = 0;

};

template<typename T>
VytvaracMatic<T>::VytvaracMatic()
{

}

template<typename T>
VytvaracMatic<T>::~VytvaracMatic()
{

}
