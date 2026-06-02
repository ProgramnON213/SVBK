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
    const int n = 5;
    double adjMatrix[100][100] = {
        {0, 2, 3, 0, 0}, // 0
        {0, 0, 0, 3, 0}, // 1
        {0, 0, 0, 1, 3}, // 2
        {0, 0, 0, 0, 1}, // 3
        {0, 0, 0, 0, 0}  // 4
    };

    int start = 0;
    int goal = 4;

    // findSocialPath
    PathNode *path = findSocialPath(adjMatrix, start, goal);
    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());
    printPath(path);
    std::cout.rdbuf(oldCout);
    CHECK(buffer.str() ==
          "Solution Path:\n"
          "Node: 0 | f: 2 | g: 0 | h: 2\n"
          "Node: 2 | f: 2 | g: 1 | h: 1\n"
          "Node: 4 | f: 2 | g: 2 | h: 0\n");

    freePath(path);
}

TEST_CASE("test_002")
{
    const int n = 4;
    double adjMatrix[100][100] = {
        {0, 1, 2, 0}, // 0
        {0, 0, 0, 3}, // 1
        {0, 0, 0, 1}, // 2
        {0, 0, 0, 0}  // 3
    };
    int start = 0;
    int goal = 3;

    PathNode *path = findSocialPath(adjMatrix, start, goal);
    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());
    printPath(path);
    std::cout.rdbuf(oldCout);

    CHECK(buffer.str() ==
          "Solution Path:\n"
          "Node: 0 | f: 2 | g: 0 | h: 2\n"
          "Node: 1 | f: 2 | g: 1 | h: 1\n"
          "Node: 3 | f: 2 | g: 2 | h: 0\n");

    freePath(path);
}

TEST_CASE("test_003")
{
    const int n = 6;
    double adjMatrix[100][100] = {
        {0, 2, 0, 0, 0, 0},
        {0, 0, 3, 0, 0, 0},
        {0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 2, 0},
        {0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0}};
    int start = 0;
    int goal = 5;

    PathNode *path = findSocialPath(adjMatrix, start, goal);
    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());
    printPath(path);
    std::cout.rdbuf(oldCout);

    CHECK(buffer.str() ==
          "Solution Path:\n"
          "Node: 0 | f: 5 | g: 0 | h: 5\n"
          "Node: 1 | f: 5 | g: 1 | h: 4\n"
          "Node: 2 | f: 5 | g: 2 | h: 3\n"
          "Node: 3 | f: 5 | g: 3 | h: 2\n"
          "Node: 4 | f: 5 | g: 4 | h: 1\n"
          "Node: 5 | f: 5 | g: 5 | h: 0\n");

    freePath(path);
}

TEST_CASE("test_004")
{
    const int n = 3;
    double adjMatrix[100][100] = {
        {0, 1, 0}, // 0
        {0, 0, 2}, // 1
        {0, 0, 0}  // 2
    };
    int start = 0;
    int goal = 2;

    PathNode *path = findSocialPath(adjMatrix, start, goal);
    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());
    printPath(path);
    std::cout.rdbuf(oldCout);

    CHECK(buffer.str() ==
          "Solution Path:\n"
          "Node: 0 | f: 2 | g: 0 | h: 2\n"
          "Node: 1 | f: 2 | g: 1 | h: 1\n"
          "Node: 2 | f: 2 | g: 2 | h: 0\n");

    freePath(path);
}

TEST_CASE("test_005")
{
    const int n = 4;
    double adjMatrix[100][100] = {
        {0, 3, 1, 0}, // 0
        {0, 0, 0, 2}, // 1
        {0, 0, 0, 4}, // 2
        {0, 0, 0, 0}  // 3
    };
    int start = 0;
    int goal = 3;

    PathNode *path = findSocialPath(adjMatrix, start, goal);
    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());
    printPath(path);
    std::cout.rdbuf(oldCout);

    
}

