﻿#pragma once


#include "winrt.h"
#include <xamlOM.h>
#include "Taskbar.h"



class AppearanceServiceAPI;
class VisualTreeWatch;
#include "AppearanceServiceAPI.h"
#include "ErrorDebug.h"

class VisualTreeWatch : public winrt::implements<VisualTreeWatch, IVisualTreeServiceCallback2, IErrorDebug, winrt::non_agile>
{
    HRESULT STDMETHODCALLTYPE OnVisualTreeChange(ParentChildRelation relation, VisualElement element, VisualMutationType mutationType) override;
    HRESULT STDMETHODCALLTYPE OnElementStateChanged(InstanceHandle element, VisualElementState elementState, LPCWSTR context) noexcept override;

private:
    size_t line = 0;
    char* file = 0;
public:
    winrt::com_ptr<IXamlDiagnostics> xamlDiagnostics;
    winrt::com_ptr<AppearanceServiceAPI> appService;
    winrt::Windows::UI::Xaml::FrameworkElement root = nullptr; 
    winrt::Windows::UI::Core::CoreDispatcher dispatcher = nullptr;
    int taskbarFrames = 0;

    std::map<InstanceHandle, Taskbar> taskbarMap = std::map<InstanceHandle, Taskbar>();
    
    VisualTreeWatch();
    void Stop();

    template<typename T>
    T ConvertFromH(InstanceHandle handle)
    {
        winrt::Windows::Foundation::IInspectable obj;
        xamlDiagnostics->GetIInspectableFromHandle(handle, reinterpret_cast<::IInspectable**>(winrt::put_abi(obj)));

        return obj.try_as<T>();
    }

    template<typename T>
    InstanceHandle ConvertToH(T obj)
    {
        InstanceHandle handle = 0;
        xamlDiagnostics->GetHandleFromIInspectable(reinterpret_cast<::IInspectable*>(winrt::get_abi(obj)), &handle);

        return handle;
    }
};

