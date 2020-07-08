#pragma once
#include <map>
#include <vtkPoints.h>
#include <vtkStructuredGrid.h>
#include <vtkXMLStructuredGridWriter.h>
#include <vtkPointData.h>

#include "AdapterBase.h"

using namespace std;
namespace vtkConv
{
  class StructuredGridAdapter : public AdapterBase<vtkStructuredGrid, vtkXMLStructuredGridWriter> {
    protected:
      enum Target {POINTS, DIMENSIONS, POINT_DATA};
      map<string, Target> targetMap {
        {"points", POINTS},
        {"dimensions", DIMENSIONS},
        {"point_data", POINT_DATA}
      };

      typedef vtkSmartPointer<vtkPoints> SmartPoints;
      typedef vtkSmartPointer<vtkStructuredGrid> SmartGrid;
      typedef vtkSmartPointer<vtkXMLStructuredGridWriter> SmartWriter;
      
      const string extName = ".vts";

      // Специфичные методы для решетки
      void setDimensions(double dim[]) {
        grid->SetDimensions(dim[0], dim[1], dim[2]);
      }

    public:
    StructuredGridAdapter() : AdapterBase() {}

    string getExtname() { return extName; }

    void appendPoints(SmartArray data) {
      SmartPoints points = SmartPoints::New();
      points->SetData(data);
      grid->SetPoints(points);
    }

    void appendData(const string& dataTarget, double data[]) {
      map<string, Target>::iterator it = targetMap.find(dataTarget);

      switch (it->second) {
        case DIMENSIONS:
          setDimensions(data);
          break;
      }
    }

    void appendData(const string& dataTarget, SmartArray data) {
      map<string, Target>::iterator it = targetMap.find(dataTarget);

      switch (it->second) {
        case POINTS:
          appendPoints(data);
          break;
        case POINT_DATA:
          grid->GetPointData()->AddArray(data);
      }
    }

  };
} // namespace vtkConv
