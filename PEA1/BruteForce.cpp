#include "pch.h"
#include "BruteForce.h"


BruteForce::BruteForce()
{
}

BruteForce::BruteForce(const string fileName)
{
	this->finalPath = "";
	std::cout << "Witam, jestem bruteforsik" << std::endl;
	if (!this->utilities.cityFile.is_open()) //check is file has been opened
	{
		this->utilities.cityFile.open(fileName.c_str(), ios::in | ios::out);

		if (!this->utilities.cityFile)
		{
			cerr << "Failed to open " << endl;
			exit(EXIT_FAILURE);  //abort program
		}
		else
		{
			
			this->utilities.cityFile >>this->numberOfCities;
			//cout << "ilosc miast = " << this->numberOfCities << endl;

			this->cities = new int*[numberOfCities];
			for (auto i = 0; i < numberOfCities; i++) {

				this->cities[i] = new int[numberOfCities];

				for (auto j = 0; j < numberOfCities; j++) {
					this->utilities.cityFile >> this->cities[i][j];
				}
			}
		
			//this->utilities.showMatrix(this->cities,this->numberOfCities);
		}
	}
}

int BruteForce::algorithm()
{
	int s = 0;
	// store all vertex apart from source vertex 
	vector<int> vertex;
	for (int i = 0; i < numberOfCities; i++)
		if (i != s)
			vertex.push_back(i);

	// store minimum weight Hamiltonian Cycle. 
	int min_path = INT_MAX;
	string path;
	string finalPath;
	long long int frequency, start, elapsed; //variable for counting executing time
	QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
	start = this->utilities.read_QPC();
	do {
		//finalPath2 = "a";
		// store current Path weight(cost) 
		int current_pathweight = 0;
		path = "0->";

		// compute current path weight 
		int k = s;
		for (int i = 0; i < vertex.size(); i++) {
			current_pathweight += cities[k][vertex[i]];
			k = vertex[i];
			path += to_string(k)+"->";
		}
		current_pathweight += cities[k][s];

		// update minimum 
		if (min(min_path, current_pathweight) == current_pathweight) {
			min_path = min(min_path, current_pathweight);
			finalPath = path;
		}


	} while (next_permutation(vertex.begin(), vertex.end()));
	elapsed = this->utilities.read_QPC() - start;
	
	this->utilities.buffer <<"Cities: " << this->numberOfCities<< " Time [ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
	cout<< "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
	
	this->utilities.save_data(this->utilities.buffer.str(), "savedData.txt", "BruteForce");

	cout <<"Minimalna sciezka dla algorytmu bruteforce :"<< min_path << endl;
	finalPath.append("0");
	cout << "Sciezka: " << finalPath<<endl<<endl;
	return min_path;
}

int BruteForce::getNumberofCities()
{
	return numberOfCities;
}

int **BruteForce::getCities()
{
	return cities;
}



BruteForce::~BruteForce()
{
	for (auto i = 0; i < numberOfCities; i++) {
		delete[]cities[i];
	}
	delete[]cities;
	cities = 0;
}
