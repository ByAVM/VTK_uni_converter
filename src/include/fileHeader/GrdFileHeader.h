#pragma once
#include "../fileHeader/FileHeader.h"

using namespace std;

namespace vtkConv
{
  class GrdFileHeader : public IFileHeader {
    protected:
      struct GrdHeader {
        char type[4];
        short sizeX;
        short sizeY;
        double xMin;
        double xMax;
        double yMin;
        double yMax;
        double zMin;
        double zMax;
      } header;
    
    public:
      double getValue(const string& key) {
        if (key == "sizeX") {
          return header.sizeX;
        } else if (key == "sizeY") {
          return header.sizeY;
        } else if (key == "xMin") {
          return header.xMin;
        } else if (key == "xMax") {
          return header.xMax;
        } else if (key == "yMin") {
          return header.yMin;
        } else if (key == "yMax") {
          return header.yMax;
        } else if (key == "zMin") {
          return header.zMin;
        } else if (key == "zMax") {
          return header.xMax;
        }

        throw new HeaderException("Key \"" + key + "\" not found");
      }
      void readFile(ifstream& stream) {
        stream.read(reinterpret_cast<char*>(&header), sizeof(header));
      }
  };
} // namespace vtkConv
