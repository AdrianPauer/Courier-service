
#include <iostream>
#include "gtest/gtest.h"

#include "1_Address.h"

using namespace ::testing;

//Uloha 1.
TEST(TestFirstTask,spaces) {
    Address adresa;
    ASSERT_EQ(adresa.removeSpaces("      c++       "), "c++");
}
TEST(TestFirstTask,onlySpaces) {
    Address adresa;
    std::string A = adresa.removeSpaces("          ");
    ASSERT_EQ(A, "");
}
TEST(TestFirstTask,constructor) {
    Address adresa;
    ASSERT_EQ("00000#UNDEFINED", adresa.getAddress());
}
TEST(TestFirstTask,wrongDash) {
    Address adresa;
    std::string vynimka;
    try{adresa.putAddress("00006*CZECHIA");}
    catch(WrongInput e){
        vynimka = e.message();}
    ASSERT_EQ(vynimka,"Address has wrong format");
}
TEST(TestFirstTask,wrongCountry) {
    Address adresa;
    std::string vynimka;
    try{adresa.putAddress("02801#S**VAKIA");}
    catch(WrongInput e){
        vynimka = e.message();}
    ASSERT_EQ(vynimka,"WRONG COUNTRY");
}
TEST(TestFirstTask,addressMoreSpaces ) {
    Address adresa;
    adresa.putAddress("    02801#         SLOVAKIA");
    ASSERT_EQ(adresa.getAddress(),"02801#SLOVAKIA");
}

TEST(TestFirstTask,spacesInCountry) {
    Address adresa;
    std::string vynimka;
    try{adresa.putAddress("#         SLOVAKIA");}
    catch(WrongInput e){
        vynimka = e.message();}
    ASSERT_EQ(vynimka,"Address has wrong format");
}
TEST(TestFirstTask,wrongNumber) {
    Address adresa;
    std::string vynimka;
    try{adresa.putAddress("100000#         SLOVAKIA");}
    catch(WrongInput e){
        vynimka = e.message();}
    ASSERT_EQ(vynimka,"WRONG POSTAL CODE");
}
TEST(TestFirstTask,wrongPostalCode2 ) {
    Address adresa;
    std::string vynimka;
    try{adresa.putAddress("    000000000000002801#         SLOVAKIA");}
    catch(WrongInput e){
        vynimka = e.message();}
    ASSERT_EQ(vynimka,"WRONG POSTAL CODE");
}

TEST(TestFirstTask,moreWordsInCountry) {
    Address adresa;
    std::string vynimka;
    adresa.putAddress("10000#   UNITED KINGDOM");
    ASSERT_EQ(adresa.getAddress(),"10000#UNITED KINGDOM");
}