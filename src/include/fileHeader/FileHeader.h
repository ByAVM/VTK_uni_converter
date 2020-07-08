#pragma once
#include <string>
#include <fstream>
#include <exception/HeaderException.h>

using namespace std;

namespace vtkConv
{
  class IFileHeader {
    public:
      virtual double getValue(const string& key) = 0;
      virtual void readFile(ifstream& stream) = 0;
  };
} // namespace vtkConv
