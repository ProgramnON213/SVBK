#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Algo.h"
#include <sstream>

using namespace std;

void printPath(PathNode* head) {
    cout << "Solution Path:\n";
    while (head != nullptr) {
        cout << "Node: " << head->name 
             << " | f: " << head->f 
             << " | g: " << head->g 
             << " | h: " << head->h << "\n";
        head = head->next;
    }
}

void freePath(PathNode* head) {
    // Check if the path is empty to avoid deleting a null pointer
    if (head != nullptr) {
        delete head;
    }
}

TEST_CASE("test_001") {
  const int n = 5;
  double adjMatrix[100][100] = {
      {0, 2, 3, 0, 0}, // 0
      {0, 0, 0, 3, 0}, // 1
      {0, 0, 0, 1, 3}, // 2
      {0, 0, 0, 0, 1}, // 3
      {0, 0, 0, 0, 0}  // 4
  };

  int coords[100][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}, {2, 1}};

  int start = 0;
  int goal = 4;
  int mode = 1; // Manhattan

  PathNode *path = findDronePath(adjMatrix, coords, start, goal, mode);

  std::ostringstream buffer;
  std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());
  printPath(path);
  std::cout.rdbuf(oldCout);

  CHECK(buffer.str() == "Solution Path:\n"
                        "Node: (0,0) | f: 3 | g: 0 | h: 3\n"
                        "Node: (1,0) | f: 5 | g: 3 | h: 2\n"
                        "Node: (1,1) | f: 5 | g: 4 | h: 1\n"
                        "Node: (2,1) | f: 5 | g: 5 | h: 0\n");

  freePath(path);
}

TEST_CASE("test_002") {
  const int n = 5;
  double adjMatrix[100][100] = {
      {0, 2, 3, 0, 0}, // 0
      {0, 0, 0, 3, 0}, // 1
      {0, 0, 0, 1, 3}, // 2
      {0, 0, 0, 0, 1}, // 3
      {0, 0, 0, 0, 0}  // 4
  };

  int coords[100][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}, {2, 1}};

  int start = 0;
  int goal = 4;
  int mode = 2; // Euclidean

  PathNode *path = findDronePath(adjMatrix, coords, start, goal, mode);

  std::ostringstream buffer;
  std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());
  printPath(path);
  std::cout.rdbuf(oldCout);

  CHECK(buffer.str() == "Solution Path:\n"
                        "Node: (0,0) | f: 2.23607 | g: 0 | h: 2.23607\n"
                        "Node: (1,0) | f: 4.41421 | g: 3 | h: 1.41421\n"
                        "Node: (1,1) | f: 5 | g: 4 | h: 1\n"
                        "Node: (2,1) | f: 5 | g: 5 | h: 0\n");

  freePath(path);
}

TEST_CASE("test_003") {
  const int n = 4;
  double adjMatrix[100][100] = {
      {0, 0, 0, 0}, // 0
      {1, 0, 0, 0}, // 1
      {1, 1, 0, 0}, // 2
      {1, 1, 1, 0}  // 3
  };

  int coords[100][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};

  int start = 0;
  int goal = 3;
  int mode = 1; // Manhattan

  PathNode *path = findDronePath(adjMatrix, coords, start, goal, mode);

  std::ostringstream buffer;
  std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());
  printPath(path);
  std::cout.rdbuf(oldCout);

  CHECK(path == nullptr);
  CHECK(buffer.str() == "Solution Path:\n");

  freePath(path);
}

TEST_CASE("test_004") {
  const int n = 4;
  double adjMatrix[100][100] = {
      {0, 1, 4, 0}, // 0
      {0, 0, 2, 0}, // 1
      {0, 0, 0, 2}, // 2
      {0, 0, 0, 0}  // 3
  };

  int coords[100][2] = {{0, 0}, {0, 1}, {5, 5}, {1, 0}};

  int start = 0;
  int goal = 2;
  int mode = 1;
  PathNode *path = findDronePath(adjMatrix, coords, start, goal, mode);

  std::ostringstream buffer;
  std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());
  printPath(path);
  std::cout.rdbuf(oldCout);

  CHECK(buffer.str() == "Solution Path:\n"
                        "Node: (0,0) | f: 10 | g: 0 | h: 10\n"
                        "Node: (5,5) | f: 4 | g: 4 | h: 0\n");

  freePath(path);
}

