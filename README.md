# lpreditor
automatic number plate recognition engine

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
//step 4 declare an onnx session (ie model), by giving references to the runtime environment, session options and file path to the model
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
by Glenn Jocher (Ultralytics.com)
GPL-3.0 License

#### onnx
Copyright (c) Facebook, Inc. and Microsoft Corporation. All rights reserved.
MIT License

## License
Affero GPLv3 http://www.gnu.org/licenses/agpl-3.0.html

Commercial-friendly licensing available.

