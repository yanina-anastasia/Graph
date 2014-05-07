#pragma once
#include "Graph.h"

/*частичная спецификация шаблона функции*/
template<>
struct std::numeric_limits<ComplexNumber> {
	static ComplexNumber min() {
		return ComplexNumber(std::numeric_limits<double>::min(), std::numeric_limits<double>::min());
	}
};

template<>
struct std::numeric_limits<std::string> {
	static std::string min() {
		return "";
	}
};

/*проверка корректности входных данных*/
template<class T>
void Graph<T>::checkValidity(int firstNode, int lastNode) {
	bool edgeNotFound = adjacencyList.count(firstNode) <= 0 || adjacencyList.count(lastNode) <= 0;
	bool nodesMoreThanSize = firstNode > size || lastNode > size;
	bool nodesLessThanZero = firstNode < 0 || lastNode < 0;
	if (nodesLessThanZero || nodesMoreThanSize || edgeNotFound) {
		throw std::invalid_argument("Invalid argument(s)/Недопустимый(е) параметр(ы)");
	}	
}

/*добавить ребро в граф*/
template <class T>
void Graph<T>::addEdge(int firstNode, int lastNode, const T & _value) {
	if ((firstNode < 0) || (lastNode < 0)) {
		throw std::invalid_argument("Invalid argument(s)/Недопустимый(е) параметр(ы)");
	}

	//если добавляемое ребро больше текущего максимального размера графа - увеличить размер графа
	if (firstNode >= size) {
		size = firstNode + 1;
	}
	if (lastNode >= size) {
		size = lastNode + 1;
	}
		
	AdjListElement<T> edge (lastNode, _value);

	auto & firstAdjListFound = adjacencyList.find(firstNode);
	auto & lastAdjListFound = adjacencyList.find(lastNode);

	if (firstAdjListFound != adjacencyList.end()) {
		firstAdjListFound->second.push_back(edge);  //если список смежности вершины уже есть в графе - изменить его
	} else {
		std::vector<AdjListElement<T>> newAdjList; 
		newAdjList.push_back(edge);
		adjacencyList.emplace(std::make_pair(firstNode, newAdjList)); //если его нет - добавить
	}

	/*добавление обратного ребра (граф неориентирован)*/
	if (firstNode != lastNode) {  //проверка, не является ли добавляемое ребро петлей
		AdjListElement<T> reversedEdge (firstNode, _value);
		if (lastAdjListFound != adjacencyList.end()) {
			lastAdjListFound->second.push_back(reversedEdge);
		} else {
			std::vector<AdjListElement<T>> newReversedAdjList;
			newReversedAdjList.push_back(reversedEdge);
			adjacencyList.emplace(std::make_pair(lastNode, newReversedAdjList));
		}
	}
}

/*изменить текущее значение на ребре*/
template <class T>
void Graph<T>::editEdge(int firstNode, int lastNode, const T & _value) {

	checkValidity(firstNode, lastNode);

	bool edgeExistance = false;

	auto & adjList = adjacencyList.find(firstNode)->second;
	for(auto & edge: adjList) {
		/*если ребро найдено - изменить значение на нем на требуемое*/
		if (edge.getVertex() == lastNode) {
			edge.setValue(_value);
			edgeExistance = true;
			break;
		}
	}

	if (firstNode != lastNode) {
		auto & reversedAdjList = adjacencyList.find(lastNode)->second;
		for(auto & edge: reversedAdjList) {
			/*если обратное ребро найдено - изменить значение на нем на требуемое*/
			if (edge.getVertex() == firstNode) {
				edge.setValue(_value);
				edgeExistance = true;
				break;
			}
		}
	}

	/*если ребро так и не было найдено - выбросить исключение*/
	if (!edgeExistance) {
		std::cout<< "This edge was not found" << std::endl;
		throw std::invalid_argument("The edge was not found/Ребро не найдено");
	}
}

