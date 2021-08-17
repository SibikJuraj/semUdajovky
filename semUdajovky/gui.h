#pragma once

#include <iostream>
#include <time.h>
#include <fstream>
#include <chrono> 

#include "structures/heap_monitor.h"
#include "matica_nesuvisla.h"
#include "matica_suvisla.h"
#include "matica.h"
#include "doubly_circular_linked_list.h"
#include "TestMatic.h"
#include "TestListov.h"
#include "TestPrioritnychFrontov.h"
#include "VytvaracMatic.h"
#include "VytvaracNesuvislychMatic.h"
#include "VytvaracSuvislychMatic.h"


class GUI {

private:
	std::string str;
	int input;
	const int pocetOperacii = 2000;

public:
	GUI();

	bool testovanie();
		void testovanieListov();
			void testovanieArrayListu();
			void testovanieLinkedListu();
			void testovanieDoublyCircularLinkedListu();


		void testovaniePrioritnychFrontov();
			void testovanieUtriedenehoPrioPola();
			void testovanieHaldy();
			void testovanieDvojzoznamu();
				template<typename T>
				void zvolenieStrategieDvojzoznamu(PriorityQueueTwoLists<T>* pqTwoLists, float operaciaVloz, int pocOperacii);

		void testovanieMatic();
			void testovanieSuvislejMatice();
			void testovanieNesuvislejMatice();

	~GUI();

	
};


GUI::GUI() :
	input(0)
{

	std::cout << "Vitajte pri testovani udajovych struktur! " << std::endl;
	std::cout << "V ponuke su momentalne tri typy testovania a to testovanie listov, prioritnych frontov a matic." << std::endl;
	std::cout << "Kazde testovanie ma preddefinovane scenare a moznost zadat si vlastny scenar!" << std::endl;
	std::cout << "Prajem prijemne testovanie!" << std::endl;

}


GUI::~GUI() {
}


 inline bool GUI::testovanie() {

	std::cout << std::endl;

	std::cout << "Stlacte : 1 : pre testovanie listov" << std::endl;
	std::cout << "Stlacte : 2 : pre testovanie prioritnych frontov" << std::endl;
	std::cout << "Stlacte : 3 : pre testovanie matic" << std::endl;
	std::cout << "Stlacte : 4 : pre koniec" << std::endl;
	std::cin >> str;

	try {
		switch (std::stoi(str))
		{
		case 1: {
			testovanieListov();
			break;
		}
		case 2: {
			testovaniePrioritnychFrontov();
			break;
		}

		case 3: {
			testovanieMatic();
			break;
		}

		case 4: {
			return false;
			break;
		}
		default:
			std::cout << "Hopla asi ste sa trocha uklepli no nevadi mozete to skusit znova" << std::endl;
			break;
		}
	}
	catch (const std::exception e) {
		std::cout << "Hopla asi ste sa trocha uklepli no nevadi mozete to skusit znova" << std::endl;
		return testovanie();
	}

	std::cout << std::endl;
}

inline void GUI::testovanieListov()
{
	std::cout << std::endl;

	std::cout << "----Testovanie listov----" << std::endl;
	std::cout << "Stlacte : 1 : pre otestovanie array listu" << std::endl;
	std::cout << "Stlacte : 2 : pre otestovanie linked listu" << std::endl;
	std::cout << "Stlacte : 3 : pre otestovanie doubly circled linked listu" << std::endl;

	std::cin >> str;

	try {
		switch (std::stoi(str))
		{

		case 1: {
			testovanieArrayListu();
			break;
		}

		case 2: {
			testovanieLinkedListu();
			break;
		}

		case 3: {
			testovanieDoublyCircularLinkedListu();
			break;
		}
		default:
			std::cout << "Hopla asi ste sa trocha uklepli no nevadi mozete to skusit znova" << std::endl;
			break;
		}
	}
	catch (const std::exception e) {
		std::cout << "Hopla asi ste sa trocha uklepli no nevadi mozete to skusit znova" << std::endl;
		return;
	}


}

