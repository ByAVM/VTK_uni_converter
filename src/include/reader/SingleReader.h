#pragma once

#include <fstream>
#include "ReaderBase.h"

using namespace std;

namespace vtkConv
{
  // Класс базового ридера. Все будущие ридеры должны наследоваться от него
  class SingleReader : public ReaderBase
  {
    protected:
    // Функция чтения одного числа из потока
    double readNumber(ifstream&);
    
    public:
    // Переопределённые методы интерфейса
    void read(ifstream&);
    
    SingleReader();
    ~SingleReader();
  };

  // Чтение файла
  void SingleReader::read(ifstream& inputStream) {
    double value = this->readNumber(inputStream);
    this->data_vector.push_back(value);
  }

  // Читение 1 числа из потока
  double SingleReader::readNumber(ifstream& stream) {
    double value = 0;

    switch (this->type) {
      case INTEGER:
      value = ReaderBase::_readNumber<int>(stream);
      break;
      case DOUBLE:
      value = ReaderBase::_readNumber<double>(stream);
      break;
      case FLOAT:
      value = ReaderBase::_readNumber<float>(stream);
      break;
    }

    return value;
  }

  SingleReader::SingleReader() {
  }

  SingleReader::~SingleReader() {}
} // namespace vtkConv

