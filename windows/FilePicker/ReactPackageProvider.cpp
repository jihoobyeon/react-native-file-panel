#include "pch.h"
#include "ReactPackageProvider.h"
#include "ReactPackageProvider.g.cpp"

#include <ModuleRegistration.h>

#include "FilePicker.h"

namespace winrt::FilePicker::implementation
{
  void ReactPackageProvider::CreatePackage(IReactPackageBuilder const& packageBuilder) noexcept
  {
    AddAttributedModules(packageBuilder);
  }
}
