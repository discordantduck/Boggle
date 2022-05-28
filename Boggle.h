#ifndef BOGGLE_BOGGLE_H
#define BOGGLE_BOGGLE_H

#include <string>
#include "Dictionary.h"

using namespace std;

const int BOARD_SIZE = 4;

class BoardNotInitialized {};

class Boggle {
public:
    // function: default constructor
    // pre: none
    // post: set the default dictionary to "dictionary.txt"
    Boggle();
    // function: normal constructor
    // pre: none
    // post: set the dictionary to given filename
    explicit Boggle(string filename);

    // function: copies the given board to the board matrix
    // pre: given board dimension is 4 x 4
    // post: the visited matrix is defaulted to 0
    void SetBoard(string board[BOARD_SIZE][BOARD_SIZE]);
    // function: calls SolveBoardHelper() for every index in the board matrix
    // pre: given output file is valid
    // post: wordsFound is set to empty every time this is called
    void SolveBoard(bool printBoard, ostream& output);
    // function: saves the wordsFound dictionary to the given filename
    // pre: none
    // post: none
    void SaveSolve(string filename);   // Saves all the words from the last solve.

    // function: returns the dict dictionary
    // pre: none
    // post: none
    Dictionary GetDictionary();
    // function: returns the wordsFound dictionary
    // pre: none
    // post: none
    Dictionary WordsFound();

private:
    Dictionary dict;
    Dictionary wordsFound;
    string board[BOARD_SIZE][BOARD_SIZE];
    int visited[BOARD_SIZE][BOARD_SIZE];

    // function: prints the board matrix and the visited matrix
    // pre: none
    // post: none
    void PrintBoard(ostream& output);
    // function: use recursive backtracking to find every word with the starting prefix at the given index and print the
    //           board if printBoard is true
    // pre: none
    // post: board and visited matrix aren't reset, and found words are added to the wordsFound dictionary
    void SolveBoardHelper(int row, int col, int step, string path, int visited[][BOARD_SIZE], bool printBoard,
                          ostream &output);
};

#endif //BOGGLE_BOGGLE_H