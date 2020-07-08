#pragma once
#include <vtkXMLWriter.h>
#include "IAdapter.h"

namespace vtkConv
{
  template<class Grid, class Writer>
  class AdapterBase : public IAdapter {
    protected:
    typedef vtkSmartPointer<Writer> SmartWriter;
    typedef vtkSmartPointer<Grid> SmartGrid;

    SmartGrid grid;
    SmartWriter writer;

    public:
    AdapterBase() {
      grid = SmartGrid::New();
      writer = SmartWriter::New();
    }

    int writeFile(const string& outputFileName) {
      cout << "Writing: " << outputFileName + this->getExtname() << endl;

      writer->SetFileName((outputFileName + this->getExtname()).c_str());

      #if VTK_MAJOR_VERSION <= 5
        writer->SetInput(grid);
      #else
        writer->SetInputData(this->grid.GetPointer());
      #endif
      int res = writer->Write();

      // Освобождение после записи потому что умный указатель не освобождает сетку
      // this->reset();

      return res;
    }

    void reset() {
      grid->ReleaseData();
    }

  };
} // namespace vtkConv
