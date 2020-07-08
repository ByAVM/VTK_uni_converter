#pragma once
#include <map>
#include <vtkPoints.h>
#include <vtkUnstructuredGrid.h>
#include <vtkXMLUnstructuredGridWriter.h>
#include <vtkPointData.h>
#include <vtkCellArray.h>
#include <vtkVertex.h>

#include "AdapterBase.h"

using namespace std;
namespace vtkConv
{
  class UnstructuredGridAdapter : public AdapterBase<vtkUnstructuredGrid, vtkXMLUnstructuredGridWriter> {
    protected:
      enum Target {POINTS, DIMENSIONS, VECTORS, POINT_DATA};
      map<string, Target> targetMap {
        {"points", POINTS},
        {"dimensions", DIMENSIONS},
        {"vectors", VECTORS},
        {"point_data", POINT_DATA}
      };

      typedef vtkSmartPointer<vtkPoints> SmartPoints;
      typedef vtkSmartPointer<vtkUnstructuredGrid> SmartGrid;
      typedef vtkSmartPointer<vtkXMLUnstructuredGridWriter> SmartWriter;
      
      const string extName = ".vtu";

      // Специфичные методы для решетки

    public:
    UnstructuredGridAdapter() : AdapterBase() {}

    string getExtname() { return extName; }

    void appendPoints(SmartArray data) {
      SmartPoints points = SmartPoints::New();
      points->SetData(data.GetPointer());
      grid->SetPoints(points);

      vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();
      cells->Allocate(data->GetNumberOfTuples());

      for (vtkIdType i = 0; i < grid->GetNumberOfPoints(); i++) {
        vtkNew<vtkVertex> vertex;
        vertex->GetPointIds()->SetId(0, i);
        cells->InsertNextCell(vertex.GetPointer());
      }

      grid->SetCells(VTK_VERTEX, cells.GetPointer());
    }

    void appendVectors(SmartArray data) {
      grid->GetPointData()->SetVectors(data.GetPointer());
    }

    void appendData(const string& dataTarget, double data[]) {
      // map<string, Target>::iterator it = targetMap.find(dataTarget);

      // switch (it->second) {
        
      // }
    }

    void appendData(const string& dataTarget, SmartArray data) {
        map<string, Target>::iterator it = targetMap.find(dataTarget);

        switch (it->second) {
          case POINTS:
            appendPoints(data);
            break;
          case VECTORS:
            appendVectors(data);
            break;
          case POINT_DATA:
            grid->GetPointData()->AddArray(data.GetPointer());
        }
      }
  };
} // namespace vtkConv
