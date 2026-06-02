g++ -o main main.cpp PathNode.cpp Algo.cpp -I . -std=c++11
g++ -o test1 -I. Algo.cpp PathNode.cpp test_findShortestPathMatrix.cpp
g++ -o test2 -I. Algo.cpp PathNode.cpp test_findDronePath.cpp
g++ -o test3 -I. Algo.cpp PathNode.cpp test_findWarehousePath.cpp
g++ -o test4 -I. Algo.cpp PathNode.cpp test_findEvacuationPath.cpp