inline void GUI::testovanieArrayListu()
{

	std::cout << "----Testovanie listov----" << std::endl;
	std::cout << "  ----Testovanie Array Listu----" << std::endl;

	std::cout << "Stlacte 'A', 'B' alebo 'C' pre testovanie jednotlivych scenarov" << std::endl;
	std::cout << "Stlacte 'V' pre testovanie vlastneho scenaru" << std::endl;

	std::cin >> str;

	
	if (str.at(0) == 'a' || str.at(0) == 'A') {
		//SCENAR A
		std::cout << "TESTUJEM" << std::endl;
		TestListov<int>* testArrayListu = new TestListov<int>(20, 20, 50, 10, pocetOperacii, new ArrayList<int>(), "arrayListA.csv");
		testArrayListu->testuj();
		delete testArrayListu;
	}
	else if (str.at(0) == 'b' || str.at(0) == 'B') {
		//SCENAR B
		std::cout << "TESTUJEM" << std::endl;
		TestListov<int>* testArrayListu = new TestListov<int>(35, 35, 20, 10, pocetOperacii, new ArrayList<int>(), "arrayListB.csv");
		testArrayListu->testuj();
		delete testArrayListu;

	}
	else if (str.at(0) == 'c' || str.at(0) == 'C') {
		//SCENAR C
		std::cout << "TESTUJEM" << std::endl;
		TestListov<int>* testArrayListu = new TestListov<int>(45, 45, 5, 5, pocetOperacii, new ArrayList<int>(), "arrayListC.csv");
		testArrayListu->testuj();
		delete testArrayListu;
		
	}
	else if (str.at(0) == 'v' || str.at(0) == 'V') {
		//Vlastny scenar
		int input[4];
		std::string text[4]{ "vloz", "zrus", "spristupni / nastav", "index prvku" };
		int vlastnyPocOp;
		std::string nazovSuboru;

		for (int i = 0; i < 4; i++)
		{
			std::cout << "Zadajte pomer operacie " << text[i] << std::endl;

			std::cin >> str;
			try
			{
				input[i] = std::stoi(str);
			}
			catch (const std::exception e) {
				std::cout << "Hopla asi ste sa trocha uklepli no nevadi mozete to skusit znova" << std::endl;
				return;
			}
		}

		std::cout << "Zadajte pocet operacii " << std::endl;

		std::cin >> str;
		try
		{
			vlastnyPocOp = std::stoi(str);
		}
		catch (const std::exception e) {
			std::cout << "Hopla asi ste sa trocha uklepli no nevadi mozete to skusit znova" << std::endl;
			return;
		}

		std::cout << "Zadajte nazov suboru " << std::endl;
		std::cin >> nazovSuboru;

		std::cout << "TESTUJEM" << std::endl;
		TestListov<int>* testArrayListu = new TestListov<int>(input[0], input[1], input[2], input[3], vlastnyPocOp, new ArrayList<int>(), nazovSuboru + ".csv");
		testArrayListu->testuj();
		delete testArrayListu;

	}
	else
	{
		std::cout << "Hopla asi ste sa trocha uklepli no nevadi mozete to skusit znova" << std::endl;
		return;
	}

	std::cout << "TESTOVANIE DOKONCENE" << std::endl;
}