TEST_CASE("test_005") {
  const int n = 5;
  double adjMatrix[100][100] = {0};
  adjMatrix[0][1] = 2; // 0->1
  adjMatrix[0][2] = 3; // 0->2
  adjMatrix[1][3] = 3; // 1->3
  adjMatrix[2][3] = 1; // 2->3
  adjMatrix[3][4] = 1; // 3->4

  int coords[100][2] = {{0, 0}, {1, 0}, {0, 1}, {1, 1}, {2, 1}};

  int start = 0;
  int goal = 4;
  int mode = 1;

  PathNode *path = findDronePath(adjMatrix, coords, start, goal, mode);

  std::ostringstream buffer;
  std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());
  printPath(path);
  std::cout.rdbuf(oldCout);

  CHECK(buffer.str() == "Solution Path:\n"
                        "Node: (0,0) | f: 3 | g: 0 | h: 3\n"
                        "Node: (0,1) | f: 5 | g: 3 | h: 2\n"
                        "Node: (1,1) | f: 5 | g: 4 | h: 1\n"
                        "Node: (2,1) | f: 5 | g: 5 | h: 0\n");

  freePath(path);
}

TEST_CASE("test_006") {
  const int n = 4;
  double adjMatrix[100][100] = {
      {0, 1, 1, 0}, // 0 -> 1, 0 -> 2
      {0, 0, 0, 1}, // 1 -> 3
      {0, 0, 0, 1}, // 2 -> 3
      {0, 0, 0, 0}  // 3
  };

  int coords[100][2] = {
      {0, 0},  // 0
      {0, 2},  // 1
      {2, 0},  // 2
      {-1, -1} // 3
  };

  int start = 0;
  int goal = 3;
  int mode = 3;

  PathNode *path = findDronePath(adjMatrix, coords, start, goal, mode);

  std::ostringstream buffer;
  std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());
  printPath(path);
  std::cout.rdbuf(oldCout);

  CHECK(buffer.str() == "Solution Path:\n"
                        "Node: (0,0) | f: 1 | g: 0 | h: 1\n"
                        "Node: (0,2) | f: 4 | g: 1 | h: 3\n"
                        "Node: (-1,-1) | f: 2 | g: 2 | h: 0\n");

  freePath(path);
}

void readAdjMatrixAndCoords(const std::string &adjFile,
                            const std::string &coorFile, double Mat[100][100],
                            int coor[100][2], int n) {
  // --- khởi tạo 0 ---
  for (int i = 0; i < n; ++i) {
    coor[i][0] = coor[i][1] = 0;
    for (int j = 0; j < n; ++j) {
      Mat[i][j] = 0.0;
    }
  }

  // --- đọc adjMatrix.txt ---
  std::ifstream finMat(adjFile);
  std::string line;
  while (std::getline(finMat, line)) {
    int u, v;
    double w;
    if (sscanf(line.c_str(), "(%d,%d,%lf)", &u, &v, &w) == 3) {
      Mat[u][v] = w;
    }
  }
  finMat.close();

  // --- đọc coords.txt ---
  std::ifstream finCoor(coorFile);
  int idx = 0;
  while (std::getline(finCoor, line)) {
    int x, y;
    if (sscanf(line.c_str(), "(%d,%d)", &x, &y) == 2) {
      coor[idx][0] = x;
      coor[idx][1] = y;
      ++idx;
    }
  }
  finCoor.close();
}

TEST_CASE("test_007") {
  const int n = 4;
  double Mat[100][100];
  int coor[100][2];

  readAdjMatrixAndCoords("tests/adjMatrix.txt", "tests/coords.txt", Mat, coor,
                         n);

  std::ostringstream buffer;
  std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

  int start = 0;
  int goal = 1;
  PathNode *OutPath;

  OutPath = findDronePath(Mat, coor, start, goal, 1);
  printPath(OutPath);
  freePath(OutPath);

  std::cout.rdbuf(oldCout);

  std::string expected = "Solution Path:\n"
                         "Node: (61,69) | f: 38 | g: 0 | h: 38\n"
                         "Node: (97,47) | f: 22.6 | g: 2.6 | h: 20\n"
                         "Node: (81,51) | f: 6.5 | g: 6.5 | h: 0\n";

  CHECK(buffer.str() == expected);
}

