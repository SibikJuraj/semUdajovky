#pragma once

#include "structures/heap_monitor.h"
#include <iostream>
#include <time.h>
#include <fstream>
#include "structures/list/array_list.h"
#include "structures/list/linked_list.h"
#include "structures/list/list.h"
#include <chrono> 

using namespace std::chrono;
using namespace structures;

template<typename T>
class TestListov {

private:
	int a_;
	int b_;
	int c_;
	int d_;
	int pocOperacii_;
	List<T>* list_;
	std::string nazovSuboru_;

public:
	TestListov(const int a, const int b, const int c, const int d, const int pocetOperacii, List<T>* list, const std::string nazovSuboru);
	~TestListov();
	void testuj();

};


template<typename T>
inline TestListov<T>::TestListov(const int a, const int b, const int c, const int d, const int pocetOperacii, List<T>* list ,const std::string nazovSuboru)
{
	a_ = a;
	b_ = b;
	c_ = c;
	d_ = d;

	pocOperacii_ = pocetOperacii;
	list_ = list;
	nazovSuboru_ = nazovSuboru;
}

template<typename T>
inline TestListov<T>::~TestListov()
{
	delete list_;
}

template<typename T>
void TestListov<T>::testuj() {
	if ((a_ + b_ + c_ + d_) != 100)
	{
		std::cout << "Testovanie bolo neuspesne : Celkovy podiel operacii sa nerovna 100!" << std::endl;
		return;
	}


	srand(999);
	std::ofstream csv;
	csv.open("testy/listy/" + nazovSuboru_);
	csv << "Ve¾kos po¾a;Vlož prvý;Vlož posledný;Vlož na index;Zruš prvý;Zruš posledný;Zruš na indexe;Sprístupni;Nastav;Index prvku" << std::endl;
	int nahCislo = 0;
	int nahParameter = 0;
	int nahIndex = 0;

	int i = 0;
	while (i < pocOperacii_) {

		if (i == (int)(pocOperacii_ * 0.25))
		{
			std::cout << "25% HOTOVO " << std::endl;
		}
		else if (i == (int)(pocOperacii_ * 0.5))
		{
			std::cout << "50% HOTOVO " << std::endl;
		}
		else if (i == (int)(pocOperacii_ * 0.75))
		{
			std::cout << "75% HOTOVO " << std::endl;
		}

		csv << list_->size();
		nahCislo = rand() % (a_ + b_ + c_ + d_) + 1;
		nahParameter = (rand() % 10001);

		if (list_->size() > 0) {
			nahIndex = rand() % list_->size();
		}
		else
		{
			nahIndex = 0;
		}

		// Vkladanie
		if (nahCislo <= a_) {
			nahCislo = rand() % 3;
			switch (nahCislo) {
				// Vloz prvy
			case 0: {

				auto start = high_resolution_clock::now();
				list_->insert(nahParameter, 0);
				auto stop = high_resolution_clock::now();
				auto duration = duration_cast<nanoseconds>(stop - start);
				csv << ";" << duration.count() << std::endl;
				break;
			}
				  // Vloz posledny
			case 1: {
				auto start = high_resolution_clock::now();
				list_->add(nahParameter);
				auto stop = high_resolution_clock::now();
				auto duration = duration_cast<nanoseconds>(stop - start);
				csv << ";;" << duration.count() << std::endl;
				break;
			}
				  // Vloz na index
			case 2: {
				auto start = high_resolution_clock::now();
				list_->insert(nahParameter, nahIndex);
				auto stop = high_resolution_clock::now();
				auto duration = duration_cast<nanoseconds>(stop - start);
				csv << ";;;" << duration.count() << std::endl;
				break;
			}
			default:
				break;
			}

			i++;
			continue;
		}

		// Rusenie
		if (nahCislo > a_ && nahCislo <= a_ + b_) {
			if (list_->isEmpty()) {
				i++;
				continue;
			}
			nahCislo = rand() % 3;
			switch (nahCislo) {
				// Zrus prvy
			case 0: {
				auto start = high_resolution_clock::now();
				list_->removeAt(0);
				auto stop = high_resolution_clock::now();
				auto duration = duration_cast<nanoseconds>(stop - start);
				csv << ";;;;" << duration.count() << std::endl;
				break;
			}
				  // Zrus posledny
			case 1: {
				auto start = high_resolution_clock::now();
				list_->removeAt(list_->size() - 1);
				auto stop = high_resolution_clock::now();
				auto duration = duration_cast<nanoseconds>(stop - start);
				csv << ";;;;;" << duration.count() << std::endl;
				break;
			}
				  // Zrus na indexe
			case 2: {
				auto start = high_resolution_clock::now();
				list_->removeAt(nahIndex);
				auto stop = high_resolution_clock::now();
				auto duration = duration_cast<nanoseconds>(stop - start);
				csv << ";;;;;;" << duration.count() << std::endl;
				break;
			}
			default:
				break;
			}
			i++;
			continue;
		}

		// Spristupni / Nastav
		if (nahCislo > a_ + b_ && nahCislo <= a_ + b_ + c_) {
			if (list_->isEmpty()) {
				i++;
				continue;
			}
			nahCislo = rand() % 2;
			switch (nahCislo) {
				// Spristupni
			case 0: {
				auto start = high_resolution_clock::now();
				(*list_)[nahIndex];
				auto stop = high_resolution_clock::now();
				auto duration = duration_cast<nanoseconds>(stop - start);
				csv << ";;;;;;;" << duration.count() << std::endl;
				break;
			}
				  // Nastav
			case 1: {
				auto start = high_resolution_clock::now();
				(*list_)[nahIndex] = nahParameter;
				auto stop = high_resolution_clock::now();
				auto duration = duration_cast<nanoseconds>(stop - start);
				csv << ";;;;;;;;" << duration.count() << std::endl;
				break;
			}
			default:
				break;
			}
			i++;
			continue;
		}

		// Index prvku
		if (nahCislo > a_ + b_ + c_ && nahCislo <= a_ + b_ + c_ + d_) {
			if (list_->isEmpty()) {
				i++;
				continue;
			}
			auto start = high_resolution_clock::now();
			list_->getIndexOf(nahParameter);
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<nanoseconds>(stop - start);
			csv << ";;;;;;;;;" << duration.count() << std::endl;
			i++;
			continue;
		}

		
	}
	std::cout << "100% HOTOVO " << std::endl;

	csv.close();

}