inline void GUI::testovanieLinkedListu()
{

	std::cout << "----Testovanie listov----" << std::endl;
	std::cout << "  ----Testovanie Linked Listu----" << std::endl;

	std::cout << "Stlacte 'A', 'B' alebo 'C' pre testovanie jednotlivych scenarov" << std::endl;
	std::cout << "Stlacte 'V' pre testovanie vlastneho scenaru" << std::endl;

	std::cin >> str;
	if (str.at(0) == 'a' || str.at(0) == 'A') {
		//SCENAR A
		std::cout << "TESTUJEM" << std::endl;
		TestListov<int>* testLinkedListu = new TestListov<int>(20, 20, 50, 10, pocetOperacii, new LinkedList<int>(), "linkedListA.csv");
		testLinkedListu->testuj();
		delete testLinkedListu;
	}
	else if (str.at(0) == 'b' || str.at(0) == 'B') {
		//SCENAR B
		std::cout << "TESTUJEM" << std::endl;
		TestListov<int>* testLinkedListu = new TestListov<int>(35, 35, 20, 10, pocetOperacii, new LinkedList<int>(), "linkedListB.csv");
		testLinkedListu->testuj();
		delete testLinkedListu;
	}
	else if (str.at(0) == 'c' || str.at(0) == 'C') {
		//SCENAR C
		std::cout << "TESTUJEM" << std::endl;
		TestListov<int>* testLinkedListu = new TestListov<int>(45, 45, 5, 5, pocetOperacii, new LinkedList<int>(), "linkedListC.csv");
		testLinkedListu->testuj();
		delete testLinkedListu;
		
	}
	else if (str.at(0) == 'v' || str.at(0) == 'V') {
		//Vlastny scenar
		int input[4];
		std::string text[4]{ "vloz", "zrus", "spristupni / nastav", "index prvku" };
		int vlastnyPocOp;
		std::string nazovSuboru;

		for (int i = 0; i < 4; i++)
		{
			std::cout << "Zadajte pomer operacie " << text[i] << std::endl;

			std::cin >> str;
			try
			{
				input[i] = std::stoi(str);
			}
			catch (const std::exception e) {
				std::cout << "Hopla asi ste sa trocha uklepli no nevadi mozete to skusit znova" << std::endl;
				return;
			}
		}

		std::cout << "Zadajte pocet operacii " << std::endl;

		std::cin >> str;
		try
		{
			vlastnyPocOp = std::stoi(str);
		}
		catch (const std::exception e) {
			std::cout << "Hopla asi ste sa trocha uklepli no nevadi mozete to skusit znova" << std::endl;
			return;
		}

		std::cout << "Zadajte nazov suboru " << std::endl;
		std::cin >> nazovSuboru;

		std::cout << "TESTUJEM" << std::endl;
		TestListov<int>* testLinkedListu = new TestListov<int>(input[0], input[1], input[2], input[3], vlastnyPocOp, new LinkedList<int>(), nazovSuboru + ".csv");
		testLinkedListu->testuj();
		delete testLinkedListu;

	}
	else
	{
		std::cout << "Hopla asi ste sa trocha uklepli no nevadi mozete to skusit znova" << std::endl;
		return;
	}
	std::cout << "TESTOVANIE DOKONCENE" << std::endl;
}

