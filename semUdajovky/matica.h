#pragma once

#include "structures/heap_monitor.h"

template<typename T>
class Matica {

public:
	Matica();
	virtual ~Matica();
	virtual T& getPrvok(const int riadok, const int stlpec) const = 0;
	virtual void setPrvok(const int riadok, const int stlpec, const T hodnota) const = 0;
	virtual int getPocetRiadkov() const = 0;
	virtual int getPocetStlpcov() const = 0;
	
	virtual Matica<T>& scitaj(Matica<T>& other) const = 0;
	virtual Matica<T>& vynasob(Matica<T>& other) const = 0;

	

};


template<typename T>
Matica<T>::Matica() {

}


template<typename T>
Matica<T>::~Matica() {

}



