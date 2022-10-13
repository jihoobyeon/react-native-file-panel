#pragma once

#include <winrt/Microsoft.ReactNative.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Pickers.h>
#include <winrt/Windows.UI.Xaml.h>

#include "pch.h"
#include "JSValue.h"
#include "NativeModules.h"

using namespace std;
using namespace winrt;
using namespace winrt::Microsoft::ReactNative;
using namespace Windows::Foundation;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;
using namespace Windows::UI::Xaml;

namespace FilePicker
{
    REACT_MODULE(Panel);
    struct Panel
    {
        ReactContext Context;
        
        REACT_INIT(Initialize);
        void Initialize(const ReactContext& reactContext) noexcept
        {
            Context = reactContext;
        }
        
        REACT_METHOD(Open, L"open");
        void Open(const hstring ext, React::ReactPromise<string>&& promise) noexcept
        {
            Context.UIDispatcher().Post([=]()->fire_and_forget {
                FileOpenPicker openPicker;
                openPicker.ViewMode(PickerViewMode::List);
                openPicker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);
                openPicker.FileTypeFilter().ReplaceAll({ ext });

                StorageFile file = co_await openPicker.PickSingleFileAsync();
                if (file != nullptr) { promise.Resolve(to_string(file.Path())); } 
                else { promise.Reject("No file selected."); }
            });
        }

        REACT_METHOD(Save, L"save");
        void Save(const hstring ext, const hstring content) noexcept
        {
            Context.UIDispatcher().Post([=]()->fire_and_forget {
                FileSavePicker savePicker;
                savePicker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);
                savePicker.FileTypeChoices().Insert(ext, single_threaded_vector<hstring>({ ext }));

                StorageFile file = co_await savePicker.PickSaveFileAsync();
                if (file != nullptr) { FileIO::WriteTextAsync(file, content); }
            });
        }
    };
}
