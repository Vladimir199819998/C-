// This program is able to recognize geometric shapes given in bitmask

#include <iostream>
#include <fstream>
using namespace std;

void deallocMem(int **&matrix, int &rows);
void parseFile(const char *filename, int **&matrix, int &cols, int &rows);
int findPerimeter(int **&matrix, int i, int j);
void outputToFile(int **&matrix, int &cols, int &rows);
short findCorners(int **&matrix, int i, int j);
void eleminateLines(int **&matrix, int i, int j);
short detectOddElements(int **&matrix, int i, int j);
short countCorners(int **&matrix, int i, int j);
void shapesCounterInFile(struct Shapes &shapes);

typedef struct Shapes
{
    short rectangles;
    short circles;
    short triangles;
    Shapes() : rectangles(0), circles(0), triangles(0) {}
} Shapes;

int main()
{
    Shapes shapes;
    short corners = 0;
    int **matrix = NULL;
    int rows = 0;
    int cols = 0;
    string inputFile;
    cout << "Enter the input file's name(input[1-3].txt): ";
    cin >> inputFile;
    parseFile(inputFile.c_str(), matrix, cols, rows);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matrix[i][j] == 1)
            {
                findPerimeter(matrix, i, j);
            }
        }
    }
    // outputToFile(matrix, cols, rows);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matrix[i][j] == 2)
            {
                findCorners(matrix, i, j);
            }
        }
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matrix[i][j] == 5)
            {
                if ((matrix[i - 1][j]) == 0 & (matrix[i + 1][j] == 0) & (matrix[i][j - 1] == 0) & (matrix[i][j + 1] == 0))
                    matrix[i][j] = 0;
                corners = detectOddElements(matrix, i, j);
                if (corners > 4)
                {
                    eleminateLines(matrix, i, j);
                }
            }
        }
    }
    // outputToFile(matrix, cols, rows);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matrix[i][j] == 4 | matrix[i][j] == 1)
            {
                corners = countCorners(matrix, i, j);
                if (corners == 0)
                {
                    shapes.rectangles++;
                }
                else if (corners == 4)
                {
                    shapes.circles++;
                }
                else
                {
                    shapes.triangles++;
                }
            }
        }
    }

    // outputToFile(matrix, cols, rows);
    shapesCounterInFile(shapes);
    deallocMem(matrix, rows);
    return 0;
}

void deallocMem(int **&matrix, int &rows)
{
    for (int i = 0; i < rows; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void parseFile(const char *filename, int **&matrix, int &cols, int &rows)
{
    fstream in;
    in.open(filename, ios_base::in);
    if (!in.is_open())
    {
        throw runtime_error("Cannot open this file!");
    }
    string line;
    char ch;
    while (getline(in, line))
    {
        rows++;
        if (rows == 1)
        {
            for (string::const_iterator it = line.begin(); it != line.end(); it++)
            {
                cols++;
            }
        }
    }
    matrix = new int *[rows];
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = new int[cols];
    }
    in.clear();
    in.seekg(0, ios::beg);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            in >> ch;
            if (ch != '\n' | ch != '\r')
            {
                int item = ch - '0';
                matrix[i][j] = item;
            }
            else
            {
                continue;
            }
        }
    }
    in.close();
}

int findPerimeter(int **&matrix, int i, int j)
{
    int EAST = j + 1;
    int WEST = j - 1;
    int NORTH = i - 1;
    int SOUTH = i + 1;
    int VISITED = 2;
    int INNER = 3;
    int EDGE = 0;
    int curr_i = i;
    int curr_j = j;
    if (matrix[curr_i][curr_j] == VISITED | matrix[curr_i][curr_j] == EDGE | matrix[curr_i][curr_j] == INNER)
        return 0;
    if (matrix[curr_i][EAST] == EDGE | matrix[curr_i][WEST] == EDGE | matrix[NORTH][curr_j] == EDGE | matrix[SOUTH][curr_j] == EDGE)
    {
        matrix[curr_i][curr_j] = VISITED;
        return 1 + findPerimeter(matrix, SOUTH, j) + findPerimeter(matrix, NORTH, j) + findPerimeter(matrix, i, WEST) + findPerimeter(matrix, i, EAST);
    }
    else
    {
        matrix[curr_i][curr_j] = INNER;
        return findPerimeter(matrix, SOUTH, j) + findPerimeter(matrix, NORTH, j) + findPerimeter(matrix, i, WEST) + findPerimeter(matrix, i, EAST);
    }
}

// void outputToFile(int **&matrix, int &cols, int &rows)
// {
//     char filename[64];
//     filename[63] = '\0';
//     cout << "Enter the file's name you want to output into: ";
//     cin >> filename;
//     fstream output(filename, ios_base::out | ios_base::binary);
//     if (!output.is_open())
//         throw runtime_error("Cannot open or create such a file!\n");
//     for (int i = 0; i < rows; i++)
//     {
//         for (int j = 0; j < cols; j++)
//         {
//             output << matrix[i][j];
//         }
//         output << "\n";
//     }
//     output.close();
// }

