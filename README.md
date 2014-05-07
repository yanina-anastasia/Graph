Граф
=====

Данное консольное приложение позволяет искать кратчайший путь между двумя группами вершин в графе.
Реализован шаблонный класс неориентированного взвешенного графа, есть возможность добавлять/удалять ребра, редактировать значения на ребрах, изменять размер графа. Есть возможность выводить результат в консоль или записывать в файл. Есть поддержка русского языка при вводе начальных данных/выводе результата.
Кратчайший путь между двумя группами вершин ищется алгоритмом Форда-Беллмана или алгоритмом Дейкстры в зависимости от наличия/отсутствия в графе циклов с отрицательным весом.
В качестве примера реализован класс комплексных чисел и протестирована корректность работы алгоритмов на комплексных числах. Кроме того, протестирована правильность работы алгоритмов со строками, целыми и вещественными числами, на произвольно сгенерированном наборе данных.

Файлы:
Graph.h  - основные классы: Graph, AdjListElement, а также структуры: valueContainer и edgeAdjunct.
Graph.hpp – реализация основных методов работы с графом(добавить/удалить ребро, редактировать значение на ребре и т.д.) и алгоритмов поиска оптимального пути
ComplexNumber.h, ComplexNumber.cpp – реализация класса комплексных чисел (класс использовался для тестирования функциональности графа)
Tests.cpp – тестирование функциональности (Boost Unit Testing Framework)
Используются возможности С++11

