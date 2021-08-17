#pragma once

#include "structures/heap_monitor.h"
#include <iostream>
#include <time.h>
#include <fstream>
#include <chrono> 
#include "structures/priority_queue/heap.h"
#include "structures/priority_queue/priority_queue_sorted_array_list.h"
#include "structures/priority_queue/priority_queue_limited_sorted_array_list.h"
#include "structures/priority_queue/priority_queue_two_lists.h"

using namespace std::chrono;
using namespace structures;

template<typename T>
class TestPrioritnychFrontov {

private:
	int a_;
	int b_;
	int c_;
	int pocOperacii_;
	PriorityQueue<T>* front_;
	std::string nazovSuboru_;

public:
	TestPrioritnychFrontov(const int a, const int b, const int c, const int pocetOperacii, PriorityQueue<T>* front, const std::string nazovSuboru);
	~TestPrioritnychFrontov();
	void testuj();

};


template<typename T>
inline TestPrioritnychFrontov<T>::TestPrioritnychFrontov(const int a, const int b, const int c, const int pocetOperacii, PriorityQueue<T>* front, const std::string nazovSuboru)
{
	a_ = a;
	b_ = b;
	c_ = c;
	pocOperacii_ = pocetOperacii;
	front_ = front;
	nazovSuboru_ = nazovSuboru;
}

template<typename T>
inline TestPrioritnychFrontov<T>::~TestPrioritnychFrontov()
{
	delete front_;
}

template<typename T>
void TestPrioritnychFrontov<T>::testuj() {
	if ((a_ + b_ + c_) != 100)
	{
		std::cout << "Testovanie bolo neuspesne : Celkovy podiel operacii sa nerovna 100!" << std::endl;
		return;
	}

	srand(999);
	std::ofstream csv;
	csv.open("testy/prioritneFronty/" + nazovSuboru_);
	csv << "Ve¾kos frontu;Vlož;Vyber;Ukáž" << std::endl;
	int nahCislo = 0;
	int nahParameter = 0;
	int nahPriorita = 0;

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

		csv << front_->size();
		nahCislo = rand() % (a_ + b_ + c_) + 1;

		if (front_->size() > 0) {
			nahPriorita = (rand() % 10001);
			nahParameter = rand() % 10001;
		}


		// Vloz
		if (nahCislo <= a_) {
			auto start = high_resolution_clock::now();
			front_->push(nahPriorita, nahParameter);
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<nanoseconds>(stop - start);
			csv << ";" << duration.count() << std::endl;
			i++;
			continue;
		}

		// Vyber
		if (nahCislo > a_ && nahCislo <= (a_ + b_)) {
			if (front_->isEmpty()) {
				i++;
				continue;
			}
			auto start = high_resolution_clock::now();
			front_->pop();
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<nanoseconds>(stop - start);
			csv << ";;" << duration.count() << std::endl;
	
			i++;
			continue;
		}

		// Ukaz
		if (nahCislo > (a_ + b_) && nahCislo <= (a_ + b_ + c_)) {
			if (front_->isEmpty()) {
				i++;
				continue;
			}
			
			auto start = high_resolution_clock::now();
			front_->peek();
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<nanoseconds>(stop - start);
			csv << ";;;" << duration.count() << std::endl;
			
			i++;
			continue;
		}

	}
	std::cout << "100% HOTOVO " << std::endl;
	csv.close();
}
