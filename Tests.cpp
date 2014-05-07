#include "Graph.hpp"
#include <boost\chrono\chrono.hpp>
#include <chrono>

#define BOOST_TEST_MODULE GraphTesting

#include <boost\test\unit_test.hpp>
#include <boost\test\auto_unit_test.hpp>

//проверка корректности алгоритма на целых числах
BOOST_AUTO_TEST_CASE(test1) {
	std::cout << "TEST1..." << std::endl;
	Graph<int> testGraph(10, std::cout);
	testGraph.addEdge(1, 2, 100);
	testGraph.addEdge(2, 3, 100);
	testGraph.addEdge(1, 3, 1000);
	testGraph.addEdge(1, 4, 5000);
	testGraph.addEdge(1, 1, 10000);
	testGraph.addEdge(1, 5, 5700);
	testGraph.addEdge(2, 9, 5300);
	testGraph.addEdge(3, 5, 5000);
	testGraph.addEdge(4, 7, 5800);
	testGraph.addEdge(5, 8, 11000);
	testGraph.addEdge(9, 10, 16000);
	testGraph.addEdge(3, 10, 3300);
	std::vector<int> from;
	std::vector<int> to;
	from.push_back(1);
	from.push_back(2);
	to.push_back(9);
	to.push_back(10);
	BOOST_REQUIRE(testGraph.findPath(from, to));
	std::cout << std::endl;
}

//проверка корректности алгоритма на дробных числах
BOOST_AUTO_TEST_CASE(test2) {
	std::cout << "TEST2..." << std::endl;
	Graph<double> testGraph(10, std::cout);
	testGraph.addEdge(1, 2, 100.23);
	testGraph.addEdge(2, 3, 100.45);
	testGraph.addEdge(1, 3, 1000.5);
	testGraph.addEdge(1, 4, 5000.78);
	testGraph.addEdge(1, 1, 10000.5);
	testGraph.addEdge(1, 5, 5700.1);
	testGraph.addEdge(2, 9, 5300.3);
	testGraph.addEdge(3, 5, 5000.345);
	testGraph.addEdge(4, 7, 5800.654);
	testGraph.addEdge(5, 8, 11000.432);
	testGraph.addEdge(9, 10, 16000.342);
	testGraph.addEdge(3, 10, 3300.432);
	std::vector<int> from;
	std::vector<int> to;
	from.push_back(1);
	from.push_back(2);
	to.push_back(9);
	to.push_back(10);
	BOOST_REQUIRE(testGraph.findPath(from, to));
	std::cout << std::endl;
}

//проверка корректности алгоритма на комплексных числах
BOOST_AUTO_TEST_CASE(test3) {
	std::cout << "TEST3..." << std::endl;
	Graph<ComplexNumber> testGraph(10, std::cout);
	testGraph.addEdge(1, 2, ComplexNumber(100,23));
	testGraph.addEdge(2, 3, ComplexNumber(100,45));
	testGraph.addEdge(1, 3, ComplexNumber(1000,5));
	testGraph.addEdge(1, 4, ComplexNumber(5000,78));
	testGraph.addEdge(1, 1, ComplexNumber(10000,5));
	testGraph.addEdge(1, 5, ComplexNumber(5700,1));
	testGraph.addEdge(2, 9, ComplexNumber(5300,3));
	testGraph.addEdge(3, 5, ComplexNumber(5000,345));
	testGraph.addEdge(4, 7, ComplexNumber(5800,654));
	testGraph.addEdge(5, 8, ComplexNumber(11000,432));
	testGraph.addEdge(9, 10, ComplexNumber(16000,342));
	testGraph.addEdge(3, 10, ComplexNumber(3300,432));
	std::vector<int> from;
	std::vector<int> to;
	from.push_back(1);
	from.push_back(2);
	to.push_back(9);
	to.push_back(10);
	BOOST_REQUIRE(testGraph.findPath(from, to));
	std::cout << std::endl;
}

