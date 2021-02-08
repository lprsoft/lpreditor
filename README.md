
  
**Deep learning number plate recognition engine, based on ![YOLOv5](https://github.com/ultralytics/yolov5) and ![onnx](https://github.com/onnx/onnx). Operates on latin characters.**

- [Build](#build)
    + [(Common) Step 1 : Download ![OpenCV](https://github.com/opencv/opencv), cmake and build](#-common--step-1---download---opencv--https---githubcom-opencv-opencv---cmake-and-build)
  * [On Windows :](#on-windows--)
    + [Step 2 : ![onnxruntime-win-x64-1.4.0](https://github.com/microsoft/onnxruntime/releases)](#step-2-----onnxruntime-win-x64-140--https---githubcom-microsoft-onnxruntime-releases-)
    + [Step 3 : modify CMakeLists.txt](#step-3---modify-cmakeliststxt)
    + [Step 4 : cmake](#step-4---cmake)
    + [Step 4 : build solution in Visual Studio](#step-4---build-solution-in-visual-studio)
  * [On Linux :](#on-linux--)
    + [Step 2 : ![onnxruntime-linux-x64-1.6.0](https://github.com/microsoft/onnxruntime/releases)](#step-2-----onnxruntime-linux-x64-160--https---githubcom-microsoft-onnxruntime-releases-)
    + [Step 3 : modify CMakeLists.txt](#step-3---modify-cmakeliststxt-1)
    + [Step 4 : cmake](#step-4---cmake-1)
    + [Step 4 : make in the build LPReditor_ANPR/build dir](#step-4---make-in-the-build-lpreditor-anpr-build-dir)
- [Integrating to your c++ code](#integrating-to-your-c---code)
- [Deep learning model file](#deep-learning-model-file)
- [More detailed description](#more-detailed-description)
- [Third party software](#third-party-software)
  * [c++ inference (present code)](#c---inference--present-code-)
    + [![OpenCV 4.5.0 and higher](https://github.com/opencv/opencv)](#--opencv-450-and-higher--https---githubcom-opencv-opencv-)
    + [![ONNXRUNTIME](https://github.com/microsoft/onnxruntime)](#--onnxruntime--https---githubcom-microsoft-onnxruntime-)
  * [model trained with the use of :](#model-trained-with-the-use-of--)
    + [![YOLOv5](https://github.com/ultralytics/yolov5)](#--yolov5--https---githubcom-ultralytics-yolov5-)
    + [![onnx](https://github.com/onnx/onnx)](#--onnx--https---githubcom-onnx-onnx-)
- [License](#license)

  
# Build
This code is standard c++ and relies on ![OpenCV](https://github.com/opencv/opencv) and ![ONNXRUNTIME](https://github.com/microsoft/onnxruntime). These two softwares are meant to operate on a vast range of hardwares and os. Based on that, it should be possible to build on various platforms. Among them, I tested successfully Windows 10 and Linux Ubuntu (20.04). Use of CUDA has not (yet) been tested (only CPU). 
### (Common) Step 1 : Download ![OpenCV](https://github.com/opencv/opencv), cmake and build
## On Windows :
### Step 2 : ![onnxruntime-win-x64-1.4.0](https://github.com/microsoft/onnxruntime/releases)
Download onnxruntime-win-x64-1.4.0.zip and decompress somewhere
### Step 3 : modify CMakeLists.txt
In LPReditor_ANPR/CMakeLists.txt, change ../onnxruntime-win-x64-1.4.0/ to point to the actual path of the onnxruntime-win-x64-1.4.0 directory
### Step 4 : cmake
From cmake-gui, configure and generate LPReditor_ANPR/CMakeLists.txt 
### Step 4 : build solution in Visual Studio

## On Linux :
### Step 2 : ![onnxruntime-linux-x64-1.6.0](https://github.com/microsoft/onnxruntime/releases)
Download onnxruntime-linux-x64-1.6.0.tgz and decompress somewhere
### Step 3 : modify CMakeLists.txt
In LPReditor_ANPR/CMakeLists.txt, change ../onnxruntime-linux-x64-1.6.0/ to point to the actual path of the onnxruntime-linux-x64-1.6.0 directory
### Step 4 : cmake
From cmake-gui, configure and generate LPReditor_ANPR/CMakeLists.txt 
### Step 4 : make in the build LPReditor_ANPR/build dir

# Integrating to your c++ code

```javascript
//step 1 declare a global instance of ONNX Runtime api
const OrtApi* g_ort = OrtGetApiBase()->GetApi(ORT_API_VERSION);
```
```javascript
//step2 declare an onnx runtime environment
std::string instanceName{ "image-classification-inference" };
// https://github.com/microsoft/onnxruntime/blob/rel-1.6.0/include/onnxruntime/core/session/onnxruntime_c_api.h#L123
Ort::Env env(OrtLoggingLevel::ORT_LOGGING_LEVEL_WARNING,instanceName.c_str());
```
```javascript
//step 3 declare options for the runtime environment
Ort::SessionOptions sessionOptions;
sessionOptions.SetIntraOpNumThreads(1);
sessionOptions.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_EXTENDED);
```
<a name="step_4">
 
```javascript
//step 4 declare an onnx session (ie model), by giving references to the runtime environment, session options and path to the model
std::wstring widestr = std::wstring(model_filename.begin(), model_filename.end());
Yolov5_anpr_onxx_detector onnx_net(env, widestr.c_str(), sessionOptions);
```
```javascript
//step 5 call the detect function of the Yolov5_anpr_onxx_detector object, on a cv::mat frame.
//This will retieves the lpn string
std::string lpn;
onnx_net.detect(frame, lpn);
```
# Deep learning model file
Mandatory : to operate, the executable must load the model file. Doing that, you have to specify, either in the command line or directly in the source code (see [step 4](#step_4)) its file path. You can download the model from here : due to its size, the lpreditor_anpr.onnx file is in the LPReditor_ANPR.zip release, under (LPReditor_ANPR/data/models/)
# More detailed description
Building will produce an executable, with command line options (see them in the Open_LPReditor.cpp). It can read lpn(s) from a single image file or alternatively, from multiple image files, in a common directory. If the actual license plate number is provided (see func getTrueLPN in the code), in the image filename, then statistics of the correctness of the readings, are available. 
 	

 

---
&nbsp;
Optionaly (in the command line), it can display a window, named with the read lpn :
 	

 

---
&nbsp;
![highgui](https://github.com/lprsoft/lpreditor/blob/master/image2.jpg).
&nbsp;
 	

 

---
Another option is to display bounding boxes of caracters and license plate ROI (by activate show_boxes function, directly in the code) :
&nbsp;
 	

 

---
(<img src="https://github.com/lprsoft/lpreditor/blob/master/image.jpg" width="640" height="480" />) 

# Third party software

## c++ inference (present code)

### ![OpenCV 4.5.0 and higher](https://github.com/opencv/opencv)
Copyright © 2021 , OpenCV team
Apache 2 License

### ![ONNXRUNTIME](https://github.com/microsoft/onnxruntime)
Copyright © 2020 Microsoft. All rights reserved.
MIT License

## model trained with the use of :

### ![YOLOv5](https://github.com/ultralytics/yolov5)

by Glenn Jocher (Ultralytics.com)
GPL-3.0 License

### ![onnx](https://github.com/onnx/onnx)
Copyright (c) Facebook, Inc. and Microsoft Corporation. All rights reserved.
MIT License

# License
all files, including the deep learning model file provided are subject to GNU General Public License v3.0

Commercial-friendly licensing available.

