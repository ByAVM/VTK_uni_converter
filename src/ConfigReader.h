#pragma once
#include <fstream>
#include <string>
#include <map>
#include <experimental/filesystem>
#include <nlohmann/json.hpp>

#include "factory/ReaderFactory.h"
#include "factory/ConverterFactory.h"
#include "factory/AdapterFactory.h"

using namespace std;
using json = nlohmann::json;
namespace fs = experimental::filesystem;

namespace vtkConv
{
  class ConfigReader {
    const string INPUT_NAME = "input";
    const string OUTPUT_NAME = "output";
    const string CONVERTER_TYPE_NAME = "converter";
    
  protected:
    shared_ptr<ConverterFactory> _converterFactory;
    shared_ptr<ReaderFactory> _readerFactory;
    shared_ptr<AdapterFactory> _adapterFactory;
    string _type;
    json config;

    /** Runs the default fields checking
     */
    void processConfig() {
      _type = this->config[CONVERTER_TYPE_NAME].get<string>();

      if (!_converterFactory->hasKey(_type)) {
        throw runtime_error("Converter '" + _type + "' not registered");
      }

      if (
        this->config.find(INPUT_NAME) == this->config.end() ||
        this->config.find(OUTPUT_NAME) == this->config.end()
      ) {
        cout << "Input / Output values not found" << endl;
      }
      fs::path input_path = this->config[INPUT_NAME].get<string>();
      fs::path output_path = this->config[OUTPUT_NAME].get<string>();

      fs::file_status input_status = fs::status(input_path);
      fs::file_status output_status = fs::status(output_path);

      if (!fs::exists(input_status) || !fs::is_directory(input_status))
      {
        throw runtime_error("Not found input directory: '" + input_path.string() + "'");
      }

      if (!fs::exists(output_status) || !fs::is_directory(output_status))
      {
        throw runtime_error("Not found output directory: '" + output_path.string() + "'");
      }
    }

  public:
    ConfigReader(shared_ptr<ConverterFactory> cf, shared_ptr<AdapterFactory> af, shared_ptr<ReaderFactory> rf) {
      _converterFactory = cf;
      _adapterFactory = af;
      _readerFactory = rf;
    }

    string getInput() {
      return this->config[INPUT_NAME].get<string>();
    }

    string getOutput() {
      return this->config[OUTPUT_NAME].get<string>();
    }

    // Чтение конфига, парсинг.
    void readConfig(const string& configPath) {
      ifstream configStream(configPath);
      configStream >> this->config;
      configStream.close();

      processConfig();
    }

    /** Return initialized converter by current config file
     * 
    */
    unique_ptr<IConverter> getConverter() {
      unique_ptr<IConverter> converter = _converterFactory->create(_type);
      converter->setDependencies(_readerFactory, _adapterFactory);
      converter->init(this->config);
      return converter;
    }
  };
} // namespace vtkConv
