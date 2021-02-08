# lpreditor
automatic number plate recognition engine

## Build
This code is standard c++ and relies on OPENCV and ONNXruntime. These two softwares are meant to operate on a vast range of hardwares and os. Based on that, it should be possible to build on various platforms. Among them, I tested successfully Windows 10 and Linux Ubuntu (20.04). Use of CUDA has not (yet) been tested (only CPU). Building will produce an executable with command line options. It can read lpn(s) from a single image file or from multiple image files in a common directory (see command line options in the Open_LPReditor.cpp). If the actual license plate number is provided in the image filename, then statistics of the correctness of the readings are available. Furthermore, it can display a window whose name is the read lpn. It is also possible to see bounding boxes of caracters (activate show_boxes function in the code).
#### (Common) Step 1 : Download OPENCV, cmake and build
### On Windows :
#### Step 2 : onnxruntime-win-x64-1.4.0
Download onnxruntime-win-x64-1.4.0.zip and decompress somewhere
#### Step 3 : modify CMakeLists.txt
In LPReditor_ANPR/CMakeLists.txt, change ../onnxruntime-win-x64-1.4.0/ to point to the actual path of the onnxruntime-win-x64-1.4.0 directory
#### Step 4 : cmake
From cmake-gui, configure and generate LPReditor_ANPR/CMakeLists.txt 
#### Step 4 : build solution in Visual Studio

### On Linux :
#### Step 2 : onnxruntime-linux-x64-1.6.0
Download onnxruntime-linux-x64-1.6.0.tgz and decompress somewhere
#### Step 3 : modify CMakeLists.txt
In LPReditor_ANPR/CMakeLists.txt, change ../onnxruntime-linux-x64-1.6.0/ to point to the actual path of the onnxruntime-linux-x64-1.6.0 directory
#### Step 4 : cmake
From cmake-gui, configure and generate LPReditor_ANPR/CMakeLists.txt 
#### Step 4 : in the build LPReditor_ANPR/build dir make

## Integrating the Library to your c++ application
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

## Third party software

### c++ inference (present source code)

#### OpenCV 4.5.0 and higher
Copyright © 2021 , OpenCV team
Apache 2 License

#### ONNXRUNTIME
Copyright © 2020 Microsoft. All rights reserved.
MIT License

### model training

#### YOLOv5 
#1
mojombo#1
mojombo/github-flavored-markdown#1
by Glenn Jocher (Ultralytics.com)
GPL-3.0 License

#### onnx
Copyright (c) Facebook, Inc. and Microsoft Corporation. All rights reserved.
MIT License

## License
Affero GPLv3 http://www.gnu.org/licenses/agpl-3.0.html

Commercial-friendly licensing available.

