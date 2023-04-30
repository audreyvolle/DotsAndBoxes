/*
CS 438 Dots and Boxes
v1.cpp: very very basic fixed (dynamic board sizes and 0,0 is bottom left) implementation that plays the first blank move that it finds (no logic)
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

void best(int dim)
{
    // find blank move and edit
    for (int r = 0; r < dim; r++)
    {
        for (int c = 0; c < dim; c++)
        {
            if (squares[r][c].top == 0)
            {
                squares[r][c].top = 1;
                std::cout << r << " " << c << " "
                          << "top" << std::endl;
                editAdjacent(r, c, "top", dim);
                return;
            }
            if (squares[r][c].right == 0)
            {
                squares[r][c].right = 1;
                std::cout << r << " " << c << " "
                          << "right" << std::endl;
                editAdjacent(r, c, "right", dim);
                return;
            }
            if (squares[r][c].bottom == 0)
            {
                squares[r][c].bottom = 1;
                std::cout << r << " " << c << " "
                          << "bottom" << std::endl;
                editAdjacent(r, c, "bottom", dim);
                return;
            }
            if (squares[r][c].left == 0)
            {
                squares[r][c].left = 1;
                std::cout << r << " " << c << " "
                          << "left" << std::endl;
                editAdjacent(r, c, "left", dim);
                return;
            }
        }
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
        best(dim);
        printBoardToFile(dim);
    }
    else
    {
        std::cout << "Error with file handling" << std::endl;
        return 1;
    }
}