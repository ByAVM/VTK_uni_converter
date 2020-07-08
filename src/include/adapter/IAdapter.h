#pragma once
#include <vtkDataArray.h>
#include <vtkSmartPointer.h>
#include <enum/enum_target.h>

using namespace std;
namespace vtkConv
{
  // Назначение: преобразование данных файла в готовые данные для записи в решетку
  class IAdapter {
    protected:
    typedef vtkSmartPointer<vtkDataArray> SmartArray;

    public:
    virtual int writeFile(const string&) = 0;
    virtual void appendPoints(SmartArray data) = 0;
    virtual void appendData(const string&, SmartArray) = 0;
    virtual void appendData(const string&, double[]) = 0;
    virtual void reset() = 0;
    virtual string getExtname() = 0;
  };
} // namespace vtkConv