inline void GUI::testovanieDoublyCircularLinkedListu()
{
	
	std::cout << "----Testovanie listov----" << std::endl;
	std::cout << "  ----Testovanie Doubly Circular Linked Listu----" << std::endl;

	std::cout << "Stlacte 'A', 'B' alebo 'C' pre testovanie jednotlivych scenarov" << std::endl;
	std::cout << "Stlacte 'V' pre testovanie vlastneho scenaru" << std::endl;

	std::cin >> str;
	if (str.at(0) == 'a' || str.at(0) == 'A') {
		//SCENAR A
		std::cout << "TESTUJEM" << std::endl;
		TestListov<int>* testDCLinkedListu = new TestListov<int>(20, 20, 50, 10, pocetOperacii, new DoublyCircularLinkedList<int>(), "doublyCircledLinkedListA.csv");
		testDCLinkedListu->testuj();
		delete testDCLinkedListu;

	}
	else if (str.at(0) == 'b' || str.at(0) == 'B') {
		//SCENAR B
		std::cout << "TESTUJEM" << std::endl;
		TestListov<int>* testDCLinkedListu = new TestListov<int>(35, 35, 20, 10, pocetOperacii, new DoublyCircularLinkedList<int>(), "doublyCircledLinkedListB.csv");
		testDCLinkedListu->testuj();
		delete testDCLinkedListu;

	}
	else if (str.at(0) == 'c' || str.at(0) == 'C') {
		//SCENAR C
		std::cout << "TESTUJEM" << std::endl;
		TestListov<int>* testDCLinkedListu = new TestListov<int>(45, 45, 5, 5, pocetOperacii, new DoublyCircularLinkedList<int>(), "doublyCircledLinkedListC.csv");
		testDCLinkedListu->testuj();
		delete testDCLinkedListu;
	}
	else if (str.at(0) == 'v' || str.at(0) == 'V') {
		//Vlastny scenar
		int input[4];
		std::string text[4]{ "vloz", "zrus", "spristupni / nastav", "index prvku" };
		int vlastnyPocOp;
		std::string nazovSuboru;

		for (int i = 0; i < 4; i++)
		{
			std::cout << "Zadajte pomer operacie " << text[i] << std::endl;

			std::cin >> str;
			try
			{
				input[i] = std::stoi(str);
			}
			catch (const std::exception e) {
				std::cout << "Hopla asi ste sa trocha uklepli no nevadi mozete to skusit znova" << std::endl;
				return;
			}
		}

		std::cout << "Zadajte pocet operacii " << std::endl;

		std::cin >> str;
		try
		{
			vlastnyPocOp = std::stoi(str);
		}
		catch (const std::exception e) {
			std::cout << "Hopla asi ste sa trocha uklepli no nevadi mozete to skusit znova" << std::endl;
			return;
		}

		std::cout << "Zadajte nazov suboru " << std::endl;
		std::cin >> nazovSuboru;

		std::cout << "TESTUJEM" << std::endl;
		TestListov<int>* testDCLinkedListu = new TestListov<int>(input[0], input[1], input[2], input[3], vlastnyPocOp, new DoublyCircularLinkedList<int>(), nazovSuboru + ".csv");
		testDCLinkedListu->testuj();
		delete testDCLinkedListu;

	}

	else
	{
		std::cout << "Hopla asi ste sa trocha uklepli no nevadi mozete to skusit znova" << std::endl;
		return;
	}
	std::cout << "TESTOVANIE DOKONCENE" << std::endl;
}

inline void GUI::testovaniePrioritnychFrontov()
{
	std::cout << std::endl;

	std::cout << "----Testovanie prioritnych frontov----" << std::endl;
	std::cout << "Stlacte : 1 : pre otestovanie utriedeneho pola na zaklade priority" << std::endl;
	std::cout << "Stlacte : 2 : pre otestovanie haldy" << std::endl;
	std::cout << "Stlacte : 3 : pre otestovanie dvojzoznamu" << std::endl;

	std::cin >> str;

	try {
		switch (std::stoi(str))
		{
		case 1: {
			testovanieUtriedenehoPrioPola();
			break;
		}

		case 2: {
			testovanieHaldy();
			break;
		}

		case 3: {
			testovanieDvojzoznamu();
			break;
		}

		default:
			std::cout << "Hopla asi ste sa trocha uklepli no nevadi mozete to skusit znova" << std::endl;
			break;
		}
		
	}
	catch (const std::exception e) {
		std::cout << "Hopla asi ste sa trocha uklepli no nevadi mozete to skusit znova" << std::endl;
	}

}

