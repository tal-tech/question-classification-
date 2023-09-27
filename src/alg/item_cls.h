#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <string>
#include <opencv2/opencv.hpp>
//#include <caffe/blob.hpp>
//#include <caffe/common.hpp>
//#include <caffe/layer.hpp>
//#include <caffe/net.hpp>

using namespace std;

class item_cls
{
public:
	item_cls();
	~item_cls();
	long Init(const std::string deploy_file, const std::string model_file,const int gpu_id);
	long predict(const cv::Mat& src_img, vector<int>&labelvec, vector<float>&probvec);
private:
	//std::string det_deploy_file;	
	//std::string det_model_file;	
	void setmode();	
	bool PredictCls(const cv::Mat& src_img, float& result_socre, vector<int>&labelvec, vector<float>&probvec);
	void ForwardPreprocess(const cv::Mat& src_img);
	std::vector<float> cls_mean;			
	int cls_img_height;
	int cls_img_width;
	int m_DeviceID;
	//std::shared_ptr<caffe::Net<float> > cls_net;	
};

