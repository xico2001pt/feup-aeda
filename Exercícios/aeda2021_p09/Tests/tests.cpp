#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include "bet.h"
#include "player.h"

using testing::Eq;

TEST(test_1, a_GenerateBet){
    vector<unsigned> vals;
    vals.push_back(30); vals.push_back(45); vals.push_back(22);
    vals.push_back(17); vals.push_back(45); vals.push_back(8);
    vals.push_back(30); vals.push_back(15); vals.push_back(24);
    vals.push_back(22);
    Bet b1;
    b1.generateBet(vals,6);
    EXPECT_EQ(6, b1.getNumbers().size());
}

TEST(test_1, b_VerifyBet){
    vector<unsigned> vals;
    vals.push_back(30); vals.push_back(45); vals.push_back(22);
    vals.push_back(17); vals.push_back(45); vals.push_back(8);
    vals.push_back(30); vals.push_back(15); vals.push_back(24);
    vals.push_back(22);
    Bet b1;
    b1.generateBet(vals,6);
    EXPECT_EQ(true, b1.contains(30));
    EXPECT_EQ(true, b1.contains(45));
    EXPECT_EQ(true, b1.contains(15));
    EXPECT_EQ(false, b1.contains(21));
}

TEST(test_1, c_CountBet){
    vector<unsigned> vals;
    vals.push_back(30); vals.push_back(45); vals.push_back(22);
    vals.push_back(17); vals.push_back(45); vals.push_back(8);
    vals.push_back(30); vals.push_back(15); vals.push_back(24);
    vals.push_back(22);
    Bet b1;
    b1.generateBet(vals,6);
    vector<unsigned> valsF;
    valsF.push_back(44); valsF.push_back(18); valsF.push_back(22);
    valsF.push_back(33); valsF.push_back(45); valsF.push_back(8);
    Bet key;
    key.generateBet(valsF,6);
    EXPECT_EQ(3,b1.countRights(key.getNumbers()));
}

TEST(test_2, a_PlayerAddBet){
    Player player1("Rui");
    vector<unsigned> vals;
    vals.push_back(30); vals.push_back(45); vals.push_back(22);
    vals.push_back(17); vals.push_back(45); vals.push_back(8);
    vals.push_back(30); vals.push_back(15); vals.push_back(24);
    vals.push_back(22);
    Bet b1;
    b1.generateBet(vals,6);
    player1.addBet(b1);
    vals.clear();
    vals.push_back(3); vals.push_back(44); vals.push_back(22);
    vals.push_back(15); vals.push_back(44); vals.push_back(3);
    vals.push_back(34); vals.push_back(20); vals.push_back(17);
    Bet b2;
    b2.generateBet(vals,6);
    player1.addBet(b2);
    vals.clear();
    vals.push_back(41); vals.push_back(32); vals.push_back(12);
    vals.push_back(15); vals.push_back(28); vals.push_back(32);
    vals.push_back(12); vals.push_back(41); vals.push_back(4);
    Bet b3;
    b3.generateBet(vals,6);
    player1.addBet(b3);
    EXPECT_EQ(3,player1.getNumBets());
}

TEST(test_2, b_PlayerBetsNumber){
    Player player1("Rui");
    vector<unsigned> vals;
    vals.push_back(30); vals.push_back(45); vals.push_back(22);
    vals.push_back(17); vals.push_back(45); vals.push_back(8);
    vals.push_back(30); vals.push_back(15); vals.push_back(24);
    vals.push_back(22);
    Bet b1;
    b1.generateBet(vals,6);
    player1.addBet(b1);
    vals.clear();
    vals.push_back(3); vals.push_back(44); vals.push_back(22);
    vals.push_back(15); vals.push_back(44); vals.push_back(3);
    vals.push_back(34); vals.push_back(20); vals.push_back(17);
    Bet b2;
    b2.generateBet(vals,6);
    player1.addBet(b2);
    vals.clear();
    vals.push_back(41); vals.push_back(32); vals.push_back(12);
    vals.push_back(15); vals.push_back(28); vals.push_back(32);
    vals.push_back(12); vals.push_back(41); vals.push_back(4);
    Bet b3;
    b3.generateBet(vals,6);
    player1.addBet(b3);
    EXPECT_EQ(2,player1.betsInNumber(22));
}

TEST(test_2, c_PlayerDrawnBets){
    Player player1("Rui");
    vector<unsigned> vals;
    vals.push_back(30); vals.push_back(45); vals.push_back(22);
    vals.push_back(17); vals.push_back(45); vals.push_back(8);
    vals.push_back(30); vals.push_back(18); vals.push_back(24);
    vals.push_back(22);
    Bet b1;
    b1.generateBet(vals,6);
    player1.addBet(b1);
    vals.clear();
    vals.push_back(3); vals.push_back(4); vals.push_back(22);
    vals.push_back(15); vals.push_back(4); vals.push_back(3);
    vals.push_back(34); vals.push_back(20); vals.push_back(17);
    Bet b2;
    b2.generateBet(vals,6);
    player1.addBet(b2);
    vals.clear();
    vals.push_back(45); vals.push_back(32); vals.push_back(18);
    vals.push_back(15); vals.push_back(8); vals.push_back(32);
    vals.push_back(18); vals.push_back(45); vals.push_back(33);
    Bet b3;
    b3.generateBet(vals,6);
    player1.addBet(b3);

    vector<unsigned> valsF;
    valsF.push_back(44); valsF.push_back(18); valsF.push_back(22);
    valsF.push_back(33); valsF.push_back(45); valsF.push_back(8);
    Bet key;
    key.generateBet(valsF,6);

    EXPECT_EQ(4,b1.countRights(key.getNumbers()));
    EXPECT_EQ(1,b2.countRights(key.getNumbers()));
    EXPECT_EQ(4,b3.countRights(key.getNumbers()));

    EXPECT_EQ(2,player1.drawnBets(key.getNumbers()).size());
}
