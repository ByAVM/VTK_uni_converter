#pragma once
#include "../adapter/IAdapter.h"
#include "AbstractFactory.h"

namespace vtkConv
{
  class AdapterFactory : public AbstractFactory<IAdapter, string> {};
} // namespace vtkConv
