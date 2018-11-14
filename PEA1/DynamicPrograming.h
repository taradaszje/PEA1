#pragma once
class DynamicPrograming:
	public BruteForce
{
	vector<vector<int>> state;
public:
	DynamicPrograming();
	DynamicPrograming(const string filename);
	int algorithm(int pos, int visited);
	
	~DynamicPrograming();
};

