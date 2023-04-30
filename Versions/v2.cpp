/*
CS 438 Dots and Boxes
v2.cpp: uses basic game logic but does not check neighbors
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

const int row = 5;
const int col = 5;
struct Square
{
    bool top;
    bool bottom;
    bool left;
    bool right;
    std::string owner;
};

Square squares[row][col];

void read()
{
    FILE *fp;
    fp = fopen("squares.board", "r");

    if (fp == NULL)
    {
        std::cout << "Error opening file!" << std::endl;
        return;
    }

    // Read data lines
    for (int r = 0; r < row; r++)
    {
        // Parse line
        char line[256];
        if (fgets(line, sizeof(line), fp) == NULL)
        {
            std::cout << "Error parsing file!" << std::endl;
            fclose(fp);
            return;
        }

        int top[row], right[row], bottom[row], left[row];
        char owner[row][256];

        // Extract values from line
        if (sscanf(line, "{%d, %d, %d, %d, %255[^}]} {%d, %d, %d, %d, %255[^}]} {%d, %d, %d, %d, %255[^}]} {%d, %d, %d, %d, %255[^}]} {%d, %d, %d, %d, %255[^}]}", &top[0], &right[0], &bottom[0], &left[0], owner[0], &top[1], &right[1], &bottom[1], &left[1], owner[1], &top[2], &right[2], &bottom[2], &left[2], owner[2], &top[3], &right[3], &bottom[3], &left[3], owner[3], &top[4], &right[4], &bottom[4], &left[4], owner[4]) != 25)
        {
            std::cout << "Error parsing file!" << std::endl;
            fclose(fp);
            return;
        }

        for (int c = 0; c < col; c++)
        {
            squares[r][c].top = top[c];
            squares[r][c].right = right[c];
            squares[r][c].bottom = bottom[c];
            squares[r][c].left = left[c];
            squares[r][c].owner = std::string(owner[c]);
        }
    }

    fclose(fp);
}

void editAdjacent(int r, int c, std::string level)
{
    if (level == "top")
    {
        if (r != 0)
        {
            squares[r - 1][c].bottom = 1;
        }
    }
    else if (level == "right")
    {
        if (c != col - 1)
        {
            squares[r][c + 1].left = 1;
        }
    }
    else if (level == "bottom")
    {
        if (r != row - 1)
        {
            squares[r + 1][c].top = 1;
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


void betterBest()
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
    for (int r = 0; r < row; r++)
    {
        for (int c = 0; c < col; c++)
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
            editAdjacent(move3[0].first, move3[0].second, "top");
            return;
        }
        if (!squares[move3[0].first][move3[0].second].right)
        {
            squares[move3[0].first][move3[0].second].right = 1;
            editAdjacent(move3[0].first, move3[0].second, "right");
            return;
        }
        if (!squares[move3[0].first][move3[0].second].bottom)
        {
            squares[move3[0].first][move3[0].second].bottom = 1;
            editAdjacent(move3[0].first, move3[0].second, "bottom");
            return;
        }
        if (!squares[move3[0].first][move3[0].second].left)
        {
            squares[move3[0].first][move3[0].second].left = 1;
            editAdjacent(move3[0].first, move3[0].second, "left");
            return;
        }
    }
    else if (move1.size() != 0)
    {
        if (!squares[move1[0].first][move1[0].second].top)
        {
            squares[move1[0].first][move1[0].second].top = 1;
            editAdjacent(move1[0].first, move1[0].second, "top");
            return;
        }
        if (!squares[move1[0].first][move1[0].second].right)
        {
            squares[move1[0].first][move1[0].second].right = 1;
            editAdjacent(move1[0].first, move1[0].second, "right");
            return;
        }
        if (!squares[move1[0].first][move1[0].second].bottom)
        {
            squares[move1[0].first][move1[0].second].bottom = 1;
            editAdjacent(move1[0].first, move1[0].second, "bottom");
            return;
        }
        if (!squares[move1[0].first][move1[0].second].left)
        {
            squares[move1[0].first][move1[0].second].left = 1;
            editAdjacent(move1[0].first, move1[0].second, "left");
            return;
        }
    }
    else if (move0.size() != 0)
    {
        if (!squares[move0[0].first][move0[0].second].top)
        {
            squares[move0[0].first][move0[0].second].top = 1;
            editAdjacent(move0[0].first, move0[0].second, "top");
            return;
        }
        if (!squares[move0[0].first][move0[0].second].right)
        {
            squares[move0[0].first][move0[0].second].right = 1;
            editAdjacent(move0[0].first, move0[0].second, "right");
            return;
        }
        if (!squares[move0[0].first][move0[0].second].bottom)
        {
            squares[move0[0].first][move0[0].second].bottom = 1;
            editAdjacent(move0[0].first, move0[0].second, "bottom");
            return;
        }
        if (!squares[move0[0].first][move0[0].second].left)
        {
            squares[move0[0].first][move0[0].second].left = 1;
            editAdjacent(move0[0].first, move0[0].second, "left");
            return;
        }
    }
    else if (move2.size() != 0)
    {
        if (!squares[move2[0].first][move2[0].second].top)
        {
            squares[move2[0].first][move2[0].second].top = 1;
            editAdjacent(move2[0].first, move2[0].second, "top");
            return;
        }
        if (!squares[move2[0].first][move2[0].second].right)
        {
            squares[move2[0].first][move2[0].second].right = 1;
            editAdjacent(move2[0].first, move2[0].second, "right");
            return;
        }
        if (!squares[move2[0].first][move2[0].second].bottom)
        {
            squares[move2[0].first][move2[0].second].bottom = 1;
            editAdjacent(move2[0].first, move2[0].second, "bottom");
            return;
        }
        if (!squares[move2[0].first][move2[0].second].left)
        {
            squares[move2[0].first][move2[0].second].left = 1;
            editAdjacent(move2[0].first, move2[0].second, "left");
            return;
        }
    }
    else
    {
        return;
    }
}


void printBoardToFile()
{
    std::ofstream outfile("squares.board"); // Create an output file stream

    if (outfile.is_open())
    { // Check if the file is opened successfully
        /* Print the current board state to the file */
        for (int r = 0; r < row; r++)
        {
            for (int c = 0; c < col; c++)
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
    read();
    betterBest();
    printBoardToFile();
    return 1;
}