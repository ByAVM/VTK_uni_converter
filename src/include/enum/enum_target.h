#pragma once
#include <string>

namespace vtkConv
{
  enum EnumTarget {POINTS, VECTORS, POINT_DATA, CELL_DATA, NOTHING};
  std::string _strEnumTarget[] {"points", "vectors", "point_data", "cell_data"};
  EnumTarget s2target(std::string& t) {
    if (t == _strEnumTarget[POINTS]) {
      return POINTS;
    } else if (t == _strEnumTarget[VECTORS]) {
      return VECTORS;
    } else if (t == _strEnumTarget[POINT_DATA]) {
      return POINT_DATA;
    }

    return NOTHING;
  }
} // namespace vtkConv
