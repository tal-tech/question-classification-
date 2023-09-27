#ifndef PARSEJSONNLP_H
#define PARSEJSONNLP_H
# include "json.h"
#include<iostream>
#include<vector>
#include<string>
using namespace std;

class ParseJsonNLP
{
public:
	ParseJsonNLP(const char * jsonStr);
	~ParseJsonNLP();


	string getAns(int index);
	string getStem(int index);
	int getStatusNLP();
	int getNum();
	int getKey(int index);
	int getX(int index);
	int getY(int index);
	int getW(int index);
	int getH(int index);
	vector<string> getCandidates(int index);
	string getText(int index);
	int getJudge(int index);
	vector<int> getFragment(int index);
	int getFromType(int index);
	vector<int>getIndexRect(int index);
private:
	int index;
	int statusNLP;
	vector<int> statusVector;
	vector<int> left_up_xVector;
	vector<int> left_up_yVector;
	vector<int> widthVector;
	vector<int> heightVector;
	vector<string> recognition_textVector;
	vector<string> stemVector;
	vector<string> ansVector;
	vector<int> judgeVector;
	vector<vector<int>> fragmentVector;
	vector<int> fromType;
	vector<vector<string>> candi_list;
	vector<vector<int>>indexRect_list;
};
#endif
