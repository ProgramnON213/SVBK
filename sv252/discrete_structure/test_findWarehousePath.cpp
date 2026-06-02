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

TEST_CASE("test_001")
{
    const int m = 5, n = 5;

    int maze[100][100] = {
        {0, 0, 0, 0, 0}, // row 0
        {1, 1, 0, 1, 0}, // row 1
        {0, 0, 0, 1, 0}, // row 2
        {0, 1, 1, 0, 0}, // row 3
        {0, 0, 0, 0, 0}  // row 4
    };

    int startX = 0, startY = 0;
    int goalX = 4, goalY = 4;

    PathNode *path = findWarehousePath(maze, m, n, startX, startY, goalX, goalY, 1);

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());
    printPath(path);
    std::cout.rdbuf(oldCout);

    CHECK(buffer.str() ==
          "Solution Path:\n"
          "Node: Right | f: 8 | g: 1 | h: 7\n"
          "Node: Down-Right | f: 7.5 | g: 2.5 | h: 5\n"
          "Node: Down | f: 7.5 | g: 3.5 | h: 4\n"
          "Node: Down-Right | f: 7 | g: 5 | h: 2\n"
          "Node: Down-Right | f: 6.5 | g: 6.5 | h: 0\n");
    freePath(path);
}

TEST_CASE("test_002")
{
    const int m = 5, n = 5;

    int maze[100][100] = {
        {0, 0, 0, 0, 0}, // row 0
        {1, 1, 0, 1, 0}, // row 1
        {0, 0, 0, 1, 0}, // row 2
        {0, 1, 1, 0, 0}, // row 3
        {0, 0, 0, 0, 0}  // row 4
    };

    int startX = 0, startY = 4;
    int goalX = 4, goalY = 0;

    PathNode *path = findWarehousePath(maze, m, n, startX, startY, goalX, goalY, 1);

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());
    printPath(path);
    std::cout.rdbuf(oldCout);

    CHECK(buffer.str() ==
          "Solution Path:\n"
          "Node: Left | f: 8 | g: 1 | h: 7\n"
          "Node: Down-Left | f: 7.5 | g: 2.5 | h: 5\n"
          "Node: Down-Left | f: 7 | g: 4 | h: 3\n"
          "Node: Down-Left | f: 6.5 | g: 5.5 | h: 1\n"
          "Node: Down | f: 6.5 | g: 6.5 | h: 0\n");
    freePath(path);
}

TEST_CASE("test_003")
{
    const int m = 10, n = 5;
    int maze[100][100] = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0}};

    int startX = 0, startY = 0;
    int goalX = 9, goalY = 4;

    PathNode *path = findWarehousePath(maze, m, n, startX, startY, goalX, goalY, 1);

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());
    printPath(path);
    std::cout.rdbuf(oldCout);

    CHECK(buffer.str() ==
          "Solution Path:\n"
          "Node: Down | f: 13 | g: 1 | h: 12\n"
          "Node: Down-Right | f: 12.5 | g: 2.5 | h: 10\n"
          "Node: Down-Right | f: 12 | g: 4 | h: 8\n"
          "Node: Down-Right | f: 11.5 | g: 5.5 | h: 6\n"
          "Node: Down-Right | f: 11 | g: 7 | h: 4\n"
          "Node: Down | f: 11 | g: 8 | h: 3\n"
          "Node: Down | f: 11 | g: 9 | h: 2\n"
          "Node: Down | f: 11 | g: 10 | h: 1\n"
          "Node: Down | f: 11 | g: 11 | h: 0\n");

    freePath(path);
}

TEST_CASE("test_004")
{
    const int m = 5, n = 10;
    int maze[100][100] = {
        {0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
        {0, 1, 1, 0, 1, 1, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 1, 1, 0}};

    int startX = 0, startY = 0;
    int goalX = 4, goalY = 9;

    PathNode *path = findWarehousePath(maze, m, n, startX, startY, goalX, goalY, 1);

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());
    printPath(path);
    std::cout.rdbuf(oldCout);

    CHECK(buffer.str() ==
          "Solution Path:\n"
          "Node: Down | f: 13 | g: 1 | h: 12\n"
          "Node: Down-Right | f: 12.5 | g: 2.5 | h: 10\n"
          "Node: Right | f: 12.5 | g: 3.5 | h: 9\n"
          "Node: Right | f: 12.5 | g: 4.5 | h: 8\n"
          "Node: Right | f: 12.5 | g: 5.5 | h: 7\n"
          "Node: Right | f: 12.5 | g: 6.5 | h: 6\n"
          "Node: Down-Right | f: 12 | g: 8 | h: 4\n"
          "Node: Right | f: 12 | g: 9 | h: 3\n"
          "Node: Right | f: 12 | g: 10 | h: 2\n"
          "Node: Down-Right | f: 11.5 | g: 11.5 | h: 0\n");
    freePath(path);
}

TEST_CASE("test_005")
{
    const int m = 10, n = 10;
    int maze[100][100] = {
        {0, 1, 0, 0, 0, 1, 0, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 1, 0},
        {0, 0, 0, 1, 0, 0, 0, 1, 0, 0},
        {1, 1, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 1, 1, 0, 1, 1, 1, 0, 1},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {1, 0, 1, 1, 1, 1, 0, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    int startX = 0, startY = 0;
    int goalX = 9, goalY = 9;

    PathNode *path = findWarehousePath(maze, m, n, startX, startY, goalX, goalY, 1);

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());
    printPath(path);
    std::cout.rdbuf(oldCout);
    CHECK(buffer.str() ==
          "Solution Path:\n"
          "Node: Down | f: 18 | g: 1 | h: 17\n"
          "Node: Down-Right | f: 17.5 | g: 2.5 | h: 15\n"
          "Node: Down-Right | f: 17 | g: 4 | h: 13\n"
          "Node: Right | f: 17 | g: 5 | h: 12\n"
          "Node: Down-Right | f: 16.5 | g: 6.5 | h: 10\n"
          "Node: Down-Right | f: 16 | g: 8 | h: 8\n"
          "Node: Right | f: 16 | g: 9 | h: 7\n"
          "Node: Right | f: 16 | g: 10 | h: 6\n"
          "Node: Right | f: 16 | g: 11 | h: 5\n"
          "Node: Down-Right | f: 15.5 | g: 12.5 | h: 3\n"
          "Node: Down | f: 15.5 | g: 13.5 | h: 2\n"
          "Node: Down | f: 15.5 | g: 14.5 | h: 1\n"
          "Node: Down | f: 15.5 | g: 15.5 | h: 0\n");

    freePath(path);
}

TEST_CASE("test_006")
{
    const int m = 3, n = 3;

    int maze[100][100] = {
        {0, 1, 0}, // row 0
        {1, 1, 1}, // row 1 (chặn hết)
        {0, 1, 0}  // row 2
    };

    int startX = 0, startY = 0;
    int goalX = 2, goalY = 2;

    PathNode *path = findWarehousePath(maze, m, n, startX, startY, goalX, goalY, 1);

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());
    printPath(path);
    std::cout.rdbuf(oldCout);

    CHECK(path == nullptr);
    CHECK(buffer.str() == "Solution Path:\n");

    freePath(path);
}

