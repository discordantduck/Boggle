#ifndef BOGGLE_DICTIONARY_H
#define BOGGLE_DICTIONARY_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int NUM_CHARS = 26;

class DictionaryError
{
public:
    explicit DictionaryError(string msg)
    {
        this->msg = msg;
    }
    string Msg()
    {
        return msg;  // returns king of flavor
    }
private:
    string msg;
};

class Dictionary
{
public:
    // function: default constructor
    // pre: none
    // post: sets root to an empty node and numWords to 0
    Dictionary();
    ~Dictionary();  // I will not require this
    // function: copy constructor
    // pre: none
    // post: same as the default constructor, but also calls helper functions to copy the other dictionary
    Dictionary(const Dictionary& otherDict);    // copy constructor
    // function: normal constructor
    // pre: none
    // post: sets rot to an empty node and loads the words from the given filename into the dictionary
    explicit Dictionary(string filename);       // The keyword explicit is used to tell the compiler
                                                // that this is not a conversion constructor.

    // function: copies the given dictionary into the current dictionary and return the result
    // pre: none
    // post: root is set to an empty node, and numWords is set to otherDict's numWords
    Dictionary& operator=(const Dictionary& otherDict);
    // function: loads the words from the given dictionary into the trie using AddWord()
    // pre: given filename is valid
    // post: the trie is updated with the words from the given dictionary
    void LoadDictionaryFile(string filename);
    // function: saves the words from the trie into the given filename
    // pre: filename is valid
    // post: a file with the given filename has the content of the trie
    void SaveDictionaryFile(string filename);

    // function: adds a word to the trie
    // pre: given word is a lowercase alphabetical word
    // post: sets the node of the last letter of the word's isWord to true and increment numWords
    void AddWord(string word);
    // function: removes every word from the trie
    // pre: none
    // post: root is set to an empty node, and numWords is set to 0
    void MakeEmpty();

    // function: returns true if given string is a word in the trie, false otherwise
    // pre: given string is a lowercase alphabetical word
    // post: none
    bool IsWord(string word);
    // function: same as IsWord() but checks if the word is a prefix
    // pre: same as IsWord()
    // post: none
    bool IsPrefix(string word);
    // function: returns number of words in the trie
    // pre: none
    // post: none
    int WordCount();

private:
    class Node
    {
    public:
        Node* letter[NUM_CHARS] = {nullptr};
        bool isWord;

        Node()
        {
            isWord = false;
        }
    };

    Node* root;
    int numWords;

    // Any private methods you need/want
    // You may change these helpers if you want, but you don't need to.

    // function: removes every node in the tree
    // pre: none
    // post: none
    void destroyHelper(Node* thisTree);
    // function: copies the given trie to the current trie
    // pre: none
    // post: none
    void copyHelper(Node*& thisTree, Node*& otherTree);
    // function: saves every node to the given file, in order
    // pre: none
    // post: none
    void SaveDictionaryHelper(Node* curr, string currPrefix, ofstream& outFile);
};

#endif //BOGGLE_DICTIONARY_H
