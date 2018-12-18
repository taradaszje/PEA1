#include "pch.h"
#include "Utilities.h"
#include <fstream>



Utilities::Utilities()
{
}
void Utilities::showMatrix(int **tab, int numberOfCities) {
	for (auto i = 0; i < numberOfCities; i++) {

		for (auto j = 0; j < numberOfCities; j++) {
			std::cout << tab[i][j] << "	";
		}
		std::cout << std::endl;
	}
}


void Utilities::save_data(string czas_wykonania, const string filename,const string algorithm)
{
	fstream plik;
	plik.open("savedData.txt", std::ios::app | std::ios::out);
	if (plik.good() == true)
	{
		plik << algorithm<<" "  << czas_wykonania << std::endl;

		plik.close();
	}
}
long long int Utilities::read_QPC()
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}




Utilities::~Utilities()
{
}
