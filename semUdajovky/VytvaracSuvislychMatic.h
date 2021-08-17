#pragma once
#include "VytvaracMatic.h"
#include "matica.h"
#include "matica_suvisla.h"
#include "structures/heap_monitor.h"

namespace structures {
	template<typename T>
	class VytvaracSuvislychMatic : public VytvaracMatic<T> {

	public:
		VytvaracSuvislychMatic();
		virtual ~VytvaracSuvislychMatic();

		MaticaSuvisla<T>* vytvorMaticu(int pocetRiadkov, int pocetStlpcov, T hodnota) const override;

	};

	template<typename T>
	VytvaracSuvislychMatic<T>::VytvaracSuvislychMatic() :
		VytvaracMatic<T>::VytvaracMatic()
	{
	}

	template<typename T>
	VytvaracSuvislychMatic<T>::~VytvaracSuvislychMatic()
	{
	}

	template<typename T>
	inline MaticaSuvisla<T>* VytvaracSuvislychMatic<T>::vytvorMaticu(int pocetRiadkov, int pocetStlpcov, T hodnota) const
	{
		return new MaticaSuvisla<T>(pocetRiadkov, pocetStlpcov, hodnota);
	}

}