TEST_CASE("test_008") {
  const int n = 4;
  double Mat[100][100];
  int coor[100][2];

  // --- đọc file ---
  readAdjMatrixAndCoords("tests/adjMatrix.txt", "tests/coords.txt", Mat, coor,
                         n);

  std::ostringstream buffer;
  std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

  int start = 1;
  int goal = 0;
  PathNode *OutPath;

  OutPath = findDronePath(Mat, coor, start, goal, 1);
  printPath(OutPath);
  freePath(OutPath);

  OutPath = findDronePath(Mat, coor, start, goal, 2);
  printPath(OutPath);
  freePath(OutPath);

  OutPath = findDronePath(Mat, coor, start, goal, 3);
  printPath(OutPath);
  freePath(OutPath);
  std::cout.rdbuf(oldCout);

  std::string expected = "Solution Path:\n"
                         "Node: (81,51) | f: 38 | g: 0 | h: 38\n"
                         "Node: (55,74) | f: 14.9 | g: 3.9 | h: 11\n"
                         "Node: (65,90) | f: 31.7 | g: 6.7 | h: 25\n"
                         "Node: (61,69) | f: 8.6 | g: 8.6 | h: 0\n"

                         "Solution Path:\n"
                         "Node: (81,51) | f: 26.9072 | g: 0 | h: 26.9072\n"
                         "Node: (44,54) | f: 27.0716 | g: 4.4 | h: 22.6716\n"
                         "Node: (61,69) | f: 6 | g: 6 | h: 0\n"

                         "Solution Path:\n"
                         "Node: (81,51) | f: 20 | g: 0 | h: 20\n"
                         "Node: (44,54) | f: 21.4 | g: 4.4 | h: 17\n"
                         "Node: (61,69) | f: 6 | g: 6 | h: 0\n";

  CHECK(buffer.str() == expected);
}

TEST_CASE("test_009") {
  const int n = 100;
  double Mat[100][100];
  int coor[100][2];

  // --- đọc file ---
  readAdjMatrixAndCoords("tests/adjMatrix.txt", "tests/coords.txt", Mat, coor,
                         n);

  std::ostringstream buffer;
  std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

  int start = 0;
  int goal = 59;
  PathNode *OutPath;

  // Heuristic type 1
  OutPath = findDronePath(Mat, coor, start, goal, 1);
  printPath(OutPath);
  freePath(OutPath);

  // Heuristic type 2
  OutPath = findDronePath(Mat, coor, start, goal, 2);
  printPath(OutPath);
  freePath(OutPath);

  OutPath = findDronePath(Mat, coor, start, goal, 3);
  printPath(OutPath);
  freePath(OutPath);
  std::cout.rdbuf(oldCout);

  std::cout.rdbuf(oldCout);

  std::string expected = "Solution Path:\n"
                         "Node: (61,69) | f: 71 | g: 0 | h: 71\n"
                         "Node: (67,10) | f: 24.2 | g: 6.2 | h: 18\n"
                         "Node: (72,4) | f: 34.5 | g: 7.5 | h: 27\n"
                         "Node: (64,12) | f: 32.1 | g: 15.1 | h: 17\n"
                         "Node: (50,9) | f: 16.7 | g: 16.7 | h: 0\n"

                         "Solution Path:\n"
                         "Node: (61,69) | f: 61 | g: 0 | h: 61\n"
                         "Node: (67,10) | f: 23.2294 | g: 6.2 | h: 17.0294\n"
                         "Node: (72,4) | f: 30.061 | g: 7.5 | h: 22.561\n"
                         "Node: (64,12) | f: 29.4178 | g: 15.1 | h: 14.3178\n"
                         "Node: (50,9) | f: 16.7 | g: 16.7 | h: 0\n"

                         "Solution Path:\n"
                         "Node: (61,69) | f: 60 | g: 0 | h: 60\n"
                         "Node: (67,10) | f: 23.2 | g: 6.2 | h: 17\n"
                         "Node: (72,4) | f: 29.5 | g: 7.5 | h: 22\n"
                         "Node: (64,12) | f: 29.1 | g: 15.1 | h: 14\n"
                         "Node: (50,9) | f: 16.7 | g: 16.7 | h: 0\n";

  CHECK(buffer.str() == expected);
}

