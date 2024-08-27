#include "pch.h"

#include "FilePanel.h"

using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Security::Cryptography;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Pickers;
using namespace winrt::Windows::Storage::Streams;

namespace winrt::FilePanel
{
  void FilePanel::Initialize(React::ReactContext const &reactContext) noexcept {
    m_context = reactContext;
  }

  void FilePanel::Open(const std::vector<std::string> ext, React::ReactPromise<std::string>&& result) noexcept {
    FilePanel::m_context.UIDispatcher().Post([ext, result, this] {
      StorageFile file = nullptr;
      FileOpenPicker picker;
      picker.ViewMode(PickerViewMode::Thumbnail);
      picker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);
      if (winrt::to_hstring(ext[0]) != L"*") {
        std::vector<winrt::hstring> hext = std::vector<winrt::hstring>();
        for (const auto& extension : ext) {
          hext.push_back(winrt::to_hstring(extension));
        }
        winrt::array_view<winrt::hstring> hextview(hext);
        picker.FileTypeFilter().ReplaceAll(hextview);
      }

      file = picker.PickSingleFileAsync().get();

      FilePanel::m_context.JSDispatcher().Post([result, file] {
        if (file != nullptr) {
          IBuffer buffer = FileIO::ReadBufferAsync(file).get();
          result.Resolve(winrt::to_string(CryptographicBuffer::EncodeToBase64String(buffer)));
        }
        else {
          result.Reject(L"No file selected.");
        }
      });
    });
  }

  void FilePanel::OpenMultiple(const std::vector<std::string> ext, React::ReactPromise<std::vector<std::string>>&& result) noexcept {
    FilePanel::m_context.UIDispatcher().Post([ext, result, this] {
      IVectorView<StorageFile> files = nullptr;
      FileOpenPicker picker;
      picker.ViewMode(PickerViewMode::Thumbnail);
      picker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);
      if (winrt::to_hstring(ext[0]) != L"*") {
        std::vector<winrt::hstring> hext = std::vector<winrt::hstring>();
        for (const auto& extension : ext) {
          hext.push_back(winrt::to_hstring(extension));
        }
        winrt::array_view<winrt::hstring> hextview(hext);
        picker.FileTypeFilter().ReplaceAll(hextview);
      }

      files = picker.PickMultipleFilesAsync().get();

      FilePanel::m_context.JSDispatcher().Post([result, files] {
        std::vector<std::string> contents = std::vector<std::string>();
        if (files.Size() > 0) {
          for (StorageFile const& file : files) {
            IBuffer buffer = FileIO::ReadBufferAsync(file).get();
            contents.push_back(winrt::to_string(CryptographicBuffer::EncodeToBase64String(buffer)));
          }
          result.Resolve(contents);
        }
        else {
          result.Reject(L"No file selected.");
        }
      });
    });
  }

  void FilePanel::OpenFolder(React::ReactPromise<std::string>&& result) noexcept {
    FilePanel::m_context.UIDispatcher().Post([result, this] {
      StorageFolder folder = nullptr;
      FolderPicker picker;
      picker.ViewMode(PickerViewMode::Thumbnail);
      picker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);

      folder = picker.PickSingleFolderAsync().get();

      FilePanel::m_context.JSDispatcher().Post([result, folder] {
        if (folder != nullptr) {
          result.Resolve(winrt::to_string(folder.Path()));
        }
        else {
          result.Reject(L"No folder selected.");
        }
      });
    });
  }

  void FilePanel::Save(std::string const& content, const std::vector<std::string> ext, React::ReactPromise<void>&& result) noexcept {
    FilePanel::m_context.UIDispatcher().Post([content, ext, result, this] {
      StorageFile file = nullptr;
      FileSavePicker picker;
      picker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);
      if (winrt::to_hstring(ext[0]) != L"*") {
        for (const auto& extension : ext) {
          IVector<winrt::hstring> extvec = IVector<winrt::hstring>();
          extvec.Append(winrt::to_hstring(extension));
          picker.FileTypeChoices().Insert(winrt::to_hstring(extension) + L" file", extvec);
        }
      }

      file = picker.PickSaveFileAsync().get();

      FilePanel::m_context.JSDispatcher().Post([content, result, file] {
        if (file != nullptr) {
          FileIO::WriteBufferAsync(file, CryptographicBuffer::DecodeFromBase64String(winrt::to_hstring(content)));
          result.Resolve();
        }
        else {
          result.Reject(L"No file selected.");
        }
      });
    });
  }
} // namespace winrt::FilePanel
