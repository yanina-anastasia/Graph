#pragma once
#include "ComplexNumber.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <memory>
#include <map>
#include <vector>

/*элемент списка смежности в формате: (<конечная вершина ребра>,<значение на ребре>)*/
template <class T>
class AdjListElement {
private:
	int vertex; 
	std::shared_ptr<T> value; 
public:
	AdjListElement() :
		vertex(-1),
		value(nullptr) {}
	
	AdjListElement(int _vertex, const T & _value) :
		vertex(_vertex),
		value(std::make_shared<T>(_value)) {}

	bool operator ==(const AdjListElement<T> &element) const {
		return ((vertex == element.vertex) && (*value == *element.value));
	}

	int getVertex() const {
		return vertex;
	}

	void setVertex(int _vertex) {
		vertex = _vertex;
	}

	T & getValue() const {
		return *value;
	}

	void setValue (const T & _value) {
		value = std::make_shared<T>(_value);
	}
};


template <class T>
class Graph {
private:
	std::map<int, std::vector<AdjListElement<T>>> adjacencyList;  //список смежности
	int size;  //размер графа
	std::ostream & out;   //поток вывода(можно выводить в консоль или записывать в файл)

	/*структура для работы алгоритмов поиска оптимального пути в графе*/
	struct valueContainer { 
		T value;
		bool isInfinity;

		valueContainer() {
			isInfinity = true;
		}

		valueContainer (const T & _value) {
			value = _value;
			isInfinity = false;
		}

		valueContainer& operator=(const T & _value) {
			value = _value;
			isInfinity = false;
			return *this;
		}

		bool operator == (const valueContainer & other) const {
			if (other.isInfinity || this->isInfinity) {
				return false;
			}

			return (other.value == this->value);
		}

		bool operator < (const valueContainer & other) const {
			if (this->isInfinity ) {
				return false;
			}
			if (other.isInfinity) {
				return true;
			}
			return (this->value < other.value);
		}

		valueContainer operator+ (const valueContainer & other) const {
			if (isInfinity || other.isInfinity) {
				return valueContainer();
			}
			return valueContainer(value + other.value);
		}

	};
	
	/*построение ребер с нулевыми весами от новой стартовой вершины до всех вершин, из которых нужно производить поиск*/
	struct edgeAdjunct {  
		const std::vector<int> & edges;
		Graph<T> & graph;

		edgeAdjunct(const std::vector<int> & _edges, Graph<T> & _graph):
			edges(_edges),
			graph(_graph) {
			int start = graph.showSize();
			graph.changeSize(graph.showSize() + 1);
			for (size_t index = 0; index < edges.size(); ++index) {
				graph.addEdge(edges[index], start, T());
			}
		}

		~edgeAdjunct() {
			int start = graph.showSize() - 1;
			for (size_t index = 0; index < edges.size(); ++index) {
				graph.deleteEdge(edges[index], start);
			}
			graph.changeSize(graph.showSize() - 1);
		}
	};

public:
	Graph() :
		size(0) {
		std::locale cp_1251("Russian_Russia.1251");  //поддержка русского языка
		std::locale::global(cp_1251);
		std::cout.imbue(cp_1251);
		std::ios::sync_with_stdio(false);
		out = std::cout;
	}

	Graph (int _size, std::ostream & _out) :
		size(_size),
		out(_out) {
		std::locale cp_1251("Russian_Russia.1251");  //поддержка русского языка
		std::locale::global(cp_1251);
		out.imbue(cp_1251);
		std::ios::sync_with_stdio(false);
	}

	/*проверяет допустимость параметров ф-й, выбрасывает исключение в случае некорректных данных*/
	void checkValidity(int firstNode, int lastNode);

	/*добавить ребро*/
	void addEdge(int firstNode, int lastNode, const T & _value);

	/*изменить значение на ребре*/
	void editEdge(int firstNode, int lastNode, const T & _value);  

	/*удалить ребро*/
	void deleteEdge (int firstNode, int lastNode);  

	/*возвращает перечень всех вершин, содержащихся в графе*/
	std::vector<int> showVertex() { 
		std::vector<int> result;
		for (auto & adjList: adjacencyList) {
			result.push_back(adjList.first);
		}
		return result;
	}

	/*возвращает список смежности для конкретной вершины*/
	std::vector<AdjListElement<T>> showAdjList(int vertex) {
		std::vector<AdjListElement<T>> result;
		if (adjacencyList.count(vertex) > 0) {
			result = adjacencyList.find(vertex)->second;
		}
		return result;
	}
	
	/*возвращает размер графа*/
	int showSize() const {
		return size;
	}

	/*позволяет изменить размер графа*/
	void changeSize(int _size) {
		for (auto & adjList: adjacencyList) {
			if (adjList.first > _size) {
				throw std::invalid_argument("Unable to change size/Невозможно изменить размер графа");
			}
		}
		size = _size;
	}

	/*печатает граф в формате <вершина>: <ее список смежности>*/
	void print() const;

	/*проверяет корректность входных данных для алгоритмов поиска оптимального пути в графе*/
	void checkFindSetValidity (const std::vector<int> & findSet);

	/*поиск оптимального пути в графе*/
	bool findPath (const std::vector<int> & from, const std::vector<int> & to); 

	bool Dijkstra(const std::vector<int> & from, const std::vector<int> & to, std::vector<int> & path, T & pathLength);

	bool FordBellman(const std::vector<int> & from, const std::vector<int> & to, std::vector<int> & path, T & pathLength);
};