inline void GUI::testovanieUtriedenehoPrioPola()
{
	std::cout << "----Testovanie prioritnych frontov----" << std::endl;
	std::cout << "  ----Testovanie Utriedeneho Pola Zoradeneho Podla Priority----" << std::endl;

	std::cout << "Stlacte 'A', 'B' alebo 'C' pre testovanie jednotlivych scenarov" << std::endl;
	std::cout << "Stlacte 'V' pre testovanie vlastneho scenaru" << std::endl;
	std::cin >> str;
	if (str.at(0) == 'a' || str.at(0) == 'A') {
		//SCENAR A
		std::cout << "TESTUJEM" << std::endl;
		TestPrioritnychFrontov<int>* testUsporiadanehoListu = new TestPrioritnychFrontov<int>(35, 35, 30, pocetOperacii, new PriorityQueueSortedArrayList<int>(), "priorityQueueSortedArrayListA.csv");
		testUsporiadanehoListu->testuj();
		delete testUsporiadanehoListu;
	}
	else if (str.at(0) == 'b' || str.at(0) == 'B') {
		//SCENAR B
		std::cout << "TESTUJEM" << std::endl;
		TestPrioritnychFrontov<int>* testUsporiadanehoListu = new TestPrioritnychFrontov<int>(50, 30, 20, pocetOperacii, new PriorityQueueSortedArrayList<int>(), "priorityQueueSortedArrayListB.csv");
		testUsporiadanehoListu->testuj();
		delete testUsporiadanehoListu;
	}
	else if (str.at(0) == 'c' || str.at(0) == 'C') {
		//SCENAR C
		std::cout << "TESTUJEM" << std::endl;
		TestPrioritnychFrontov<int>* testUsporiadanehoListu = new TestPrioritnychFrontov<int>(70, 25, 5, pocetOperacii, new PriorityQueueSortedArrayList<int>(), "priorityQueueSortedArrayListC.csv");
		testUsporiadanehoListu->testuj();
		delete testUsporiadanehoListu;

	}
	else if (str.at(0) == 'v' || str.at(0) == 'V') {
		//Vlastny scenar
		int input[3];
		std::string text[3]{ "vloz", "vyber", "ukaz" };
		int vlastnyPocOp;
		std::string nazovSuboru;

		for (int i = 0; i < 3; i++)
		{
			std::cout << "Zadajte pomer operacie " << text[i] << std::endl;

			std::cin >> str;
			try
			{
				input[i] = std::stoi(str);
			}
			catch (const std::exception e) {
				std::cout << "Hopla asi ste sa trocha uklepli no nevadi mozete to skusit znova" << std::endl;
				return;
			}
		}

		std::cout << "Zadajte pocet operacii " << std::endl;

		std::cin >> str;
		try
		{
			vlastnyPocOp = std::stoi(str);
		}
		catch (const std::exception e) {
			std::cout << "Hopla asi ste sa trocha uklepli no nevadi mozete to skusit znova" << std::endl;
			return;
		}

		std::cout << "Zadajte nazov suboru " << std::endl;
		std::cin >> nazovSuboru;

		std::cout << "TESTUJEM" << std::endl;
		TestPrioritnychFrontov<int>* testUsporiadanehoListu = new TestPrioritnychFrontov<int>(input[0], input[1], input[2], vlastnyPocOp, new PriorityQueueSortedArrayList<int>(), nazovSuboru + ".csv");
		testUsporiadanehoListu->testuj();
		delete testUsporiadanehoListu;

	}
	else
	{
		std::cout << "Hopla asi ste sa trocha uklepli no nevadi mozete to skusit znova" << std::endl;
		return;
	}
	std::cout << "TESTOVANIE DOKONCENE" << std::endl;
}