TEST_CASE("test_010") {
  const int n = 100;
  double Mat[100][100];
  int coor[100][2];

  // --- đọc file ---
  readAdjMatrixAndCoords("tests/adjMatrix.txt", "tests/coords.txt", Mat, coor,
                         n);

  std::ostringstream buffer;
  std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

  int start = 59;
  int goal = 0;
  PathNode *OutPath;

  // Heuristic type 1
  OutPath = findDronePath(Mat, coor, start, goal, 1);
  printPath(OutPath);
  freePath(OutPath);

  // Heuristic type 2
  OutPath = findDronePath(Mat, coor, start, goal, 2);
  printPath(OutPath);
  freePath(OutPath);

  OutPath = findDronePath(Mat, coor, start, goal, 3);
  printPath(OutPath);
  freePath(OutPath);
  std::cout.rdbuf(oldCout);

  std::cout.rdbuf(oldCout);

  std::string expected = "Solution Path:\n"
                         "Node: (50,9) | f: 71 | g: 0 | h: 71\n"
                         "Node: (61,69) | f: 9.9 | g: 9.9 | h: 0\n"

                         "Solution Path:\n"
                         "Node: (50,9) | f: 61 | g: 0 | h: 61\n"
                         "Node: (61,69) | f: 9.9 | g: 9.9 | h: 0\n"

                         "Solution Path:\n"
                         "Node: (50,9) | f: 60 | g: 0 | h: 60\n"
                         "Node: (61,69) | f: 9.9 | g: 9.9 | h: 0\n";

  CHECK(buffer.str() == expected);
}

TEST_CASE("test_011") {
  const int n = 100;
  double Mat[100][100];
  int coor[100][2];

  // --- đọc file ---
  readAdjMatrixAndCoords("tests/adjMatrix.txt", "tests/coords.txt", Mat, coor,
                         n);

  std::ostringstream buffer;
  std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

  int start = 8;
  int goal = 36;
  PathNode *OutPath;

  // Heuristic type 1
  OutPath = findDronePath(Mat, coor, start, goal, 1);
  printPath(OutPath);
  freePath(OutPath);

  // Heuristic type 2
  OutPath = findDronePath(Mat, coor, start, goal, 2);
  printPath(OutPath);
  freePath(OutPath);

  OutPath = findDronePath(Mat, coor, start, goal, 3);
  printPath(OutPath);
  freePath(OutPath);
  std::cout.rdbuf(oldCout);

  std::cout.rdbuf(oldCout);

  std::string expected = "Solution Path:\n"
                         "Node: (64,39) | f: 33 | g: 0 | h: 33\n"
                         "Node: (65,45) | f: 31.1 | g: 3.1 | h: 28\n"
                         "Node: (81,51) | f: 28.7 | g: 10.7 | h: 18\n"
                         "Node: (97,47) | f: 26.3 | g: 18.3 | h: 8\n"
                         "Node: (99,38) | f: 34.9 | g: 21.9 | h: 13\n"
                         "Node: (87,42) | f: 33.5 | g: 26.5 | h: 7\n"
                         "Node: (92,44) | f: 35.6 | g: 35.6 | h: 0\n"

                         "Solution Path:\n"
                         "Node: (64,39) | f: 28.4429 | g: 0 | h: 28.4429\n"
                         "Node: (65,45) | f: 30.1185 | g: 3.1 | h: 27.0185\n"
                         "Node: (97,67) | f: 33.3372 | g: 9.8 | h: 23.5372\n"
                         "Node: (92,44) | f: 20.2 | g: 20.2 | h: 0\n"

                         "Solution Path:\n"
                         "Node: (64,39) | f: 28 | g: 0 | h: 28\n"
                         "Node: (65,45) | f: 30.1 | g: 3.1 | h: 27\n"
                         "Node: (97,67) | f: 32.8 | g: 9.8 | h: 23\n"
                         "Node: (92,44) | f: 20.2 | g: 20.2 | h: 0\n";

  CHECK(buffer.str() == expected);
}

