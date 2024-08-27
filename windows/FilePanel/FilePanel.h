#pragma once

#include "pch.h"
#include "resource.h"

#if __has_include("codegen\NativeFilePanelDataTypes.g.h")
  #include "codegen\NativeFilePanelDataTypes.g.h"
#endif
#include "codegen\NativeFilePanelSpec.g.h"

#include "NativeModules.h"

#include <string>
#include <vector>

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Security.Cryptography.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Pickers.h>

using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Security::Cryptography;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Pickers;
using namespace winrt::Windows::Storage::Streams;

namespace winrt::FilePanel
{

REACT_MODULE(FilePanel)
struct FilePanel
{
  using ModuleSpec = FilePanelCodegen::FilePanelSpec;

  REACT_INIT(Initialize)
  void Initialize(React::ReactContext const &reactContext) noexcept;

  REACT_METHOD(Open, L"openFile");
  void Open(const std::vector<std::string> ext, React::ReactPromise<std::string>&& result) noexcept;

  REACT_METHOD(OpenMultiple, L"openFiles");
  void OpenMultiple(const std::vector<std::string> ext, React::ReactPromise<std::vector<std::string>>&& result) noexcept;

  REACT_METHOD(OpenFolder, L"openFolder");
  void OpenFolder(React::ReactPromise<std::string>&& result) noexcept;

  REACT_METHOD(Save, L"saveFile");
  void Save(std::string const& content, const std::vector<std::string> ext, React::ReactPromise<void>&& result) noexcept;

private:
  React::ReactContext m_context;
};

} // namespace winrt::FilePanel