inline void GUI::testovanieHaldy()
{
	std::cout << "----Testovanie prioritnych frontov----" << std::endl;
	std::cout << "  ----Testovanie Haldy----" << std::endl;

	std::cout << "Stlacte 'A', 'B' alebo 'C' pre testovanie jednotlivych scenarov" << std::endl;
	std::cout << "Stlacte 'V' pre testovanie vlastneho scenaru" << std::endl;

	std::cin >> str;
	if (str.at(0) == 'a' || str.at(0) == 'A') {
		//SCENAR A
		std::cout << "TESTUJEM" << std::endl;
		TestPrioritnychFrontov<int>* testHaldy = new TestPrioritnychFrontov<int>(35, 35, 30, pocetOperacii, new Heap<int>(), "heapA.csv");
		testHaldy->testuj();
		delete testHaldy;
	}
	else if (str.at(0) == 'b' || str.at(0) == 'B') {
		//SCENAR B
		std::cout << "TESTUJEM" << std::endl;
		TestPrioritnychFrontov<int>* testHaldy = new TestPrioritnychFrontov<int>(50, 30, 20, pocetOperacii, new Heap<int>(), "heapB.csv");
		testHaldy->testuj();
		delete testHaldy;
	}
	else if (str.at(0) == 'c' || str.at(0) == 'C') {
		//SCENAR C
		std::cout << "TESTUJEM" << std::endl;
		TestPrioritnychFrontov<int>* testHaldy = new TestPrioritnychFrontov<int>(70, 25, 5, pocetOperacii, new Heap<int>(), "heapC.csv");
		testHaldy->testuj();
		delete testHaldy;

	}
	else if (str.at(0) == 'v' || str.at(0) == 'V') {
		//Vlastny scenar
		int input[3];
		std::string text[3]{ "vloz", "vyber", "ukaz" };
		int vlastnyPocOp;
		std::string nazovSuboru;

		for (int i = 0; i < 3; i++)
		{
			std::cout << "Zadajte pomer operacie " << text[i] << std::endl;

			std::cin >> str;
			try
			{
				input[i] = std::stoi(str);
			}
			catch (const std::exception e) {
				std::cout << "Hopla asi ste sa trocha uklepli no nevadi mozete to skusit znova" << std::endl;
				return;
			}
		}

		std::cout << "Zadajte pocet operacii " << std::endl;

		std::cin >> str;
		try
		{
			vlastnyPocOp = std::stoi(str);
		}
		catch (const std::exception e) {
			std::cout << "Hopla asi ste sa trocha uklepli no nevadi mozete to skusit znova" << std::endl;
			return;
		}

		std::cout << "Zadajte nazov suboru " << std::endl;
		std::cin >> nazovSuboru;

		std::cout << "TESTUJEM" << std::endl;
		TestPrioritnychFrontov<int>* testHaldy = new TestPrioritnychFrontov<int>(input[0], input[1], input[2], vlastnyPocOp, new Heap<int>(), nazovSuboru + ".csv");
		testHaldy->testuj();
		delete testHaldy;

	}
	else
	{
		std::cout << "Hopla asi ste sa trocha uklepli no nevadi mozete to skusit znova" << std::endl;
		return;
	}
	std::cout << "TESTOVANIE DOKONCENE" << std::endl;
}