TEST_CASE("test_012") {
  const int n = 100;
  double Mat[100][100];
  int coor[100][2];

  // --- đọc file ---
  readAdjMatrixAndCoords("tests/adjMatrix.txt", "tests/coords.txt", Mat, coor,
                         n);

  std::ostringstream buffer;
  std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

  int start = 0;
  int goal = 4;
  PathNode *OutPath;

  // Heuristic type 1
  OutPath = findDronePath(Mat, coor, start, goal, 1);
  printPath(OutPath);
  freePath(OutPath);

  // Heuristic type 2
  OutPath = findDronePath(Mat, coor, start, goal, 2);
  printPath(OutPath);
  freePath(OutPath);

  OutPath = findDronePath(Mat, coor, start, goal, 3);
  printPath(OutPath);
  freePath(OutPath);
  std::cout.rdbuf(oldCout);

  std::cout.rdbuf(oldCout);

  std::string expected = "Solution Path:\n"
                         "Node: (61,69) | f: 57 | g: 0 | h: 57\n"
                         "Node: (88,65) | f: 36.1 | g: 2.1 | h: 34\n"
                         "Node: (96,92) | f: 18.2 | g: 3.2 | h: 15\n"
                         "Node: (95,68) | f: 45.3 | g: 7.3 | h: 38\n"
                         "Node: (65,90) | f: 40.8 | g: 8.8 | h: 32\n"
                         "Node: (88,99) | f: 14.3 | g: 14.3 | h: 0\n"

                         "Solution Path:\n"
                         "Node: (61,69) | f: 40.3609 | g: 0 | h: 40.3609\n"
                         "Node: (88,65) | f: 36.1 | g: 2.1 | h: 34\n"
                         "Node: (96,92) | f: 13.8301 | g: 3.2 | h: 10.6301\n"
                         "Node: (95,68) | f: 39.0805 | g: 7.3 | h: 31.7805\n"
                         "Node: (65,90) | f: 33.4982 | g: 8.8 | h: 24.6982\n"
                         "Node: (88,99) | f: 14.3 | g: 14.3 | h: 0\n"

                         "Solution Path:\n"
                         "Node: (61,69) | f: 30 | g: 0 | h: 30\n"
                         "Node: (88,65) | f: 36.1 | g: 2.1 | h: 34\n"
                         "Node: (96,92) | f: 11.2 | g: 3.2 | h: 8\n"
                         "Node: (55,74) | f: 37.8 | g: 4.8 | h: 33\n"
                         "Node: (88,99) | f: 13.4 | g: 13.4 | h: 0\n";

  CHECK(buffer.str() == expected);
}

