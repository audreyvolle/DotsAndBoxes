/*
CS 438 Dots and Boxes
v2.1.cpp: uses basic game logic but does not check neighbors
    1)AI should priority play "1" at a square with 3 positions already played
    2) next priority play square with 0 or 1 positions played
    3) least priority is square with 2 plays
*/
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <sstream>
const int MAXROW = 9;
const int MAXCOL = 9;
struct Square
{
    bool top;
    bool bottom;
    bool left;
    bool right;
    std::string owner;
};

Square squares[MAXROW][MAXCOL];

int read()
{
    FILE *fp;
    int dim;
    fp = fopen("squares.board", "r");

    if (fp == NULL)
    {
        std::cout << "Error opening file!" << std::endl;
        return -1;
    }

    // read and ignore the first line
    char line0[256];
    if (fgets(line0, sizeof(line0), fp) == NULL)
    {
        std::cout << "Error parsing file!" << std::endl;
        fclose(fp);
        return -1;
    }
    else
    {
        if (sscanf(line0, "%d", &dim) != 1)
        {
            std::cout << "Error reading integer!" << std::endl;
            fclose(fp);
            return -1;
        }
        std::cout << "Dimension: " << dim << std::endl;
    }

    // Read data lines
    for (int r = 0; r < dim; r++)
    {
        // Parse line
        char line[256];
        if (fgets(line, sizeof(line), fp) == NULL)
        {
            std::cout << "Error parsing file!" << std::endl;
            fclose(fp);
            return -1;
        }

        int top[MAXCOL], right[MAXCOL], bottom[MAXCOL], left[MAXCOL];
        char owner[MAXCOL][256];

        // Initialize owner array
        for (int c = 0; c < dim; c++)
        {
            strcpy(owner[c], "none");
        }

        // Parse the row data
        char *token = strtok(line, "}");
        for (int c = 0; c < dim; c++)
        {
            if (token == NULL)
            {
                std::cout << "Error parsing file!" << std::endl;
                fclose(fp);
                return -1;
            }
            if (sscanf(token, " {%d, %d, %d, %d, %255[^}]} ", &top[c], &right[c], &bottom[c], &left[c], owner[c]) != 5)
            {
                std::cout << "Error reading board data!" << std::endl;
                fclose(fp);
                return -1;
            }
            token = strtok(NULL, "}");
            squares[r][c].top = top[c];
            squares[r][c].right = right[c];
            squares[r][c].bottom = bottom[c];
            squares[r][c].left = left[c];
            squares[r][c].owner = std::string(owner[c]);
        }
    }
    fclose(fp);
    return dim;
}

void editAdjacent(int r, int c, std::string level, int dim)
{
    if (level == "top")
    {
        if (r != dim - 1)
        {
            squares[r + 1][c].bottom = 1;
        }
    }
    else if (level == "right")
    {
        if (c != dim - 1)
        {
            squares[r][c + 1].left = 1;
        }
    }
    else if (level == "bottom")
    {
        if (r != 0)
        {
            squares[r - 1][c].top = 1;
        }
    }
    else if (level == "left")
    {
        if (c != 0)
        {
            squares[r][c - 1].right = 1;
        }
    }
}

