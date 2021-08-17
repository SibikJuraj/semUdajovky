#pragma once

#include "structures/heap_monitor.h"
#include "matica.h"
#include "structures/array/array.h"


namespace structures {

	template<typename T>
	class MaticaNesuvisla : public Matica<T> {

	private:
		int pocRiadkov;
		int pocStlpcov;
		Array<Array<T>*>* matica_;

	public:
		MaticaNesuvisla(const int pocetRiadkov, const int pocetStlpcov, const T hodnota);
		MaticaNesuvisla(const int pocetRiadkov, const int pocetStlpcov, Array<Array<T>*>& listHodnot);
		~MaticaNesuvisla() override;
		T& getPrvok(const int indexRiadku, const int indexStlpca) const override;
		void setPrvok(const int indexRiadku, const int indexStlpca, const T hodnota) const override;
		int getPocetRiadkov() const override;
		int getPocetStlpcov() const override;


		MaticaNesuvisla<T>& scitaj(Matica<T>& other) const override;
		MaticaNesuvisla<T>& vynasob(Matica<T>& other) const override;

	};



	template<typename T>
	inline MaticaNesuvisla<T>::MaticaNesuvisla(const int pocetRiadkov, const int pocetStlpcov, const T hodnota) :
	Matica<T>::Matica(),
	pocRiadkov(pocetRiadkov),
	pocStlpcov(pocetStlpcov)
	{
		if (pocetRiadkov <= 0 || pocetStlpcov <= 0)
		{
			throw std::logic_error("MaticaNesuvisla(const int pocetRiadkov, const int pocetStlpcov, const T hodnota) => nespravny pocet riadkov(stlpcov)");
		}


		matica_ = new Array<Array<T>*> (pocRiadkov);
		for (int i = 0; i < pocRiadkov; i++) {
			(*matica_)[i] = new Array<T>(pocStlpcov);

			for (int j = 0; j < pocStlpcov; j++) {
				(*(*matica_)[i])[j] = hodnota;
			}
		}	

	}

	template<typename T>
	inline MaticaNesuvisla<T>::MaticaNesuvisla(const int pocetRiadkov, const int pocetStlpcov, Array<Array<T>*>& listHodnot) :
		Matica<T>::Matica(),
		pocRiadkov(pocetRiadkov),
		pocStlpcov(pocetStlpcov)
	{
		if (pocetRiadkov <= 0 || pocetStlpcov <= 0)
		{
			throw std::logic_error("MaticaNesuvisla(const int pocetRiadkov, const int pocetStlpcov, Array<Array<T>*>& listHodnot) => nespravny pocet riadkov(stlpcov)");
		}

		
		matica_ = &listHodnot;

		//std::cout << "ADRESA VYTVORENEJ MATICE V KONSTRUKTORE : " << this << std::endl;
		//std::cout << "ADRESA LISTU HODNOT V KONSTRUKTORE : " << &listHodnot << std::endl;

	}

	template<typename T>
	MaticaNesuvisla<T>::~MaticaNesuvisla() {
		for (int i = 0; i < pocRiadkov; i++) {
			delete (*matica_)[i];
			(*matica_)[i] = nullptr;
		}

		delete matica_;
		matica_ = nullptr;

	}

	template<typename T>
	T& MaticaNesuvisla<T>::getPrvok(const int indexRiadku, const int indexStlpca) const {
		DSRoutines::rangeCheckExcept(indexRiadku, pocRiadkov, "Zly index riadku!");
		DSRoutines::rangeCheckExcept(indexStlpca, pocStlpcov, "Zly index stlpca!");
		return (*(*matica_)[indexRiadku])[indexStlpca];
	}
	
	template<typename T>
	void MaticaNesuvisla<T>::setPrvok(const int indexRiadku, const int indexStlpca, const T hodnota) const {
		DSRoutines::rangeCheckExcept(indexRiadku, pocRiadkov, "Zly index riadku!");
		DSRoutines::rangeCheckExcept(indexStlpca, pocStlpcov, "Zly index stlpca!");
		(*(*matica_)[indexRiadku])[indexStlpca] = hodnota;

	}

	template<typename T>
	int MaticaNesuvisla<T>::getPocetRiadkov() const
	{
		return pocRiadkov;
	}

	template<typename T>
	int MaticaNesuvisla<T>::getPocetStlpcov() const
	{
		return pocStlpcov;
	}
	


	template<typename T>
	inline MaticaNesuvisla<T>& MaticaNesuvisla<T>::scitaj(Matica<T>& other) const
	{

		if (pocRiadkov == other.getPocetRiadkov() && pocStlpcov == other.getPocetStlpcov())
		{
			Array<Array<T>*>* listHodnot = new Array<Array<T>*>(pocRiadkov);
			

			for (int i = 0; i < pocRiadkov; i++)
			{
				(*listHodnot)[i] = new Array<T>(pocStlpcov);
				for (int j = 0; j < pocStlpcov; j++)
				{
					(*(*listHodnot)[i])[j] = getPrvok(i, j) + other.getPrvok(i, j);
				}

			}

			MaticaNesuvisla* maticaSuctu = new MaticaNesuvisla(pocRiadkov, pocStlpcov, *listHodnot);

			//std::cout << "ADRESA VYTVORENEJ MATICE V METODE : " << maticaSuctu << std::endl;
			//std::cout << "ADRESA LISTU HODNOT V METODE : " << listHodnot << std::endl;

			return *maticaSuctu;
		}
		throw std::logic_error("MaticaNesuvisla<T>::scitaj(Matica<T>& other) const => matice nesplnaju podmienky na vzajomne scitanie");

	}

	template<typename T>
	inline MaticaNesuvisla<T>& MaticaNesuvisla<T>::vynasob(Matica<T>& other) const
	{

		if (pocStlpcov == other.getPocetRiadkov())
		{
			Array<Array<T>*>* listHodnot = new Array<Array<T>*>(pocRiadkov);
			

			for (int i = 0; i < pocRiadkov; i++)
			{
				(*listHodnot)[i] = new Array<T>(other.getPocetStlpcov());

				for (int j = 0; j < other.getPocetStlpcov(); j++)
				{

					for (int k = 0; k < pocStlpcov; k++)
					{
						(*(*listHodnot)[i])[j] += getPrvok(i, k) * other.getPrvok(k, j);
					}
					
				}

			}

			MaticaNesuvisla* maticaSucinu = new MaticaNesuvisla(pocRiadkov, other.getPocetStlpcov(), *listHodnot);

			
			//std::cout << "ADRESA VYTVORENEJ MATICE V METODE : " << maticaSucinu << std::endl;
			//std::cout << "ADRESA LISTU HODNOT V METODE : " << listHodnot << std::endl;

			return *maticaSucinu;
		}
		throw std::logic_error("MaticaNesuvisla<T>::vynasob(Matica<T>& other) const => matice nesplnaju podmienky na vzajomne nasobenie");
	}



	




}