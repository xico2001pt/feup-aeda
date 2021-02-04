#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "kid.h"
#include "game.h"
#include <vector>
#include <string>

using testing::Eq;


TEST(test, a_addKid){
    Kid c1("Rui",6);
    Kid c2("Ana",4);
    Kid c3("Rita",6);
    Kid c4("Joao",5);
    Kid c5("Marta",4);
    Kid c6("Vasco",5);

    Game game1;
    list<Kid> cc = game1.getKids();
    EXPECT_EQ(0, cc.size());

    game1.addKid(c1);
    game1.addKid(c2);
    game1.addKid(c3);
    game1.addKid(c4);
    game1.addKid(c5);
    game1.addKid(c6);

    cc = game1.getKids();
    EXPECT_EQ(6, cc.size());

    if (cc.size()==6) {
        Kid c = cc.front();
        EXPECT_EQ("Rui", c.getName());
        c = cc.back();
        EXPECT_EQ("Vasco", c.getName());
    }

    Game game2;
    cc.clear();
    cc.push_back(c1); cc.push_back(c2);
    cc.push_back(c3); cc.push_back(c4);
    game2.setKids(cc);

    cc = game2.getKids();
    EXPECT_EQ(4, cc.size());

    if (cc.size()==4) {
        Kid c = cc.front();
        EXPECT_EQ("Rui", c.getName());
        c = cc.back();
        EXPECT_EQ("Joao", c.getName());
    }
}


TEST(test, b_writeGame){
    Game game1;
    EXPECT_EQ("", game1.write());

    Kid c1("Rui",6);
    Kid c2("Ana",4);
    Kid c3("Vasco",5);
    game1.addKid(c1);
    game1.addKid(c2);
    game1.addKid(c3);
    cout << game1.write();
    EXPECT_EQ("Rui : 6\nAna : 4\nVasco : 5\n", game1.write());
}

TEST(test, c_loseGame){
    Kid c1("Rui",6);
    Kid c2("Ana",4);
    Kid c3("Rita",6);
    Kid c4("Joao",5);
    Kid c5("Marta",4);
    Kid c6("Vasco",5);

    Game game1;
    game1.addKid(c1);
    game1.addKid(c2);
    game1.addKid(c3);
    game1.addKid(c4);
    game1.addKid(c5);
    game1.addKid(c6);

    string s = "Pim Pam Pum cada bola mata um pra galinha e pro peru quem se livra es mesmo tu";
    Kid cx = game1.loseGame(s);
    EXPECT_EQ("Rui", cx.getName());

    Game game2;
    s = "Pim Pam Pum";
    game2.addKid(c1);
    game2.addKid(c2);
    game2.addKid(c3);
    cx = game2.loseGame(s);
    EXPECT_EQ("Ana", cx.getName());
}

TEST(test, d_reverseGame){
    Kid c1("Rui",6);
    Kid c2("Vasco",5);
    Kid c3("Ana",4);
    Kid c4("Joao",5);
    Kid c5("Marta",4);
    Kid c6("Rita",6);

    Game game1;
    game1.addKid(c1);
    game1.addKid(c2);
    game1.addKid(c3);
    game1.addKid(c4);
    game1.addKid(c5);
    game1.addKid(c6);

    EXPECT_EQ("Rui", game1.getKids().front().getName());
    EXPECT_EQ("Rita", game1.getKids().back().getName());

    list<Kid> invertida = game1.reverse();
    EXPECT_EQ("Rita", invertida.front().getName());
    EXPECT_EQ("Rui", invertida.back().getName());
}

TEST(test, e_divideGame){
    Kid c1("Rui",6);
    Kid c2("Ana",4);
    Kid c3("Rita",3);
    Kid c4("Joao",5);
    Kid c5("Marta",7);
    Kid c6("Vasco",5);
    Game game1;
    game1.addKid(c1);
    game1.addKid(c2);
    game1.addKid(c3);
    game1.addKid(c4);
    game1.addKid(c5);
    game1.addKid(c6);

    list<Kid> kidsOlder = game1.removeOlder(5);
    Game game2(kidsOlder);
    EXPECT_EQ("Rui : 6\nMarta : 7\n", game2.write());
}

TEST(test, f_GameEqual){
    list<Kid> kids1;
    kids1.push_back( Kid("Rui",6) );
    kids1.push_back( Kid("Ana",4) );
    kids1.push_back( Kid("Rita",3) );
    kids1.push_back( Kid("Joao",5) );
    kids1.push_back( Kid("Marta",7) );
    kids1.push_back( Kid("Vasco",5) );
    kids1.push_back( Kid("Ines",5) );

    Game game1(kids1);
    Game game2(kids1);
    EXPECT_EQ(true, game1 == game2);

    list<Kid> kids2;
    kids2.push_back( Kid("Rui",6) );
    kids2.push_back( Kid("Ana",4) );
    kids2.push_back( Kid("Rita",3) );
    kids2.push_back( Kid("Maria",5) );
    kids2.push_back( Kid("Marta",7) );
    kids2.push_back( Kid("Vasco",5) );
    kids2.push_back( Kid("Ines",5) );

    game2.setKids(kids2);
    EXPECT_EQ(false, game1 == game2);
}

TEST(test, g_Shuffle){
    list<Kid> kids;
    kids.push_back( Kid("Rui",6) );
    kids.push_back( Kid("Ana",4) );
    kids.push_back( Kid("Rita",3) );
    kids.push_back( Kid("Joao",5) );
    kids.push_back( Kid("Marta",7) );
    kids.push_back( Kid("Vasco",5) );
    kids.push_back( Kid("Ines",5) );

    Game game1;
    game1.setKids(kids);

    list<Kid> kids2 = game1.shuffle();
    EXPECT_EQ(7, kids2.size());

    list<Kid>::iterator it;
    it= find(kids2.begin(), kids2.end(),Kid("Rui",6));
    EXPECT_EQ("Rui", it->getName());

    it= find(kids2.begin(), kids2.end(),Kid("Ines",5));
    EXPECT_EQ("Ines", it->getName());

    Game game2(kids2);
    EXPECT_EQ(false, game1 == game2);
}