void betterBest(int dim)
{
    std::vector<std::pair<int, int>> move3;
    std::vector<std::pair<int, int>> move2;
    std::vector<std::pair<int, int>> move1;
    std::vector<std::pair<int, int>> move0;
    std::vector<std::string> move3val;
    std::string level[4];
    level[0] = "top";
    level[1] = "right";
    level[2] = "bottom";
    level[3] = "left";
    std::string best;
    int heuristic = -1;
    int bestheuristic = -1;
    int played;
    for (int r = 0; r < dim; r++)
    {
        for (int c = 0; c < dim; c++)
        {
            played = 0;
            // Check if the current square has 3 positions already played
            if (squares[r][c].top)
            {
                played++;
            }
            if (squares[r][c].right)
            {
                played++;
            }
            if (squares[r][c].bottom)
            {
                played++;
            }
            if (squares[r][c].left)
            {
                played++;
            }

            if (played == 3)
            {
                move3.push_back(std::make_pair(r, c));
            }
            if (played == 2)
            {
                move2.push_back(std::make_pair(r, c));
            }
            if (played == 1)
            {
                move1.push_back(std::make_pair(r, c));
            }
            if (played == 0)
            {
                move0.push_back(std::make_pair(r, c));
            }
        }
    }

    if (move3.size() != 0)
    {
        if (!squares[move3[0].first][move3[0].second].top)
        {
            squares[move3[0].first][move3[0].second].top = 1;
            editAdjacent(move3[0].first, move3[0].second, "top", dim);
            return;
        }
        if (!squares[move3[0].first][move3[0].second].right)
        {
            squares[move3[0].first][move3[0].second].right = 1;
            editAdjacent(move3[0].first, move3[0].second, "right", dim);
            return;
        }
        if (!squares[move3[0].first][move3[0].second].bottom)
        {
            squares[move3[0].first][move3[0].second].bottom = 1;
            editAdjacent(move3[0].first, move3[0].second, "bottom", dim);
            return;
        }
        if (!squares[move3[0].first][move3[0].second].left)
        {
            squares[move3[0].first][move3[0].second].left = 1;
            editAdjacent(move3[0].first, move3[0].second, "left", dim);
            return;
        }
    }
    else if (move1.size() != 0)
    {
        if (!squares[move1[0].first][move1[0].second].top)
        {
            squares[move1[0].first][move1[0].second].top = 1;
            editAdjacent(move1[0].first, move1[0].second, "top", dim);
            return;
        }
        if (!squares[move1[0].first][move1[0].second].right)
        {
            squares[move1[0].first][move1[0].second].right = 1;
            editAdjacent(move1[0].first, move1[0].second, "right", dim);
            return;
        }
        if (!squares[move1[0].first][move1[0].second].bottom)
        {
            squares[move1[0].first][move1[0].second].bottom = 1;
            editAdjacent(move1[0].first, move1[0].second, "bottom", dim);
            return;
        }
        if (!squares[move1[0].first][move1[0].second].left)
        {
            squares[move1[0].first][move1[0].second].left = 1;
            editAdjacent(move1[0].first, move1[0].second, "left", dim);
            return;
        }
    }
    else if (move0.size() != 0)
    {
        if (!squares[move0[0].first][move0[0].second].top)
        {
            squares[move0[0].first][move0[0].second].top = 1;
            editAdjacent(move0[0].first, move0[0].second, "top", dim);
            return;
        }
        if (!squares[move0[0].first][move0[0].second].right)
        {
            squares[move0[0].first][move0[0].second].right = 1;
            editAdjacent(move0[0].first, move0[0].second, "right", dim);
            return;
        }
        if (!squares[move0[0].first][move0[0].second].bottom)
        {
            squares[move0[0].first][move0[0].second].bottom = 1;
            editAdjacent(move0[0].first, move0[0].second, "bottom", dim);
            return;
        }
        if (!squares[move0[0].first][move0[0].second].left)
        {
            squares[move0[0].first][move0[0].second].left = 1;
            editAdjacent(move0[0].first, move0[0].second, "left", dim);
            return;
        }
    }
    else if (move2.size() != 0)
    {
        if (!squares[move2[0].first][move2[0].second].top)
        {
            squares[move2[0].first][move2[0].second].top = 1;
            editAdjacent(move2[0].first, move2[0].second, "top", dim);
            return;
        }
        if (!squares[move2[0].first][move2[0].second].right)
        {
            squares[move2[0].first][move2[0].second].right = 1;
            editAdjacent(move2[0].first, move2[0].second, "right", dim);
            return;
        }
        if (!squares[move2[0].first][move2[0].second].bottom)
        {
            squares[move2[0].first][move2[0].second].bottom = 1;
            editAdjacent(move2[0].first, move2[0].second, "bottom", dim);
            return;
        }
        if (!squares[move2[0].first][move2[0].second].left)
        {
            squares[move2[0].first][move2[0].second].left = 1;
            editAdjacent(move2[0].first, move2[0].second, "left", dim);
            return;
        }
    }
    else
    {
        return;
    }
}

void printBoardToFile(int dim)
{
    std::ofstream outfile("squares.board"); // Create an output file stream

    if (outfile.is_open())
    { // Check if the file is opened successfully
        /* Print the current board state to the file */
        outfile << dim << "\n";
        for (int r = 0; r < dim; r++)
        {
            for (int c = 0; c < dim; c++)
            {
                // Print the square's data in the specified format to the file
                outfile << "{"
                        << squares[r][c].top << ", "
                        << squares[r][c].right << ", "
                        << squares[r][c].bottom << ", "
                        << squares[r][c].left << ", "
                        << squares[r][c].owner << "} ";
            }
            outfile << "\n"; // Add a newline after each row
        }

        outfile.close(); // Close the output file
        std::cout << "Board state saved to squares.board." << std::endl;
    }
    else
    {
        std::cerr << "Error: Failed to open squares.board for writing." << std::endl;
    }
}
int main()
{
    int dim = read();
    if (dim != -1)
    {
        betterBest(dim);
        printBoardToFile(dim);
    }
    else
    {
        std::cout << "Error with file handling" << std::endl;
        return 1;
    }
}
