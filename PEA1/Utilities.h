#pragma once
#include <fstream>
class Utilities
{
public:
	std::ifstream cityFile;
	std::stringstream buffer;
public:
	void save_data(std::string czas_wykonania,const std::string filename,const std::string algorithm);

	long long int read_QPC();

	void showMatrix(int **tab, int numberOfCities);
	Utilities();
	~Utilities();
};

