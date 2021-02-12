/*
************************************************************************
// Copyright (C) 2021, Raphael Poulenard.
************************************************************************
// Line.h: interface for the C_Line class.
//
This program is free software : you can redistribute itand /or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
//////////////////////////////////////////////////////////////////////

third party software

c++ inference source code

OpenCV 4.5.0 and higher
Copyright © 2021 , OpenCV team
Apache 2 License

ONNXRUNTIME
Copyright © 2020 Microsoft. All rights reserved.
MIT License

model production

YOLOv5
by Glenn Jocher (Ultralytics.com)
GPL-3.0 License

onnx
Copyright (c) Facebook, Inc. and Microsoft Corporation. All rights reserved.
MIT License

*/
// Open_LPReditor.cpp : Defines the entry point for the console application.
//



#include <iterator>
#include <iostream>
#include <assert.h>
#include <cmath>
#include <exception>
#include <fstream>
#include <limits>
#include <numeric>
#include <string>
#include <filesystem>

#include <onnxruntime_c_api.h>
#include <onnxruntime_cxx_api.h>
#include <cuda_provider_factory.h>

#include <opencv2/opencv.hpp>
#include <opencv2/dnn/dnn.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>


#include "yolov5_anpr_onnx_detector.h"

#include "ONNX_detector.h"
static void help(char** argv)
{
	std::cout << "\nThis program demonstrates the automatic numberplate recognition software named LPReditor\n"
		"Usage:\n" << argv[0] << "\n--model = path to the model *.onnx file\n"
		<< "[--image = path to your image file (if you opt to process just one image) ]\n"
		<< "[--dir = path to a directory containing images files (if you opt to process all the images in the same directory)]\n"
		<< "[--show], whether to show the image in a window with license plate in banner\n"
		<< "[--time_delay= time delay in ms between two consecutive images]\n" << std::endl;
	std::cout << "Note : model.onnx file is in the package" << std::endl;
	std::cout << "Note : options [--image ] and [--dir ] are incompatible, model argument is mandatory" << std::endl;
	std::cout << "Note : if you want to see how well the engine performs, you must place the true license plate number in the image filename this way : number+underscore+license plate number\n"
		<< "for instance filename 0000000001_3065WWA34.jpg will be interpreted as an image with the license plate 3065WWA34 in it." << std::endl;
}

#include <opencv2/dnn/dnn.hpp>
//step 1 declare a global instance of ONNX Runtime api
const OrtApi* g_ort = OrtGetApiBase()->GetApi(ORT_API_VERSION);

