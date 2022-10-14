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
    ReactContext context = nullptr;

    REACT_INIT(Initialize);
    void Initialize(const ReactContext& reactContext) noexcept
    {
      context = reactContext;
    }

    REACT_METHOD(Open, L"open");
    void Open(const hstring ext, React::ReactPromise<hstring>&& promise) noexcept
    {
      context.UIDispatcher().Post([ext, promise, this] {
        IAsyncOperation<StorageFile> file = nullptr;
        FileOpenPicker openPicker;
        openPicker.ViewMode(PickerViewMode::List);
        openPicker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);
        openPicker.FileTypeFilter().ReplaceAll({ ext });

        file = openPicker.PickSingleFileAsync();

        context.JSDispatcher().Post([promise, file] {
          if (file != nullptr) { promise.Resolve(file.get().Path()); }
          else { promise.Reject("No file selected."); }
        });
      });
    }

    REACT_METHOD(Save, L"save");
    void Save(const hstring ext, const hstring content) noexcept
    {
      context.UIDispatcher().Post([ext, content, this] {
        IAsyncOperation<StorageFile> file = nullptr;
        FileSavePicker savePicker;
        savePicker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);
        savePicker.FileTypeChoices().Insert(ext, single_threaded_vector<hstring>({ ext }));

        file = savePicker.PickSaveFileAsync();

        context.JSDispatcher().Post([content, file] {
          if (file != nullptr) { FileIO::WriteTextAsync(file.get(), content); }
        });
      });
    }
  };
}
