
#include "Dictionary.h"
#include "Boggle.h"

// This function is done.
Dictionary Boggle::GetDictionary()
{
    return dict;
}

// This function is done.
Dictionary Boggle::WordsFound()
{
    return wordsFound;
}

Boggle::Boggle()
{
    dict.LoadDictionaryFile("dictionary.txt");
}

Boggle::Boggle(string filename)
{
    dict.LoadDictionaryFile(filename);
}

void Boggle::SetBoard(string (*board)[4])
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            this->board[i][j] = board[i][j];
            visited[i][j] = 0;
        }
    }
}

void Boggle::SolveBoard(bool printBoard, ostream &output)
{
    wordsFound.MakeEmpty();

    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            SolveBoardHelper(i, j, 0, "", visited, printBoard, output);
        }
    }
}

void Boggle::SaveSolve(string filename)
{
    wordsFound.SaveDictionaryFile(filename);
}

void Boggle::PrintBoard(ostream &output)
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(visited[i][j] > 0)
            {
                output << " '" << board[i][j] << "' ";
            }
            else
            {
                output << "  " << board[i][j] << "  ";
            }
        }

        output << "\t";

        for(int j = 0; j < BOARD_SIZE; j++)
        {
            output << "  " << visited[i][j] << "  ";
        }

        output << endl;
    }

    output << endl;
}

void Boggle::SolveBoardHelper(int row, int col, int step, string path, int visited[][BOARD_SIZE], bool printBoard,
                              ostream &output)
{
    if(row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE)
    {
        return;
    }
    if(visited[row][col] > 0)
    {
        return;
    }
    if(!dict.IsPrefix(path + board[row][col]))
    {
        return;
    }

    visited[row][col] = step + 1;

    if(dict.IsWord(path + board[row][col]) && !wordsFound.IsWord(path + board[row][col]))
    {
        wordsFound.AddWord(path + board[row][col]);

        if(printBoard)
        {
            output << "Word: " << path + board[row][col] << endl;
            output << "Number of Words: " << wordsFound.WordCount() << endl;
            PrintBoard(output);
        }
        else
        {
            output << wordsFound.WordCount() << "\t";
            output << path + board[row][col] << endl;
        }
    }

    SolveBoardHelper(row - 1, col, step + 1, path + board[row][col], visited, printBoard, output);
    SolveBoardHelper(row - 1, col + 1, step + 1, path + board[row][col], visited, printBoard, output);
    SolveBoardHelper(row, col + 1, step + 1, path + board[row][col], visited, printBoard, output);
    SolveBoardHelper(row + 1, col + 1, step + 1, path + board[row][col], visited, printBoard, output);
    SolveBoardHelper(row + 1, col, step + 1, path + board[row][col], visited, printBoard, output);
    SolveBoardHelper(row + 1, col - 1, step + 1, path + board[row][col], visited, printBoard, output);
    SolveBoardHelper(row, col - 1, step + 1, path + board[row][col], visited, printBoard, output);
    SolveBoardHelper(row - 1, col - 1, step + 1, path + board[row][col], visited, printBoard, output);

    visited[row][col] = 0;
}