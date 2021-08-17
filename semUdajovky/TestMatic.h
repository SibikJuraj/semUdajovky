#pragma once
#include <iostream>
#include <time.h>
#include <fstream>
#include "matica_nesuvisla.h"
#include "matica_suvisla.h"
#include "matica.h"
#include "VytvaracMatic.h"
#include "VytvaracNesuvislychMatic.h"
#include "VytvaracSuvislychMatic.h"
#include "structures/heap_monitor.h"

#include "structures/ds_routines.h"
#include <chrono> 

using namespace std::chrono;
using namespace structures;


template<typename T>
class TestMatic {

private:
	VytvaracMatic<T>* vytvaracMatic_;
	std::string nazovSuboru_;

	const int maxHodnota_ = 2000;

public:
	TestMatic(VytvaracMatic<T>* vytvaracMatic, const std::string nazovSuboru);
	~TestMatic();
	void testujScenarA(bool zmenaRiadkov, bool zmenaStlpcov);
	void testujScenarB(bool zmenaRiadkov, bool zmenaStlpcov);

};


template<typename T>
inline TestMatic<T>::TestMatic(VytvaracMatic<T>* vytvaracMatic, const std::string nazovSuboru)
{

	vytvaracMatic_ = vytvaracMatic;
	nazovSuboru_ = nazovSuboru;

}

template<typename T>
inline TestMatic<T>::~TestMatic()
{
	delete vytvaracMatic_;
}



template<typename T>
void TestMatic<T>::testujScenarA(bool zmenaRiadkov, bool zmenaStlpcov) {
	srand(999);
	std::ofstream csv;

	std::string modifikator = "";

	if (zmenaRiadkov)
	{
		modifikator += "R";
	}
	if (zmenaStlpcov)
	{
		modifikator += "S";
	}

	csv.open("testy/matice/sucet/" + modifikator + nazovSuboru_);
	csv << "Poèet riadkov;Poèet ståpcov;Súèet" << std::endl;
	int riadok = 10;
	int stlpec = 10;
	int nahParameter = 0;

	
	int i = 10;
	while (i <= maxHodnota_) {

		if (i == (int)(maxHodnota_ * 0.25))
		{
			std::cout << "25% HOTOVO " << std::endl;
		}
		else if (i == (int)(maxHodnota_ * 0.5))
		{
			std::cout << "50% HOTOVO " << std::endl;
		}
		else if (i == (int)(maxHodnota_ * 0.75))
		{
			std::cout << "75% HOTOVO " << std::endl;
		}

		
		nahParameter = rand() % 101;



		if (zmenaRiadkov)
		{
			riadok = i;
		}
		if (zmenaStlpcov)
		{
			stlpec = i;
		}

		Matica<T>* vytvorenaMatica = vytvaracMatic_->vytvorMaticu(riadok, stlpec, nahParameter);

		// Súèet	
		auto start = high_resolution_clock::now();
		Matica<T>* matSuvSucet = &vytvorenaMatica->scitaj(*vytvorenaMatica);
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<nanoseconds>(stop - start);
		csv << matSuvSucet->getPocetRiadkov()  << ";" << matSuvSucet->getPocetStlpcov() << ";" << duration.count() << std::endl;
		

		i++;
		


		delete vytvorenaMatica;
		delete matSuvSucet;

	}

	std::cout << "100% HOTOVO " << std::endl;

	csv.close();
}


template<typename T>
void TestMatic<T>::testujScenarB(bool zmenaRiadkov, bool zmenaStlpcov) {
	srand(999);
	std::ofstream csv;

	std::string modifikator = "";

	if (zmenaRiadkov)
	{
		modifikator += "R";
	}
	if (zmenaStlpcov)
	{
		modifikator += "S";
	}


	csv.open("testy/matice/sucin/" + modifikator + nazovSuboru_ );
	csv << "Poèet riadkov;Poèet ståpcov;Súèin" << std::endl;
	int riadok = 10;
	int stlpec = 10;
	int nahParameter = 0;

	int i = 10;
	while (i <= maxHodnota_) {

		if (i == (int)(maxHodnota_ * 0.25))
		{
			std::cout << "25% HOTOVO " << std::endl;
		}
		else if (i == (int)(maxHodnota_ * 0.5))
		{
			std::cout << "50% HOTOVO " << std::endl;
		}
		else if (i == (int)(maxHodnota_ * 0.75))
		{
			std::cout << "75% HOTOVO " << std::endl;
		}

		nahParameter = rand() % 101;


		if (zmenaRiadkov)
		{
			riadok = i;
		}
		if (zmenaStlpcov)
		{
			stlpec = i;
		}

		Matica<T>* matica1 = vytvaracMatic_->vytvorMaticu(riadok, i, nahParameter);
		Matica<T>* matica2 = vytvaracMatic_->vytvorMaticu(i, stlpec, nahParameter);
		

		// Súèin

		auto start = high_resolution_clock::now();
		Matica<T>* matSuvSucin = &matica1->vynasob(*matica2);
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<nanoseconds>(stop - start);
		csv << matSuvSucin->getPocetRiadkov() << ";" << matSuvSucin->getPocetStlpcov() << ";" << duration.count() << std::endl;

		if (i < 100)
		{
			i++;
		}
		else 
		{
			i += 100;
		}



		delete matica1;
		delete matica2;

		delete matSuvSucin;
	}

	std::cout << "100% HOTOVO " << std::endl;

	csv.close();
}