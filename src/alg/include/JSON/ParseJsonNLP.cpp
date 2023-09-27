#include "ParseJsonNLP.h"

ParseJsonNLP::ParseJsonNLP(const char *jsonStr)
{

	Json::Reader reader;
	Json::Value root;

	vector<int>().swap(statusVector);
	vector<int>().swap(left_up_xVector);
	vector<int>().swap(left_up_yVector);
	vector<int>().swap(widthVector);
	vector<int>().swap(heightVector);
	vector<string>().swap(recognition_textVector);
	vector<int>().swap(judgeVector);
	vector<vector<int>>().swap(fragmentVector);
	vector<vector<string>>().swap(candi_list);
	vector<vector<int>>().swap(indexRect_list);
	if (reader.parse(jsonStr, root))
	{
		if (root["status"].type() == Json::nullValue) {
			cout << "statusNLP key is wrong" << endl;
		}
		statusNLP = root["status"].asInt();

		if (root["recognition"].type() == Json::nullValue) {
			cout << "recognition key is wrong" << endl;
		}

		for (int ii = 0; ii < root["recognition"].size(); ii++)
		{
			if (root["recognition"][ii]["status"].type() == Json::nullValue) {
				cout << "status key is wrong" << endl;
			}

			if (root["recognition"][ii]["left_up_x"].type() == Json::nullValue) {
				cout << "left_up_x key is wrong" << endl;
			}
			if (root["recognition"][ii]["left_up_y"].type() == Json::nullValue) {
				cout << "left_up_y key is wrong" << endl;
			}
			if (root["recognition"][ii]["width"].type() == Json::nullValue) {
				cout << "width key is wrong" << endl;
			}
			if (root["recognition"][ii]["height"].type() == Json::nullValue) {
				cout << "height key is wrong" << endl;
			}

			if (root["recognition"][ii]["recognition_text"].type() == Json::nullValue) {
				cout << "recognition_text key is wrong" << endl;
			}
			if (root["recognition"][ii]["judge"].type() == Json::nullValue) {
				cout << "judge key is wrong" << endl;
			}
			if (root["recognition"][ii]["index_of_fragment"].type() == Json::nullValue) {
				cout << "index_of_fragment key is wrong" << endl;
			}
			if(root["recognition"][ii]["fromType"].type() ==Json::nullValue){
				cout<< " index_of_fromType key is wrong" << endl;
			}
			if (root["recognition"][ii]["indexRect"].type() == Json::nullValue) {
				cout << "indexRect key is wrong" << endl;
			}
			fromType.push_back(root["recognition"][ii]["fromType"].asInt());
			statusVector.push_back(root["recognition"][ii]["status"].asInt());
			left_up_xVector.push_back(root["recognition"][ii]["left_up_x"].asInt());
			left_up_yVector.push_back(root["recognition"][ii]["left_up_y"].asInt());
			widthVector.push_back(root["recognition"][ii]["width"].asInt());
			heightVector.push_back(root["recognition"][ii]["height"].asInt());
			recognition_textVector.push_back(root["recognition"][ii]["recognition_text"].asString());
			stemVector.push_back(root["recognition"][ii]["recognition_question"].asString());
			ansVector.push_back(root["recognition"][ii]["recognition_answer"].asString());
			judgeVector.push_back(root["recognition"][ii]["judge"].asInt());
			vector<int> rect;
			vector<string> candi_one;
			vector<int>index_one;
			for (int jj = 0; jj < root["recognition"][ii]["index_of_fragment"].size(); jj++)
			{
				rect.push_back(root["recognition"][ii]["index_of_fragment"][jj].asInt());
			} 
			for(int jj=0;jj<root["recognition"][ii]["indexRect"].size();jj++){
				index_one.push_back(root["recognition"][ii]["indexRect"][jj].asInt());
                         }
			for(int jj=0; jj <root["recognition"][ii]["candidates"].size();jj++){
				candi_one.push_back(root["recognition"][ii]["candidates"][jj].asString());
                         }
			indexRect_list.push_back(index_one);
			candi_list.push_back(candi_one);
			fragmentVector.push_back(rect);
		}
	}
}

ParseJsonNLP::~ParseJsonNLP() {
}

int ParseJsonNLP::getStatusNLP()
{
	return statusNLP;
}

int ParseJsonNLP::getNum()
{
	return statusVector.size();
}
int ParseJsonNLP::getFromType(int index)
{
	if (index >= 0 && index < fromType.size())  return fromType[index];
	else return JSON_EMPTY_INT;
}
int ParseJsonNLP::getKey(int index)
{
	if (index >= 0 && index < statusVector.size())	return statusVector[index];
	else return JSON_EMPTY_INT;
}

int ParseJsonNLP::getX(int index)
{
	if (index >= 0 && index < statusVector.size()) return left_up_xVector[index];
	else return JSON_EMPTY_INT;
}

int ParseJsonNLP::getY(int index)
{
	if (index >= 0 && index < statusVector.size()) return left_up_yVector[index];
	else return JSON_EMPTY_INT;
}

int ParseJsonNLP::getW(int index)
{
	if (index >= 0 && index < statusVector.size()) return widthVector[index];
	else return JSON_EMPTY_INT;
}

int ParseJsonNLP::getH(int index)
{
	if (index >= 0 && index < statusVector.size()) return heightVector[index];
	else return JSON_EMPTY_INT;
}

string ParseJsonNLP::getText(int index)
{
	if (index >= 0 && index < statusVector.size()) return recognition_textVector[index];
	else return JSON_EMPTY_STRING;
}
vector<string> ParseJsonNLP::getCandidates(int index)
{
	vector<string>out;
	out.push_back(JSON_EMPTY_STRING);
	if (index >= 0 && index < candi_list.size()) return candi_list[index];
	else return out;//JSON_EMPTY_STRING;
}

int ParseJsonNLP::getJudge(int index)
{
	if (index >= 0 &&  index < statusVector.size()) return judgeVector[index];
	else return JSON_EMPTY_INT;
}

vector<int> ParseJsonNLP::getFragment(int index)
{
	vector<int> out;
	out.push_back(JSON_EMPTY_INT);
	if (index >= 0 && index < statusVector.size()) return fragmentVector[index];
	else return out;
}
string ParseJsonNLP::getStem(int index)
{
	if (index >= 0 && index < statusVector.size()) return stemVector[index];
	else return JSON_EMPTY_STRING;
}

string ParseJsonNLP::getAns(int index)
{
	if (index >= 0 && index < statusVector.size()) return ansVector[index];
	else return JSON_EMPTY_STRING;
}
vector<int> ParseJsonNLP::getIndexRect(int index){
	vector<int>out;
	out.push_back(JSON_EMPTY_INT);
	if (index >= 0 && index < statusVector.size()) return indexRect_list[index];
	else return out; 
}