//проверка корректности работы алгоритма на строках
BOOST_AUTO_TEST_CASE(test4) {
	std::cout << "TEST4..." << std::endl;
	Graph<std::string> testGraph(10, std::cout);
	testGraph.addEdge(1, 2, "one_");
	testGraph.addEdge(2, 3, "two_");
	testGraph.addEdge(1, 3, "three_");
	testGraph.addEdge(1, 4, "four_");
	testGraph.addEdge(1, 1, "five_");
	testGraph.addEdge(1, 5, "six_");
	testGraph.addEdge(2, 9, "seven_");
	testGraph.addEdge(3, 5, "eight_");
	testGraph.addEdge(4, 7, "nine_");
	testGraph.addEdge(3, 10, "twelve_");
	std::vector<int> from;
	std::vector<int> to;
	from.push_back(1);
	from.push_back(2);
	to.push_back(9);
	to.push_back(10);
	BOOST_REQUIRE(testGraph.findPath(from, to));
	std::cout << std::endl;
}

//проверка корректности алгоритма на произвольном наборе данных
BOOST_AUTO_TEST_CASE(test5) {
	std::cout << "TEST5..." << std::endl;
	auto time = std::chrono::high_resolution_clock::now().max;
    srand((int)time);
	std::cout << std::endl;
	int first = 0;
	int second = 0;
	int value = 0;
	Graph<int> testGraph(1010, std::cout);
	for (int i = 0; i < 1000; ++i) {
		first = rand() % 1000 + 1;
		second = rand() % 1000 + 1;
		value = rand() % 100 + 1;
		testGraph.addEdge(first, second, value);
	}
	std::vector<int> from;
	std::vector<int> to;
	for (int i = 0; i < 10; ++i) {
		first = rand() % testGraph.showVertex().size() + 1;
		second = rand() % testGraph.showVertex().size() + 1;
		from.push_back(testGraph.showVertex()[first]);
		to.push_back(testGraph.showVertex()[second]);
	}
	BOOST_REQUIRE(testGraph.findPath(from, to));
	std::cout << std::endl;
}

//проверка возможности записи данных в файл
BOOST_AUTO_TEST_CASE(test6) {
	std::cout << "TEST6..." << std::endl;
	std::cout << "Writing in file.../Запись в файл..." << std::endl;
	std::ofstream out;
	out.open("d:\\test.txt");
	Graph<std::string> testGraph(10, out);
	testGraph.addEdge(1, 2, "one_");
	testGraph.addEdge(2, 3, "two_");
	testGraph.addEdge(1, 3, "three_");
	testGraph.addEdge(1, 4, "four_");
	testGraph.addEdge(1, 1, "five_");
	testGraph.addEdge(1, 5, "six_");
	testGraph.addEdge(2, 9, "seven_");
	testGraph.addEdge(3, 5, "eight_");
	testGraph.addEdge(4, 7, "nine_");
	testGraph.addEdge(5, 8, "ten_");
	testGraph.addEdge(9, 10, "eleven_");
	testGraph.addEdge(3, 10, "twelve_");
	std::vector<int> from;
	std::vector<int> to;
	from.push_back(1);
	from.push_back(2);
	to.push_back(9);
	to.push_back(10);
	BOOST_REQUIRE(testGraph.findPath(from, to));
	testGraph.print();
	out.close();
	std::cout << std::endl;
}

//проверка на невалидных данных
BOOST_AUTO_TEST_CASE(test7) {
	std::cout << "TEST7..." << std::endl;
	Graph<std::string> testGraph(10, std::cout);
	BOOST_CHECK_THROW(testGraph.addEdge(1, -2, "one"), std::invalid_argument);
	BOOST_CHECK_THROW(testGraph.addEdge(-1, 2, "one"), std::invalid_argument);
	testGraph.addEdge(1, 2, "one");
	BOOST_CHECK_THROW(testGraph.deleteEdge(1, 3), std::invalid_argument);
	BOOST_CHECK_THROW(testGraph.deleteEdge(-1, 3), std::invalid_argument);
	BOOST_CHECK_THROW(testGraph.deleteEdge(1, -3), std::invalid_argument);
	testGraph.addEdge(1, 15, "two");
	testGraph.addEdge(2, 5, "three");
	std::cout << std::endl;
}

