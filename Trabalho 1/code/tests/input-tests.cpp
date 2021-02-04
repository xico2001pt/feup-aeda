#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include "Input.h"
using testing::Eq;

TEST(input, trimString) {
    std::string str1 = "      Leading whitespace";
    input::trimString(str1);
    EXPECT_EQ(str1, "Leading whitespace");
    std::string str2 = "Trailing whitespace            ";
    input::trimString(str2);
    EXPECT_EQ(str2, "Trailing whitespace");
    std::string str3 = "Repeated         whitespace         within                 string";
    input::trimString(str3);
    EXPECT_EQ(str3, "Repeated whitespace within string");
    std::string str4 = "       Complete         example    ";
    input::trimString(str4);
    EXPECT_EQ(str4, "Complete example");
    std::string str5 = "                                     ";
    input::trimString(str5);
    EXPECT_EQ(str5, "");
    EXPECT_EQ(str5.empty(), true);
}

TEST(input, strToVar){
    std::string str1 = "4 a";
    int var1;
    std::string var2;
    EXPECT_EQ(input::strToVar(str1, var1), false);
    EXPECT_EQ(input::strToVar(str1, var2), false);
    std::string str2 = "4";
    EXPECT_EQ(input::strToVar(str2, var1), true);
    EXPECT_EQ(var1, 4);
    EXPECT_EQ(input::strToVar(str2, var2), true);
    EXPECT_EQ(var2, "4");
}

TEST(input, validateNickname){
    EXPECT_EQ(input::validateNickname(""), false);
    EXPECT_EQ(input::validateNickname("$\"/#!/"), false);
    EXPECT_EQ(input::validateNickname("ab/"), false);
    EXPECT_EQ(input::validateNickname("               "), false);
    EXPECT_EQ(input::validateNickname("examp le"), false);
    EXPECT_EQ(input::validateNickname("NicknameTooLargeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee"), false);

    EXPECT_EQ(input::validateNickname("Name123"), true);
    EXPECT_EQ(input::validateNickname("example123"), true);
}

TEST(input, validateName){
    EXPECT_EQ(input::validateName(""), false);
    EXPECT_EQ(input::validateName("$\"/#!/"), false);
    EXPECT_EQ(input::validateName("ab/"), false);
    EXPECT_EQ(input::validateName("First0 Second Third"), false);
    EXPECT_EQ(input::validateName("First Second Third"), true);
}

TEST(input, validateBirthDate){
    EXPECT_EQ(input::validateBirthDate("18/11/3125"), false);
}