TEST_CASE("test_006")
{
    const int n = 6;
    double adjMatrix[100][100] = {0};
    // From S=0
    adjMatrix[0][1] = 1; // S -> A
    adjMatrix[0][2] = 4; // S -> B
    // From A=1
    adjMatrix[1][4] = 2; // A -> D
    adjMatrix[1][3] = 2; // A -> C
    // From B=2
    adjMatrix[2][4] = 1; // B -> D
    // From C=3
    adjMatrix[3][5] = 3; // C -> G
    // From D=4
    adjMatrix[4][5] = 1; // D -> G

    int start = 0; // S
    int goal = 5;  // G

    // Tìm đường đi
    PathNode *path = findSocialPath(adjMatrix, start, goal);

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());
    printPath(path);
    std::cout.rdbuf(oldCout);

    CHECK(buffer.str() ==
          "Solution Path:\n"
          "Node: 0 | f: 3 | g: 0 | h: 3\n"
          "Node: 1 | f: 3 | g: 1 | h: 2\n"
          "Node: 3 | f: 3 | g: 2 | h: 1\n"
          "Node: 5 | f: 3 | g: 3 | h: 0\n");
    freePath(path);
}

TEST_CASE("test_007")
{
    const int n = 6;
    double adjMatrix[100][100] = {
        {0, 7, 0, 0, 0, 0},
        {0, 0, 3, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 2},
        {0, 0, 0, 0, 0, 0}};

    int start = 0;
    int goal = 5;

    PathNode *path = findSocialPath(adjMatrix, start, goal);

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());
    printPath(path);
    std::cout.rdbuf(oldCout);

    CHECK(path == nullptr);
    CHECK(buffer.str() == "Solution Path:\n");

    freePath(path);
}

TEST_CASE("test_008")
{
    const int n = 100;
    double Mat[100][100] = {0};

    std::ifstream fin("tests/input/input1.txt");

    std::string line;
    while (std::getline(fin, line))
    {
        int u = 0, v = 0;

        if (sscanf(line.c_str(), "(%d,%d)", &u, &v) == 2)
        {
            if (u >= 0 && u < n && v >= 0 && v < n)
            {
                Mat[u][v] = 1.0;
            }
        }
    }

    fin.close();

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());
    int start = 0;
    int goal = 1;
    PathNode *OutPath;
    OutPath = findSocialPath(Mat, start, goal);
    printPath(OutPath);
    std::cout.rdbuf(oldCout);
    std::string expected =
        "Solution Path:\n"
        "Node: 0 | f: 4 | g: 0 | h: 4\n"
        "Node: 4 | f: 4 | g: 1 | h: 3\n"
        "Node: 47 | f: 4 | g: 2 | h: 2\n"
        "Node: 52 | f: 4 | g: 3 | h: 1\n"
        "Node: 1 | f: 4 | g: 4 | h: 0\n";

    CHECK(buffer.str() == expected);
}

TEST_CASE("test_009")
{
    const int n = 100;
    double Mat[100][100] = {0};

    std::ifstream fin("tests/input/input2.txt");

    std::string line;
    while (std::getline(fin, line))
    {
        int u = 0, v = 0;

        if (sscanf(line.c_str(), "(%d,%d)", &u, &v) == 2)
        {
            if (u >= 0 && u < n && v >= 0 && v < n)
            {
                Mat[u][v] = 1.0;
            }
        }
    }

    fin.close();

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

    int start = 1;
    int goal = 0;

    PathNode *OutPath = findSocialPath(Mat, start, goal);
    printPath(OutPath);

    std::cout.rdbuf(oldCout);

    std::string expected =
        "Solution Path:\n"
        "Node: 1 | f: 3 | g: 0 | h: 3\n"
        "Node: 11 | f: 3 | g: 1 | h: 2\n"
        "Node: 28 | f: 3 | g: 2 | h: 1\n"
        "Node: 0 | f: 3 | g: 3 | h: 0\n";

    CHECK(buffer.str() == expected);
}