TEST_CASE("test_007")
{
    const int m = 10, n = 10;
    int maze[100][100] = {
        {0, 1, 0, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 1, 0, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1, 0, 0, 1, 1, 1},
        {0, 1, 1, 1, 1, 0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 1, 1, 1, 1, 0},
        {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 0, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 0}};

    int startX = 0,
        startY = 0;
    int goalX = 9, goalY = 9;

    PathNode *path = findWarehousePath(maze, m, n, startX, startY, goalX, goalY, 1);

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());
    printPath(path);
    std::cout.rdbuf(oldCout);
    CHECK(buffer.str() ==
          "Solution Path:\n"
          "Node: Down-Right | f: 17.5 | g: 1.5 | h: 16\n"
          "Node: Up-Right | f: 19 | g: 3 | h: 16\n"
          "Node: Down-Right | f: 18.5 | g: 4.5 | h: 14\n"
          "Node: Down | f: 18.5 | g: 5.5 | h: 13\n"
          "Node: Down | f: 18.5 | g: 6.5 | h: 12\n"
          "Node: Down-Left | f: 20 | g: 8 | h: 12\n"
          "Node: Left | f: 22 | g: 9 | h: 13\n"
          "Node: Down-Left | f: 23.5 | g: 10.5 | h: 13\n"
          "Node: Down | f: 23.5 | g: 11.5 | h: 12\n"
          "Node: Down-Right | f: 23 | g: 13 | h: 10\n"
          "Node: Up-Right | f: 24.5 | g: 14.5 | h: 10\n"
          "Node: Right | f: 24.5 | g: 15.5 | h: 9\n"
          "Node: Right | f: 24.5 | g: 16.5 | h: 8\n"
          "Node: Up-Right | f: 26 | g: 18 | h: 8\n"
          "Node: Up-Right | f: 27.5 | g: 19.5 | h: 8\n"
          "Node: Down-Right | f: 27 | g: 21 | h: 6\n"
          "Node: Right | f: 27 | g: 22 | h: 5\n"
          "Node: Down-Right | f: 26.5 | g: 23.5 | h: 3\n"
          "Node: Down-Left | f: 28 | g: 25 | h: 3\n"
          "Node: Down-Left | f: 29.5 | g: 26.5 | h: 3\n"
          "Node: Down-Right | f: 29 | g: 28 | h: 1\n"
          "Node: Right | f: 29 | g: 29 | h: 0\n");

    freePath(path);
}

TEST_CASE("test_008")
{
    const int m = 3, n = 3;

    int maze[100][100] = {
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 0}};

    int startX = 0, startY = 0;
    int goalX = 2, goalY = 2;

    PathNode *path = findWarehousePath(maze, m, n, startX, startY, goalX, goalY, 1);

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());
    printPath(path);
    std::cout.rdbuf(oldCout);

    CHECK(buffer.str() ==
          "Solution Path:\n"
          "Node: Right | f: 4 | g: 1 | h: 3\n"
          "Node: Down-Right | f: 3.5 | g: 2.5 | h: 1\n"
          "Node: Down | f: 3.5 | g: 3.5 | h: 0\n");

    freePath(path);
}

