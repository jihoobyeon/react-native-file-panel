#pragma once

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Pickers.h>

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
		fire_and_forget Open(wchar_t ext[], React::ReactPromise<string> promise) noexcept
		{
			wchar_t str[32] = L".";
			wcscat_s(str, 32, ext);
			
			FileOpenPicker openPicker;
			openPicker.ViewMode(PickerViewMode::List);
			openPicker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);
			openPicker.FileTypeFilter().ReplaceAll({ str });
			
			StorageFile file = co_await openPicker.PickSingleFileAsync();
			string uri = to_string(file.Path());
			if (uri == "") {
				promise.Reject("No file selected.");
			} else {
				promise.Resolve(uri);
			}
		}

		REACT_METHOD(Save, L"save");
		fire_and_forget Save(wchar_t ext[], wchar_t content[]) noexcept
		{
			wchar_t str[32] = L".";
			wcscat_s(str, 32, ext);
			
			FileSavePicker savePicker;
			savePicker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);
			savePicker.FileTypeChoices().Insert(L"", single_threaded_vector<hstring>({ str }));

			await FileIO::WriteTextAsync(co_await savePicker.PickSaveFileAsync(), content);
		}
	};
}
