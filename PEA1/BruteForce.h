#pragma once
using namespace std;
class BruteForce 
{
protected:
	int **cities;
	int numberOfCities;
	string finalPath;

public:

	Utilities utilities;

	BruteForce();
	BruteForce(const string fileName);
	~BruteForce();

	int algorithm();
	int getNumberofCities();
	int **getCities();


};