TEST_CASE("test_009")
{
    const int m = 9, n = 10;

    int Maze1[100][100] = {
        {0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 1, 0, 0, 0, 1},
        {0, 1, 1, 0, 1, 0, 1, 1, 0, 0},
        {0, 1, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 1, 0, 0, 0, 1, 1},
        {0, 0, 0, 1, 1, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

    int startX = 0;
    int startY = 0;
    int goalX = 8;
    int goalY = 9;

    PathNode *OutPath;
    OutPath = findWarehousePath(Maze1, m, n, startX, startY, goalX, goalY, 1);
    printPath(OutPath);
    std::cout.rdbuf(oldCout);

    std::string expected =
        "Solution Path:\n"
        "Node: Down | f: 17 | g: 1 | h: 16\n"
        "Node: Down-Right | f: 16.5 | g: 2.5 | h: 14\n"
        "Node: Right | f: 16.5 | g: 3.5 | h: 13\n"
        "Node: Right | f: 16.5 | g: 4.5 | h: 12\n"
        "Node: Down-Right | f: 16 | g: 6 | h: 10\n"
        "Node: Down-Right | f: 15.5 | g: 7.5 | h: 8\n"
        "Node: Down | f: 15.5 | g: 8.5 | h: 7\n"
        "Node: Down-Right | f: 15 | g: 10 | h: 5\n"
        "Node: Down-Right | f: 14.5 | g: 11.5 | h: 3\n"
        "Node: Down-Right | f: 14 | g: 13 | h: 1\n"
        "Node: Right | f: 14 | g: 14 | h: 0\n";

    CHECK(buffer.str() == expected);

    freePath(OutPath);
}

TEST_CASE("test_010")
{
    const int m = 9, n = 10;

    int Maze1[100][100] = {
        {0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 1, 0, 0, 0, 1},
        {0, 1, 1, 0, 1, 0, 1, 1, 0, 0},
        {0, 1, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 1, 0, 0, 0, 1, 1},
        {0, 0, 0, 1, 1, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

    int startX = 0;
    int startY = 0;
    int goalX = 0;
    int goalY = 9;
    int r = 9, c = 10;

    PathNode *OutPath;
    OutPath = findWarehousePath(Maze1, r, c, startX, startY, goalX, goalY, 1);
    printPath(OutPath);
    std::cout.rdbuf(oldCout);

    std::string expected =
        "Solution Path:\n"
        "Node: Down | f: 11 | g: 1 | h: 10\n"
        "Node: Down-Right | f: 12.5 | g: 2.5 | h: 10\n"
        "Node: Right | f: 12.5 | g: 3.5 | h: 9\n"
        "Node: Right | f: 12.5 | g: 4.5 | h: 8\n"
        "Node: Right | f: 12.5 | g: 5.5 | h: 7\n"
        "Node: Right | f: 12.5 | g: 6.5 | h: 6\n"
        "Node: Right | f: 12.5 | g: 7.5 | h: 5\n"
        "Node: Right | f: 12.5 | g: 8.5 | h: 4\n"
        "Node: Up-Right | f: 12 | g: 10 | h: 2\n"
        "Node: Up-Right | f: 11.5 | g: 11.5 | h: 0\n";

    CHECK(buffer.str() == expected);

    freePath(OutPath);
}

TEST_CASE("test_011")
{
    const int m = 9, n = 10;

    int Maze1[100][100] = {
        {0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 1, 0, 0, 0, 1},
        {0, 1, 1, 0, 1, 0, 1, 1, 0, 0},
        {0, 1, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 1, 0, 0, 0, 1, 1},
        {0, 0, 0, 1, 1, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

    int startX = 4;
    int startY = 5;
    int goalX = 4;
    int goalY = 0;
    int r = 9, c = 10;

    PathNode *OutPath;
    OutPath = findWarehousePath(Maze1, r, c, startX, startY, goalX, goalY, 1);
    printPath(OutPath);
    std::cout.rdbuf(oldCout);

    std::string expected =
        "Solution Path:\n"
        "Node: Up-Left | f: 6.5 | g: 1.5 | h: 5\n"
        "Node: Up-Left | f: 8 | g: 3 | h: 5\n"
        "Node: Left | f: 8 | g: 4 | h: 4\n"
        "Node: Left | f: 8 | g: 5 | h: 3\n"
        "Node: Down-Left | f: 7.5 | g: 6.5 | h: 1\n"
        "Node: Down | f: 7.5 | g: 7.5 | h: 0\n";

    CHECK(buffer.str() == expected);

    freePath(OutPath);
}

TEST_CASE("test_012")
{
    const int m = 9, n = 10;

    int Maze1[100][100] = {
        {0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 1, 0, 0, 0, 1},
        {0, 1, 1, 0, 1, 0, 1, 1, 0, 0},
        {0, 1, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 1, 0, 0, 0, 1, 1},
        {0, 0, 0, 1, 1, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

    int startX = 4;
    int startY = 5;
    int goalX = 0;
    int goalY = 5;
    int r = 9, c = 10;

    PathNode *OutPath;
    OutPath = findWarehousePath(Maze1, r, c, startX, startY, goalX, goalY, 1);
    printPath(OutPath);
    std::cout.rdbuf(oldCout);

    std::string expected =
        "Solution Path:\n"
        "Node: Up-Left | f: 5.5 | g: 1.5 | h: 4\n"
        "Node: Up-Right | f: 5 | g: 3 | h: 2\n"
        "Node: Up | f: 5 | g: 4 | h: 1\n"
        "Node: Up | f: 5 | g: 5 | h: 0\n";

    CHECK(buffer.str() == expected);

    freePath(OutPath);
}

TEST_CASE("test_013")
{
    const int m = 9, n = 10;

    int Maze1[100][100] = {
        {0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 1, 0, 0, 0, 1},
        {0, 1, 1, 0, 1, 0, 1, 1, 0, 0},
        {0, 1, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 1, 0, 0, 0, 1, 1},
        {0, 0, 0, 1, 1, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

    int startX = 4;
    int startY = 8;
    int goalX = 5;
    int goalY = 0;
    int r = 9, c = 10;

    PathNode *OutPath;
    OutPath = findWarehousePath(Maze1, r, c, startX, startY, goalX, goalY, 1);
    printPath(OutPath);
    std::cout.rdbuf(oldCout);

    std::string expected =
        "Solution Path:\n"
        "Node: Up-Left | f: 10.5 | g: 1.5 | h: 9\n"
        "Node: Left | f: 10.5 | g: 2.5 | h: 8\n"
        "Node: Up-Left | f: 12 | g: 4 | h: 8\n"
        "Node: Left | f: 12 | g: 5 | h: 7\n"
        "Node: Left | f: 12 | g: 6 | h: 6\n"
        "Node: Left | f: 12 | g: 7 | h: 5\n"
        "Node: Left | f: 12 | g: 8 | h: 4\n"
        "Node: Down-Left | f: 11.5 | g: 9.5 | h: 2\n"
        "Node: Down | f: 11.5 | g: 10.5 | h: 1\n"
        "Node: Down | f: 11.5 | g: 11.5 | h: 0\n";

    CHECK(buffer.str() == expected);

    freePath(OutPath);
}

TEST_CASE("test_014")
{
    const int m = 9, n = 10;

    int Maze1[100][100] = {
        {0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 1, 0, 0, 0, 1},
        {0, 1, 1, 0, 1, 0, 1, 1, 0, 0},
        {0, 1, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 1, 0, 0, 0, 1, 1},
        {0, 0, 0, 1, 1, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

    int startX = 4;
    int startY = 8;
    int goalX = 0;
    int goalY = 3;
    int r = 9, c = 10;

    PathNode *OutPath;
    OutPath = findWarehousePath(Maze1, r, c, startX, startY, goalX, goalY, 1);
    printPath(OutPath);
    std::cout.rdbuf(oldCout);

    std::string expected =
        "Solution Path:\n"
        "Node: Up-Left | f: 8.5 | g: 1.5 | h: 7\n"
        "Node: Up-Left | f: 8 | g: 3 | h: 5\n"
        "Node: Left | f: 8 | g: 4 | h: 4\n"
        "Node: Left | f: 8 | g: 5 | h: 3\n"
        "Node: Left | f: 8 | g: 6 | h: 2\n"
        "Node: Left | f: 10 | g: 7 | h: 3\n"
        "Node: Left | f: 12 | g: 8 | h: 4\n"
        "Node: Up-Left | f: 13.5 | g: 9.5 | h: 4\n"
        "Node: Up-Right | f: 13 | g: 11 | h: 2\n"
        "Node: Right | f: 13 | g: 12 | h: 1\n"
        "Node: Right | f: 13 | g: 13 | h: 0\n";

    CHECK(buffer.str() == expected);

    freePath(OutPath);
}

TEST_CASE("test_015")
{
    const int m = 9, n = 10;

    int Maze1[100][100] = {
        {0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 1, 0, 0, 0, 1},
        {0, 1, 1, 0, 1, 0, 1, 1, 0, 0},
        {0, 1, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 1, 0, 0, 0, 1, 1},
        {0, 0, 0, 1, 1, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

    int startX = 8;
    int startY = 0;
    int goalX = 0;
    int goalY = 9;
    int r = 9, c = 10;

    PathNode *OutPath;
    OutPath = findWarehousePath(Maze1, r, c, startX, startY, goalX, goalY, 1);
    printPath(OutPath);
    std::cout.rdbuf(oldCout);

    std::string expected =
        "Solution Path:\n"
        "Node: Up-Right | f: 16.5 | g: 1.5 | h: 15\n"
        "Node: Up-Right | f: 16 | g: 3 | h: 13\n"
        "Node: Up-Right | f: 15.5 | g: 4.5 | h: 11\n"
        "Node: Up | f: 15.5 | g: 5.5 | h: 10\n"
        "Node: Up-Right | f: 15 | g: 7 | h: 8\n"
        "Node: Up-Right | f: 14.5 | g: 8.5 | h: 6\n"
        "Node: Right | f: 14.5 | g: 9.5 | h: 5\n"
        "Node: Right | f: 14.5 | g: 10.5 | h: 4\n"
        "Node: Up-Right | f: 14 | g: 12 | h: 2\n"
        "Node: Up-Right | f: 13.5 | g: 13.5 | h: 0\n";

    CHECK(buffer.str() == expected);

    freePath(OutPath);
}

TEST_CASE("test_016")
{
    const int m = 9, n = 10;

    int Maze1[100][100] = {
        {0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 1, 0, 0, 0, 1},
        {0, 1, 1, 0, 1, 0, 1, 1, 0, 0},
        {0, 1, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 1, 0, 0, 0, 1, 1},
        {0, 0, 0, 1, 1, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

    int startX = 8;
    int startY = 0;
    int goalX = 0;
    int goalY = 7;
    int r = 9, c = 10;

    PathNode *OutPath;
    OutPath = findWarehousePath(Maze1, r, c, startX, startY, goalX, goalY, 1);
    printPath(OutPath);
    std::cout.rdbuf(oldCout);

    std::string expected =
        "Solution Path:\n"
        "Node: Up-Right | f: 14.5 | g: 1.5 | h: 13\n"
        "Node: Up-Right | f: 14 | g: 3 | h: 11\n"
        "Node: Up-Right | f: 13.5 | g: 4.5 | h: 9\n"
        "Node: Up | f: 13.5 | g: 5.5 | h: 8\n"
        "Node: Up-Right | f: 13 | g: 7 | h: 6\n"
        "Node: Up-Right | f: 12.5 | g: 8.5 | h: 4\n"
        "Node: Up-Right | f: 12 | g: 10 | h: 2\n"
        "Node: Up-Right | f: 11.5 | g: 11.5 | h: 0\n";

    CHECK(buffer.str() == expected);

    freePath(OutPath);
}

TEST_CASE("test_017")
{
    const int m = 9, n = 10;

    int Maze1[100][100] = {
        {0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 1, 0, 0, 0, 1},
        {0, 1, 1, 0, 1, 0, 1, 1, 0, 0},
        {0, 1, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 1, 0, 0, 0, 1, 1},
        {0, 0, 0, 1, 1, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

    int startX = 5;
    int startY = 7;
    int goalX = 0;
    int goalY = 3;
    int r = 9, c = 10;

    PathNode *OutPath;
    OutPath = findWarehousePath(Maze1, r, c, startX, startY, goalX, goalY, 1);
    printPath(OutPath);
    std::cout.rdbuf(oldCout);

    std::string expected =
        "Solution Path:\n"
        "Node: Up-Right | f: 10.5 | g: 1.5 | h: 9\n"
        "Node: Up-Left | f: 10 | g: 3 | h: 7\n"
        "Node: Up-Left | f: 9.5 | g: 4.5 | h: 5\n"
        "Node: Left | f: 9.5 | g: 5.5 | h: 4\n"
        "Node: Left | f: 9.5 | g: 6.5 | h: 3\n"
        "Node: Left | f: 9.5 | g: 7.5 | h: 2\n"
        "Node: Left | f: 11.5 | g: 8.5 | h: 3\n"
        "Node: Left | f: 13.5 | g: 9.5 | h: 4\n"
        "Node: Up-Left | f: 15 | g: 11 | h: 4\n"
        "Node: Up-Right | f: 14.5 | g: 12.5 | h: 2\n"
        "Node: Right | f: 14.5 | g: 13.5 | h: 1\n"
        "Node: Right | f: 14.5 | g: 14.5 | h: 0\n";

    CHECK(buffer.str() == expected);

    freePath(OutPath);
}

TEST_CASE("test_018")
{
    const int m = 9, n = 10;

    int Maze1[100][100] = {
        {0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 1, 0, 0, 0, 1},
        {0, 1, 1, 0, 1, 0, 1, 1, 0, 0},
        {0, 1, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 1, 0, 0, 0, 1, 1},
        {0, 0, 0, 1, 1, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

    int startX = 7;
    int startY = 2;
    int goalX = 0;
    int goalY = 3;
    int r = 9, c = 10;

    PathNode *OutPath;
    OutPath = findWarehousePath(Maze1, r, c, startX, startY, goalX, goalY, 1);
    printPath(OutPath);
    std::cout.rdbuf(oldCout);

    std::string expected =
        "Solution Path:\n"
        "Node: Left | f: 10 | g: 1 | h: 9\n"
        "Node: Up-Left | f: 11.5 | g: 2.5 | h: 9\n"
        "Node: Up | f: 11.5 | g: 3.5 | h: 8\n"
        "Node: Up | f: 11.5 | g: 4.5 | h: 7\n"
        "Node: Up | f: 11.5 | g: 5.5 | h: 6\n"
        "Node: Up | f: 11.5 | g: 6.5 | h: 5\n"
        "Node: Up | f: 11.5 | g: 7.5 | h: 4\n"
        "Node: Up-Right | f: 11 | g: 9 | h: 2\n"
        "Node: Right | f: 11 | g: 10 | h: 1\n"
        "Node: Right | f: 11 | g: 11 | h: 0\n";

    CHECK(buffer.str() == expected);

    freePath(OutPath);
}

TEST_CASE("test_101")
{
    const int m = 5, n = 5;

    int maze[100][100] = {
        {0, 0, 0, 0, 0}, // row 0
        {1, 1, 0, 1, 0}, // row 1
        {0, 0, 0, 1, 0}, // row 2
        {0, 1, 1, 0, 0}, // row 3
        {0, 0, 0, 0, 0}  // row 4
    };

    int startX = 0, startY = 0;
    int goalX = 4, goalY = 4;

    PathNode *path = findWarehousePath(maze, m, n, startX, startY, goalX, goalY, 2);

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());
    printPath(path);
    std::cout.rdbuf(oldCout);

    CHECK(buffer.str() ==
          "Solution Path:\n"
          "Node: Right | f: 5 | g: 1 | h: 4\n"
          "Node: Down-Right | f: 5.5 | g: 2.5 | h: 3\n"
          "Node: Down | f: 5.5 | g: 3.5 | h: 2\n"
          "Node: Down-Right | f: 6 | g: 5 | h: 1\n"
          "Node: Down-Right | f: 6.5 | g: 6.5 | h: 0\n");
    freePath(path);
}

TEST_CASE("test_102")
{
    const int m = 5, n = 5;

    int maze[100][100] = {
        {0, 0, 0, 0, 0}, // row 0
        {1, 1, 0, 1, 0}, // row 1
        {0, 0, 0, 1, 0}, // row 2
        {0, 1, 1, 0, 0}, // row 3
        {0, 0, 0, 0, 0}  // row 4
    };

    int startX = 0, startY = 4;
    int goalX = 4, goalY = 0;

    PathNode *path = findWarehousePath(maze, m, n, startX, startY, goalX, goalY, 2);

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());
    printPath(path);
    std::cout.rdbuf(oldCout);

    CHECK(buffer.str() ==
          "Solution Path:\n"
          "Node: Left | f: 5 | g: 1 | h: 4\n"
          "Node: Down-Left | f: 5.5 | g: 2.5 | h: 3\n"
          "Node: Down-Left | f: 6 | g: 4 | h: 2\n"
          "Node: Down-Left | f: 6.5 | g: 5.5 | h: 1\n"
          "Node: Down | f: 6.5 | g: 6.5 | h: 0\n");
    freePath(path);
}

TEST_CASE("test_103")
{
    const int m = 10, n = 5;
    int maze[100][100] = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0}};

    int startX = 0, startY = 0;
    int goalX = 9, goalY = 4;

    PathNode *path = findWarehousePath(maze, m, n, startX, startY, goalX, goalY, 2);

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());
    printPath(path);
    std::cout.rdbuf(oldCout);

    CHECK(buffer.str() ==
          "Solution Path:\n"
          "Node: Down | f: 9 | g: 1 | h: 8\n"
          "Node: Down-Right | f: 9.5 | g: 2.5 | h: 7\n"
          "Node: Down-Right | f: 10 | g: 4 | h: 6\n"
          "Node: Down-Right | f: 10.5 | g: 5.5 | h: 5\n"
          "Node: Down-Right | f: 11 | g: 7 | h: 4\n"
          "Node: Down | f: 11 | g: 8 | h: 3\n"
          "Node: Down | f: 11 | g: 9 | h: 2\n"
          "Node: Down | f: 11 | g: 10 | h: 1\n"
          "Node: Down | f: 11 | g: 11 | h: 0\n");

    freePath(path);
}

TEST_CASE("test_104")
{
    const int m = 5, n = 10;
    int maze[100][100] = {
        {0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
        {0, 1, 1, 0, 1, 1, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 1, 1, 0}};

    int startX = 0, startY = 0;
    int goalX = 4, goalY = 9;

    PathNode *path = findWarehousePath(maze, m, n, startX, startY, goalX, goalY, 2);

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());
    printPath(path);
    std::cout.rdbuf(oldCout);

    CHECK(buffer.str() ==
          "Solution Path:\n"
          "Node: Down | f: 10 | g: 1 | h: 9\n"
          "Node: Down-Right | f: 10.5 | g: 2.5 | h: 8\n"
          "Node: Right | f: 10.5 | g: 3.5 | h: 7\n"
          "Node: Right | f: 10.5 | g: 4.5 | h: 6\n"
          "Node: Right | f: 10.5 | g: 5.5 | h: 5\n"
          "Node: Right | f: 10.5 | g: 6.5 | h: 4\n"
          "Node: Right | f: 10.5 | g: 7.5 | h: 3\n"
          "Node: Down-Right | f: 11 | g: 9 | h: 2\n"
          "Node: Right | f: 11 | g: 10 | h: 1\n"
          "Node: Down-Right | f: 11.5 | g: 11.5 | h: 0\n");
    freePath(path);
}

TEST_CASE("test_105")
{
    const int m = 10, n = 10;
    int maze[100][100] = {
        {0, 1, 0, 0, 0, 1, 0, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 1, 0},
        {0, 0, 0, 1, 0, 0, 0, 1, 0, 0},
        {1, 1, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 1, 1, 0, 1, 1, 1, 0, 1},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {1, 0, 1, 1, 1, 1, 0, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    int startX = 0, startY = 0;
    int goalX = 9, goalY = 9;

    PathNode *path = findWarehousePath(maze, m, n, startX, startY, goalX, goalY, 2);

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());
    printPath(path);
    std::cout.rdbuf(oldCout);
    CHECK(buffer.str() ==
          "Solution Path:\n"
          "Node: Down | f: 10 | g: 1 | h: 9\n"
          "Node: Down-Right | f: 10.5 | g: 2.5 | h: 8\n"
          "Node: Right | f: 10.5 | g: 3.5 | h: 7\n"
          "Node: Down-Right | f: 11 | g: 5 | h: 6\n"
          "Node: Down-Right | f: 11.5 | g: 6.5 | h: 5\n"
          "Node: Down-Right | f: 12 | g: 8 | h: 4\n"
          "Node: Right | f: 13 | g: 9 | h: 4\n"
          "Node: Right | f: 14 | g: 10 | h: 4\n"
          "Node: Right | f: 15 | g: 11 | h: 4\n"
          "Node: Down-Right | f: 15.5 | g: 12.5 | h: 3\n"
          "Node: Down | f: 15.5 | g: 13.5 | h: 2\n"
          "Node: Down | f: 15.5 | g: 14.5 | h: 1\n"
          "Node: Down | f: 15.5 | g: 15.5 | h: 0\n");

    freePath(path);
}

TEST_CASE("test_106")
{
    const int m = 3, n = 3;

    int maze[100][100] = {
        {0, 1, 0}, // row 0
        {1, 1, 1}, // row 1 (chặn hết)
        {0, 1, 0}  // row 2
    };

    int startX = 0, startY = 0;
    int goalX = 2, goalY = 2;

    PathNode *path = findWarehousePath(maze, m, n, startX, startY, goalX, goalY, 2);

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());
    printPath(path);
    std::cout.rdbuf(oldCout);

    CHECK(path == nullptr);
    CHECK(buffer.str() == "Solution Path:\n");

    freePath(path);
}

TEST_CASE("test_107")
{
    const int m = 10, n = 10;
    int maze[100][100] = {
        {0, 1, 0, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 1, 0, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1, 0, 0, 1, 1, 1},
        {0, 1, 1, 1, 1, 0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 1, 1, 1, 1, 0},
        {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 0, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 0}};

    int startX = 0,
        startY = 0;
    int goalX = 9, goalY = 9;

    PathNode *path = findWarehousePath(maze, m, n, startX, startY, goalX, goalY, 2);

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());
    printPath(path);
    std::cout.rdbuf(oldCout);
    CHECK(buffer.str() ==
          "Solution Path:\n"
          "Node: Down-Right | f: 9.5 | g: 1.5 | h: 8\n"
          "Node: Up-Right | f: 12 | g: 3 | h: 9\n"
          "Node: Down-Right | f: 12.5 | g: 4.5 | h: 8\n"
          "Node: Down | f: 12.5 | g: 5.5 | h: 7\n"
          "Node: Down | f: 12.5 | g: 6.5 | h: 6\n"
          "Node: Down-Left | f: 15 | g: 8 | h: 7\n"
          "Node: Left | f: 17 | g: 9 | h: 8\n"
          "Node: Down-Left | f: 19.5 | g: 10.5 | h: 9\n"
          "Node: Down | f: 20.5 | g: 11.5 | h: 9\n"
          "Node: Down-Right | f: 21 | g: 13 | h: 8\n"
          "Node: Up-Right | f: 21.5 | g: 14.5 | h: 7\n"
          "Node: Right | f: 21.5 | g: 15.5 | h: 6\n"
          "Node: Right | f: 21.5 | g: 16.5 | h: 5\n"
          "Node: Up-Right | f: 22 | g: 18 | h: 4\n"
          "Node: Up-Right | f: 24.5 | g: 19.5 | h: 5\n"
          "Node: Down-Right | f: 25 | g: 21 | h: 4\n"
          "Node: Right | f: 26 | g: 22 | h: 4\n"
          "Node: Down-Right | f: 26.5 | g: 23.5 | h: 3\n"
          "Node: Down-Left | f: 27 | g: 25 | h: 2\n"
          "Node: Down-Left | f: 28.5 | g: 26.5 | h: 2\n"
          "Node: Down-Right | f: 29 | g: 28 | h: 1\n"
          "Node: Right | f: 29 | g: 29 | h: 0\n");

    freePath(path);
}

TEST_CASE("test_108")
{
    const int m = 3, n = 3;

    int maze[100][100] = {
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 0}};

    int startX = 0, startY = 0;
    int goalX = 2, goalY = 2;

    PathNode *path = findWarehousePath(maze, m, n, startX, startY, goalX, goalY, 2);

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());
    printPath(path);
    std::cout.rdbuf(oldCout);

    CHECK(buffer.str() ==
          "Solution Path:\n"
          "Node: Right | f: 3 | g: 1 | h: 2\n"
          "Node: Down-Right | f: 3.5 | g: 2.5 | h: 1\n"
          "Node: Down | f: 3.5 | g: 3.5 | h: 0\n");

    freePath(path);
}

TEST_CASE("test_109")
{
    const int m = 9, n = 10;

    int Maze1[100][100] = {
        {0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 1, 0, 0, 0, 1},
        {0, 1, 1, 0, 1, 0, 1, 1, 0, 0},
        {0, 1, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 1, 0, 0, 0, 1, 1},
        {0, 0, 0, 1, 1, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

    int startX = 0;
    int startY = 0;
    int goalX = 8;
    int goalY = 9;

    PathNode *OutPath;
    OutPath = findWarehousePath(Maze1, m, n, startX, startY, goalX, goalY, 2);
    printPath(OutPath);
    std::cout.rdbuf(oldCout);

    std::string expected =
        "Solution Path:\n"
        "Node: Down | f: 10 | g: 1 | h: 9\n"
        "Node: Down-Right | f: 10.5 | g: 2.5 | h: 8\n"
        "Node: Right | f: 10.5 | g: 3.5 | h: 7\n"
        "Node: Right | f: 10.5 | g: 4.5 | h: 6\n"
        "Node: Down-Right | f: 11 | g: 6 | h: 5\n"
        "Node: Down-Right | f: 11.5 | g: 7.5 | h: 4\n"
        "Node: Down | f: 12.5 | g: 8.5 | h: 4\n"
        "Node: Down-Right | f: 13 | g: 10 | h: 3\n"
        "Node: Right | f: 13 | g: 11 | h: 2\n"
        "Node: Down-Right | f: 13.5 | g: 12.5 | h: 1\n"
        "Node: Down-Right | f: 14 | g: 14 | h: 0\n";

    CHECK(buffer.str() == expected);

    freePath(OutPath);
}

TEST_CASE("test_110")
{
    const int m = 9, n = 10;

    int Maze1[100][100] = {
        {0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 1, 0, 0, 0, 1},
        {0, 1, 1, 0, 1, 0, 1, 1, 0, 0},
        {0, 1, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 1, 0, 0, 0, 1, 1},
        {0, 0, 0, 1, 1, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

    int startX = 0;
    int startY = 0;
    int goalX = 0;
    int goalY = 9;
    int r = 9, c = 10;

    PathNode *OutPath;
    OutPath = findWarehousePath(Maze1, r, c, startX, startY, goalX, goalY, 2);
    printPath(OutPath);
    std::cout.rdbuf(oldCout);

    std::string expected =
        "Solution Path:\n"
        "Node: Down | f: 10 | g: 1 | h: 9\n"
        "Node: Down-Right | f: 10.5 | g: 2.5 | h: 8\n"
        "Node: Right | f: 10.5 | g: 3.5 | h: 7\n"
        "Node: Right | f: 10.5 | g: 4.5 | h: 6\n"
        "Node: Right | f: 10.5 | g: 5.5 | h: 5\n"
        "Node: Right | f: 10.5 | g: 6.5 | h: 4\n"
        "Node: Right | f: 10.5 | g: 7.5 | h: 3\n"
        "Node: Right | f: 10.5 | g: 8.5 | h: 2\n"
        "Node: Up-Right | f: 11 | g: 10 | h: 1\n"
        "Node: Up-Right | f: 11.5 | g: 11.5 | h: 0\n";

    CHECK(buffer.str() == expected);

    freePath(OutPath);
}

TEST_CASE("test_111")
{
    const int m = 9, n = 10;

    int Maze1[100][100] = {
        {0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 1, 0, 0, 0, 1},
        {0, 1, 1, 0, 1, 0, 1, 1, 0, 0},
        {0, 1, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 1, 0, 0, 0, 1, 1},
        {0, 0, 0, 1, 1, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

    int startX = 4;
    int startY = 5;
    int goalX = 4;
    int goalY = 0;
    int r = 9, c = 10;

    PathNode *OutPath;
    OutPath = findWarehousePath(Maze1, r, c, startX, startY, goalX, goalY, 2);
    printPath(OutPath);
    std::cout.rdbuf(oldCout);

    std::string expected =
        "Solution Path:\n"
        "Node: Up-Left | f: 5.5 | g: 1.5 | h: 4\n"
        "Node: Up-Left | f: 6 | g: 3 | h: 3\n"
        "Node: Left | f: 6 | g: 4 | h: 2\n"
        "Node: Left | f: 7 | g: 5 | h: 2\n"
        "Node: Down-Left | f: 7.5 | g: 6.5 | h: 1\n"
        "Node: Down | f: 7.5 | g: 7.5 | h: 0\n";

    CHECK(buffer.str() == expected);

    freePath(OutPath);
}

TEST_CASE("test_112")
{
    const int m = 9, n = 10;

    int Maze1[100][100] = {
        {0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 1, 0, 0, 0, 1},
        {0, 1, 1, 0, 1, 0, 1, 1, 0, 0},
        {0, 1, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 1, 0, 0, 0, 1, 1},
        {0, 0, 0, 1, 1, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

    int startX = 4;
    int startY = 5;
    int goalX = 0;
    int goalY = 5;
    int r = 9, c = 10;

    PathNode *OutPath;
    OutPath = findWarehousePath(Maze1, r, c, startX, startY, goalX, goalY, 2);
    printPath(OutPath);
    std::cout.rdbuf(oldCout);

    std::string expected =
        "Solution Path:\n"
        "Node: Up-Right | f: 4.5 | g: 1.5 | h: 3\n"
        "Node: Up | f: 4.5 | g: 2.5 | h: 2\n"
        "Node: Up | f: 4.5 | g: 3.5 | h: 1\n"
        "Node: Up-Left | f: 5 | g: 5 | h: 0\n";

    CHECK(buffer.str() == expected);

    freePath(OutPath);
}

TEST_CASE("test_113")
{
    const int m = 9, n = 10;

    int Maze1[100][100] = {
        {0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 1, 0, 0, 0, 1},
        {0, 1, 1, 0, 1, 0, 1, 1, 0, 0},
        {0, 1, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 1, 0, 0, 0, 1, 1},
        {0, 0, 0, 1, 1, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

    int startX = 4;
    int startY = 8;
    int goalX = 5;
    int goalY = 0;
    int r = 9, c = 10;

    PathNode *OutPath;
    OutPath = findWarehousePath(Maze1, r, c, startX, startY, goalX, goalY, 2);
    printPath(OutPath);
    std::cout.rdbuf(oldCout);

    std::string expected =
        "Solution Path:\n"
        "Node: Up-Left | f: 8.5 | g: 1.5 | h: 7\n"
        "Node: Left | f: 8.5 | g: 2.5 | h: 6\n"
        "Node: Up-Left | f: 9 | g: 4 | h: 5\n"
        "Node: Left | f: 9 | g: 5 | h: 4\n"
        "Node: Left | f: 9 | g: 6 | h: 3\n"
        "Node: Left | f: 10 | g: 7 | h: 3\n"
        "Node: Left | f: 11 | g: 8 | h: 3\n"
        "Node: Down-Left | f: 11.5 | g: 9.5 | h: 2\n"
        "Node: Down | f: 11.5 | g: 10.5 | h: 1\n"
        "Node: Down | f: 11.5 | g: 11.5 | h: 0\n";

    CHECK(buffer.str() == expected);

    freePath(OutPath);
}

TEST_CASE("test_114")
{
    const int m = 9, n = 10;

    int Maze1[100][100] = {
        {0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 1, 0, 0, 0, 1},
        {0, 1, 1, 0, 1, 0, 1, 1, 0, 0},
        {0, 1, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 1, 0, 0, 0, 1, 1},
        {0, 0, 0, 1, 1, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

    int startX = 4;
    int startY = 8;
    int goalX = 0;
    int goalY = 3;
    int r = 9, c = 10;

    PathNode *OutPath;
    OutPath = findWarehousePath(Maze1, r, c, startX, startY, goalX, goalY, 2);
    printPath(OutPath);
    std::cout.rdbuf(oldCout);

    std::string expected =
        "Solution Path:\n"
        "Node: Up-Left | f: 5.5 | g: 1.5 | h: 4\n"
        "Node: Left | f: 5.5 | g: 2.5 | h: 3\n"
        "Node: Up-Left | f: 6 | g: 4 | h: 2\n"
        "Node: Left | f: 7 | g: 5 | h: 2\n"
        "Node: Left | f: 8 | g: 6 | h: 2\n"
        "Node: Left | f: 9 | g: 7 | h: 2\n"
        "Node: Left | f: 10 | g: 8 | h: 2\n"
        "Node: Up-Left | f: 12.5 | g: 9.5 | h: 3\n"
        "Node: Up-Right | f: 13 | g: 11 | h: 2\n"
        "Node: Right | f: 13 | g: 12 | h: 1\n"
        "Node: Right | f: 13 | g: 13 | h: 0\n";

    CHECK(buffer.str() == expected);

    freePath(OutPath);
}

TEST_CASE("test_115")
{
    const int m = 9, n = 10;

    int Maze1[100][100] = {
        {0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 1, 0, 0, 0, 1},
        {0, 1, 1, 0, 1, 0, 1, 1, 0, 0},
        {0, 1, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 1, 0, 0, 0, 1, 1},
        {0, 0, 0, 1, 1, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

    int startX = 8;
    int startY = 0;
    int goalX = 0;
    int goalY = 9;
    int r = 9, c = 10;

    PathNode *OutPath;
    OutPath = findWarehousePath(Maze1, r, c, startX, startY, goalX, goalY, 2);
    printPath(OutPath);
    std::cout.rdbuf(oldCout);

    std::string expected =
        "Solution Path:\n"
        "Node: Up-Right | f: 9.5 | g: 1.5 | h: 8\n"
        "Node: Up-Right | f: 10 | g: 3 | h: 7\n"
        "Node: Up-Right | f: 10.5 | g: 4.5 | h: 6\n"
        "Node: Right | f: 10.5 | g: 5.5 | h: 5\n"
        "Node: Up-Right | f: 11 | g: 7 | h: 4\n"
        "Node: Up-Right | f: 11.5 | g: 8.5 | h: 3\n"
        "Node: Up-Right | f: 12 | g: 10 | h: 2\n"
        "Node: Up-Right | f: 12.5 | g: 11.5 | h: 1\n"
        "Node: Up-Right | f: 13 | g: 13 | h: 0\n";

    CHECK(buffer.str() == expected);

    freePath(OutPath);
}

TEST_CASE("test_116")
{
    const int m = 9, n = 10;

    int Maze1[100][100] = {
        {0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 1, 0, 0, 0, 1},
        {0, 1, 1, 0, 1, 0, 1, 1, 0, 0},
        {0, 1, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 1, 0, 0, 0, 1, 1},
        {0, 0, 0, 1, 1, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

    int startX = 8;
    int startY = 0;
    int goalX = 0;
    int goalY = 7;
    int r = 9, c = 10;

    PathNode *OutPath;
    OutPath = findWarehousePath(Maze1, r, c, startX, startY, goalX, goalY, 2);
    printPath(OutPath);
    std::cout.rdbuf(oldCout);

    std::string expected =
        "Solution Path:\n"
        "Node: Up-Right | f: 8.5 | g: 1.5 | h: 7\n"
        "Node: Up-Right | f: 9 | g: 3 | h: 6\n"
        "Node: Up-Right | f: 9.5 | g: 4.5 | h: 5\n"
        "Node: Up | f: 9.5 | g: 5.5 | h: 4\n"
        "Node: Up-Right | f: 10 | g: 7 | h: 3\n"
        "Node: Up-Right | f: 10.5 | g: 8.5 | h: 2\n"
        "Node: Up-Right | f: 11 | g: 10 | h: 1\n"
        "Node: Up-Right | f: 11.5 | g: 11.5 | h: 0\n";

    CHECK(buffer.str() == expected);

    freePath(OutPath);
}

TEST_CASE("test_117")
{
    const int m = 9, n = 10;

    int Maze1[100][100] = {
        {0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 1, 0, 0, 0, 1},
        {0, 1, 1, 0, 1, 0, 1, 1, 0, 0},
        {0, 1, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 1, 0, 0, 0, 1, 1},
        {0, 0, 0, 1, 1, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

    int startX = 5;
    int startY = 7;
    int goalX = 0;
    int goalY = 3;
    int r = 9, c = 10;

    PathNode *OutPath;
    OutPath = findWarehousePath(Maze1, r, c, startX, startY, goalX, goalY, 2);
    printPath(OutPath);
    std::cout.rdbuf(oldCout);

    std::string expected =
        "Solution Path:\n"
        "Node: Down-Left | f: 7.5 | g: 1.5 | h: 6\n"
        "Node: Up-Left | f: 8 | g: 3 | h: 5\n"
        "Node: Up | f: 8 | g: 4 | h: 4\n"
        "Node: Up-Left | f: 8.5 | g: 5.5 | h: 3\n"
        "Node: Up-Left | f: 9 | g: 7 | h: 2\n"
        "Node: Left | f: 10 | g: 8 | h: 2\n"
        "Node: Left | f: 11 | g: 9 | h: 2\n"
        "Node: Up-Left | f: 13.5 | g: 10.5 | h: 3\n"
        "Node: Up-Right | f: 14 | g: 12 | h: 2\n"
        "Node: Right | f: 14 | g: 13 | h: 1\n"
        "Node: Right | f: 14 | g: 14 | h: 0\n";

    CHECK(buffer.str() == expected);

    freePath(OutPath);
}

TEST_CASE("test_118")
{
    const int m = 9, n = 10;

    int Maze1[100][100] = {
        {0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 1, 0, 0, 0, 1},
        {0, 1, 1, 0, 1, 0, 1, 1, 0, 0},
        {0, 1, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 1, 0, 0, 0, 1, 1},
        {0, 0, 0, 1, 1, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

    int startX = 7;
    int startY = 2;
    int goalX = 0;
    int goalY = 3;
    int r = 9, c = 10;

    PathNode *OutPath;
    OutPath = findWarehousePath(Maze1, r, c, startX, startY, goalX, goalY, 2);
    printPath(OutPath);
    std::cout.rdbuf(oldCout);

    std::string expected =
        "Solution Path:\n"
        "Node: Left | f: 8 | g: 1 | h: 7\n"
        "Node: Up-Left | f: 8.5 | g: 2.5 | h: 6\n"
        "Node: Up | f: 8.5 | g: 3.5 | h: 5\n"
        "Node: Up | f: 8.5 | g: 4.5 | h: 4\n"
        "Node: Up | f: 8.5 | g: 5.5 | h: 3\n"
        "Node: Up | f: 9.5 | g: 6.5 | h: 3\n"
        "Node: Up | f: 10.5 | g: 7.5 | h: 3\n"
        "Node: Up-Right | f: 11 | g: 9 | h: 2\n"
        "Node: Right | f: 11 | g: 10 | h: 1\n"
        "Node: Right | f: 11 | g: 11 | h: 0\n";

    CHECK(buffer.str() == expected);

    freePath(OutPath);
}
