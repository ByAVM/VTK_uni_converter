#pragma once
#include <string>
#include <exception>
#include <fstream>
#include <vtkSOADataArrayTemplate.h>
#include <nlohmann/json.hpp>

#include "../fileHeader/UserFileHeader.h"
#include "../factory/AdapterFactory.h"
#include "../factory/ReaderFactory.h"
#include "ConverterBase.h"

using namespace std;
using json = nlohmann::json;

namespace vtkConv
{
  class CustomConverter : public ConverterBase
  {
    protected:
    vector<unique_ptr<IReader>> conveyor;
    unique_ptr<CustomFileHeader> header;
    unique_ptr<IAdapter> adapter;

    public:
    unique_ptr<IAdapter>& convertFile(const string& filePath) {

      if (conveyor.size() > 0) {
        header->reset();
        
        for (unique_ptr<IReader>& reader : conveyor) {
          reader->reset();
        }
      }

      cout << "Reading: " << filePath << endl;
      ifstream file(filePath, ios::binary);

      header->readFile(file);
      
      for (unique_ptr<IReader>& reader : conveyor) {
        if (reader->getComponentsCount() == 0) {
          reader->setComponentsCount( header->getValue( reader->getRefLink()));
        }

        if (reader->getTuplesCount() == 0) {
          reader->setTuplesCount( header->getValue( reader->getRefLink()));
        }

        reader->read(file);
      }

      file.close();

      // TODO: Последняя часть. Правильно раскидывать данные. И не забыть специальные ридеры
      for (unique_ptr<IReader>& reader : conveyor) {
        vtkSmartPointer<vtkSOADataArrayTemplate<double>> dataArray
        = vtkSmartPointer<vtkSOADataArrayTemplate<double>>::New();

        dataArray->SetNumberOfComponents(reader->getComponentsCount());
        dataArray->SetNumberOfTuples(reader->getTuplesCount());

        for (int i = 0; i < reader->getComponentsCount(); i++) {
          double* vectorDataCopy = new double[reader->getTuplesCount()];
          copy(
            reader->getVector().begin(),
            reader->getVector().end(),
            vectorDataCopy
          );

          dataArray->SetArray(i, vectorDataCopy, reader->getTuplesCount(), true, false);
        }

        dataArray->SetName(reader->getTitle().c_str());
      }

      
      // adapter->appendData("points", points);
      // adapter->appendData("vectors", vectors);
      // adapter->appendData("point_data", e);
      // adapter->appendData("point_data", r);

      return adapter;
    }

    bool validate(const json& config) {
      json::const_iterator end = config.end();

      string required_config_fields[] = {
        "grid",
        "header",
        "data"
      };

      for (const string& field : required_config_fields) {
        if (config.find(field) == end) {
          cout << "Required field '" + field + "' not found" << endl;

          return false;
        }
      }

      return true;
    }

    void init(const json& config) {
      if (this->validate(config) == false) {
        cout << "Initialization failed" << endl;
        return;
      }
      
      header = make_unique<CustomFileHeader>(this->readerFactory); // Заголовок
      header->init(config["header"]);

      string adapterKey = config["grid"].get<string>();
      if (!adapterFactory->hasKey(adapterKey)) {
        throw new runtime_error("Grid not found");
      }

      adapter = adapterFactory->create(adapterKey); // Адаптер структурированной решетки


      for (const json& item : config["data"]) {
        string type = item["type"].get<string>(); // Тип данных
        string target = item["target"].get<string>(); // Назначение
        // TODO: Добавить проверку таргет для решетки

        string tuples = item["tuples"].get<string>();
        string components = item["components"].get<string>();
        
        string readerKey = item["reader"].get<string>();

        if (!readerFactory->hasKey(readerKey)) {
          throw new runtime_error("Reader not found");
        }

        unique_ptr<IReader> reader = readerFactory->create(readerKey);
        reader->setTarget(target);
        reader->setType(type);

        if (config["tuples"].is_number()) {
          reader->setTuplesCount(config["tuples"].get<int>());
        } else {
          reader->setRefLink(config["tuples"].get<string>());
        }

        if (config["components"].is_number()) {
          reader->setComponentsCount(config["components"].get<int>());
        } else {
          reader->setRefLink(config["components"].get<string>());
        }

        conveyor.push_back(move(reader));
      }
    }
  };
} // namespace vtkConv
