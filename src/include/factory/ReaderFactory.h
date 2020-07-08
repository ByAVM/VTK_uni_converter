#pragma once
#include "../reader/IReader.h"
#include "AbstractFactory.h"

namespace vtkConv
{
  // Специализация абстрактной фабрики для ридера
  class ReaderFactory : public AbstractFactory<IReader, string> {};
} // namespace vtkConv
