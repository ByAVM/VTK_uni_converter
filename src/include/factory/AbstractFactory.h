#pragma once
#include <map>

using namespace std;

namespace vtkConv
{
  // Интерфейс Creator'а, 
  template <class Base>
  class AbstractCreator {
    public:
      AbstractCreator() {}
      virtual ~AbstractCreator(){}
      virtual unique_ptr<Base> create() const = 0;
  };

  // Прокси-класс для фабрики
  // C - класс-наследник
  // Base - класс-интерфейс
  template <class C, class Base>
  class Creator : public AbstractCreator<Base> {
    public:
      Creator() {}
      virtual ~Creator() {}
      unique_ptr<Base> create() const {
        return make_unique<C>();
      }
  };
// Reader == Base
// IdType == string
// AbstractFactory<Reader, string>
// add<BaseReader>("BaseReader")

  template <class Base, class IdType>
  class AbstractFactory {
    protected:
      // Буду создавать объекты Base класса (Тип фабрики)
      typedef AbstractCreator<Base> CreatorType;
      // В мапе под ключом IdType будут лежать указатели
      typedef map<IdType, unique_ptr<CreatorType>> FactoryMap;
      FactoryMap _map;

      void registerClass(const IdType& id, unique_ptr<CreatorType> p) {
        typename FactoryMap::iterator it = _map.find(id);
        if (it == _map.end()) {
          _map[id] = move(p);
        }
      }
    public:
      AbstractFactory() {}
      virtual ~AbstractFactory() {};

      template <class C>
      void add(const IdType& id) {
        registerClass(id, make_unique<Creator<C, Base>>());
      }

      unique_ptr<Base> create(const IdType& id) const {
        typename FactoryMap::const_iterator it = _map.find(id);
        if (it != _map.end()) {
          return it->second->create();
        }
		    throw new runtime_error("Create failed");
      }

      bool hasKey(const IdType & key) {
        typename FactoryMap::const_iterator id = _map.find(key);
        return id != _map.end();
      }
  };
} // namespace vtkConv
