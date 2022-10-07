#pragma once

#include "pch.h"
#include "JSValue.h"
#include "NativeModules.h"
#include <functional>

using namespace std;
using namespace winrt;
using namespace winrt::Microsoft::ReactNative;
using namespace Windows::Foundation;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;
using namespace Windows::Storage::Provider;
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
		void Open(wchar_t ext[], React::ReactPromise<string>&& result) noexcept
		{
			auto lifetime = get_strong();
			
			FileOpenPicker openPicker;
			openPicker.ViewMode(PickerViewMode::Thumbnail);
			openPicker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);
			openPicker.FileTypeFilter().Add(wcscat(dot, ext));

			StorageFile file = co_await openPicker.PickSingleFileAsync();

			if (file == nullptr) {
				result.Reject();
			} else {
				string uri = file.Path;
				result.Resolve(uri);
			}
		}

		REACT_METHOD(Save, L"save");
		void Save(wchar_t ext[], wchar_t content[]) noexcept
		{
			auto lifetime = get_strong();
			
			FileSavePicker savePicker;
			savePicker.ViewMode(PickerViewMode::Thumbnail);
			savePicker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);
			savePicker.FileTypeFilter().Add(wcscat(dot, ext));

			StorageFile file = co_await savePicker.PickSaveFileAsync();

			if (file == nullptr) {
				
			}
			else {
				await FileIO::WriteTextAsync(file, content);
			}
		}
	};
}
