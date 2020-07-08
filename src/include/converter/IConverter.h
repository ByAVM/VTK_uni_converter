#pragma once
#include <string>
#include <nlohmann/json.hpp>

#include "../adapter/IAdapter.h"
#include "../factory/ReaderFactory.h"
#include "../factory/AdapterFactory.h"
using namespace std;

namespace vtkConv
{
  class IConverter
  {
  public:
    virtual unique_ptr<IAdapter>& convertFile(const string& filePath) = 0;
    /// Initialization by json config-file
    virtual void init(const nlohmann::json& config) = 0;
    virtual void setDependencies(shared_ptr<ReaderFactory>, shared_ptr<AdapterFactory>) = 0;
  };
} // namespace vtkConv
