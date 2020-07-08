#pragma once

#include <exception>

using namespace std;
namespace vtkConv
{
  class HeaderException : public runtime_error
  {
  private:
    /* data */
  public:
    HeaderException(const string& msg) : runtime_error(msg) {};
    HeaderException(const char *msg) : runtime_error(msg) {};
  };  
} // namespace vtkConv
