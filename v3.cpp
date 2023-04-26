/*
CS 438 Dots and Boxes
v3.cpp: Extemely broken alpha-beta
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


// Heuristic function to evaluate game state
int evaluateGameState()
{
    int score = 0;
    return score;
}

// Alpha-beta pruning algorithm
int alphaBeta(int depth, int alpha, int beta, bool maximizingPlayer)
{
    // Base case: if game is over or reached maximum depth
    // Return the evaluation of the game state
    if (depth == 0 /*||  check for game over condition */)
    {
        return evaluateGameState();
    }

    if (maximizingPlayer)
    {
        int maxEval = INT_MIN;
        // ... Add your code for generating possible moves here ...
        for (/* loop through possible moves */)
        {
            // ... Add your code for making a move here ...

            int eval = alphaBeta(depth - 1, alpha, beta, false);
            maxEval = std::max(maxEval, eval);
            alpha = std::max(alpha, eval);
            if (beta <= alpha)
            {
                // Beta cut-off
                break;
            }

            // ... Add your code for undoing the move here ...
        }
        return maxEval;
    }
    else
    {
        int minEval = INT_MAX;
        // ... Add your code for generating possible moves here ...
        for (/* loop through possible moves */)
        {
            // ... Add your code for making a move here ...

            int eval = alphaBeta(depth - 1, alpha, beta, true);
            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);
            if (beta <= alpha)
            {
                // Alpha cut-off
                break;
            }

            // ... Add your code for undoing the move here ...
        }
        return minEval;
    }
}

// Function to make AI player's move using alpha-beta pruning
void makeAIMove(std::vector<std::pair<int, int>> move3, std::vector<std::pair<int, int>> move2, std::vector<std::pair<int, int>> move1, std::vector<std::pair<int, int>> move0)
{
    int bestMoveScore = INT_MIN;
    int bestMoveRow = -1;
    int bestMoveCol = -1;
    std::string bestMoveLevel = "";
    for (int i = 0; i < move3.size(); i++)
    {
        // ... Add your code for making a move here ...

        int moveScore = alphaBeta(3, INT_MIN, INT_MAX, false); // Depth of 3 for example, you can adjust as needed
        if (moveScore > bestMoveScore)
        {
            bestMoveScore = moveScore;
            bestMoveRow = move3[i].first;
            bestMoveCol = move3[i].second;
        }
    }
    if (bestMoveCol != -1)
    {
        // find the level
        squares[move3[bestMoveRow].first][move3[bestMoveRow].second]; //. = 1;
        editAdjacent(move3[0].first, move3[0].second, "");
        return;
    }
    for (int i = 0; i < move1.size(); i++)
    {
        // ... Add your code for making a move here ...

        int moveScore = alphaBeta(3, INT_MIN, INT_MAX, false); // Depth of 3 for example, you can adjust as needed
        if (moveScore > bestMoveScore)
        {
            bestMoveScore = moveScore;
            bestMoveRow = move1[i].first;
            bestMoveCol = move1[i].second;
        }
    }
    if (bestMoveCol != -1)
    {
        squares[move1[bestMoveRow].first][move1[bestMoveRow].second]; //. = 1;
        editAdjacent(move1[0].first, move1[0].second, "");
        return;
    }
    for (int i = 0; i < move0.size(); i++)
    {
        // ... Add your code for making a move here ...

        int moveScore = alphaBeta(3, INT_MIN, INT_MAX, false); // Depth of 3 for example, you can adjust as needed
        if (moveScore > bestMoveScore)
        {
            bestMoveScore = moveScore;
            bestMoveRow = move0[i].first;
            bestMoveCol = move0[i].second;
        }
    }
    if (bestMoveCol != -1)
    {
        squares[move0[bestMoveRow].first][move0[bestMoveRow].second]; //. = 1;
        editAdjacent(move0[0].first, move0[0].second, "");
        return;
    }
    for (int i = 0; i < move2.size(); i++)
    {
        // ... Add your code for making a move here ...

        int moveScore = alphaBeta(3, INT_MIN, INT_MAX, false); // Depth of 3 for example, you can adjust as needed
        if (moveScore > bestMoveScore)
        {
            bestMoveScore = moveScore;
            bestMoveRow = move2[i].first;
            bestMoveCol = move2[i].second;
        }
    }
    squares[move2[0].first][move2[0].second].bottom = 1;
    editAdjacent(move2[0].first, move2[0].second, "bottom");
    return;
}
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

int checkAdjacent(int r, int c, std::string level)
{
    // checks adjacent squares and returns a heuristic value
    int count = 0;
    if (level == "top")
    {
        if (r != 0)
        {
            if (squares[r - 1][c].top)
            {
                count++;
            }
            if (squares[r - 1][c].right)
            {
                count++;
            }
            if (squares[r - 1][c].left)
            {
                count++;
            }
            return count;
        }
    }
    else if (level == "right")
    {
        if (c != col - 1)
        {
            if (squares[r][c + 1].top)
            {
                count++;
            }
            if (squares[r][c + 1].right)
            {
                count++;
            }
            if (squares[r][c + 1].bottom)
            {
                count++;
            }
            return count;
        }
    }
    else if (level == "bottom")
    {
        if (r != row - 1)
        {
            if (squares[r + 1][c].left)
            {
                count++;
            }
            if (squares[r + 1][c].right)
            {
                count++;
            }
            if (squares[r + 1][c].bottom)
            {
                count++;
            }
            return count;
        }
    }
    else if (level == "left")
    {
        if (c != 0)
        {
            if (squares[r][c - 1].top)
            {
                count++;
            }
            if (squares[r][c - 1].left)
            {
                count++;
            }
            if (squares[r][c - 1].bottom)
            {
                count++;
            }
            return count;
        }
    }
    return 0;
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
    int bestRow = -1;
    int bestCol = -1;
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
    makeAIMove(move3, move2, move1, move0);
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