TEST_CASE("test_013") {
  const int n = 100;
  double Mat[100][100];
  int coor[100][2];

  // --- đọc file ---
  readAdjMatrixAndCoords("tests/adjMatrix.txt", "tests/coords.txt", Mat, coor,
                         n);

  std::ostringstream buffer;
  std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

  int start = 35;
  int goal = 21;
  PathNode *OutPath;

  // Heuristic type 1
  OutPath = findDronePath(Mat, coor, start, goal, 1);
  printPath(OutPath);
  freePath(OutPath);

  // Heuristic type 2
  OutPath = findDronePath(Mat, coor, start, goal, 2);
  printPath(OutPath);
  freePath(OutPath);

  OutPath = findDronePath(Mat, coor, start, goal, 3);
  printPath(OutPath);
  freePath(OutPath);
  std::cout.rdbuf(oldCout);

  std::cout.rdbuf(oldCout);

  std::string expected = "Solution Path:\n"
                         "Node: (34,41) | f: 59 | g: 0 | h: 59\n"
                         "Node: (45,74) | f: 16.4 | g: 1.4 | h: 15\n"
                         "Node: (65,90) | f: 23.9 | g: 2.9 | h: 21\n"
                         "Node: (61,69) | f: 16.8 | g: 4.8 | h: 12\n"
                         "Node: (55,74) | f: 18.2 | g: 13.2 | h: 5\n"
                         "Node: (57,77) | f: 21.9 | g: 21.9 | h: 0\n"

                         "Solution Path:\n"
                         "Node: (34,41) | f: 42.72 | g: 0 | h: 42.72\n"
                         "Node: (45,74) | f: 13.7693 | g: 1.4 | h: 12.3693\n"
                         "Node: (65,90) | f: 18.1643 | g: 2.9 | h: 15.2643\n"
                         "Node: (61,69) | f: 13.7443 | g: 4.8 | h: 8.94427\n"
                         "Node: (47,85) | f: 21.0062 | g: 8.2 | h: 12.8062\n"
                         "Node: (57,77) | f: 18.8 | g: 18.8 | h: 0\n"

                         "Solution Path:\n"
                         "Node: (34,41) | f: 36 | g: 0 | h: 36\n"
                         "Node: (45,74) | f: 13.4 | g: 1.4 | h: 12\n"
                         "Node: (65,90) | f: 15.9 | g: 2.9 | h: 13\n"
                         "Node: (61,69) | f: 12.8 | g: 4.8 | h: 8\n"
                         "Node: (47,85) | f: 18.2 | g: 8.2 | h: 10\n"
                         "Node: (57,77) | f: 18.8 | g: 18.8 | h: 0\n";

  CHECK(buffer.str() == expected);
}

TEST_CASE("test_014") {
  const int n = 100;
  double Mat[100][100];
  int coor[100][2];

  // --- đọc file ---
  readAdjMatrixAndCoords("tests/adjMatrix.txt", "tests/coords.txt", Mat, coor,
                         n);

  std::ostringstream buffer;
  std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

  int start = 46;
  int goal = 23;
  PathNode *OutPath;

  // Heuristic type 1
  OutPath = findDronePath(Mat, coor, start, goal, 1);
  printPath(OutPath);
  freePath(OutPath);

  // Heuristic type 2
  OutPath = findDronePath(Mat, coor, start, goal, 2);
  printPath(OutPath);
  freePath(OutPath);

  OutPath = findDronePath(Mat, coor, start, goal, 3);
  printPath(OutPath);
  freePath(OutPath);
  std::cout.rdbuf(oldCout);

  std::cout.rdbuf(oldCout);
  std::string expected = "Solution Path:\n"
                         "Node: (8,96) | f: 19 | g: 0 | h: 19\n"
                         "Node: (8,74) | f: 12.1 | g: 1.1 | h: 11\n"
                         "Node: (17,72) | f: 24.2 | g: 2.2 | h: 22\n"
                         "Node: (24,86) | f: 37.9 | g: 12.9 | h: 25\n"
                         "Node: (22,73) | f: 44.5 | g: 18.5 | h: 26\n"
                         "Node: (4,81) | f: 22.7 | g: 22.7 | h: 0\n"

                         "Solution Path:\n"
                         "Node: (8,96) | f: 15.5242 | g: 0 | h: 15.5242\n"
                         "Node: (25,59) | f: 35.4138 | g: 5 | h: 30.4138\n"
                         "Node: (4,81) | f: 10.9 | g: 10.9 | h: 0\n"

                         "Solution Path:\n"
                         "Node: (8,96) | f: 15 | g: 0 | h: 15\n"
                         "Node: (25,59) | f: 27 | g: 5 | h: 22\n"
                         "Node: (4,81) | f: 10.9 | g: 10.9 | h: 0\n";

  CHECK(buffer.str() == expected);
}