//проверка поиска пути на невалидных данных (1)
BOOST_AUTO_TEST_CASE(test8) {
	std::cout << "TEST8..." << std::endl;
	Graph<std::string> testGraph(10, std::cout);
	testGraph.addEdge(1, 2, "one");
	testGraph.addEdge(1, 15, "two");
	testGraph.addEdge(2, 5, "three");
	std::vector<int> from;
	std::vector<int> to;
	from.push_back(1);
	from.push_back(4);
	to.push_back(15);
	to.push_back(2);
	BOOST_CHECK_THROW(testGraph.findPath(from, to), std::invalid_argument);	
	std::cout << std::endl;
}

//проверка поиска пути на невалидных данных (2)
BOOST_AUTO_TEST_CASE(test9) {
	std::cout << "TEST9..." << std::endl;
	Graph<std::string> testGraph(10, std::cout);
	testGraph.addEdge(1, 2, "one");
	testGraph.addEdge(1, 15, "two");
	testGraph.addEdge(2, 5, "three");
	std::vector<int> from;
	std::vector<int> to;
	from.push_back(1);
	from.push_back(2);
	to.push_back(15);
	to.push_back(10);
	BOOST_CHECK_THROW(testGraph.findPath(from, to), std::invalid_argument);	
	std::cout << std::endl;
}

//проверка поиска пути на невалидных данных (3)
BOOST_AUTO_TEST_CASE(test10) {
	std::cout << "TEST10..." << std::endl;
	Graph<std::string> testGraph(10, std::cout);
	testGraph.addEdge(1, 2, "one");
	testGraph.addEdge(1, 15, "two");
	testGraph.addEdge(2, 5, "three");
	std::vector<int> from;
	std::vector<int> to;
	from.push_back(-1);
	from.push_back(2);
	to.push_back(15);
	to.push_back(-10);
	BOOST_CHECK_THROW(testGraph.findPath(from, to), std::invalid_argument);	
	std::cout << std::endl;
}

//проверка поиска пути на невалидных данных (3)
BOOST_AUTO_TEST_CASE(test11) {
	std::cout << "TEST11..." << std::endl;
	Graph<std::string> testGraph(10, std::cout);
	testGraph.addEdge(1, 2, "one");
	testGraph.addEdge(1, 15, "two");
	testGraph.addEdge(2, 5, "three");
	std::vector<int> from;
	std::vector<int> to;
	from.push_back(1);
	from.push_back(2);
	to.push_back(16);
	BOOST_CHECK_THROW(testGraph.findPath(from, to), std::invalid_argument);	
	std::cout << std::endl;
}

//проверка правильности вставки/удаления ребер
BOOST_AUTO_TEST_CASE(test12) {
	std::cout << "TEST12..." << std::endl;
	Graph<std::string> testGraph(10, std::cout);
	testGraph.addEdge(1, 2, "one");
	testGraph.addEdge(1, 15, "two");
	testGraph.addEdge(2, 5, "three");
	testGraph.deleteEdge(2, 5);
	testGraph.addEdge(15, 2, "four");
	BOOST_CHECK_THROW(testGraph.deleteEdge(3, 2), std::invalid_argument);
	std::vector<int> requirement;
	requirement.push_back(1);
	requirement.push_back(2);
	requirement.push_back(15);
	BOOST_REQUIRE(testGraph.showVertex() == requirement);	
	std::cout << std::endl;
}

//проверка правильности вставки/удаления ребер-петель (1)
BOOST_AUTO_TEST_CASE(test13) {
	std::cout << "TEST13..." << std::endl;
	Graph<std::string> testGraph(10, std::cout);
	testGraph.addEdge(1, 2, "one");
	testGraph.addEdge(1, 15, "two");
	testGraph.addEdge(2, 2, "three");
	testGraph.deleteEdge(2, 2);
	testGraph.addEdge(2, 2, "four");
	testGraph.addEdge(3, 3, "five");
	std::vector<AdjListElement<std::string>> requirement;
	requirement.push_back(AdjListElement<std::string>(1, "one"));
	requirement.push_back(AdjListElement<std::string>(2, "four"));
	BOOST_REQUIRE(testGraph.showAdjList(2) == requirement);	
	std::cout << std::endl;
}

