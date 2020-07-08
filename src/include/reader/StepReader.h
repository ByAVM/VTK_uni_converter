#pragma once

#include "ReaderBase.h"

using namespace std;

namespace vtkConv
{
  class StepReader
  {
  private:
    streampos startPosition;
  public:
    void read(ifstream& stream);
    StepReader(/* args */);
    ~StepReader();
  };

  void StepReader::read(ifstream& stream)
  {
    startPosition = stream.tellg();
    streampos currentPosition = startPosition;
    
    

    stream.seekg(startPosition);
  }
  
  StepReader::StepReader(/* args */)
  {
  }
  
  StepReader::~StepReader()
  {
  }
  
} // namespace vtkConv
