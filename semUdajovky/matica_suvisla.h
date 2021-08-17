#pragma once

#include "structures/heap_monitor.h"
#include "matica.h"
#include "structures/array/array.h"

namespace structures {

	template<typename T>
	class MaticaSuvisla : public Matica<T> {

	private:
		const int pocRiadkov;
		const int pocStlpcov;
		Array<T>* matica_;
		size_t size_;

	public:
		MaticaSuvisla(const int pocetRiadkov, const int pocetStlpcov, const T hodnota);
		MaticaSuvisla(const int pocetRiadkov, const int pocetStlpcov, Array<T>& listHodnot);
		~MaticaSuvisla() override;
		T& getPrvok(const int indexRiadku, const int indexStlpca) const override;
		void setPrvok(const int indexRiadku, const int indexStlpca, T hodnota) const override;
		int getPocetRiadkov() const override;
		int getPocetStlpcov() const override;

		int mapovaciaFunkcia(const int indexRiadku, const int indexStlpca) const;

		MaticaSuvisla<T>& scitaj(Matica<T>& other) const override;
		MaticaSuvisla<T>& vynasob(Matica<T>& other) const override;

	};


	template<typename T>
	inline MaticaSuvisla<T>::MaticaSuvisla(const int pocetRiadkov, const int pocetStlpcov, const T hodnota) :
		Matica<T>::Matica(),
		pocRiadkov(pocetRiadkov),
		pocStlpcov(pocetStlpcov)
	{	
		if (pocetRiadkov <= 0 || pocetStlpcov <= 0)
		{
			throw std::logic_error("MaticaSuvisla(const int pocetRiadkov, const int pocetStlpcov, const T hodnota) => nespravny pocet riadkov(stlpcov)");
		}



		size_ = pocRiadkov * pocStlpcov;

		
		matica_ = new Array<T>(size_);

		for (int prvok = 0; prvok < size_; prvok++)
		{
			(*matica_)[prvok] = hodnota;
		}
		
	}

	template<typename T>
	inline MaticaSuvisla<T>::MaticaSuvisla(const int pocetRiadkov, const int pocetStlpcov, Array<T>& listHodnot) :
		Matica<T>::Matica(),
		pocRiadkov(pocetRiadkov),
		pocStlpcov(pocetStlpcov)
	{
		if (pocetRiadkov <= 0 || pocetStlpcov <= 0)
		{
			throw std::logic_error("MaticaSuvisla(const int pocetRiadkov, const int pocetStlpcov, Array<T>& listHodnot) => nespravny pocet riadkov(stlpcov)");
		}

		size_t size_ = pocRiadkov * pocStlpcov;


		matica_ = &listHodnot;


		//std::cout << "ADRESA VYTVORENEJ MATICE V KONSTRUKTORE : " << this << std::endl;
		//std::cout << "ADRESA LISTU HODNOT V KONSTRUKTORE : " << &listHodnot << std::endl;
	}



	template<typename T>
	MaticaSuvisla<T>::~MaticaSuvisla() {

		delete matica_;
		matica_ = nullptr;

	}

	template<typename T>
	T& MaticaSuvisla<T>::getPrvok(const int indexRiadku, const int indexStlpca) const {

		//return (*matica_)[indexRiadku * pocStlpcov + indexStlpca];
		return (*matica_)[mapovaciaFunkcia(indexRiadku, indexStlpca)];

	}

	template<typename T>
	void MaticaSuvisla<T>::setPrvok(const int indexRiadku, const int indexStlpca, const T hodnota) const {
		(*matica_)[mapovaciaFunkcia(indexRiadku, indexStlpca)] = hodnota;
	}

	template<typename T>
	int MaticaSuvisla<T>::getPocetRiadkov() const
	{
		return pocRiadkov;
	}

	template<typename T>
	int MaticaSuvisla<T>::getPocetStlpcov() const
	{
		return pocStlpcov;
	}

	template<typename T>
	int MaticaSuvisla<T>::mapovaciaFunkcia(const int indexRiadku, const int indexStlpca) const
	{
		DSRoutines::rangeCheckExcept(indexRiadku, pocRiadkov, "Zly index riadku!");
		DSRoutines::rangeCheckExcept(indexStlpca, pocStlpcov, "Zly index stlpca!");
		return (indexRiadku * pocStlpcov + indexStlpca);
	}



	template<typename T>
	inline MaticaSuvisla<T>& MaticaSuvisla<T>::scitaj(Matica<T>& other) const
	{

		if (pocRiadkov == other.getPocetRiadkov() && pocStlpcov == other.getPocetStlpcov())
		{
			Array<T>* listHodnot = new Array<T>(size_);

			int riadok = 0;
			int stlpec = 0;
			
			for (int i = 0; i < pocRiadkov; i++)
			{
				for (int j = 0; j < pocStlpcov; j++)
				{
					(*listHodnot)[i] = getPrvok(i, j) + other.getPrvok(i, j);
				}
				/*
				stlpec = i % pocStlpcov;

				if (i % pocStlpcov == 0 && i != 0)
				{
					riadok++;
				}
				*/
				
				
				
			}

			MaticaSuvisla* maticaSuctu = new MaticaSuvisla(pocRiadkov, pocStlpcov, *listHodnot);

			//std::cout << "ADRESA VYTVORENEJ MATICE V METODE : " << maticaSuctu << std::endl;
			//std::cout << "ADRESA LISTU HODNOT V METODE : " << listHodnot << std::endl;

			return *maticaSuctu;
		}

		throw std::logic_error("MaticaSuvisla<T>::scitaj(Matica<T>& other) const => matice nesplnaju podmienky na vzajomne scitanie");

	}

	template<typename T>
	inline MaticaSuvisla<T>& MaticaSuvisla<T>::vynasob(Matica<T>& other) const
	{

		if (pocStlpcov == other.getPocetRiadkov() )
		{
			Array<T>* listHodnot = new Array<T>(pocRiadkov * other.getPocetStlpcov());

			int riadok = 0;
			int stlpec = 0;

			for (int i = 0; i < pocRiadkov; i++)
			{
				for (int j = 0; j < other.getPocetStlpcov(); j++)
				{
					for (int k = 0; k < pocStlpcov; k++)
					{
						(*listHodnot)[i] += getPrvok(i, k) * other.getPrvok(k, j);

					}
				}

				/*
				stlpec = i % other.getPocetStlpcov();

				if (i % other.getPocetStlpcov() == 0 && i != 0)
				{
					riadok++;
				}

				for (int j = 0; j < pocStlpcov; j++)
				{
					(*listHodnot)[i] += getPrvok(riadok, j) * other.getPrvok(j, stlpec);

				}
				*/


			}

			MaticaSuvisla* maticaSucinu = new MaticaSuvisla(pocRiadkov, other.getPocetStlpcov(), *listHodnot);

			//std::cout << "ADRESA VYTVORENEJ MATICE V METODE : " << maticaSucinu << std::endl;
			//std::cout << "ADRESA LISTU HODNOT V METODE : " << listHodnot << std::endl;

			return *maticaSucinu;
		}
		
		throw std::logic_error("MaticaSuvisla<T>::vynasob(Matica<T>& other) const => matice nesplnaju podmienky na vzajomne nasobenie");
	}



}