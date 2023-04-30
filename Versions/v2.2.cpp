/*
CS 438 Dots and Boxes
v2.2.cpp: uses basic game logic but and check neighbors
    1) AI should priority play "1" at a square with 3 positions already played
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

int checkAdjacent(int r, int c, std::string level, int dim)
{
    /*returns heurisic "h"
    2 = best Play (that play would complete the adjacent box)
    1 = fine play, 0 or 1 plays in the adjacent box
    0 = worst play. 2 plays in that box. The other player would complete this box
    */
    int played = 0;
    int h = 0;
    if (level == "top")
    {
        if (r != dim - 1)
        {
            if (squares[r + 1][c].top)
            {
                played++;
            }
            if (squares[r + 1][c].right)
            {
                played++;
            }
            if (squares[r + 1][c].bottom)
            {
                played++;
            }
            if (squares[r + 1][c].left)
            {
                played++;
            }
        }
    }
    else if (level == "right")
    {
        if (c != dim - 1)
        {
            if (squares[r][c + 1].top)
            {
                played++;
            }
            if (squares[r][c + 1].right)
            {
                played++;
            }
            if (squares[r][c + 1].bottom)
            {
                played++;
            }
            if (squares[r][c + 1].left)
            {
                played++;
            }
        }
    }
    else if (level == "bottom")
    {
        if (r != 0)
        {
            if (squares[r - 1][c].top)
            {
                played++;
            }
            if (squares[r - 1][c].right)
            {
                played++;
            }
            if (squares[r - 1][c].bottom)
            {
                played++;
            }
            if (squares[r - 1][c].left)
            {
                played++;
            }
        }
    }
    else if (level == "left")
    {
        if (c != 0)
        {
            if (squares[r][c - 1].top)
            {
                played++;
            }
            if (squares[r][c - 1].right)
            {
                played++;
            }
            if (squares[r][c - 1].bottom)
            {
                played++;
            }
            if (squares[r][c - 1].left)
            {
                played++;
            }
        }
    }

    // evaluate played to a heuristic
    if (played == 3)
    {
        h = 2;
    }
    else if (played == 1 || played == 0)
    {
        h = 1;
    }
    else if (played == 2)
    {
        h = 0;
    }
    return h;
}
void play(int r, int c, std::string level, int dim)
{
    std::cout << "Played: " << r << ", " << c << " " << level << std::endl;
    if (level == "top")
    {
        squares[r][c].top = 1;
    }
    else if (level == "right")
    {
        squares[r][c].right = 1;
    }
    else if (level == "bottom")
    {
        squares[r][c].bottom = 1;
    }
    else if (level == "left")
    {
        squares[r][c].left = 1;
    }
}

