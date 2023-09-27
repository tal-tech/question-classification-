#include "ParseJsonPHP.h"



ParseJsonPHP::ParseJsonPHP(const char* strvalue)
{
	Json::Reader reader;
		Json::Value root;
		//cout<<strvalue<<endl;
		status = 0;
		passnum="";
	if (reader.parse(strvalue, root))
	{
		// 检查是否存在相应的key
		if (root["result"]["status"].type() == Json::nullValue) {
			msg = "status key is wrong.";
				status= -1;
				return;
		}
		vector<string>  keys;
			int pstatus = root["result"]["status"].asInt();
			if (pstatus != 1) {
				msg = "信息获取失败";
					status= -1;
					return ;
			}
		
			if (root["result"]["data"].type() == Json::nullValue) {
				msg = "data key is wrong.";
					status= -1;
					return;
			}
		
			if (root["result"]["data"]["AI_identity_tag"].type() == Json::nullValue) {
				msg = "AI_identity_tag key is wrong.";
					status= -1;
					return;
			}
		
			if (root["result"]["data"]["test_infos"].type() == Json::nullValue) {
				msg = "test_infos key is wrong.";
					status= -1;
					return;
			}
		int AI_identity_tag = root["result"]["data"]["AI_identity_tag"].asInt();
			
			
			// 获取题干和答案
			ti_num = root["result"]["data"]["test_infos"].size();
			for (unsigned int ii = 0; ii < ti_num; ii++)
			{
				quesInf Q;
					string valueorin = root["result"]["data"]["test_infos"][ii]["answer"][ii].asString();
					
					if (root["result"]["data"]["test_infos"][ii]["stem"].type() == Json::nullValue) {
						msg = "stem  key is wrong.";
							status= -1;
							break;
					}
				
					if (root["result"]["data"]["test_infos"][ii]["answer"].type() == Json::nullValue) {
						msg = "answer key is wrong.";
							status= -1;
							break;
					}
				
					if (root["result"]["data"]["test_infos"][ii]["answer_num"].type() == Json::nullValue) {
						msg = "answer_num  key is wrong.";
							status= -1;
							break;
					}
				
					if (root["result"]["data"]["test_infos"][ii]["test_id"].type() == Json::nullValue) {
						msg = "test_id  key is wrong.";
							status= -1;
							break;
					}
				
					ifWinter = root["result"]["data"]["winterStation"].asInt();
				
					ifSenior = root["result"]["data"]["seniorGrades"].asInt();
					
					passnum=root["result"]["data"]["station_id"].asString();
				// testid
				int test_id = root["result"]["data"]["test_infos"][ii]["test_id"].asInt();
					//cout<<"test_id"<<test_id<<endl;
					int appli_problem = root["result"]["data"]["test_infos"][ii]["appli_problem"].asInt();
					string audio_url = "\"0\"";
					if (appli_problem == 1)
						audio_url = "\"" + root["result"]["data"]["test_infos"][ii]["audio_url"].asString() + "\"";
							//if(ii==ti_num-1)
							//	audio_url="\"https://zhidao.baidu.com/question/590141743.html\"";
							testid_json = testid_json + "\"" + "test_id" + to_string(ii) + "\":" + to_string(test_id);
							audio_json = audio_json + "\"" + "audio_id" + to_string(ii) + "\":" + audio_url;
							if (ii <ti_num - 1)
							{
								testid_json = testid_json + ",";
									audio_json = audio_json + ",";
							}
				
					
					// ti_stem 
					string ti_stem = root["result"]["data"]["test_infos"][ii]["stem"].asString();
					str_replace(ti_stem, "\\", "\\\\");
					str_replace(ti_stem, "\n", "");
					str_replace(ti_stem, "\"", "\\\"");
					//str_replace(ti_stem, "$", "");
					ti_stems.push_back(ti_stem);
					//ti_answer
					string valueori = root["result"]["data"]["test_infos"][ii]["answer"][0].asString();
					string value;
					analyze_fenshu(valueori, value);
					str_replace(valueori, "\\", "\\\\");
					valueori = "\"" + valueori + "\"";
					
					
					string ach;
					//			string audio_url=root["result"]["data"]["test_infos"][ii]["audio_url"].asString();
					int num = root["result"]["data"]["test_infos"][ii]["answer_num"].asInt();
					for (unsigned int i = 1; i <num; i++)
					{
						string valueorin = root["result"]["data"]["test_infos"][ii]["answer"][i].asString();
							string value1;
							analyze_fenshu(valueorin, value1);
							value = value + "," + value1;
							str_replace(valueorin, "\\", "\\\\");
							valueori = valueori + "," + "\"" + valueorin + "\"";
					}
				if (AI_identity_tag == 1) {
					answerStrs.push_back(value);
				}
				else
				{
					answerStrs.push_back("[" + valueori + "]");
				}
				Q.stem = ti_stem;
				str_replace(value,"\\\cdots\\\cdots","......");
					Q.answer = value;
					string cc="test_id";
					string bb = "audio_id";
					Q.test_id =  to_string(test_id);
					Q.answer_num = num;
					Q.audiourl = audio_url;
					string QW;
					if (appli_problem = 0 && num==1)
					{
						QW = ti_stem;
							str_replace(QW, "[Blank=8]", value);
					}
					else
					{
						QW = ti_stem;
					}
				Q.text = QW;
					queList.push_back(Q);
			}
		
			audio_json = "{" + audio_json + "}";
			testid_json = "{" + testid_json + "}";
			string cc = "testId";
			string bb = "audioId";
			testid_json = "\"" + cc + "\":" + testid_json;
			audio_json = "\"" + bb + "\":" + audio_json;  // "\""+"audioId"+"\":"+audio_json;
		status = 1;
			if (AI_identity_tag != 1) {
				msg = "AI Can't Recognition this passId";
					cout<<msg<<endl;
				status = -2;
					return;
			}
		
			
	}
	else
	{
		cout << "parse error\n" << endl;
			msg = "parse error";
			status = -1;
			return;
	}
}


