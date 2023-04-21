/*
CS 438 Dots and Boxes
v3.cpp: 
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

int checkAdjacent(int r, int c)
{
}

void best()
{
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
    best();
    printBoardToFile();
    return 1;
}
