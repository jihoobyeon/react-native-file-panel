#pragma once

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
        REACT_METHOD(Open, L"open");
        fire_and_forget Open(const hstring ext, React::ReactPromise<string> promise) noexcept
        {
            FileOpenPicker openPicker;
            openPicker.ViewMode(PickerViewMode::List);
            openPicker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);
            openPicker.FileTypeFilter().ReplaceAll({ "*" });
            
            StorageFile file = co_await openPicker.PickSingleFileAsync();
            if (file == nullptr) {
                promise.Reject("No file selected.");
            } else {
                promise.Resolve(to_string(file.Path()));
            }
        }

        REACT_METHOD(Save, L"save");
        fire_and_forget Save(const hstring ext, const hstring content) noexcept
        {
            FileSavePicker savePicker;
            savePicker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);
            savePicker.FileTypeChoices().Insert(L"All", single_threaded_vector<hstring>({ "*" }));
            
            StorageFile file = co_await savePicker.PickSaveFileAsync();
            await FileIO::WriteTextAsync(file, content);
        }
    };
}