ParseJsonPHP::~ParseJsonPHP()
{
}
void ParseJsonPHP::str_replace(std::string & str, const std::string & strsrc, const std::string &strdst)
{
	std::string::size_type pos = 0;//位置
	std::string::size_type srclen = strsrc.size();//要替换的字符串大小
	std::string::size_type dstlen = strdst.size();//目标字符串大小
	while ((pos = str.find(strsrc, pos)) != std::string::npos)
	{
		str.replace(pos, srclen, strdst);
			pos += dstlen;
	}
}
void ParseJsonPHP::delfrac(string value, string &valueout)
{
	valueout = value;
		std::size_t found = value.find("ac{");
		if (found != string::npos) {
			size_t found = value.find("ac{");
				size_t left11 = value.find("{");
				size_t right1 = value.find("}");
				
				size_t left12 = value.find("{", right1);
				size_t right2 = value.find("}", left12);
				int len1 = right1 - left11 - 1;
				int len2 = right2 - left12 - 1;
				string fenzi = value.substr(left11 + 1, len1);
				string fenmu = value.substr(left12 + 1, len2);
				valueout = fenzi + '/' + fenmu;
		}
}
	
string ParseJsonPHP::getPassNum()
{
	return passnum;
}
void ParseJsonPHP::analyze_fenshu(string ans, string &valueout)
{
	if (ans.find("[") != string::npos)
	{
		int fPos = ans.find_first_of(",");
			vector<string> ansList;
			while (fPos != string::npos)
			{
				string cutAns = ans.substr(0, fPos);
					ans = ans.substr(fPos + 1, ans.length());
					delfrac(cutAns, cutAns);
					
					ansList.push_back(cutAns);
					
					fPos = ans.find_first_of(",");
			}
		delfrac(ans, ans);
			ansList.push_back(ans);
			valueout = "[";
			for (int i = 0; i < ansList.size(); i++)
			{
				valueout += ansList[i] + ",";
			}
		valueout = valueout.substr(0, valueout.length() - 1);
	}
	else
	{
		delfrac(ans, valueout);
	}
}

string ParseJsonPHP::getTestid_json() {
	return testid_json;
}
string ParseJsonPHP::getAudio_json() {
	return audio_json;
}
vector<string> ParseJsonPHP::getTi_stems() {
	return ti_stems;
}
vector<string> ParseJsonPHP::getAnswerStrs() {
	return answerStrs;
}
string ParseJsonPHP::getSupportMsg() {
	return msg;
}
int ParseJsonPHP::getTi_num() {
	return ti_num;
}
int ParseJsonPHP::getSupportNum()
{
	return status;
}
int ParseJsonPHP::getIfWinter()
{
	return ifWinter;
}
int ParseJsonPHP::getIfSenior()
{
	return ifSenior;
}
vector<quesInf> ParseJsonPHP::getQueList()
{
	return queList;
}
