# include "json.h"
#include<iostream>
#include<vector>
#include<string>
using namespace std;

class ParseJsonModel
{
public:
	ParseJsonModel(const char * jsonStr);
	~ParseJsonModel();

	int getStatus();
	vector<string> getRegStrs();
	vector<double> getRegWeights();
	vector<int> getPositions();

private:

	int index;
	int statusVector;
	vector<string> regStrsVector;
	vector<double> weightsVector;
	vector<int> positionsVector;

};