inline void GUI::testovanieDvojzoznamu()
{
	std::cout << "----Testovanie prioritnych frontov----" << std::endl;
	std::cout << "  ----Testovanie Dvojzoznamu----" << std::endl;

	std::cout << "Stlacte 'A', 'B' alebo 'C' pre testovanie jednotlivych scenarov" << std::endl;
	std::cout << "Stlacte 'V' pre testovanie vlastneho scenaru" << std::endl;

	std::cin >> str;
	if (str.at(0) == 'a' || str.at(0) == 'A') {
		//SCENAR A
		std::cout << "TESTUJEM" << std::endl;
		PriorityQueueTwoLists<int>*	 pqTwoLists = new PriorityQueueTwoLists<int>();
		zvolenieStrategieDvojzoznamu(pqTwoLists, 35, pocetOperacii);

		TestPrioritnychFrontov<int>* testDvojZoznamu = new TestPrioritnychFrontov<int>(35, 35, 30, pocetOperacii, pqTwoLists, "pQTwoListsA" + str + ".csv");
		testDvojZoznamu->testuj();
		delete testDvojZoznamu;

	}
	else if (str.at(0) == 'b' || str.at(0) == 'B') {
		//SCENAR B
		std::cout << "TESTUJEM" << std::endl;
		PriorityQueueTwoLists<int>* pqTwoLists = new PriorityQueueTwoLists<int>();
		zvolenieStrategieDvojzoznamu(pqTwoLists, 50, pocetOperacii);

		TestPrioritnychFrontov<int>* testDvojZoznamu = new TestPrioritnychFrontov<int>(50, 30, 20, pocetOperacii, pqTwoLists, "pQTwoListsB" + str  + ".csv");
		testDvojZoznamu->testuj();
		delete testDvojZoznamu;

	}
	else if (str.at(0) == 'c' || str.at(0) == 'C') {
		//SCENAR C
		std::cout << "TESTUJEM" << std::endl;
		PriorityQueueTwoLists<int>* pqTwoLists = new PriorityQueueTwoLists<int>();
		zvolenieStrategieDvojzoznamu(pqTwoLists, 70, pocetOperacii);

		TestPrioritnychFrontov<int>* testDvojZoznamu = new TestPrioritnychFrontov<int>(70, 25, 5, pocetOperacii, pqTwoLists, "pQTwoListsC" + str + ".csv");
		testDvojZoznamu->testuj();
		delete testDvojZoznamu;
	}
	else if (str.at(0) == 'v' || str.at(0) == 'V') {
		//Vlastny scenar
		int input[3];
		std::string text[3]{ "vloz", "vyber", "ukaz" };
		int vlastnyPocOp;
		std::string nazovSuboru;

		for (int i = 0; i < 3; i++)
		{
			std::cout << "Zadajte pomer operacie " << text[i] << std::endl;

			std::cin >> str;
			try
			{
				input[i] = std::stoi(str);
			}
			catch (const std::exception e) {
				std::cout << "Hopla asi ste sa trocha uklepli no nevadi mozete to skusit znova" << std::endl;
				return;
			}
		}

		std::cout << "Zadajte pocet operacii " << std::endl;

		std::cin >> str;
		try
		{
			vlastnyPocOp = std::stoi(str);
		}
		catch (const std::exception e) {
			std::cout << "Hopla asi ste sa trocha uklepli no nevadi mozete to skusit znova" << std::endl;
			return;
		}

		PriorityQueueTwoLists<int>* pqTwoLists = new PriorityQueueTwoLists<int>();
		zvolenieStrategieDvojzoznamu(pqTwoLists, input[0], vlastnyPocOp);

		std::cout << "Zadajte nazov suboru " << std::endl;
		std::cin >> nazovSuboru;

		std::cout << "TESTUJEM" << std::endl;
		TestPrioritnychFrontov<int>* testDvojZoznamu = new TestPrioritnychFrontov<int>(input[0], input[1], input[2], vlastnyPocOp, pqTwoLists, nazovSuboru + ".csv");
		testDvojZoznamu->testuj();
		delete testDvojZoznamu;

	}
	else
	{
		std::cout << "Hopla asi ste sa trocha uklepli no nevadi mozete to skusit znova" << std::endl;
		return;
	}
	std::cout << "TESTOVANIE DOKONCENE" << std::endl;

	
}

template<typename T>
inline void GUI::zvolenieStrategieDvojzoznamu(PriorityQueueTwoLists<T>* pqTwoLists, float operaciaVloz, int pocOperacii)
{
	std::cout << "Stlacte 'A' pre strategiu definovania dlzky ako konstanty 1/1000 poctu vsetkych vlozeni do frontu" << std::endl;
	std::cout << "Stlacte 'B' pre strategiu definovania dlzky ako odmocnina z n, kde n je pocet prvkov vo fronte " << std::endl;
	std::cout << "Stlacte 'C' pre strategiu definovania dlzky ako n / 2, kde n je pocet prvkov vo fronte " << std::endl;

	std::cin >> str;

	if (str.at(0) == 'a' || str.at(0) == 'A')
	{
		int pom = (operaciaVloz / 100) * pocOperacii;
		pqTwoLists->constCapacityStrategy(pom);
	}
	else if (str.at(0) == 'b' || str.at(0) == 'B')
	{
		pqTwoLists->setStrategy(0);
	}
	else if (str.at(0) == 'c' || str.at(0) == 'C')
	{
		pqTwoLists->setStrategy(1);
	}
	else
	{
		std::cout << "Hopla asi ste sa trocha uklepli no nevadi mozete to skusit znova" << std::endl;
	}

}

inline void GUI::testovanieMatic()
{
	std::cout << std::endl;

	std::cout << "----Testovanie matic----" << std::endl;
	std::cout << "Stlacte : 1 : pre otestovanie suvislej matice" << std::endl;
	std::cout << "Stlacte : 2 : pre otestovanie nesuvislej matice" << std::endl;

	std::cin >> str;

	try {
		switch (std::stoi(str))
		{
		case 1: {
			testovanieSuvislejMatice();
			break;
		}

		case 2: {
			testovanieNesuvislejMatice();
			break;
		}

		default:
			std::cout << "Hopla asi ste sa trocha uklepli no nevadi mozete to skusit znova" << std::endl;
			break;
		}
		
	}
	catch (const std::exception e) {
		std::cout << "Hopla asi ste sa trocha uklepli no nevadi mozete to skusit znova" << std::endl;
	}


}

