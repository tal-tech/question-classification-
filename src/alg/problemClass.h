#pragma once
#include "JSON/json.h"
#include <iostream>
#include <string>

using namespace std;

class ProblemClass {
public:
	ProblemClass();
	~ProblemClass();
	void Init(string token, string saveDir);

	int preProcess(vector<cv::Mat>& srcImgs);

	int process(cv::Mat srcMat, Json::Value& resJson, int problemCls, vector<int> subClsResVec, Json::Value layoutJson,int index);

	cv::Rect json2Rect(Json::Value root);
	string LayoutProcess(const cv::Mat &image_src, const string &regjsonstring, const string &labelstring);
private:

	Json::Value reStructureProblem(Json::Value inputJson);
private:
	string m_token;
	string m_saveDir;
	

};