//проверка правильности вставки/удаления ребер-петель (2)
BOOST_AUTO_TEST_CASE(test14) {
	std::cout << "TEST14..." << std::endl;
	Graph<std::string> testGraph(10, std::cout);
	testGraph.addEdge(1, 2, "one");
	testGraph.addEdge(1, 15, "two");
	testGraph.addEdge(2, 2, "three");
	testGraph.addEdge(2, 2, "four");
	testGraph.addEdge(3, 3, "five");
	std::vector<AdjListElement<std::string>> requirement;
	requirement.push_back(AdjListElement<std::string>(1, "one"));
	requirement.push_back(AdjListElement<std::string>(2, "three"));
	requirement.push_back(AdjListElement<std::string>(2, "four"));
	BOOST_REQUIRE(testGraph.showAdjList(2) == requirement);
	std::cout << std::endl;
}

//проверка корректности работы алгоритма с кратными ребрами
BOOST_AUTO_TEST_CASE(test15) {
	std::cout << "TEST15..." << std::endl;
	std::cout << std::endl;
	Graph<int> testGraph(10, std::cout);
	testGraph.addEdge(4, 3, 2);
	testGraph.addEdge(3, 2, 1);
	testGraph.addEdge(3, 2, 10);
	testGraph.addEdge(3, 2, 100);
	testGraph.addEdge(3, 2, 11);
	testGraph.addEdge(3, 2, 87);
	testGraph.addEdge(2, 1, 4);
	std::vector<int> from;
	std::vector<int> to;
	from.push_back(4);
	to.push_back(1);
	BOOST_REQUIRE(testGraph.findPath(from, to));
	std::cout << std::endl;
}

//проверка корректности работы алгоритма Дейкстры
BOOST_AUTO_TEST_CASE(test16) {
	std::cout << "TEST16..." << std::endl;
	std::cout << std::endl;
	Graph<int> testGraph(10, std::cout);
	testGraph.addEdge(1, 2, 2);
	testGraph.addEdge(1, 3, 10);
	testGraph.addEdge(2, 4, 5);
	testGraph.addEdge(3, 4, 100);
	testGraph.addEdge(4, 5, 11);
	testGraph.addEdge(4, 6, 10);
	std::vector<int> from;
	std::vector<int> to;
	from.push_back(1);
	to.push_back(5);
	to.push_back(6);
	std::vector<int> pathReq;
	pathReq.push_back(1);
	pathReq.push_back(2);
	pathReq.push_back(4);
	pathReq.push_back(6);
	std::vector<int> path;
	int pathLength;
	BOOST_REQUIRE(testGraph.Dijkstra(from, to, path, pathLength));
	BOOST_REQUIRE(path == pathReq);
	BOOST_REQUIRE(pathLength == 17);	
	std::cout << std::endl;
}

//проверка корректности работы алгоритма Форда-Беллмана
BOOST_AUTO_TEST_CASE(test17) {
	std::cout << "TEST17..." << std::endl;
	std::cout << std::endl;
	Graph<int> testGraph(10, std::cout);
	testGraph.addEdge(1, 2, 2);
	testGraph.addEdge(1, 3, 10);
	testGraph.addEdge(2, 4, 5);
	testGraph.addEdge(3, 4, 100);
	testGraph.addEdge(4, 5, 11);
	testGraph.addEdge(4, 6, 10);
	std::vector<int> from;
	std::vector<int> to;
	from.push_back(1);
	to.push_back(5);
	to.push_back(6);
	std::vector<int> pathReq;
	pathReq.push_back(1);
	pathReq.push_back(2);
	pathReq.push_back(4);
	pathReq.push_back(6);
	std::vector<int> path;
	int pathLength;
	BOOST_REQUIRE(testGraph.FordBellman(from, to, path, pathLength));
	BOOST_REQUIRE(path == pathReq);
	BOOST_REQUIRE(pathLength == 17);
	std::cout << std::endl;
}

//проверка правильности нахождения цикла с отрицательным весом
BOOST_AUTO_TEST_CASE(test18) {
	std::cout << "TEST18..." << std::endl;
	std::cout << std::endl;
	Graph<int> testGraph(10, std::cout);
	testGraph.addEdge(1, 2, 2);
	testGraph.addEdge(1, 3, 10);
	testGraph.addEdge(2, 4, 5);
	testGraph.addEdge(3, 4, -100);
	testGraph.addEdge(4, 5, 11);
	testGraph.addEdge(4, 6, 10);
	std::vector<int> from;
	std::vector<int> to;
	from.push_back(1);
	to.push_back(5);
	to.push_back(6);
	std::vector<int> pathReq;
	pathReq.push_back(4);
	pathReq.push_back(3);
	pathReq.push_back(4);
	std::vector<int> path;
	int pathLength;
	BOOST_REQUIRE(!testGraph.FordBellman(from, to, path, pathLength));
	BOOST_REQUIRE(path == pathReq);
	std::cout << std::endl;
}

