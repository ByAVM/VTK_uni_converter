#pragma once
#include <vector>
#include <map>
#include <nlohmann/json.hpp>

#include "FileHeader.h"
#include "../reader/IReader.h"
#include "../factory/ReaderFactory.h"

using namespace std;
using json = nlohmann::json;

namespace vtkConv
{
  class CustomFileHeader : public IFileHeader {
    protected:    
      shared_ptr<ReaderFactory> readerFactory;
      map<string, double> _header;
      vector<unique_ptr<IReader>> headerConveyor;
    public:
      CustomFileHeader(shared_ptr<ReaderFactory> rf) : readerFactory(rf) {}
      double getValue(const string& key) {
        map<string, double>::iterator it = _header.find(key);

        if (it != _header.end()) {
          return it->second;
        }

        throw new HeaderException("Key \"" + key + "\" not found");
      }

      void readFile(ifstream& stream) {
        for (auto& reader : headerConveyor) {
          reader->read(stream);

          _header[reader->getTarget()] = reader->getValue();
        }
      }

      void init(const json& config) {

        for (const json& item : config) {
          unique_ptr<IReader> reader = readerFactory->create("single");
          reader->setTarget(item["ref"].get<string>());
          reader->setType(item["type"].get<string>());
          headerConveyor.push_back(move(reader));
        }
      }

      void reset() {
        for (unique_ptr<IReader>& reader : headerConveyor) {
          reader->reset();
        }
      }
  };
} // namespace vtkConv
