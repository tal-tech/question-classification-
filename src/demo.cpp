//#include "alg_impl.h"
#include "./alg/item_cls.h"
#include "./alg/problemClass.h"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <curl/curl.h>
#include <future>
#include <map>
#include <string>
#include"json/json.h"

static item_cls* itemcls_g = nullptr;
std::vector<cv::Mat> cv_images_={cv::imread("./test.jpg")};
struct OCRItem{
    long orcitem = -1;
    std::vector<int> label_vec;
};

struct AfterProcess{
    bool success = false;
    OCRItem ocr_item;
    std::string question_detect;
    std::string orc_result;
    cv::Mat  img;
};

/*
static  size_t write_data(void *ptr, size_t size, size_t nmemb, std::string *buffer)
{
    unsigned long sizes = size * nmemb;
    if (buffer == nullptr) {
        return 0;
    }
    buffer->append((char *)ptr, sizes);
    return sizes;
}
*/

static bool LayoutProcess(std::shared_ptr<ProblemClass> p_class,
    const AfterProcess &a_p, int img_index, Json::Value &res_json){
    if(a_p.ocr_item.orcitem != 20000 || a_p.ocr_item.label_vec.empty()){
        return false;
    }
    Json::Value question_json;
    Json::Reader json_reader;
    if(!json_reader.parse(a_p.question_detect, question_json) ||//题型检测结果失败
       question_json["code"] != 20000){
        return false;
    }
    Json::Value ocr_json;
    if(!json_reader.parse(a_p.orc_result, ocr_json) ||//ocr失败
    (ocr_json["code"] != 20000 && ocr_json["code"] != 20001)){
        return false;
    }

    Json::Value layout_json;
    std::string ocr_json_str, question_json_str;
    ocr_json_str = Json::FastWriter().write(ocr_json);
    question_json_str = Json::FastWriter().write(question_json["data"]);
    auto l_p_result = p_class->LayoutProcess(a_p.img, ocr_json_str, question_json_str);
    if(!json_reader.parse(l_p_result, layout_json) ||
        !layout_json["Data"].isArray() ||
        layout_json["Data"].empty()){
        return false;
    }

    int sub_problem_num = layout_json["Data"][0].size();                         //子题目数量
    vector<int> sub_cls_res_vec;                                                 //存储每个子题目的题型类别
    for (int j = 1; j < sub_problem_num; j++) {
        string item_name = "item" + to_string(j);                              //子题目字段
        Json::Value item_json = layout_json["Data"][0][item_name];
        cv::Rect sub_rect = p_class->json2Rect(item_json);                 //json转Rect
        cv::Mat sub_img = a_p.img(sub_rect);                                 //子题目图

        /*调用题型分类模型*/
        long sub_cls_res = 0;
        std::vector<int> label;
        std::vector<float> prob;
        sub_cls_res = itemcls_g->predict(sub_img, label, prob);
        if(sub_cls_res != 20000 || label.empty()){
            return false;
        }
        sub_cls_res_vec.push_back(label[0]);
    }

    p_class->process(a_p.img, res_json, a_p.ocr_item.label_vec[0],
        sub_cls_res_vec, layout_json, img_index);
    return true;
}

bool handler(Json::Value &alg_result) {
    // 校验除请求body格式及image_url、image_base64之外的参数
    std::shared_ptr<ProblemClass> p_class(new ProblemClass());
    //预处理
    if(p_class->preProcess(cv_images_)){
        return false;
    }
    std::future<AfterProcess> af_fu[cv_images_.size()];//存放同步处理图片的结果
    cv::Mat image = cv::imread("./test.jpg");
    cv_images_.push_back(image);
    for(int i = 0; i < cv_images_.size(); i++){
        af_fu[i] = std::async(std::launch::async, [=]()->AfterProcess {//并发处理多张图片（处理后的结果需要按顺序后处理）
            //题型分类
            std::future<OCRItem> orc_item = std::async(std::launch::async, [=]()->OCRItem {
                std::vector<float> prob;
                OCRItem item;
                item.orcitem = itemcls_g->predict(cv_images_.at(i), item.label_vec, prob);
                return item;
            });
            //题型检测
            std::future<std::string> question_detect = std::async(std::launch::async, [=]()->std::string {
                std::string body, err_msg, result;
                Json::Value body_json;
               
                body_json["image_base64"] = "ok";
                
                body = Json::FastWriter().write(body_json);
                return result;
            });
            //OCR
            std::future<std::string> orc_result = std::async(std::launch::async, [=]()->std::string {
                std::string body, err_msg, result;
                Json::Value body_json;
                body_json["idx"] = std::to_string(i);
               
                body_json["openMode"] = 1;
                body_json["URL"] = "";
                body_json["imageLength"] = "ok";
                body_json["imagedata"] = "ok";
                std::map<std::string, std::string> headers;
                body = Json::FastWriter().write(body_json);
                return result;
            });
            //获取本张图片处理结果
            AfterProcess after_p;
            after_p.ocr_item = orc_item.get();
            after_p.question_detect = question_detect.get();
            after_p.orc_result = orc_result.get();
            after_p.img = cv_images_.at(i);
            return after_p;
        });
    }
    int i = 0;
    alg_result.clear();
    for(auto & fu : af_fu){
        auto res = fu.get();
        auto err = LayoutProcess(p_class, res, i, alg_result);
        i++;
    }
    return true;
}

int main(){
    Json::Value res;
    cv::Mat image = cv::imread("./test.png");
    cv_images_.push_back(image);
    handler(res);
    std::cout<<res<<std::endl;


    return 0;
}
