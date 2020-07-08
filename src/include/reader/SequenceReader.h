#pragma once
#include <fstream>
#include "ReaderBase.h"

using namespace std;

namespace vtkConv
{
  // Ридер для чтения последовательности символов
  // TODO: Доработать смысл
  class SequenceReader : public ReaderBase
  {
    protected:
    template<typename T>
    void readSequence(vector<double>&, ifstream&, int);

    public:
    void read(ifstream& stream);

    SequenceReader();
    ~SequenceReader();
  };

  void SequenceReader::read(ifstream& stream) {
    switch (this->type) {
      case INTEGER:
      readSequence<int>(this->data_vector, stream, this->components * this->tuples);
      break;
      case DOUBLE:
      readSequence<double>(this->data_vector, stream, this->components * this->tuples);
      break;
      case FLOAT:
      readSequence<float>(this->data_vector, stream, this->components * this->tuples);
      break;
    }
  }

  template<typename T>
  void SequenceReader::readSequence(IReader::DataVector& result, ifstream& stream, int size) {

    vector<T> tmp(size);
    stream.read(reinterpret_cast<char*>(&tmp[0]), size * sizeof(T));

    result.assign(tmp.begin(), tmp.end());
  }

  SequenceReader::SequenceReader()
  {
  }
  
  SequenceReader::~SequenceReader() 
  {
  }
  
} // namespace vtkConv