short findCorners(int **&matrix, int i, int j)
{
    int EAST = j + 1;
    int WEST = j - 1;
    int NORTH = i - 1;
    int SOUTH = i + 1;
    int OUTER = 0;
    int MARKED = 1;
    int INNER = 3;
    int CORNER = 5;
    int curr_i = i;
    int curr_j = j;

    if ((matrix[curr_i][curr_j] == OUTER) | (matrix[curr_i][curr_j] == MARKED) | (matrix[curr_i][curr_j] == CORNER))
        return 0;

    if (((matrix[curr_i][WEST] == OUTER) & (matrix[NORTH][curr_j] == OUTER) & (matrix[curr_i][EAST] == OUTER)) |
        ((matrix[NORTH][curr_j] == OUTER) & (matrix[curr_i][EAST] == OUTER) & (matrix[SOUTH][curr_j] == OUTER)) |
        ((matrix[curr_i][EAST] == OUTER) & (matrix[SOUTH][curr_j] == OUTER) & (matrix[curr_i][WEST] == OUTER)) |
        ((matrix[SOUTH][curr_j] == OUTER) & (matrix[curr_i][WEST] == OUTER) & (matrix[NORTH][curr_j] == OUTER)))
    {
        matrix[curr_i][curr_j] = CORNER;
        return short(1) + findCorners(matrix, SOUTH, curr_j) + findCorners(matrix, NORTH, curr_j) + findCorners(matrix, curr_i, EAST) + findCorners(matrix, curr_i, WEST);
    }
    else
    {
        matrix[curr_i][curr_j] = MARKED;
        return findCorners(matrix, SOUTH, curr_j) + findCorners(matrix, NORTH, curr_j) + findCorners(matrix, curr_i, EAST) + findCorners(matrix, curr_i, WEST);
    }
}

void shapesCounterInFile(struct Shapes &shapes)
{
    string filename;
    cout << "Enter the file name for shapes counter: ";
    cin >> filename;
    fstream file(filename, ios_base::out | ios_base::binary);
    if (!file.is_open())
        throw runtime_error("Cannot open or create such a file!\n");

    file << "Rectangles: " << shapes.rectangles << endl;
    file << "Circles: " << shapes.circles << endl;
    file << "Triangles: " << shapes.triangles << endl;
    file.close();
}

void eleminateLines(int **&matrix, int i, int j)
{
    int NORTH = i - 1;
    int SOUTH = i + 1;
    int WEST = j - 1;
    int EAST = j + 1;
    int OUTER = 0;
    if (matrix[i][j] == OUTER)
        return;

    if (matrix[i][j] != OUTER)
    {
        matrix[i][j] = OUTER;
        eleminateLines(matrix, NORTH, j);
        eleminateLines(matrix, SOUTH, j);
        eleminateLines(matrix, i, WEST);
        eleminateLines(matrix, i, EAST);
        eleminateLines(matrix, NORTH, EAST);
        eleminateLines(matrix, NORTH, WEST);
        eleminateLines(matrix, SOUTH, EAST);
        eleminateLines(matrix, SOUTH, WEST);
    }
}

short detectOddElements(int **&matrix, int i, int j)
{
    int NORTH = i - 1;
    int SOUTH = i + 1;
    int WEST = j - 1;
    int EAST = j + 1;
    int MARKED = 2;
    int INNER = 1;
    int CORNER = 5;
    int NEW_CORNER = 4;
    int OUTER = 0;
    if ((matrix[i][j] == OUTER) | (matrix[i][j] == MARKED) | (matrix[i][j] == NEW_CORNER))
    {
        return 0;
    }
    else if (matrix[i][j] == INNER)
    {
        matrix[i][j] = MARKED;
        return detectOddElements(matrix, NORTH, j) + detectOddElements(matrix, SOUTH, j) + detectOddElements(matrix, i, WEST) + detectOddElements(matrix, i, EAST) + detectOddElements(matrix, NORTH, WEST) + detectOddElements(matrix, SOUTH, WEST) + detectOddElements(matrix, SOUTH, EAST) + detectOddElements(matrix, NORTH, EAST);
    }
    else
    {
        matrix[i][j] = NEW_CORNER;
        return short(1) + detectOddElements(matrix, NORTH, j) + detectOddElements(matrix, SOUTH, j) + detectOddElements(matrix, i, WEST) + detectOddElements(matrix, i, EAST) + detectOddElements(matrix, NORTH, WEST) + detectOddElements(matrix, SOUTH, WEST) + detectOddElements(matrix, SOUTH, EAST) + detectOddElements(matrix, NORTH, EAST);
    }
}

short countCorners(int **&matrix, int i, int j)
{
    int CORNER = 4;
    int NORTH = i - 1;
    int SOUTH = i + 1;
    int WEST = j - 1;
    int EAST = j + 1;
    int OUTER = 0;
    int INNER = 2;
    int MARKED = 5;
    if ((matrix[i][j] == OUTER) | (matrix[i][j] == MARKED))
        return 0;

    else if (matrix[i][j] == CORNER)
    {
        matrix[i][j] = MARKED;
        return short(1) + countCorners(matrix, NORTH, j) + countCorners(matrix, SOUTH, j) + countCorners(matrix, i, WEST) + countCorners(matrix, i, EAST);
    }
    else
    {
        matrix[i][j] = MARKED;
        return countCorners(matrix, NORTH, j) + countCorners(matrix, SOUTH, j) + countCorners(matrix, i, WEST) + countCorners(matrix, i, EAST);
    }
}
