#pragma once
#include <fstream>
#include <vector>
#include <vtkSmartPointer.h>
#include <vtkDoubleArray.h>
#include <enum/enum_type.h>

using namespace std;

namespace vtkConv
{
  // Интерфейс ридера
  class IReader
  {
    protected:
    typedef vector<double> DataVector;

    public:
    // Определяет сценарий чтения данных из файла
    virtual void read(std::ifstream& stream) = 0;
    // Геттер для массива данных
    virtual vector<double>& getVector() = 0;
    // Сеттер типа данных
    virtual void setType(const std::string& type) = 0;
    // Геттер типа
    virtual EnumType getType() = 0;
    // Задание размеров элементов данных
    virtual void setTuplesCount(int tuples) = 0;
    virtual void setComponentsCount(int components) = 0;
    virtual int getTuplesCount() = 0;
    virtual int getComponentsCount() = 0;
    virtual double getValue(int index = 0) = 0;
    virtual void setTarget(const std::string& target) = 0;
    virtual const std::string& getTarget() = 0;
    virtual void setRefLink(const string&) = 0;
    virtual const string& getRefLink() = 0;
    virtual void setTitle(const string&) = 0;
    virtual const string& getTitle() = 0;
    virtual void reset() = 0;
  };  
} // namespace vtkConv
