
#include <climits>
#include "pch.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <time.h>
using namespace std;
const int N = 17;
// final_path[] stores the final solution ie, the
// path of the salesman.
int final_path[N + 1];

// visited[] keeps track of the already visited nodes
// in a particular path
bool visited[N];

// Stores the final minimum weight of shortest tour.
int final_res = INT_MAX;

// Function to copy temporary solution to
// the final solution
void copyToFinal(int curr_path[])
{
	for (int i = 0; i < N; i++)
		final_path[i] = curr_path[i];
	final_path[N] = curr_path[0];
}

// Function to find the minimum edge cost
// having an end at the vertex i
int firstMin(int **adj, int i)
{
	int min = INT_MAX;
	for (int k = 0; k < N; k++)
		if (adj[i][k] < min && i != k)
			min = adj[i][k];
	return min;
}

// function to find the second minimum edge cost
// having an end at the vertex i
int secondMin(int **adj, int i)
{
	int first = INT_MAX, second = INT_MAX;
	for (int j = 0; j < N; j++)
	{
		if (i == j)
			continue;

		if (adj[i][j] <= first)
		{
			second = first;
			first = adj[i][j];
		}
		else if (adj[i][j] <= second &&
			adj[i][j] != first)
			second = adj[i][j];
	}
	return second;
}



// function that takes as arguments:
// curr_bound -> lower bound of the root node
// curr_weight-> stores the weight of the path so far
// level-> current level while moving in the search
//         space tree
// curr_path[] -> where the solution is being stored which
//                would later be copied to final_path[]
void TSPRec(int **adj, int curr_bound, int curr_weight,
	int level, int curr_path[])
{
	// base case is when we have reached level N which
	// means we have covered all the nodes once
	if (level == N)
	{
		// check if there is an edge from last vertex in
		// path back to the first vertex
		if (adj[curr_path[level - 1]][curr_path[0]] != 0)
		{
			// curr_res has the total weight of the
			// solution we got
			int curr_res = curr_weight +
				adj[curr_path[level - 1]][curr_path[0]];

			// Update final result and final path if
			// current result is better.
			if (curr_res < final_res)
			{
				copyToFinal(curr_path);
				final_res = curr_res;
			}
		}
		return;
	}

	// for any other level iterate for all vertices to
	// build the search space tree recursively
	for (int i = 0; i < N; i++)
	{
		// Consider next vertex if it is not same (diagonal
		// entry in adjacency matrix and not visited
		// already)
		if (adj[curr_path[level - 1]][i] != 0 &&
			visited[i] == false)
		{
			int temp = curr_bound;
			curr_weight += adj[curr_path[level - 1]][i];

			// different computation of curr_bound for
			// level 2 from the other levels
			if (level == 1)
				curr_bound -= ((firstMin(adj, curr_path[level - 1]) +
					firstMin(adj, i)) / 2);
			else
				curr_bound -= ((secondMin(adj, curr_path[level - 1]) +
					firstMin(adj, i)) / 2);

			// curr_bound + curr_weight is the actual lower bound
			// for the node that we have arrived on
			// If current lower bound < final_res, we need to explore
			// the node further
			if (curr_bound + curr_weight < final_res)
			{
				curr_path[level] = i;
				visited[i] = true;

				// call TSPRec for the next level
				TSPRec(adj, curr_bound, curr_weight, level + 1,
					curr_path);
			}

			// Else we have to prune the node by resetting
			// all changes to curr_weight and curr_bound
			curr_weight -= adj[curr_path[level - 1]][i];
			curr_bound = temp;

			// Also reset the visited array
			memset(visited, false, sizeof(visited));
			for (int j = 0; j <= level - 1; j++)
				visited[curr_path[j]] = true;
		}
	}
}

