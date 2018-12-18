#include "pch.h"
#include "DynamicPrograming.h"


DynamicPrograming::DynamicPrograming()
{
}

DynamicPrograming::DynamicPrograming(const string fileName)
{
	
	
	std::cout << "Witam, jestem dynamiczny" << std::endl;
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

			this->utilities.cityFile >> this->numberOfCities;
			//cout << "ilosc miast = " << this->numberOfCities << endl;

			this->cities = new int*[numberOfCities];
			for (auto i = 0; i < numberOfCities; i++) {

				this->cities[i] = new int[numberOfCities];

				for (auto j = 0; j < numberOfCities; j++) {
					this->utilities.cityFile >> this->cities[i][j];
				}
			}

			//this->utilities.showMatrix(this->cities, this->numberOfCities);
		}
	}

	vector<vector<int>> init(this->numberOfCities);
	this->state.swap(init);
	for (auto& neighbors : state)
		neighbors = vector<int>((1 << this->numberOfCities) - 1, INT_MAX);

	//cout << "Wynik dzialania 1 << this->numberOfCities) - 1 = " <<( 1 << this->numberOfCities - 1)<<endl;

	long long int frequency, start, elapsed; //variable for counting executing time
	QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);

	start = this->utilities.read_QPC();
	cout << "Minimalna droga wg programowania dynamicznego: " << this->algorithm(0, 1) << endl;
	elapsed = this->utilities.read_QPC() - start;

	cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
	this->utilities.buffer <<"Cities: "<<this->numberOfCities<< " Time [ms] = " << setprecision(0) << (1000.0 * elapsed) / frequency << endl;
	this->utilities.save_data(this->utilities.buffer.str(), "savedData.txt", "Dynamic Programming");


	//cout << "Droga: " << this->finalPath <<	endl;
}

int DynamicPrograming::algorithm(int pos, int visited)
{
	
	//returning to starting city when visited == 2^(numberOfCities-1)
	if (visited == ((1 << this->numberOfCities) - 1)) {

		
		return cities[pos][0]; // return to starting city
	}
	//returning to starting city when road to point isn't intmax
	if (state[pos][visited] != INT_MAX) {
		
		return state[pos][visited];
	}
	// tu sie zaczyna rozpierdol takze polecam obejrzec jakiegos turasa na necie.
	for (int i = 0; i < this->numberOfCities; ++i)
	{
		// can't visit ourselves unless we're ending & skip if already visited
		if (i == pos || (visited & (1 << i)))
			continue;

		int distance = cities[pos][i] + algorithm( i, visited | (1 << i));
		if (distance < state[pos][visited]) {
			state[pos][visited] = distance;
			this->finalPath += to_string(i);
		}
	}

	return state[pos][visited];
}




DynamicPrograming::~DynamicPrograming()
{
}
