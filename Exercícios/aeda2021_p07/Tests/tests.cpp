#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "game.h"
#include "dictionary.h"
#include <fstream>

using testing::Eq;

TEST(test_1, a_CreateDictionary){
    ifstream f;
    f.open("dic.txt");
    if (!f) {
        cout << "File does not exist";
        EXPECT_EQ(true,false);
        return;
    }
    Dictionary d1;
    d1.readDictionary(f);
    f.close();
    BST<WordMeaning> wTree = d1.getWords();
    bool isEmp = wTree.isEmpty();
    EXPECT_EQ(false, isEmp);
    if (isEmp==false) {
        BSTItrIn<WordMeaning> it(wTree);
        it.advance();
        it.advance();
        EXPECT_EQ("island", it.retrieve().getWord());
    }
}

TEST(test_1, b_PrintDictionary){
    cout << "This test never fails! VERIFY information written in monitorr" << endl;
    EXPECT_TRUE(true);
    ifstream f;
    f.open("dic.txt");
    if (!f) {
        cout << "File does not exist";
        EXPECT_EQ(true,false);
        return;
    }
    Dictionary d1;
    d1.readDictionary(f);
    f.close();
    d1.print();
}

TEST(test_1, c_SearchForDictionary){
    ifstream f;
    f.open("dic.txt");
    if (!f) {
        cout << "File does not exist";
        EXPECT_EQ(true,false);
        return;
    }
    Dictionary d1;
    d1.readDictionary(f);
    f.close();
    EXPECT_EQ("feline mammal", d1.searchFor("cat"));
    EXPECT_THROW(d1.searchFor("window"), WordInexistent);
    try {
        string m=d1.searchFor("river");
    }
    catch (WordInexistent &e) {
        cout << "Caught Exception: Word Inexistent" << endl;
        EXPECT_EQ("potato", e.getWordBefore());
        EXPECT_EQ("tubercle vegetable", e.getMeaningBefore());
        EXPECT_EQ("sea", e.getWordAfter());
        EXPECT_EQ("large mass and extension of salt water", e.getMeaningAfter());
    }
}

TEST(test_1, d_CorrectDictionary){
    ifstream f;
    f.open("dic.txt");
    if (!f) {
        cout << "File does not exist";
        EXPECT_EQ(true,false);
        return;
    }
    Dictionary d1;
    d1.readDictionary(f);
    f.close();
    EXPECT_EQ(true,d1.correct("strawberry","red fruit"));
    EXPECT_EQ("red fruit", d1.searchFor("strawberry"));
    EXPECT_EQ(false,d1.correct("squirrel","small long-tailed rodent mammal"));
    BST<WordMeaning> wTree=d1.getWords();
    bool isEmp = wTree.isEmpty();
    EXPECT_EQ(false, isEmp);
    if (isEmp==false) {
        BSTItrIn<WordMeaning> it(wTree);
        it.advance(); it.advance(); it.advance();
        it.advance(); it.advance(); it.advance();
        EXPECT_EQ("squirrel", it.retrieve().getWord());
        EXPECT_EQ("small long-tailed rodent mammal", d1.searchFor("squirrel"));
    }
}

TEST(test_2, a_InitiateGame){
    vector<int> points;
    vector<bool> states;
    points.push_back(1); points.push_back(2); points.push_back(3);
    points.push_back(4); points.push_back(5); points.push_back(6); points.push_back(7);
    states.push_back(true); states.push_back(false); states.push_back(false);
    states.push_back(false); states.push_back(false); states.push_back(true); states.push_back(false);
    Game game1(2, points, states);
    EXPECT_EQ(1, game1.getGame().getRoot().getPoints());
}

TEST(test_2, b_WriteGame){
    vector<int> points;
    vector<bool> states;
    points.push_back(1); points.push_back(2); points.push_back(3);
    points.push_back(4); points.push_back(5); points.push_back(6);
    points.push_back(7); points.push_back(8); points.push_back(9);
    points.push_back(10); points.push_back(11); points.push_back(12);
    points.push_back(13); points.push_back(14); points.push_back(15);
    states.push_back(true); states.push_back(false); states.push_back(false);
    states.push_back(false); states.push_back(false); states.push_back(true);
    states.push_back(false); states.push_back(true); states.push_back(true);
    states.push_back(true); states.push_back(true); states.push_back(true);
    states.push_back(true); states.push_back(true); states.push_back(true);
    Game game1(3, points, states);
    string gameStr="1-true-0\n2-false-0\n3-false-0\n4-false-0\n5-false-0\n6-true-0\n7-false-0\n8-true-0\n9-true-0\n10-true-0\n11-true-0\n12-true-0\n13-true-0\n14-true-0\n15-true-0\n";
    EXPECT_EQ(gameStr, game1.writeGame());
}

TEST(test_2, c_DoMove){
    vector<int> points;
    vector<bool> states;
    points.push_back(1); points.push_back(2); points.push_back(3);
    points.push_back(4); points.push_back(5); points.push_back(6);
    points.push_back(7); points.push_back(8); points.push_back(9);
    points.push_back(10); points.push_back(11); points.push_back(12);
    points.push_back(13); points.push_back(14); points.push_back(15);
    states.push_back(true); states.push_back(false); states.push_back(false);
    states.push_back(false); states.push_back(false); states.push_back(true);
    states.push_back(false); states.push_back(true); states.push_back(true);
    states.push_back(true); states.push_back(true); states.push_back(true);
    states.push_back(true); states.push_back(true); states.push_back(true);
    Game game1(3, points, states);
    EXPECT_EQ(13, game1.move());
    EXPECT_EQ(8,game1.move());
}

TEST(test_2, d_MostVisited){
    vector<int> points;
    vector<bool> states;
    points.push_back(1); points.push_back(2); points.push_back(3);
    points.push_back(4); points.push_back(5); points.push_back(6);
    points.push_back(7); points.push_back(8); points.push_back(9);
    points.push_back(10); points.push_back(11); points.push_back(12);
    points.push_back(13); points.push_back(14); points.push_back(15);
    states.push_back(true); states.push_back(false); states.push_back(false);
    states.push_back(false); states.push_back(false); states.push_back(true);
    states.push_back(false); states.push_back(true); states.push_back(true);
    states.push_back(true); states.push_back(true); states.push_back(true);
    states.push_back(true); states.push_back(true); states.push_back(true);
    Game game1(3, points, states);
    game1.move(); game1.move(); game1.move();
    EXPECT_EQ(2, game1.mostVisited());
    game1.move(); game1.move(); game1.move();game1.move();
    EXPECT_EQ(4, game1.mostVisited());
}
