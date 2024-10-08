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

  HWND getHwnd() { // https://stackoverflow.com/questions/75436438
    struct ProcessWindow { DWORD pid; HWND hwnd; } pw = {};
    pw.pid = GetCurrentProcessId();
    EnumWindows([](auto hwnd, auto lp) {
      DWORD pid;
      GetWindowThreadProcessId(hwnd, &pid);
      if (pid != ((ProcessWindow *) lp)->pid) return TRUE;
      ((ProcessWindow *) lp)->hwnd = hwnd;
      return FALSE;
    }, (LPARAM)&pw);

    return pw.hwnd;
  }

  void FilePanel::Open(const std::vector<std::string> ext, React::ReactPromise<std::string>&& result) noexcept {
    HWND hwnd = getHwnd();
    FileOpenPicker picker = FileOpenPicker();
    picker.try_as<IInitializeWithWindow>()->Initialize(hwnd);
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
    else {
      picker.FileTypeFilter().Append(L"*");
    }

    StorageFile file = picker.PickSingleFileAsync().get();

    if (file != nullptr) {
      result.Resolve(winrt::to_string(file.Path()));
    }
    else {
      result.Reject(L"No file selected.");
    }
  }

  void FilePanel::OpenMultiple(const std::vector<std::string> ext, React::ReactPromise<std::vector<std::string>>&& result) noexcept {
    HWND hwnd = getHwnd();
    FileOpenPicker picker = FileOpenPicker();
    picker.try_as<IInitializeWithWindow>()->Initialize(hwnd);
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
    else {
      picker.FileTypeFilter().Append(L"*");
    }

    IVectorView<StorageFile> files = picker.PickMultipleFilesAsync().get();

    std::vector<std::string> contents = std::vector<std::string>();
    if (files.Size() > 0) {
      for (StorageFile const& file : files) {
        contents.push_back(winrt::to_string(file.Path()));
      }
      result.Resolve(contents);
    }
    else {
      result.Reject(L"No file selected.");
    }
  }

  void FilePanel::OpenFolder(React::ReactPromise<std::string>&& result) noexcept {
    HWND hwnd = getHwnd();
    FolderPicker picker = FolderPicker();
    picker.try_as<IInitializeWithWindow>()->Initialize(hwnd);
    picker.ViewMode(PickerViewMode::Thumbnail);
    picker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);
    picker.FileTypeFilter().Append(L"*");

    StorageFolder folder = picker.PickSingleFolderAsync().get();

    if (folder != nullptr) {
      result.Resolve(winrt::to_string(folder.Path()));
    }
    else {
      result.Reject(L"No folder selected.");
    }
  }

  void FilePanel::Save(const std::vector<std::string> ext, std::string const& content, React::ReactPromise<std::string>&& result) noexcept {
    HWND hwnd = getHwnd();
    FileSavePicker picker = FileSavePicker();
    picker.try_as<IInitializeWithWindow>()->Initialize(hwnd);
    picker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);
    winrt::hstring m = L"";

    auto extvec = winrt::single_threaded_vector<winrt::hstring>();
    if (winrt::to_hstring(ext[0]) != L"*") {
      for (const auto& extension : ext) {
        extvec.Append(winrt::to_hstring(extension));
        picker.FileTypeChoices().Insert(winrt::to_hstring(extension) + L" file", extvec);
      }
    }
    else {
      result.Reject(L"No extension specified.");
    }

    StorageFile file = picker.PickSaveFileAsync().get();

    if (file != nullptr) {
      FileIO::WriteBufferAsync(file, CryptographicBuffer::DecodeFromBase64String(winrt::to_hstring(content)));
      result.Resolve(winrt::to_string(file.Path()));
    }
    else {
      result.Reject(L"No file selected.");
    }
  }
} // namespace winrt::FilePanel