/*удалить ребро из графа*/
template <class T>
void Graph<T>::deleteEdge (int firstNode, int lastNode) {
	
	checkValidity(firstNode, lastNode);

	if (adjacencyList.count(firstNode) <= 0) {
		throw std::invalid_argument("Adjacency list was not found/Список смежности не найден");
	}

	std::vector<AdjListElement<T>> toDelete = adjacencyList.find(firstNode)->second;
	int eraser = 0;

	for (size_t i = 0; i < toDelete.size(); ++i) {
		if (toDelete[i].getVertex() == lastNode) {
			eraser = i;  //позиция ребра, которое нужно удалить, в списке смежности
			break;
		}
	}

	auto & firstAdjListFound = adjacencyList.find(firstNode)->second;  //список смежности начальной вершины
	auto & lastAdjListFound = adjacencyList.find(lastNode)->second;  //список смежности конечной вершины

	firstAdjListFound.erase(firstAdjListFound.begin() + eraser);  //удаление ребра
	toDelete = lastAdjListFound;
	eraser = 0;

	for (size_t i = 0; i < toDelete.size(); ++i) {
		if (toDelete[i].getVertex() == firstNode) {
			eraser = i;
			break;
		}
	}

	if (lastNode != firstNode) {  //если это не петля
		lastAdjListFound.erase(lastAdjListFound.begin() + eraser);  //удаление обратного ребра
	}

	/*если список смежности вершины оказался пустым, удалить его из adjacencyList*/
	if (adjacencyList[firstNode].empty()) {
		adjacencyList.erase(firstNode);
	}
	if (adjacencyList[lastNode].empty()) {
		adjacencyList.erase(lastNode);
	}
}

/*вывод структуры графа на печать*/
template <class T>
void Graph<T>::print() const {
	for (auto & mapIter: adjacencyList) {
		out << mapIter.first << ": ";
		for (auto & edge: mapIter.second) {
			out << "(" << edge.getVertex() << ", " << edge.getValue() << "); ";
		}
		out << std::endl;
	}
}

/*проверка корректности входных данных для алгоритмов поиска оптимального пути*/
template<class T> 
void Graph<T>::checkFindSetValidity (const std::vector<int> & findSet) {
	for (size_t i = 0; i < findSet.size(); ++i) {
		bool vertexWasNotFound = adjacencyList.find(findSet[i]) == adjacencyList.end();
		if (findSet[i] > size - 1 || findSet[i] < 0 || vertexWasNotFound) {
			throw std::invalid_argument("Invalid argument(s)/Недопустимый(е) параметр(ы)");
		}
	}
}

/*поиск оптимального пути от одной группы вершин до другой*/
template <class T>
bool Graph<T>::findPath (const std::vector<int> &from, const std::vector<int> &to) {

	/*проверка корректности входных данных*/
	checkFindSetValidity(from);
	checkFindSetValidity(to);

	/*проверка наличия в графе циклов с отрицательным весом*/
	bool hasNegativeEdges = false;
	for (auto & mapIter: adjacencyList) {
		for (auto & edge: mapIter.second) {
			if (edge.getValue() < T()) {
				hasNegativeEdges = true;
				break;
			}
		}
	}

	bool hasPath;
	T minLength;
	std::vector<int> path;

	if (!hasNegativeEdges) {
		hasPath = Dijkstra(from, to, path, minLength);	//алгоритм Дейкстры
	} else {
		hasPath = FordBellman(from, to, path, minLength); //алгоритм Форда-Беллмана	
	}

	/*вывод результатов поиска оптимального пути в графе на печать*/
	if (hasPath) {
		out << "Length of the best route/Длина наикратчайшего пути: " << minLength << std::endl;
		out << "Route/Маршрут: ";
		for (size_t i = 0; i < path.size(); ++i) {
			out << path[i] << " ";
		}
	} else {
		out << "The path was not found/Путь не найден" << std::endl;
		return false;
	}

	return true;
}