// This function sets up final_path[]  
void TSP(int **adj)
{
	int curr_path[N + 1];

	// Calculate initial lower bound for the root node
	// using the formula 1/2 * (sum of first min +
	// second min) for all edges.
	// Also initialize the curr_path and visited array
	int curr_bound = 0;
	memset(curr_path, -1, sizeof(curr_path));
 	memset(visited, 0, sizeof(visited));

	// Compute initial bound
	for (int i = 0; i < N; i++)
		curr_bound += (firstMin(adj, i) +
			secondMin(adj, i));

	// Rounding off the lower bound to an integer
	curr_bound = (curr_bound & 1) ? curr_bound / 2 + 1 :
		curr_bound / 2;

	// We start at vertex 1 so the first vertex
	// in curr_path[] is 0
	visited[0] = true;
	curr_path[0] = 0;

	// Call to TSPRec for curr_weight equal to
	// 0 and level 1
	TSPRec(adj, curr_bound, 0, 1, curr_path);
}

void readData(const string fileName);
void showData(int **tab);


int main()
{
	BruteForce *brucik = new BruteForce();
	DynamicPrograming * dynamic = new DynamicPrograming();
	string plik;
	int wybor = 8;
	while (wybor != 0) {
		cout << "Wybierz algorytm: \n1) BruteForce\n2) Programowanie Dynamiczne\n3) Koniec"<<endl;
		cin >> wybor;
		switch (wybor) {
		case 1:
			cout << "Podaj plik do otworzenia: ";
			cin >> plik;
			brucik = new BruteForce(plik);
			brucik->algorithm();
			system("pause");
			break;
		case 2:
			cout << "Podaj plik do otworzenia: ";
			cin >> plik;
			dynamic = new DynamicPrograming(plik);
			system("pause");
			break;
		case 3:
			delete brucik;
			delete dynamic;
			return 0;
		}
	}
	

}




void readData(const string fileName) {

	ifstream CityFile;
	

	if (!CityFile.is_open()) //check is file has been opened
	{
		CityFile.open(fileName.c_str(), ios::in | ios::out);

		if (!CityFile)
		{
			cerr << "Failed to open " << endl;
			exit(EXIT_FAILURE);  //abort program
		}
		else
		{
			int numberOfCities = 0;
			CityFile >> numberOfCities;
			cout << "ilosc miast = " << numberOfCities << endl;

			int **tab = new int*[numberOfCities];
			for (auto i = 0; i < numberOfCities; i++) {
				tab[i] = new int[numberOfCities];
			}

			for (auto i = 0; i < numberOfCities; i++) {
				for (auto j = 0; j < numberOfCities; j++) {
					CityFile >> tab[i][j];
				}
			}
			
			/*
			vector<int> odwiedzone;
			int temp = INT16_MAX;
			int firstCity = 0;
			odwiedzone.push_back(firstCity);
			int nextCity = firstCity;
			int allRoad = 0;
			int tempJ = 0;

			while (odwiedzone.size() <= numberOfCities) {
				temp = INT16_MAX;
				if (numberOfCities == odwiedzone.size()) {
					//nextCity = firstCity;
					temp = tab[nextCity][firstCity];
					allRoad += temp;
					cout << "Calkowita droga:" << allRoad << endl;
					break;
				}

				for (int j = 0; j < numberOfCities; j++) {

					auto result1 = std::find(std::begin(odwiedzone), std::end(odwiedzone), j);
					if (tab[nextCity][j] < temp && tab[nextCity][j] != 0 && result1 == end(odwiedzone)) {


						temp = tab[nextCity][j];
						tempJ = j;
						int tabij = tab[nextCity][j];

						cout << "tab[" << nextCity << "][" << j << "]" << tabij << endl;

					}
					if (j == numberOfCities - 1) {


						cout << "tempy: " << temp << " :" << tempJ << endl;
						nextCity = tempJ;
						odwiedzone.push_back(tempJ);
						cout << "Nastepne miasto: " << nextCity << endl;
						allRoad += temp;
					}


					//cout << "odwiedzone: " << odwiedzone.size() << endl;

				}

				cout << "Calkowita droga:" << allRoad << endl;;
			}
			*/
			
			TSP(tab);
			double czas_wyk = 0;
			//czas_wyk = (double)(clock() - tStart) / CLOCKS_PER_SEC;
			//save_data(czas_wyk);
			printf("Time taken: %.5fs\n", czas_wyk);

			for (auto i = 0; i < numberOfCities; i++) {
				delete[]tab[i];
			}
			delete[]tab;
			tab = 0;
		}
	}


	
}
// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln