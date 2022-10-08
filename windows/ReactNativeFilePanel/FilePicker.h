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
	FilePicker::FilePicker()
	{
        	InitializeComponent();
	}
	
	REACT_MODULE(Panel);
	struct Panel
	{
		wchar_t dot[32] = L".";

		REACT_METHOD(Open, L"open");
		fire_and_forget Open(wchar_t ext[], React::ReactPromise<string>&& result) noexcept
		{
			auto lifetime = get_strong();
			
			FileOpenPicker openPicker;
			openPicker.ViewMode(PickerViewMode::Thumbnail);
			openPicker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);
			openPicker.FileTypeFilter().ReplaceAll({ wcscat_s(dot, 32, ext) });

			StorageFile file = co_await openPicker.PickSingleFileAsync();

			if (file == nullptr) {
				result.Reject("No file selected.");
			} else {
				string uri = file.Path();
				result.Resolve(uri);
			}
		}

		REACT_METHOD(Save, L"save");
		fire_and_forget Save(wchar_t ext[], wchar_t content[]) noexcept
		{
			auto lifetime = get_strong();
			
			FileSavePicker savePicker;
			savePicker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);
			savePicker.FileTypeChoices().Insert(L"", single_threaded_vector<hstring>({ wcscat_s(dot, 32, ext) }));

			StorageFile file = co_await savePicker.PickSaveFileAsync();

			if (file == nullptr) {
				
			}
			else {
				await FileIO::WriteTextAsync(file, content);
			}
		}
	};
}
