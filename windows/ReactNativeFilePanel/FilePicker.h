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
		void Open(wchar_t ext[], React::ReactPromise<string>&& result) noexcept
		{
			wchar_t dot[32] = L".";
			wcscat_s(dot, 32, ext);
			
			FileOpenPicker openPicker;
			openPicker.ViewMode(PickerViewMode::Thumbnail);
			openPicker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);
			openPicker.FileTypeFilter().ReplaceAll({ dot });

			StorageFile file = co_await openPicker.PickSingleFileAsync();

			if (file == nullptr) {
				result.Reject("No file selected.");
			} else {
				hstring uri = file.Path();
				result.Resolve(to_string(uri));
			}
		}

		REACT_METHOD(Save, L"save");
		void Save(wchar_t ext[], wchar_t content[]) noexcept
		{
			wchar_t dot[32] = L".";
			wcscat_s(dot, 32, ext);
			
			FileSavePicker savePicker;
			savePicker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);
			savePicker.FileTypeChoices().Insert(L"", single_threaded_vector<hstring>({ dot }));

			StorageFile file = co_await savePicker.PickSaveFileAsync();

			if (file == nullptr) {
				
			} else {
				await FileIO::WriteTextAsync(file, content);
			}
		}
	};
}