TEST_CASE("test_010")
{
    const int n = 100;
    double Mat[100][100] = {0};

    std::ifstream fin("tests/input/input3.txt");

    std::string line;
    while (std::getline(fin, line))
    {
        int u = 0, v = 0;

        if (sscanf(line.c_str(), "(%d,%d)", &u, &v) == 2)
        {
            if (u >= 0 && u < n && v >= 0 && v < n)
            {
                Mat[u][v] = 1.0;
            }
        }
    }

    fin.close();

    std::ostringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());

    int start = 22;
    int goal = 28;

    PathNode *OutPath = findSocialPath(Mat, start, goal);
    printPath(OutPath);

    std::cout.rdbuf(oldCout);

    std::string expected =
        "Solution Path:\n"
        "Node: 22 | f: 4 | g: 0 | h: 4\n"
        "Node: 9 | f: 4 | g: 1 | h: 3\n"
        "Node: 17 | f: 4 | g: 2 | h: 2\n"
        "Node: 27 | f: 4 | g: 3 | h: 1\n"
        "Node: 28 | f: 4 | g: 4 | h: 0\n";

    CHECK(buffer.str() == expected);
}

TEST_CASE("test_011")
{
    const int n = 100;
    double Mat[100][100] = {0};

    std::ifstream fin("tests/input/input4.txt");

    std::string line;
    while (std::getline(fin, line))
    {
        int u = 0, v = 0;
        if (sscanf(line.c_str(), "(%d,%d)", &u, &v) == 2)
            Mat[u][v] = 1.0;
    }
    fin.close();

    std::ostringstream buffer;
    std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

    int start = 28;
    int goal = 22;
    PathNode *out = findSocialPath(Mat, start, goal);
    printPath(out);

    std::cout.rdbuf(old);

    std::string expected =
        "Solution Path:\n"
        "Node: 28 | f: 3 | g: 0 | h: 3\n"
        "Node: 27 | f: 3 | g: 1 | h: 2\n"
        "Node: 9 | f: 3 | g: 2 | h: 1\n"
        "Node: 22 | f: 3 | g: 3 | h: 0\n";

    CHECK(buffer.str() == expected);
}

TEST_CASE("test_012")
{
    const int n = 100;
    double Mat[100][100] = {0};

    std::ifstream fin("tests/input/input5.txt");

    std::string line;
    while (std::getline(fin, line))
    {
        int u = 0, v = 0;
        if (sscanf(line.c_str(), "(%d,%d)", &u, &v) == 2)
            Mat[u][v] = 1.0;
    }
    fin.close();

    std::ostringstream buffer;
    std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

    int start = 14;
    int goal = 19;
    PathNode *out = findSocialPath(Mat, start, goal);
    printPath(out);

    std::cout.rdbuf(old);

    std::string expected =
        "Solution Path:\n"
        "Node: 14 | f: 4 | g: 0 | h: 4\n"
        "Node: 7 | f: 4 | g: 1 | h: 3\n"
        "Node: 24 | f: 4 | g: 2 | h: 2\n"
        "Node: 30 | f: 4 | g: 3 | h: 1\n"
        "Node: 19 | f: 4 | g: 4 | h: 0\n";

    CHECK(buffer.str() == expected);
}

TEST_CASE("test_013")
{
    const int n = 100;
    double Mat[100][100] = {0};

    std::ifstream fin("tests/input/input6.txt");

    std::string line;
    while (std::getline(fin, line))
    {
        int u = 0, v = 0;
        if (sscanf(line.c_str(), "(%d,%d)", &u, &v) == 2)
            Mat[u][v] = 1.0;
    }
    fin.close();

    std::ostringstream buffer;
    std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

    int start = 0;
    int goal = 59;
    PathNode *out = findSocialPath(Mat, start, goal);
    printPath(out);

    std::cout.rdbuf(old);

    std::string expected =
        "Solution Path:\n"
        "Node: 0 | f: 3 | g: 0 | h: 3\n"
        "Node: 4 | f: 3 | g: 1 | h: 2\n"
        "Node: 55 | f: 3 | g: 2 | h: 1\n"
        "Node: 59 | f: 3 | g: 3 | h: 0\n";

    CHECK(buffer.str() == expected);
}

