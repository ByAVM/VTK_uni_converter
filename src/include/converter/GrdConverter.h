#pragma once
#include <fstream>
#include <vtkSOADataArrayTemplate.h>

#include "../fileHeader/GrdFileHeader.h"
#include "ConverterBase.h"

using namespace std;

namespace vtkConv
{
  class GrdConverter : public ConverterBase
  {
    protected:
    unique_ptr<IReader> zReader;
    unique_ptr<IAdapter> adapter;
  public:
    unique_ptr<IAdapter>& convertFile(const string& filePath) {
      // Инициализация
      //  = adapterFactory->create("structured_grid"); // Адаптер структурированной решетки
      unique_ptr<GrdFileHeader> header = make_unique<GrdFileHeader>(); // Заголовок
      adapter->reset();
      zReader->reset();

      cout << "Reading: " << filePath << endl;

      ifstream file(filePath, ios::binary);
      
      header->readFile(file);
      
      int sizeX = header->getValue("sizeX");
      int sizeY = header->getValue("sizeY");
      int pointsCount = sizeX * sizeY;

      zReader->setType("float");
      zReader->setComponentsCount(1);
      zReader->setTuplesCount(pointsCount);
      
      zReader->read(file);

      file.close();

      double dim[3] {(double)sizeX, (double)sizeY, 1.0};

      /**
       * собрать все в кучу с помощью SOAArray
      */
      vtkSmartPointer<vtkSOADataArrayTemplate<double>> ar
        = vtkSmartPointer<vtkSOADataArrayTemplate<double>>::New();
      ar->SetNumberOfComponents(3);
      ar->SetNumberOfTuples(pointsCount);

      double* x = new double[pointsCount]; // Приходится использовать указатели потому что vtk
      double* y = new double[pointsCount]; // пытается управлять памятью
      // double* z = new double[pointsCount];

      int ptNum = 0;
      for (int i = 0; i < sizeY; i++) {
        for (int j = 0; j < sizeX; j++) {
          x[ptNum] = j;
          y[ptNum] = i;
          ptNum++;
        }
      }

      ar->SetArray(0, x, pointsCount, false, false);
      ar->SetArray(1, y, pointsCount, false, false);

      // Копирование вектора в массив, потому что vtk сам управляет памятью.
      // copy(
      //   zReader->getVector().begin(),
      //   zReader->getVector().end(),
      //   z
      // );

      ar->SetArray(2, zReader->getVector().data(), pointsCount, false, true);

      vtkSmartPointer<vtkSOADataArrayTemplate<double>> zData
        = vtkSmartPointer<vtkSOADataArrayTemplate<double>>::New();
      zData->SetNumberOfTuples(pointsCount);
      zData->SetNumberOfComponents(1);
      zData->SetArray(0, zReader->getVector().data(), pointsCount, false, false);

      adapter->appendData("dimensions", dim); // Добавление данных в решетку
      adapter->appendData("points", ar);
      adapter->appendData("point_data", zData);

      return adapter;
    }

    void init(const nlohmann::json& config) {
      // Здесь ничего не нужно, так как в конвертере уже задана решетка
      adapter = adapterFactory->create("structured_grid"); // Адаптер структурированной решетки
      zReader = readerFactory->create("sequence");
    }
  };
} // namespace vtkConv
