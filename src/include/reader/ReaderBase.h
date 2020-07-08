#pragma once
#include "IReader.h"

using namespace std;

namespace vtkConv
{
  class ReaderBase : public IReader {
    protected:
    vector<double> data_vector;
    EnumType type;
    string target;
    string reference;
    int tuples = 0;
    int components = 0;
    string title = "";

    public:
    vector<double>& getVector() { return data_vector; }
    EnumType getType() { return type; }
    const string& getTarget() { return target; }
    int getTuplesCount() { return tuples; }
    int getComponentsCount() { return components; }
    const string& getRefLink() { return reference; }
    const string& getTitle() { return title; }

    void setTitle(const string& t) {
      title = t;
    }

    void reset() { data_vector.clear(); }
    
    void setType(const string& t) {
      type = s2type(t);
    }

    void setTarget(const string& t) {
      target = t;
    }

    void setTuplesCount(int t) {
      tuples = t;
    }

    void setComponentsCount(int c) {
      components = c;
    }

    double getValue(int index = 0) {
      return data_vector[index];
    }

    void setRefLink(const string& r) {
      reference = r;
    }

    virtual void read(ifstream&) = 0;

    // Статическая функция чтения 1 символа
    template <typename T>
    static double _readNumber(ifstream& stream) {
      int size = sizeof(T);
      char* buffer = new char[size];
      
      stream.read(buffer, size);
      T val = *reinterpret_cast<T*>(buffer);

      delete[] buffer;
      return val;
    }

  };
} // namespace vtkConv
