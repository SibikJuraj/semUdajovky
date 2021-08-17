#pragma once
#include "VytvaracMatic.h"
#include "matica_nesuvisla.h"
#include "structures/heap_monitor.h"

namespace structures {
	template<typename T>
	class VytvaracNesuvislychMatic : public VytvaracMatic<T> {

	public:
		VytvaracNesuvislychMatic();
		virtual ~VytvaracNesuvislychMatic();

		MaticaNesuvisla<T>* vytvorMaticu(int pocetRiadkov, int pocetStlpcov, T hodnota) const override;

	};

	template<typename T>
	VytvaracNesuvislychMatic<T>::VytvaracNesuvislychMatic() :
		VytvaracMatic<T>::VytvaracMatic()
	{
	}

	template<typename T>
	VytvaracNesuvislychMatic<T>::~VytvaracNesuvislychMatic()
	{
	}

	template<typename T>
	inline MaticaNesuvisla<T>* VytvaracNesuvislychMatic<T>::vytvorMaticu(int pocetRiadkov, int pocetStlpcov, T hodnota) const
	{
		return new MaticaNesuvisla<T>(pocetRiadkov, pocetStlpcov, hodnota);
	}

}