TEST_CASE("test_015") {
  const int n = 100;
  double Mat[100][100];
  int coor[100][2];

  // --- đọc file ---
  readAdjMatrixAndCoords("tests/adjMatrix.txt", "tests/coords.txt", Mat, coor,
                         n);

  std::ostringstream buffer;
  std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

  int start = 8;
  int goal = 18;
  PathNode *OutPath;

  // Heuristic type 1
  OutPath = findDronePath(Mat, coor, start, goal, 1);
  printPath(OutPath);
  freePath(OutPath);

  // Heuristic type 2
  OutPath = findDronePath(Mat, coor, start, goal, 2);
  printPath(OutPath);
  freePath(OutPath);

  OutPath = findDronePath(Mat, coor, start, goal, 3);
  printPath(OutPath);
  freePath(OutPath);
  std::cout.rdbuf(oldCout);

  std::cout.rdbuf(oldCout);

  std::string expected = "Solution Path:\n"
                         "Node: (64,39) | f: 61 | g: 0 | h: 61\n"
                         "Node: (95,80) | f: 22 | g: 7 | h: 15\n"
                         "Node: (97,47) | f: 29 | g: 9 | h: 20\n"
                         "Node: (70,61) | f: 43.1 | g: 10.1 | h: 33\n"
                         "Node: (73,68) | f: 37.7 | g: 12.7 | h: 25\n"
                         "Node: (97,67) | f: 23.2 | g: 23.2 | h: 0\n"

                         "Solution Path:\n"
                         "Node: (64,39) | f: 43.2782 | g: 0 | h: 43.2782\n"
                         "Node: (96,92) | f: 29.82 | g: 4.8 | h: 25.02\n"
                         "Node: (87,42) | f: 37.4258 | g: 10.5 | h: 26.9258\n"
                         "Node: (97,67) | f: 18.9 | g: 18.9 | h: 0\n"

                         "Solution Path:\n"
                         "Node: (64,39) | f: 33 | g: 0 | h: 33\n"
                         "Node: (65,90) | f: 35.1 | g: 3.1 | h: 32\n"
                         "Node: (73,68) | f: 28.4 | g: 4.4 | h: 24\n"
                         "Node: (97,67) | f: 14.9 | g: 14.9 | h: 0\n";

  CHECK(buffer.str() == expected);
}

TEST_CASE("test_016") {
  const int n = 100;
  double Mat[100][100];
  int coor[100][2];

  // --- đọc file ---
  readAdjMatrixAndCoords("tests/adjMatrix.txt", "tests/coords.txt", Mat, coor,
                         n);

  std::ostringstream buffer;
  std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

  int start = 46;
  int goal = 20;
  PathNode *OutPath;

  // Heuristic type 1
  OutPath = findDronePath(Mat, coor, start, goal, 1);
  printPath(OutPath);
  freePath(OutPath);

  // Heuristic type 2
  OutPath = findDronePath(Mat, coor, start, goal, 2);
  printPath(OutPath);
  freePath(OutPath);

  OutPath = findDronePath(Mat, coor, start, goal, 3);
  printPath(OutPath);
  freePath(OutPath);
  std::cout.rdbuf(oldCout);

  std::cout.rdbuf(oldCout);

  std::string expected = "Solution Path:\n"
                         "Node: (8,96) | f: 87 | g: 0 | h: 87\n"
                         "Node: (3,22) | f: 19.1 | g: 1.1 | h: 18\n"
                         "Node: (12,46) | f: 35.1 | g: 2.1 | h: 33\n"
                         "Node: (11,42) | f: 41.8 | g: 11.8 | h: 30\n"
                         "Node: (16,26) | f: 27.6 | g: 18.6 | h: 9\n"
                         "Node: (18,19) | f: 26.1 | g: 26.1 | h: 0\n"

                         "Solution Path:\n"
                         "Node: (8,96) | f: 77.6466 | g: 0 | h: 77.6466\n"
                         "Node: (3,22) | f: 16.3971 | g: 1.1 | h: 15.2971\n"
                         "Node: (38,37) | f: 30.7072 | g: 3.8 | h: 26.9072\n"
                         "Node: (16,26) | f: 14.9801 | g: 7.7 | h: 7.28011\n"
                         "Node: (18,19) | f: 15.2 | g: 15.2 | h: 0\n"

                         "Solution Path:\n"
                         "Node: (8,96) | f: 77 | g: 0 | h: 77\n"
                         "Node: (3,22) | f: 16.1 | g: 1.1 | h: 15\n"
                         "Node: (38,37) | f: 23.8 | g: 3.8 | h: 20\n"
                         "Node: (16,26) | f: 14.7 | g: 7.7 | h: 7\n"
                         "Node: (18,19) | f: 15.2 | g: 15.2 | h: 0\n";

  CHECK(buffer.str() == expected);
}