inline void GUI::testovanieSuvislejMatice()
{
	std::cout << "----Testovanie matic----" << std::endl;
	std::cout << "  ----Testovanie Suvislej Matice----" << std::endl;

	std::cout << "Stlacte 'A' pre testovanie suctu matic" << std::endl;
	std::cout << "Stlacte 'B' pre testovanie sucinu matic" << std::endl;
	//std::cout << "Stlacte 'V' pre testovanie vlastneho scenaru" << std::endl;

	std::cin >> str;
	if (str.at(0) == 'a' || str.at(0) == 'A') {
		//SCENAR A
		std::cout << "TESTUJEM" << std::endl;
		TestMatic<int>* testSuvislejMatice = new TestMatic<int>(new VytvaracSuvislychMatic<int>(), "maticaSuvislaA.csv");
		testSuvislejMatice->testujScenarA(true, false);
		testSuvislejMatice->testujScenarA(false, true);
		testSuvislejMatice->testujScenarA(true, true);
		delete testSuvislejMatice;

	}
	else if (str.at(0) == 'b' || str.at(0) == 'B') {
		//SCENAR B
		std::cout << "TESTUJEM" << std::endl;
		TestMatic<int>* testSuvislejMatice = new TestMatic<int>(new VytvaracSuvislychMatic<int>(), "maticaSuvislaB.csv");
		testSuvislejMatice->testujScenarB(true, false);
		testSuvislejMatice->testujScenarB(false, true);
		testSuvislejMatice->testujScenarB(true, true);
		delete testSuvislejMatice;

	}

	else
	{
		std::cout << "Hopla asi ste sa trocha uklepli no nevadi mozete to skusit znova" << std::endl;
		return;
	}
	std::cout << "TESTOVANIE DOKONCENE" << std::endl;
}

inline void GUI::testovanieNesuvislejMatice()
{
	std::cout << "----Testovanie matic----" << std::endl;
	std::cout << "  ----Testovanie Nesuvislej Matice----" << std::endl;

	std::cout << "Stlacte 'A' pre testovanie suctu matic" << std::endl;
	std::cout << "Stlacte 'B' pre testovanie sucinu matic" << std::endl;

	//std::cout << "Stlacte 'V' pre testovanie vlastneho scenaru" << std::endl;

	std::cin >> str;
	if (str.at(0) == 'a' || str.at(0) == 'A') {
		//SCENAR A
		std::cout << "TESTUJEM" << std::endl;
		TestMatic<int>* testNesuvislejMatice = new TestMatic<int>(new VytvaracNesuvislychMatic<int>(), "maticaNesuvislaA.csv");
		testNesuvislejMatice->testujScenarA(true, false);
		testNesuvislejMatice->testujScenarA(false, true);
		testNesuvislejMatice->testujScenarA(true, true);
		delete testNesuvislejMatice;
;
	}
	else if (str.at(0) == 'b' || str.at(0) == 'B') {
		//SCENAR B
		std::cout << "TESTUJEM" << std::endl;
		TestMatic<int>* testNesuvislejMatice = new TestMatic<int>(new VytvaracNesuvislychMatic<int>(), "maticaNesuvislaB.csv");
		testNesuvislejMatice->testujScenarB(true, false);
		testNesuvislejMatice->testujScenarB(false, true);
		testNesuvislejMatice->testujScenarB(true, true);
		delete testNesuvislejMatice;

	}
	else
	{
		std::cout << "Hopla asi ste sa trocha uklepli no nevadi mozete to skusit znova" << std::endl;
		return;
	}
	std::cout << "TESTOVANIE DOKONCENE" << std::endl;
}
