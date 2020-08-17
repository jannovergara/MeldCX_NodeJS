#include <nan.h>

#include <iostream>
#include <string>
#include <comdef.h>
#include <Windows.h>

#pragma comment(lib, "user32.lib")

void GetMonitorInfo(const Nan::FunctionCallbackInfo<v8::Value>& info) {

  DISPLAY_DEVICE dd;
	dd.cb = sizeof(DISPLAY_DEVICE);

	int iDevNum = 0;
	std::string str = "";
	while (EnumDisplayDevices(NULL, iDevNum, &dd, EDD_GET_DEVICE_INTERFACE_NAME)) {
		
		if (dd.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP) {
			
			// std::wcout << "Device Index: " << iDevNum << "\n";
			// std::wcout << "Device Name: " << dd.DeviceName << "\n";
			// std::wcout << "Device String: " << dd.DeviceString << "\n";
		}
		iDevNum++;

		_bstr_t b(dd.DeviceName), c(dd.DeviceString);
		const char *cDeviceName = b;
		const char *cDeviceString = c;

		str = std::to_string(iDevNum) + " " + cDeviceName + " " + cDeviceString;
	}

	// std::cout << "\nTotal number of attached displays: " << iDevNum << "\n";
    info.GetReturnValue().Set(Nan::New(str).ToLocalChecked());
}

void Init(v8::Local<v8::Object> exports) {
  v8::Local<v8::Context> context = exports->CreationContext();
  exports->Set(context,
               Nan::New("GetMonitorInfo").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(GetMonitorInfo)
                   ->GetFunction(context)
                   .ToLocalChecked());
}

NODE_MODULE(addon, Init)