void betterBest(int dim)
{
    std::vector<std::pair<int, int>> move3;
    std::vector<std::string> move3levels;
    std::vector<std::pair<int, int>> move2;
    std::vector<std::string> move2levels;
    std::vector<std::pair<int, int>> move1;
    std::vector<std::string> move1levels;
    std::vector<std::pair<int, int>> move0;
    std::vector<std::string> move0levels;
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
            std::vector<std::string> open;
            played = 0;
            // Check if the current square has 3 positions already played
            if (squares[r][c].top)
            {
                played++;
            }
            else
            {
                open.push_back("top");
            }
            if (squares[r][c].right)
            {
                played++;
            }
            else
            {
                open.push_back("right");
            }
            if (squares[r][c].bottom)
            {
                played++;
            }
            else
            {
                open.push_back("bottom");
            }
            if (squares[r][c].left)
            {
                played++;
            }
            else
            {
                open.push_back("left");
            }

            if (played == 3)
            {
                move3.push_back(std::make_pair(r, c));
                move3levels.push_back(open[0]);
            }
            if (played == 2)
            {
                move2.push_back(std::make_pair(r, c));
                move2levels.push_back(open[0]);
                move2.push_back(std::make_pair(r, c));
                move2levels.push_back(open[1]);
            }
            if (played == 1)
            {
                move1.push_back(std::make_pair(r, c));
                move1levels.push_back(open[0]);
                move1.push_back(std::make_pair(r, c));
                move1levels.push_back(open[1]);
                move1.push_back(std::make_pair(r, c));
                move1levels.push_back(open[2]);
            }
            if (played == 0)
            {
                move0.push_back(std::make_pair(r, c));
                move0levels.push_back(open[0]);
                move0.push_back(std::make_pair(r, c));
                move0levels.push_back(open[1]);
                move0.push_back(std::make_pair(r, c));
                move0levels.push_back(open[2]);
                move0.push_back(std::make_pair(r, c));
                move0levels.push_back(open[3]);
            }
        }
    }
    int moveVal = -1;
    if (move3.size() != 0)
    {
        std::vector<std::pair<int, int>> move3Ad;
        std::vector<std::string> move3levelsAd;
        for (int i = 0; i < move3.size(); i++)
        {
            moveVal = checkAdjacent(move3[i].first, move3[i].second, move3levels[i], dim);
            if (moveVal == 2)
            {
                play(move3[i].first, move3[i].second, move3levels[i], dim);
                editAdjacent(move3[i].first, move3[i].second, move3levels[i], dim);
                return;
            }
            else if (moveVal == 1)
            {
                // decent move push to front of stack
                move3Ad.insert(move3Ad.begin(), std::make_pair(move3[i].first, move3[i].second));
                move3levelsAd.insert(move3levelsAd.begin(), move3levels[i]);
            }
            else
            {
                // bad move push to back of stack
                move3Ad.push_back(std::make_pair(move3[i].first, move3[i].second));
                move3levelsAd.push_back(move3levels[i]);
            }
        }
        play(move3Ad[0].first, move3Ad[0].second, move3levelsAd[0], dim);
        editAdjacent(move3Ad[0].first, move3Ad[0].second, move3levelsAd[0], dim);
        return;
    }
    else if (move1.size() != 0)
    {
        std::vector<std::pair<int, int>> move1Ad;
        std::vector<std::string> move1levelsAd;
        for (int i = 0; i < move1.size(); i++)
        {
            moveVal = checkAdjacent(move1[i].first, move1[i].second, move1levels[i], dim);
            if (moveVal == 2)
            {
                play(move1[i].first, move1[i].second, move1levels[i], dim);
                editAdjacent(move1[i].first, move1[i].second, move1levels[i], dim);
                return;
            }
            else if (moveVal == 1)
            {
                // decent move push to front of stack
                move1Ad.insert(move1Ad.begin(), std::make_pair(move1[i].first, move1[i].second));
                move1levelsAd.insert(move1levelsAd.begin(), move1levels[i]);
            }
            else
            {
                // bad move push to back of stack
                move1Ad.push_back(std::make_pair(move1[i].first, move1[i].second));
                move1levelsAd.push_back(move1levels[i]);
            }
        }
        play(move1Ad[0].first, move1Ad[0].second, move1levelsAd[0], dim);
        editAdjacent(move1Ad[0].first, move1Ad[0].second, move1levelsAd[0], dim);
        return;
    }
    else if (move0.size() != 0)
    {
        std::vector<std::pair<int, int>> move0Ad;
        std::vector<std::string> move0levelsAd;
        for (int i = 0; i < move0.size(); i++)
        {
            moveVal = checkAdjacent(move0[i].first, move0[i].second, move0levels[i], dim);
            if (moveVal == 2)
            {
                play(move0[i].first, move0[i].second, move0levels[i], dim);
                editAdjacent(move0[i].first, move0[i].second, move0levels[i], dim);
                return;
            }
            else if (moveVal == 1)
            {
                // decent move push to front of stack
                move0Ad.insert(move0Ad.begin(), std::make_pair(move0[i].first, move0[i].second));
                move0levelsAd.insert(move0levelsAd.begin(), move0levels[i]);
            }
            else
            {
                // bad move push to back of stack
                move0Ad.push_back(std::make_pair(move0[i].first, move0[i].second));
                move0levelsAd.push_back(move0levels[i]);
            }
        }
        play(move0Ad[0].first, move0Ad[0].second, move0levelsAd[0], dim);
        editAdjacent(move0Ad[0].first, move0Ad[0].second, move0levelsAd[0], dim);
        return;
    }
    else if (move2.size() != 0)
    {
        std::vector<std::pair<int, int>> move2Ad;
        std::vector<std::string> move2levelsAd;
        for (int i = 0; i < move2.size(); i++)
        {
            moveVal = checkAdjacent(move2[i].first, move2[i].second, move2levels[i], dim);
            if (moveVal == 2)
            {
                play(move2[i].first, move2[i].second, move2levels[i], dim);
                editAdjacent(move2[i].first, move2[i].second, move2levels[i], dim);
                return;
            }
            else if (moveVal == 1)
            {
                // decent move push to front of stack
                move2Ad.insert(move2Ad.begin(), std::make_pair(move2[i].first, move2[i].second));
                move2levelsAd.insert(move2levelsAd.begin(), move2levels[i]);
            }
            else
            {
                // bad move push to back of stack
                move2Ad.push_back(std::make_pair(move2[i].first, move2[i].second));
                move2levelsAd.push_back(move2levels[i]);
            }
        }
        play(move2Ad[0].first, move2Ad[0].second, move2levelsAd[0], dim);
        editAdjacent(move2Ad[0].first, move2Ad[0].second, move2levelsAd[0], dim);
        return;
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