//проверка корректности вывода при наличии цикла с отрицательным весом (1)
BOOST_AUTO_TEST_CASE(test19) {
	std::cout << "TEST19..." << std::endl;
	std::cout << std::endl;
	Graph<int> testGraph(10, std::cout);
	testGraph.addEdge(1, 4, -5);
	testGraph.addEdge(1, 3, 10);
	testGraph.addEdge(1, 9, 5);
	testGraph.addEdge(3, 4, -100);
	testGraph.addEdge(4, 7, -120);
	testGraph.addEdge(4, 5, 10);
	std::vector<int> from;
	std::vector<int> to;
	from.push_back(1);
	to.push_back(5);
	to.push_back(7);
	BOOST_REQUIRE(!testGraph.findPath(from, to));
	std::cout << std::endl;
}


//проверка правильности нахождения цикла с отрицательным весом (2)
BOOST_AUTO_TEST_CASE(test20) {
	std::cout << "TEST20..." << std::endl;
	Graph<int> testGraph(10, std::cout);
	testGraph.addEdge(1, 2, 2);
	testGraph.addEdge(1, 3, 10);
	testGraph.addEdge(2, 4, 5);
	testGraph.addEdge(3, 4, -100);
	testGraph.addEdge(4, 5, 11);
	testGraph.addEdge(4, 6, 10);
	std::vector<int> from;
	std::vector<int> to;
	from.push_back(1);
	to.push_back(5);
	to.push_back(6);
	std::vector<int> pathReq;
	pathReq.push_back(4);
	pathReq.push_back(3);
	pathReq.push_back(4);
	std::vector<int> path;
	int pathLength;
	BOOST_REQUIRE(!testGraph.FordBellman(from, to, path, pathLength));
	BOOST_REQUIRE(path == pathReq);
	std::cout << std::endl;
}

//проверка правильности изменения значения на ребрах
BOOST_AUTO_TEST_CASE(test21) {
	std::cout << "TEST21..." << std::endl;
	Graph<int> testGraph(10, std::cout);
	testGraph.addEdge(1, 2, 2);
	testGraph.editEdge(1, 2, 10);
	testGraph.addEdge(1, 3, 10);
	testGraph.editEdge(1, 3, 5);
	std::vector<AdjListElement<int>> requirement;
	requirement.push_back(AdjListElement<int>(2, 10));
	requirement.push_back(AdjListElement<int>(3, 5));
	BOOST_REQUIRE(testGraph.showAdjList(1) == requirement);
	std::cout << std::endl;
}

//проверка изменения значений на ребрах на невалидных данных (1)
BOOST_AUTO_TEST_CASE(test22) {
	std::cout << "TEST22..." << std::endl;
	std::cout << std::endl;
	Graph<int> testGraph(10, std::cout);
	testGraph.addEdge(1, 2, 2);
	BOOST_CHECK_THROW(testGraph.editEdge(1, -2, 10), std::invalid_argument);
	BOOST_CHECK_THROW(testGraph.editEdge(-1, 2, 10), std::invalid_argument);
	BOOST_CHECK_THROW(testGraph.editEdge(-1, -2, 10), std::invalid_argument);
	BOOST_CHECK_THROW(testGraph.editEdge(1, 125, 10), std::invalid_argument);
	BOOST_CHECK_THROW(testGraph.editEdge(123, 2, 10), std::invalid_argument);
	std::cout << std::endl;
}

//проверка изменения значений на ребрах на невалидных данных (2)
BOOST_AUTO_TEST_CASE(test23) {
	std::cout << "TEST23..." << std::endl;
	Graph<int> testGraph(10, std::cout);
	testGraph.addEdge(1, 2, 2);
	testGraph.addEdge(1, 3, 2);
	testGraph.addEdge(2, 4, 2);
	BOOST_CHECK_THROW(testGraph.editEdge(3, 4, 10), std::invalid_argument);
	BOOST_CHECK_THROW(testGraph.editEdge(4, 3, 10), std::invalid_argument);
	BOOST_CHECK_THROW(testGraph.editEdge(5, 3, 10), std::invalid_argument);
	BOOST_CHECK_THROW(testGraph.editEdge(3, 5, 10), std::invalid_argument);
	std::cout << std::endl;
}

