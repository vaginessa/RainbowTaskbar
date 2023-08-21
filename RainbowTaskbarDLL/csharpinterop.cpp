﻿#include "winrt.h"
#include "RainbowTaskbarDLL_h.h"


#define IF_GET_API                                                              \
HRESULT hr;                                                                     \
winrt::com_ptr<IUnknown> _API;                                                  \
if (FAILED(hr = GetActiveObject(CLSID_AppearanceServiceAPI, 0, _API.put()))) {  \
    return hr;                                                                  \
}                                                                               \
winrt::com_ptr<IDispatch> API = _API.try_as<IDispatch>();                       \
if (API != nullptr)

#define INVOKE(x) API->Invoke(x, IID_NULL, 0, DISPATCH_METHOD, &params, 0, 0, 0)

#define NO_ARGS(x)                                                              \
DISPPARAMS params;                                                              \
params.cArgs = 0;                                                               \
params.cNamedArgs = 0;                                                          \
hr = INVOKE(x);                                                                 \
return hr



#define SAType 0
#define Close 1
#define Version 2

__declspec(dllexport) STDAPI SetAppearanceTypeDLL(UINT type) {
    IF_GET_API {
        VARIANTARG arg;
        arg.vt = VT_UI4;
        arg.ulVal = type;

        DISPPARAMS params;
        params.cArgs = 1;
        params.cNamedArgs = 0;
        params.rgvarg = &arg;
        hr = INVOKE(SAType);
        return hr;
    } else {
        return E_FAIL;
    }

}
__declspec(dllexport) STDAPI CloseDLL() {
    IF_GET_API {
        NO_ARGS(Close);
    } else {
        return E_FAIL;
    }
}
__declspec(dllexport) STDAPI VersionDLL() {
    IF_GET_API {
        NO_ARGS(Version);
    } else {
        return 0;
    }
}