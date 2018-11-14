#pragma once
#include <fstream>
class Utilities
{
public:
	std::ifstream cityFile;
	double time;
public:
	void save_data(double czas_wykonania,const std::string filename);

	void showMatrix(int **tab, int numberOfCities);
	Utilities();
	~Utilities();
};