int main(int argc, char* argv[])
{
#ifdef LPR_EDITOR_USE_CUDA
	bool useCUDA{ false };
#endif //LPR_EDITOR_USE_CUDA
#ifdef LPREDITOR_DEMO_NO_ARGS
	const int argc_ = 7;
	char* argv_[argc_];
	/*
	argv_[0] = argv[0];
	argv_[1] = "";
	argv_[2] = "--image=D:\\my\\path\\to\\an\\image.jpg";//
	argv_[3] = "--model=D:\\my\\path\\to\\the\\yolo\\model\\yolo_carac_detect.onnx ";//the yolo model file is provided in the repo
	argv_[4] = "--dir=D:\\my\\path\\to\\a\\directory\\with\\image\\files";
	argv_[5] = "--time_delay=1000";//if you want the images to be displayed by hihgui
	argv_[6] = "";
	*/
	argv_[0] = argv[0];
	argv_[1] = "";
	argv_[2] = "--image=../data/images/images test/0000000001_3065WWA34.jpg";//
	argv_[3] = "--model=../data/models/lpreditor_anpr.onnx";
	argv_[4] = "--dir=../data/images/images test";
	argv_[5] = "--time_delay=-1";//we don't want the images to be displayed by hihgui
	argv_[6] = "";
	cv::CommandLineParser parser(argc_, argv_, "{help h | | }{show | | }{time_delay | -1 | }{model | | }{image | | }{dir | | }");
#else //LPREDITOR_DEMO_NO_ARGS
	cv::CommandLineParser parser(argc, argv, "{help h | | }{show | | }{time_delay | -1 | }{model | | }{image | | }{dir | | }");
#endif //LPREDITOR_DEMO_NO_ARGS
	if (parser.has("help"))
	{
		help(argv);
		return 0;
	}
	bool show_image = false;
	if (parser.has("show"))
	{
		show_image = true;
	}
	int time_delay = -1;
	if (parser.has("time_delay"))
	{
		time_delay = parser.get<int>("time_delay");
	}
	if (!parser.has("model"))
	{
		std::cout << "\nYou must specify the model pathname by using mandatory arg --model=...\n" << std::endl;
		help(argv);
		return 0;
	}
	std::string model_filename = (parser.get<std::string>("model"));
	if (!model_filename.size())
	{
		std::cout << "\nCan't find the model file\n" << std::endl;
		help(argv);
		return 0;
	}
	else {
		//step 2 declare an onnx runtime environment
		std::string instanceName{ "image-classification-inference" };
		// https://github.com/microsoft/onnxruntime/blob/rel-1.6.0/include/onnxruntime/core/session/onnxruntime_c_api.h#L123
		Ort::Env env(OrtLoggingLevel::ORT_LOGGING_LEVEL_WARNING, instanceName.c_str());

		//step 3 declare options for the runtime environment
		Ort::SessionOptions sessionOptions;
		sessionOptions.SetIntraOpNumThreads(1);
#ifdef LPR_EDITOR_USE_CUDA
		if (useCUDA)
		{
			// Using CUDA backend
			// https://github.com/microsoft/onnxruntime/blob/rel-1.6.0/include/onnxruntime/core/providers/cuda/cuda_provider_factory.h#L13
			OrtStatus* status =
				OrtSessionOptionsAppendExecutionProvider_CUDA(sessionOptions, 0);
	}
#endif //LPR_EDITOR_USE_CUDA
		// Sets graph optimization level
		// Available levels are
		// ORT_DISABLE_ALL -> To disable all optimizations
		// ORT_ENABLE_BASIC -> To enable basic optimizations (Such as redundant node
		// removals) ORT_ENABLE_EXTENDED -> To enable extended optimizations
		// (Includes level 1 + more complex optimizations like node fusions)
		// ORT_ENABLE_ALL -> To Enable All possible optimizations
		sessionOptions.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_EXTENDED);
#ifdef _WIN32
		//step 4 declare an onnx session (ie model), by giving references to the runtime environment, session options and file path to the model
		std::wstring widestr = std::wstring(model_filename.begin(), model_filename.end());
		Yolov5_anpr_onxx_detector onnx_net(env, widestr.c_str(), sessionOptions);
#else
		Yolov5_anpr_onxx_detector onnx_net(env, model_filename.c_str(), sessionOptions);
#endif
		std::cout << "\nModel load succesfully\n" << std::endl;
		std::string image_filename = (parser.get<std::string>("image"));
		std::string dir = (parser.get<std::string>("dir"));
		if (!parser.has("image") && !parser.has("dir"))
		{
			std::cout << "\nYou must specify either an image filename or a directory (with images in it)\n" << std::endl;
			help(argv);
			return 0;
		}
		if (!dir.size() && image_filename.size())
		{
			std::string filename = cv::samples::findFile(parser.get<std::string>("image"));
			//cv::Mat img0 = cv::imread(filename, cv::IMREAD_COLOR);
			std::string lpn;
			onnx_net.detect(filename, lpn, show_image, time_delay);
		}
		else {
			//process all images files of a directory
			//step 5 call the detect function of the Yolov5_anpr_onxx_detector object, on a cv::mat object or an image file.
			//This will retieves boxes and classes of the license plate caracters
			onnx_net.detect(dir, show_image, time_delay); return 1;
		}
	}
	return 0;
}