TEST_CASE("test_014")
{
    const int n = 100;
    double Mat[100][100] = {0};

    std::ifstream fin("tests/input/input7.txt");

    std::string line;
    while (std::getline(fin, line))
    {
        int u = 0, v = 0;
        if (sscanf(line.c_str(), "(%d,%d)", &u, &v) == 2)
            Mat[u][v] = 1.0;
    }
    fin.close();

    std::ostringstream buffer;
    std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

    int start = 18;
    int goal = 34;
    PathNode *out = findSocialPath(Mat, start, goal);
    printPath(out);

    std::cout.rdbuf(old);

    std::string expected =
        "Solution Path:\n"
        "Node: 18 | f: 5 | g: 0 | h: 5\n"
        "Node: 1 | f: 5 | g: 1 | h: 4\n"
        "Node: 11 | f: 5 | g: 2 | h: 3\n"
        "Node: 9 | f: 5 | g: 3 | h: 2\n"
        "Node: 22 | f: 5 | g: 4 | h: 1\n"
        "Node: 34 | f: 5 | g: 5 | h: 0\n";

    CHECK(buffer.str() == expected);
}
TEST_CASE("test_015")
{
    const int n = 100;
    double Mat[100][100] = {0};

    std::ifstream fin("tests/input/input8.txt");

    std::string line;
    while (std::getline(fin, line))
    {
        int u = 0, v = 0;
        if (sscanf(line.c_str(), "(%d,%d)", &u, &v) == 2)
            Mat[u][v] = 1.0;
    }
    fin.close();

    std::ostringstream buffer;
    std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());
    int start = 34;
    int goal = 18;
    PathNode *out = findSocialPath(Mat, start, goal);
    printPath(out);

    std::cout.rdbuf(old);

    std::string expected =
        "Solution Path:\n"
        "Node: 34 | f: 2 | g: 0 | h: 2\n"
        "Node: 22 | f: 2 | g: 1 | h: 1\n"
        "Node: 18 | f: 2 | g: 2 | h: 0\n";

    CHECK(buffer.str() == expected);
}
TEST_CASE("test_016")
{
    const int n = 100;
    double Mat[100][100] = {0};

    std::ifstream fin("tests/input/input9.txt");

    std::string line;
    while (std::getline(fin, line))
    {
        int u = 0, v = 0;
        if (sscanf(line.c_str(), "(%d,%d)", &u, &v) == 2)
            Mat[u][v] = 1.0;
    }
    fin.close();

    std::ostringstream buffer;
    std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

    int start = 37;
    int goal = 33;
    PathNode *out = findSocialPath(Mat, start, goal);
    printPath(out);

    std::cout.rdbuf(old);

    std::string expected =
        "Solution Path:\n"
        "Node: 37 | f: 5 | g: 0 | h: 5\n"
        "Node: 10 | f: 5 | g: 1 | h: 4\n"
        "Node: 20 | f: 5 | g: 2 | h: 3\n"
        "Node: 56 | f: 5 | g: 3 | h: 2\n"
        "Node: 52 | f: 5 | g: 4 | h: 1\n"
        "Node: 33 | f: 5 | g: 5 | h: 0\n";

    CHECK(buffer.str() == expected);
}

TEST_CASE("test_017")
{
    const int n = 100;
    double Mat[100][100] = {0};

    std::ifstream fin("tests/input/input10.txt");

    std::string line;
    while (std::getline(fin, line))
    {
        int u = 0, v = 0;
        if (sscanf(line.c_str(), "(%d,%d)", &u, &v) == 2)
            Mat[u][v] = 1.0;
    }
    fin.close();

    std::ostringstream buffer;
    std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

    int start = 33;
    int goal = 37;
    PathNode *out = findSocialPath(Mat, start, goal);
    printPath(out);

    std::cout.rdbuf(old);

    std::string expected =
        "Solution Path:\n"
        "Node: 33 | f: 2 | g: 0 | h: 2\n"
        "Node: 0 | f: 2 | g: 1 | h: 1\n"
        "Node: 37 | f: 2 | g: 2 | h: 0\n";

    CHECK(buffer.str() == expected);
}