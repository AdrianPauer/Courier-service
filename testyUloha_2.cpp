// Copyright 2005, Google Inc.
// All rights reserved.

#include <iostream>
#include "gtest/gtest.h"

#include "2_Package.h"

using namespace ::testing;

//Uloha 2.
TEST(TestSecondTask, emptyPackage) {
    Package zasielka = Package("");
  ASSERT_EQ(zasielka.getShippingAddress(),"00000#UNDEFINED");
  ASSERT_TRUE(zasielka.putPackage("150.2\n  02801#SLOVAKIA   "));
  ASSERT_EQ(zasielka.getShippingAddress(),"02801#SLOVAKIA" );
  ASSERT_EQ(zasielka.getWeight(),float(150.2));
}

TEST(TestSecondTask,wrongWeight) {
    Package zasielka = Package("-150.2\n  02801#SLOVAKIA   ");
    ASSERT_EQ(zasielka.getTown(),"");
}
TEST(TestSecondTask, wrongAdress) {
    Package zasielka = Package("150.2\n  02801#SL5VAKIA   ");
    ASSERT_EQ(zasielka.getTown(),"");
}

TEST(TestSecondTask, townsAfterChangeNotAllowed) {
    Package zasielka = Package("150.2\n  02801#SL5VAKIA   ");
    ASSERT_EQ(zasielka.getTown(),"");
    zasielka.putPackage("15\n  02801#SLOVAKIA   ");
    ASSERT_EQ(zasielka.getTown(),"MARTIN");
    ASSERT_NE(zasielka.getWeight(),float(0));
    zasielka.putPackage("15\n  05699#SLOVAKIA   ");
    ASSERT_EQ(zasielka.getTown(),"MARTIN");
}
TEST(TestSecondTask,Town) {
    Package zasielka = Package("");
    zasielka.putPackage("15\n  05699#SLOVAKIA   ");
    ASSERT_EQ(zasielka.getTown(),"POPRAD");
}
TEST(TestSecondTask,lesser) {
    Package zasielka = Package("");
    Package zasielka2 = Package("15\n05699#CZECHIA   ");
    Package zasielka3 = Package("20\n05699#CZECHIA   ");
    ASSERT_TRUE(zasielka < zasielka2);
}
TEST(TestSecondTask,greater) {
    Package zasielka = Package("15.0001\n05699#CZECHIA   ");
    Package zasielka2 = Package("15\n05699#CZECHIA   ");
    ASSERT_TRUE(zasielka > zasielka2);
}