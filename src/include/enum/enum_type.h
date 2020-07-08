#pragma once
#include <string>

namespace vtkConv
{
  enum EnumType {INTEGER, FLOAT, DOUBLE, NONE};

  EnumType s2type(const std::string& tpName) {
    if (tpName == "int") {
      return INTEGER;
    } else if (tpName == "float")
    {
      return FLOAT;
    } else if (tpName == "double")
    {
      return DOUBLE;
    }

    return NONE;
  }
} // namespace vtkConv
