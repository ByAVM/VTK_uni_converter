# Custom user-defined converter

Предназначен для конвертации бинарных файлов с нестандартной структурой.

**Тип для конфиграции:** custom

### Дополнительные параметры

**grid** - *Строка.* Тип решетки для выходных файлов.

## Header

**header** - *Массив.* Список, в порядке следования, единичных элементов, образующих заголовок файла.

### Формат описания

**type** - *Строка.* Базовый тип данных C++ (int, float, double).

**ref** - *Строка.* Название (ссылка), по которой элемент данных может получить значение.

## Data

**data** - *Массив.* Список, в порядке следования, массивов, описывающий формат хранимых в файле данных.

### Формат описания

**type** - *Строка.* Базовый тип данных C++ (int, float, double).

**tuples** - *Число или Строка.* Количество элементов в массиве. Может быть числом, или ссылкой на элемент из **header**

**components** - *Число или Строка.* Количество компонентов в одном элементе массива. Может быть числом, или ссылкой на элемент из **header**

**target** - *Строка.* Назначение элемента. Возможный вариант зависит от используемой решетки.

## Пример конфигурации

    "input": "C:/Temporary/VTK/binData",
    "output": "C:/Temporary/VTK/vtuData",
    "grid": "unstructured_grid",
    "converter": "custom",
    "header": [
      {
        "type": "double",
        "ref": "N"
      }
    ],
    "data": [
      {
        "type": "double",
        "tuples": "N",
        "components": 1,
        "target": "point_x"
      },
      {
        "type": "double",
        "tuples": "N",
        "components": 1,
        "target": "point_y"
      },
      {
        "type": "double",
        "tuples": "N",
        "components": 1,
        "target": "point_z"
      }
    ]