template <class T>
bool Graph<T>::Dijkstra(const std::vector<int> & from, const std::vector<int> & to, std::vector<int> & path, T & pathLength) {

	/*проверка корректности входных данных*/
	checkFindSetValidity(from);
	checkFindSetValidity(to);

	int start = size;
	edgeAdjunct edgeProc(from, *this); //дополняет граф ребрами с нулевыми значениями до новой стартовой вершины

	std::vector<valueContainer> distances;  //вектор расстояний от старта до каждой вершины в графе
	distances.resize(size);
	std::vector<int> parents; 
	parents.resize(size);
	distances[start] = T();
	std::vector<char> used(size);

	/*реализация алгоритма Дейкстры*/
	for (int index = 0; index < size; ++index) {
		int vertex = -1;
		for (int j = 0; j < size; ++j) 
		{
			if (used[j]) {
				continue;
			}

			if (vertex == -1 || distances[j] < distances[vertex]) {
				vertex = j;
			}
		}
		if (distances[vertex].isInfinity) {
			break;
		}
		used[vertex] = true;
 
		auto it = adjacencyList.find(vertex);

		if (it != adjacencyList.end()) {
			for (auto & edge : it->second) {
				int to = edge.getVertex();
				const T & len = edge.getValue();

				if (distances[vertex] + len < distances[to]) {
					distances[to] = distances[vertex] + len;
					parents[to] = vertex;
				}
			}
		}
	}

	/*поиск минимального пути из множества путей до конечной группы вершин*/
	valueContainer minLength;
	int minPath = 0;
	for (size_t index = 0; index < to.size(); ++index) {
		if (distances[to[index]] < minLength) {
			minLength = distances[to[index]];
			minPath = to[index];
		}
	}

	if (minLength.isInfinity) {
		return false;
	}
	
	/*построение пути*/
	for (int vertex = minPath; vertex != start; vertex = parents[vertex]) {
		path.push_back (vertex);
	}
	std::reverse (path.begin(), path.end());

	pathLength = minLength.value; 

	return true;
}

template <class T>
bool Graph<T>::FordBellman(const std::vector<int> & from, const std::vector<int> & to, std::vector<int> & path, T & pathLength) {
	
	/*проверка корректности входных данных*/
	checkFindSetValidity(from);
	checkFindSetValidity(to);
	
	int start = size;

	/*дополняет граф ребрами с нулевыми значениями до новой стартовой вершины*/
	edgeAdjunct edgeProc(from, *this);

	/*реализация алгоритма Форда-Беллмана(с обработкой циклов с отрицательным весом)*/
	std::vector<valueContainer> distance;
	distance.resize(size);
	std::vector<int> parents;
	parents.resize(size);
	distance[start] = T();
	std::vector<char> used(size);
	int negativeCycleVertex;
	for (int index = 0; index < size; ++index) {
	negativeCycleVertex = -1;
		for (auto & adjList: adjacencyList) {
			for (auto & edge: adjList.second) {
				int from = adjList.first;
				int to = edge.getVertex();
				const T & value = edge.getValue();
				if (distance[from].isInfinity) {
					continue;
				}
				
				if (distance[from] + value < distance[to]) {
					distance[to] = std::max(std::numeric_limits<T>::min(), distance[from].value + value);
					parents[to] = from;
					negativeCycleVertex = to;
				}
			}
		}
	}

	/*поиск минимального пути из множества путей до конечной группы вершин*/
	valueContainer minLength;
	int minPath = 0;
	for (size_t index = 0; index < to.size(); ++index) {
		if (distance[to[index]] < minLength) {
			minLength = distance[to[index]];
			minPath = to[index];
		}
	}

	if (negativeCycleVertex == -1) {  //проверка - найден цикл с отрицательным весом или нет
		if (minLength.isInfinity) {
			return false;
		}
		for (int vertex = minPath; vertex != start; vertex = parents[vertex]) {
			path.push_back (vertex);
		}
		std::reverse (path.begin(), path.end());

		pathLength = minLength.value;

		return true;

	} else {
			int y = negativeCycleVertex;
			for (int index = 0; index < size; ++index) {
				y = parents[y];
			}
 
			/*находит цикл с отрицательным весом*/
			for (int cur = y; ; cur = parents[cur]) {
				path.push_back (cur);
				if (cur == y && path.size() > 1) {
					break;
				}
			}
			std::reverse (path.begin(), path.end());
 
			/*вывод результатов на печать*/
			std::cout << "There is negative cycle/Найден цикл с отрицательным весом: ";
			for (size_t index = 0; index < path.size(); ++index) {
				std::cout << path[index] << ' ';
			}
			std::cout << std::endl;

			return false;

	}

}
