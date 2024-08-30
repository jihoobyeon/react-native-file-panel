#pragma once

#include "pch.h"
#include "resource.h"

#if __has_include("codegen\NativeFilePanelDataTypes.g.h")
  #include "codegen\NativeFilePanelDataTypes.g.h"
#endif
#include "codegen\NativeFilePanelSpec.g.h"

#include "JSValue.h"
#include "NativeModules.h"

#include <string>
#include <vector>

#include <microsoft.ui.xaml.window.h>
#include <ShObjIdl_core.h>
#include <winrt/Windows.ApplicationModel.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Security.Cryptography.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Pickers.h>

namespace winrt::FilePanel
{

REACT_MODULE(FilePanel)
struct FilePanel
{
  using ModuleSpec = FilePanelCodegen::FilePanelSpec;

  REACT_INIT(Initialize)
  void Initialize(React::ReactContext const &reactContext) noexcept;

  REACT_GET_CONSTANTS(GetConstants)
  FilePanelCodegen::FilePanelSpec_Constants GetConstants() noexcept;

  REACT_METHOD(Open, L"openFile");
  void Open(const std::vector<std::string> ext, React::ReactPromise<std::string>&& result) noexcept;

  REACT_METHOD(OpenMultiple, L"openFiles");
  void OpenMultiple(const std::vector<std::string> ext, React::ReactPromise<std::vector<std::string>>&& result) noexcept;

  REACT_METHOD(OpenFolder, L"openFolder");
  void OpenFolder(React::ReactPromise<React::JSValueObject>&& result) noexcept;

  REACT_METHOD(Save, L"saveFile");
  void Save(const std::vector<std::string> ext, std::string const& content, React::ReactPromise<void>&& result) noexcept;

private:
  React::ReactContext m_context;
};

} // namespace winrt::FilePanel
