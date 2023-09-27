#include "ParseJsonModel.h"

ParseJsonModel::ParseJsonModel(const char *jsonStr)
{
	Json::Reader reader;
	Json::Value root;
	statusVector = JSON_EMPTY_INT;
	vector<string>().swap(regStrsVector);
	vector<double>().swap(weightsVector);
	vector<int>().swap(positionsVector);

	if (reader.parse(jsonStr, root))
	{		
			if (root["status"].type() == Json::nullValue){
				cout << "status key is wrong";
			}

			if (root["regStrs"].type() == Json::nullValue){
				cout << "regStrs key is wrong";
			}

			if (root["regWeights"].type() == Json::nullValue){
				cout << "regWeights key is wrong";
			}

			statusVector=root["status"].asInt();

			for (int ii = 0; ii < root["regStrs"].size(); ii++)
			{
				regStrsVector.push_back(root["regStrs"][ii].asString());
				//cout << ":::" << root["regStrs"][ii].asString()<<endl;
			}
			for (int ii = 0; ii < root["regWeights"].size(); ii++)
			{
				double weight = root["regWeights"][ii].asDouble();
				if (weight < (double)0.0001) {
					weightsVector.push_back((double)0.0001);
				}
				else {
					weightsVector.push_back(weight);
				}
			}
			for (int ii = 0; ii < root["position"].size(); ii++)
			{
				positionsVector.push_back(root["position"][ii].asInt());
			}
	}
}

ParseJsonModel::~ParseJsonModel() {
}

int ParseJsonModel::getStatus()
{
	return statusVector;
}

vector<string> ParseJsonModel::getRegStrs()
{
	return regStrsVector;
}

vector<double> ParseJsonModel::getRegWeights()
{
	return weightsVector;
}

vector<int> ParseJsonModel::getPositions()
{
	return positionsVector;
}
