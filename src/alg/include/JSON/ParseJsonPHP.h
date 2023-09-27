#pragma once
#include "json.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;
struct quesInf
{
	string stem;
	string test_id;
	string answer;
	int answer_num;
	string text;
	string audiourl;
};
class ParseJsonPHP
{
public:
	ParseJsonPHP(const char* strvalue);
	~ParseJsonPHP();

	string getPassNum();
	string getTestid_json();
	string getAudio_json();
	vector<string> getTi_stems();
	vector<string> getAnswerStrs();
	vector<quesInf> getQueList();
	string getSupportMsg();
	int getTi_num();
	int getSupportNum();
	int getIfWinter();
	int getIfSenior();
private:
	int status;
	string passnum;
	vector<quesInf> queList;
	vector<string> ti_stems;
	vector<string> answerStrs;
	int ti_num;
	string testid_json;
	string audio_json;
	string msg;
	int ifWinter;
	int ifSenior;


	void str_replace(std::string & str, const std::string & strsrc, const std::string &strdst);
	void delfrac(string value, string &valueout);
	void analyze_fenshu(string ans, string &valueout);
};

