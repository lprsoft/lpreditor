#pragma once
//************************************************************************
// Copyright (C) 2003-2006, LPReditor SARL, all rights reserved.
// author : Raphael Poulenard.
//************************************************************************
// C_MaskPixelGrey.h: interface for the C_MaskPixelGrey class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(YOLOV5_LIBTORCH_DETECTOR)
#define YOLOV5_LIBTORCH_DETECTOR

#include "detector.h"
#include <opencv2/dnn.hpp>
#include <string>
//#include <list>

class Yolov5_carac_detector : public Detector
{
public:
	//**************************
  //   construct/destruct
  //**************************
	Yolov5_carac_detector();
	Yolov5_carac_detector(const std::string& model_path, const torch::DeviceType& device_type);
	Detector& get_ref() {
		return *this;
	};
	const Detector& get_const_ref() {
		return *this;
	};
	virtual ~Yolov5_carac_detector();
	/** @brief Given the @p input frame, create input blob, run net and return result detections.
	 *  @param[in]  frame  The input image.
	 *  @param[out] classIds : classes indeces in resulting detection.
	 *  @param[out] confidences A set of corresponding confidences.
	 *  @param[out] boxes A set of bounding boxes.
	 *  @param[in] confThreshold A threshold used to filter boxes by confidences.
	 *  @param[in] nmsThreshold A threshold used in non maximum suppression.
	 */
	void detect(const cv::Mat& frame, std::vector<int>& classIds, std::vector<float>& confidences, std::vector<cv::Rect>& boxes,
		const float confThreshold = 0.4, float nmsThreshold = 0.2f);
	/** @brief Given the @p input frame, create input blob, run net and return result detections.
		 *  @param[in]  frame  The input image.
		 *  @param[out] classIds : classes indeces in resulting detection.
		 *  @param[out] confidences A set of corresponding confidences.
		 *  @param[out] boxes A set of bounding boxes.
		 *  @param[in] confThreshold A threshold used to filter boxes by confidences.
		 *  @param[in] nmsThreshold A threshold used in non maximum suppression.
		 */
	void detect(const cv::Mat& frame, std::list<int>& classIds,	std::list<float>& confidences, std::list<cv::Rect>& boxes,
		const float confThreshold = 0.4, float nmsThreshold = 0.2f);
	/** @brief  extract license plate number of all images files of a directory.
		 *  @param[in]  dir : directory path that contains all images files that will be proceeded.
	 *  @param[in]  show_image : boolean if true the image will be displayed in a window with license plate in image banner
	 *  @param[in]  time_delay : time delay in ms after which the image is destroyed
		* @return void
			* @see
		 */
	float detect(const std::string& dir, const bool show_image = false, const int time_delay = 0);
	/** @brief process an image file.
	 *  @param[in]  filename : filename of the he input image.
	 *  @param[out] lpn : the license plate number found in the image by the dnn detector.
	 *  @param[in]  show_image : boolean if true the image will be displayed in a window with license plate in image banner
	 *  @param[in]  time_delay : time delay in ms after which the image is destroyed
	* @return void
		* @see
	 */
	void detect(const std::string& image_filename, std::string& lpn, const bool show_image=false, const int time_delay=0);

	//creates training sets for a classifier that outputs the number of characters in the license plate
	//dir=directory that contains pairs of images files with corresponding xml files (that contain locataion of annotated true bb)
	/** @brief load libtorch .pt model file.
	@param model_filename : file path of the torch model file for inference
	 */
	bool load_libtorch_pt(const std::string& model_filename);
	/** @brief load classifier object.
	@param dir_path : dir path of the directory containing necessary files
	 */	
	bool load(const std::string& file_path);
};
#endif // !defined(YOLOV5_LIBTORCH_DETECTOR)