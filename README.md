# lpreditor
automatic number plate recognition engine

## Integrating the Library
```javascript

//step 1 declare a global instance of ONNX Runtime api
const OrtApi* g_ort = OrtGetApiBase()->GetApi(ORT_API_VERSION);
```
```javascript

		//step2 declare an onnx runtime environment
		std::string instanceName{ "image-classification-inference" };
		// https://github.com/microsoft/onnxruntime/blob/rel-1.6.0/include/onnxruntime/core/session/onnxruntime_c_api.h#L123
		//step2 declare an onnx runtime environment
		Ort::Env env(OrtLoggingLevel::ORT_LOGGING_LEVEL_WARNING,instanceName.c_str());
```

## License

Affero GPLv3 http://www.gnu.org/licenses/agpl-3.0.html

Commercial-friendly licensing available.

