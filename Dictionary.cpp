#include "Dictionary.h"

// The copy constructor is complete.
// However, the operator= must be completed for it to work.
Dictionary::Dictionary(const Dictionary &otherDict)
{
    root = new Node;
    numWords = 0;
    *this = otherDict;
}

Dictionary::Dictionary()
{
    root = new Node;
    numWords = 0;
}

Dictionary::~Dictionary()
{
    // TO DO
}

Dictionary::Dictionary(string filename)
{
    root = new Node;
    LoadDictionaryFile(filename);
}

Dictionary& Dictionary::operator=(const Dictionary &otherDict)
{
    root = new Node;
    numWords = otherDict.numWords;

    for(int i = 0; i < NUM_CHARS; i++)
    {
        copyHelper(root->letter[i], otherDict.root->letter[i]);
    }

    return *this;
}

void Dictionary::LoadDictionaryFile(string filename)
{
    ifstream fin;
    fin.open(filename);

    string temp;
    while(!fin.eof())
    {
        getline(fin, temp);
        AddWord(temp);
    }
}

void Dictionary::SaveDictionaryFile(string filename)
{
    ofstream fout;
    fout.open(filename);

    if(!fout.is_open())
    {
        throw DictionaryError(filename + "failed to open");
    }

    SaveDictionaryHelper(root, "", fout);
}

void Dictionary::AddWord(string word)
{
    Node* currNode = root;

    for(int i = 0; i < word.length(); i++)
    {
        int localIndex = (int)word[i] - (int)'a';

        if(localIndex < 0 || localIndex >= NUM_CHARS)
        {
            throw DictionaryError("Invalid character");
        }

        if(currNode->letter[localIndex] == nullptr)
        {
            currNode->letter[localIndex] = new Node;
        }

        currNode = currNode->letter[localIndex];
    }

    currNode->isWord = true;
    numWords++;
}

void Dictionary::MakeEmpty()
{
    destroyHelper(root);
    root = new Node;
    numWords = 0;
}

bool Dictionary::IsWord(string word)
{
    Node* currNode = root;

    for(int i = 0; i < word.length(); i++)
    {
        int localIndex = (int)word[i] - (int)'a';

        if(localIndex < 0 || localIndex >= NUM_CHARS)
        {
            throw DictionaryError("Invalid character");
        }

        if(currNode->letter[localIndex] == nullptr)
        {
            return false;
        }

        currNode = currNode->letter[localIndex];
    }

    return currNode->isWord;
}

bool Dictionary::IsPrefix(string word)
{
    Node* currNode = root;

    for(int i = 0; i < word.length(); i++)
    {
        int localIndex = (int)word[i] - (int)'a';

        if(localIndex < 0 || localIndex >= NUM_CHARS)
        {
            throw DictionaryError("Invalid character");
        }

        if(currNode->letter[localIndex] == nullptr)
        {
            return false;
        }

        currNode = currNode->letter[localIndex];
    }

    return true;
}

int Dictionary::WordCount()
{
    return numWords;
}

void Dictionary::destroyHelper(Dictionary::Node *thisTree)
{
    if(thisTree == nullptr)
    {
        return;
    }

    for(int i = 0; i < NUM_CHARS; i++)
    {
        destroyHelper(thisTree->letter[i]);
        thisTree->letter[i] = nullptr;
    }

    delete thisTree;
}

void Dictionary::copyHelper(Dictionary::Node *&thisTree, Dictionary::Node *&otherTree)
{
    if (otherTree == nullptr)
    {
        thisTree = nullptr;
        return;
    }

    thisTree = new Node;
    for(int i = 0; i < NUM_CHARS; i++)
    {
        thisTree->letter[i] = otherTree->letter[i];
        copyHelper(thisTree->letter[i], otherTree->letter[i]);
    }
    thisTree->isWord = otherTree->isWord;
}

void Dictionary::SaveDictionaryHelper(Dictionary::Node *curr, string currPrefix, ofstream &outFile)
{
    if(curr == nullptr)
    {
        return;
    }

    if(curr->isWord)
    {
        outFile << currPrefix << endl;
    }

    for(int i = 0; i < NUM_CHARS; i++)
    {
        SaveDictionaryHelper(curr->letter[i], currPrefix + (char)(i + (int)'a'),outFile);
    }
}
