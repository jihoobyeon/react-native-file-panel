#include "pch.h"

#include "FilePanel.h"

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Pickers.h>

namespace winrt::FilePanel
{
  void FilePanel::Initialize(React::ReactContext const &reactContext) noexcept {
    m_context = reactContext;
  }

  void Open(const IVector<winrt::hstring> ext, React::ReactPromise<StorageFile>&& result) noexcept {
    context.UIDispatcher().Post([ext, result, this]) {
      IAsyncOperation<StorageFile> file = nullptr;
      FileOpenPicker picker;
      picker.ViewMode(PickerViewMode::Thumbnail);
      picker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);
      if (ext.GetAt(0) != L"*") {
        picker.FileTypeFilter().ReplaceAll(ext.GetView());
      }

      file = picker.PickSingleFileAsync();

      m_context.JSDispatcher().Post([result, file]) {
        if (file.get() != nullptr) {
          result.Resolve(file.get());
        }
        else {
          result.Reject("No file selected.");
        }
      }
    }
  }

  void OpenMultiple(const IVector<winrt::hstring> ext, React::ReactPromise<IVectorView<StorageFile>>&& result) noexcept {
    context.UIDispatcher().Post([ext, result, this]) {
      IAsyncOperation<IVectorView<StorageFile>> files = nullptr;
      FileOpenPicker picker;
      picker.ViewMode(PickerViewMode::Thumbnail);
      picker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);
      if (ext.GetAt(0) != L"*") {
        picker.FileTypeFilter().ReplaceAll(ext.GetView());
      }

      files = picker.PickMultipleFileAsync();

      m_context.JSDispatcher().Post([result, files]) {
        if (files.get().Size > 0) {
          result.Resolve(files.get());
        }
        else {
          result.Reject("No file selected.");
        }
      }
    }
  }

  void OpenFolder(React::ReactPromise<StorageFolder>&& result) noexcept {
    context.UIDispatcher().Post([result, this]) {
      IAsyncOperation<StorageFolder> folder = nullptr;
      FolderPicker picker;
      picker.ViewMode(PickerViewMode::Thumbnail);
      picker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);

      folder = picker.PickSingleFolderAsync();

      m_context.JSDispatcher().Post([result, folder]) {
        if (folder.get() != nullptr) {
          result.Resolve(folder.get());
        }
        else {
          result.Reject("No file selected.");
        }
      }
    }
  }

  void Save(IBuffer const& content, const IVector<winrt::hstring> ext, React::ReactPromise<void>&& result) noexcept {
    context.UIDispatcher().Post([result, this]) {
      IAsyncOperation<StorageFile> file = nullptr;
      FileSavePicker picker;
      picker.ViewMode(PickerViewMode::Thumbnail);
      picker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);
      if (ext.GetAt(0) != L"*") {
        for (const auto& extension : ext) {
          picker.FileTypeChoices().Insert(extension + L" file", extension);
        }
      }

      file = picker.PickSaveFileAsync();

      m_context.JSDispatcher().Post([result, file]) {
        if (file.get() != nullptr) {
          FileIO::WriteBufferAsync(file.get(), content);
          result.Resolve();
        }
        else {
          result.Reject("No file selected.");
        }
      }
    }
  }
} // namespace winrt::FilePanel