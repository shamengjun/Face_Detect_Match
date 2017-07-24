#pragma once
#ifndef _BCNNAPI_H__
#define _BCNNAPI_H__

#define B_BUILDING_DLL
#ifdef B_BUILDING_DLL
#define BCNN_API _declspec(dllexport)
#else
#define BCNN_API _declspec(dllimport)
#endif
#include <iostream>
#include <string>
#include <opencv2\opencv.hpp>
#include <opencv2\opencv_modules.hpp>
#include "distance.h"
using namespace std;
using namespace cv;


//* Pair(label,confidence) represent a prediction
typedef std::pair<int, float> Prediction;

//----------------------------屏蔽模型加载过程的接口--------------------------------------------------------------
BCNN_API vector<Prediction> bcnn_classify_topN(const cv::Mat& img, int N, const string& param_file);

BCNN_API vector<float> bcnn_extract_features(const cv::Mat& img, const string& layer_name, const string& param_file);

BCNN_API vector<float> bcnn_extract_normalized_features(const cv::Mat& img, const string& layer_name, const string& param_file);

BCNN_API float bcnn_compare_objects(const cv::Mat& img1, const cv::Mat& img2, const string& feat_name, DISTANCE_TYPE distance_type, const string& param_file);

BCNN_API float bcnn_compare_features(const vector<float>& feat1, const vector<float>& feat2, DISTANCE_TYPE distance_type);



//----------------------------加载模型与功能函数分开的接口--------------------------------------------------------------

BCNN_API void INIT_BCNN_MODEL(const string& deploy_prototxt_file, const string& trained_model_file,
	const string& binary_mean_file);

BCNN_API void INIT_BCNN_MODEL(const string& param_file);

BCNN_API vector<Prediction> bcnn_classify_topN(const cv::Mat& img, int N);

BCNN_API vector<float> bcnn_extract_features(const cv::Mat& img, const string& layer_name);

BCNN_API vector<float> bcnn_extract_normalized_features(const cv::Mat& img, const string& layer_name);

BCNN_API float bcnn_compare_objects(const cv::Mat& img1, const cv::Mat& img2, const string& feat_name, DISTANCE_TYPE distance_type);

//BCNN_API float bcnn_compare_features(const vector<float>& feat1, const vector<float>& feat2, DISTANCE_TYPE distance_type);


#endif#pragma once