//проверка корректности работы графа с нулевыми ребрами
BOOST_AUTO_TEST_CASE(test24) {
	std::cout << "TEST24..." << std::endl;
	Graph<int> testGraph(10, std::cout);
	testGraph.addEdge(1, 2, 0);
	testGraph.addEdge(1, 3, 0);
	testGraph.addEdge(3, 4, 0);
	testGraph.addEdge(4, 5, 0);
	std::vector<int> from;
	std::vector<int> to;
	from.push_back(1);
	to.push_back(5);
	std::vector<int> path;
	int pathLength;
	BOOST_REQUIRE(testGraph.findPath(from, to));
	BOOST_REQUIRE(testGraph.Dijkstra(from, to, path, pathLength));
	BOOST_REQUIRE(pathLength == 0);
	std::cout << std::endl;
}

//проверка корректности работы функции showSize()
BOOST_AUTO_TEST_CASE(test25) {
	std::cout << "TEST25..." << std::endl;
	Graph<int> testGraph(10, std::cout);
	testGraph.addEdge(1, 2, 5);
	testGraph.addEdge(1, 3, 3);
	testGraph.addEdge(3, 4, 2);
	testGraph.addEdge(4, 5, 10);
	testGraph.addEdge(4, 9, 15);  
	BOOST_REQUIRE(testGraph.showSize() == 10);
	testGraph.addEdge(4, 11, 8);
	testGraph.addEdge(0, 11, 9);  //ребра нумеруются с нуля
	BOOST_REQUIRE(testGraph.showSize() == 12);
	std::cout << std::endl;
}

//проверка корректности работы функции changeSize() (1)
BOOST_AUTO_TEST_CASE(test26) {
	std::cout << "TEST26..." << std::endl;
	Graph<int> testGraph(10, std::cout);
	testGraph.addEdge(1, 2, 5);
	testGraph.addEdge(1, 3, 3);
	testGraph.addEdge(3, 4, 2);
	testGraph.addEdge(4, 5, 10);
	testGraph.addEdge(4, 9, 15);  
	testGraph.changeSize(17);
	BOOST_REQUIRE(testGraph.showSize() == 17);
	std::cout << std::endl;
}

//проверка корректности работы функции changeSize() (2)
BOOST_AUTO_TEST_CASE(test27) {
	std::cout << "TEST27..." << std::endl;
	Graph<int> testGraph(10, std::cout);
	testGraph.addEdge(1, 2, 5);
	testGraph.addEdge(1, 3, 3);
	testGraph.addEdge(3, 4, 2);
	testGraph.addEdge(4, 5, 10);
	testGraph.addEdge(4, 9, 15);  
	BOOST_CHECK_THROW(testGraph.changeSize(8), std::invalid_argument);
	BOOST_CHECK_THROW(testGraph.changeSize(1), std::invalid_argument);
	testGraph.changeSize(15);
	BOOST_REQUIRE(testGraph.showSize() == 15);
	std::cout << std::endl;
}

//проверка корректности работы с кодировками (вывод результатов на русском языке)
BOOST_AUTO_TEST_CASE(test28) {
	std::cout << "TEST28..." << std::endl;
	Graph<std::string> testGraph(10, std::cout);
	testGraph.addEdge(1, 2, "Один ");
	testGraph.addEdge(1, 3, "Два ");
	testGraph.addEdge(3, 4, "Три ");
	testGraph.addEdge(4, 5, "Четыре ");
	testGraph.addEdge(4, 9, "Пять ");  
	std::vector<int> from;
	std::vector<int> to;
	from.push_back(2);
	to.push_back(3);
	std::vector<int> path;
	std::string pathLength;
	BOOST_REQUIRE(testGraph.findPath(from, to));
	BOOST_REQUIRE(testGraph.Dijkstra(from, to, path, pathLength));
	std::cout << std::endl;
}
