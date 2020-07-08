#pragma once
#include "IConverter.h"
#include "../factory/AdapterFactory.h"
#include "../factory/ReaderFactory.h"

using namespace std;

namespace vtkConv
{
  class ConverterBase : public IConverter {
    protected:
    typedef shared_ptr<AdapterFactory> sharedAdapterFactory;
    typedef shared_ptr<ReaderFactory> sharedReaderFactory;

    shared_ptr<AdapterFactory> adapterFactory;
    shared_ptr<ReaderFactory> readerFactory;

    public:
    virtual unique_ptr<IAdapter>& convertFile(const string& filePath) = 0;
    /// Initialization by json config-file
    virtual void init(const nlohmann::json& config) = 0;

    void setDependencies(sharedReaderFactory reader_factory, sharedAdapterFactory adapter_factory) {
      adapterFactory = adapter_factory;
      readerFactory = reader_factory;
    }
  };
} // namespace vtkConv
