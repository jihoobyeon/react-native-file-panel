#pragma once

#include "pch.h"
#include "resource.h"

#if __has_include("codegen\NativeFilePanelDataTypes.g.h")
  #include "codegen\NativeFilePanelDataTypes.g.h"
#endif
#include "codegen\NativeFilePanelSpec.g.h"

#include "NativeModules.h"

namespace winrt::FilePanel
{

REACT_MODULE(FilePanel)
struct FilePanel
{
  using ModuleSpec = FilePanelCodegen::FilePanelSpec;

  REACT_INIT(Initialize)
  void Initialize(React::ReactContext const &reactContext) noexcept;

  REACT_METHOD(Open, L"openFile");
  void Open(const IVector<winrt::hstring> ext, React::ReactPromise<StorageFile>&& result) noexcept;

  REACT_METHOD(OpenMultiple, L"openFiles");
  void OpenMultiple(const IVector<winrt::hstring> ext, React::ReactPromise<IVectorView<StorageFile>>&& result) noexcept;

  REACT_METHOD(OpenFolder, L"openFolder");
  void OpenFolder(React::ReactPromise<StorageFolder>&& result) noexcept;

  REACT_METHOD(Save, L"saveFile");
  void Save(IBuffer const& content, const IVector<winrt::hstring> ext, React::ReactPromise<void>&& result) noexcept;

private:
  React::ReactContext m_context;
};

} // namespace winrt::FilePanel