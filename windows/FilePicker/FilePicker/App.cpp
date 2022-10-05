#include "pch.h"

#include "ReactPackageProvider.h"

#include "winrt/NativeModuleSample.h"

namespace winrt::SampleApp::implementation {

  App::App() noexcept {

    PackageProviders().Append(make<ReactPackageProvider>()); // Includes all modules in this project
    PackageProviders().Append(winrt::NativeModuleSample::ReactPackageProvider());
  }

} // namespace winrt::SampleApp::implementation