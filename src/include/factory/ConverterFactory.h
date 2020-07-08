#pragma once
#include "../converter/IConverter.h"
#include "AbstractFactory.h"

namespace vtkConv
{
  class ConverterFactory : public AbstractFactory<IConverter, string> {};
} // namespace vtkConv
