#include <iostream>
#include <string>
#include <fstream>
#include "dictionary.h"
#include "bst.h"

using namespace std;

BST<WordMeaning> Dictionary::getWords() const {
    return words;
}

bool WordMeaning::operator < (const WordMeaning &wm1) const {
    return this->word < wm1.getWord();
}

void Dictionary::readDictionary(ifstream &f) {
    string word, meaning;
     while (!f.eof()) {
         getline(f, word);
         getline(f, meaning);
         words.insert(WordMeaning(word, meaning));
     }
}

string Dictionary::searchFor(string word) const {
    WordMeaning wm = words.find(WordMeaning(word,""));
    if (wm.getWord() != "") return wm.getMeaning();

    // Not found
    BSTItrIn<WordMeaning> it(words);
    string wB = "", mB = "";
    while (!it.isAtEnd() && it.retrieve().getWord() < word) {
        wB = it.retrieve().getWord();
        mB = it.retrieve().getMeaning();
        it.advance();
    }
    string wA = "", mA = "";
    if (!it.isAtEnd()) {
        wA = it.retrieve().getWord();
        mA = it.retrieve().getMeaning();
    }
    throw WordInexistent(wB, mB, wA, mA);
}

bool Dictionary::correct(string word, string newMeaning) {
    WordMeaning wm = words.find(WordMeaning(word,""));
    bool exists = (wm.getWord() != "");
    if (exists) {
        words.remove(WordMeaning(word,""));
    }
    words.insert(WordMeaning(word,newMeaning));
    return exists;
}

void Dictionary::print() const {
    BSTItrIn<WordMeaning> it(words);
    while (!it.isAtEnd()) {
        cout << it.retrieve().getWord() << endl << it.retrieve().getMeaning() << endl;
        it.advance();
    }
}

