// Copyright 2005, Google Inc.
// All rights reserved.

#include <iostream>
#include "gtest/gtest.h"

#include "3_CourierCar.h"

using namespace ::testing;

TEST(TestThirdTask, emptyPackage) {
    CourierCar kurier;
  ASSERT_FALSE(kurier.putPackage(""));
}
TEST(TestThirdTask,wrongPackage ) {
    CourierCar kurier;
    ASSERT_FALSE(kurier.putPackage("150.2\n  02801#SL5AKIA   "));
    ASSERT_FALSE(kurier.putPackage("150.2\n  02801#USA   "));
}

TEST(TestThirdTask,morePackages) {
    CourierCar kurier;
    int number_of_inserted = kurier.putPackages( "111 \n 05649#SLOVAKIA \n\n"
                                                "35  \n 05119#SLOVAKIA");
    ASSERT_EQ(number_of_inserted,kurier.getNumberOfpackages());
    ASSERT_EQ(2,kurier.getNumberOfpackages());

}
TEST(TestThirdTask,maximumWeightOvercomed) {
    CourierCar kurier;
    kurier.putPackages( "1800 \n 05649#SLOVAKIA \n\n"
                        "500  \n 05119#SLOVAKIA");
    ASSERT_EQ(1,kurier.getNumberOfpackages());
}

TEST(TestThirdTask,Operator) {
    CourierCar kurier;
    int number_of_inserted = kurier.putPackages( "1800 \n 05649#SLOVAKIA \n\n"
                                                 "500  \n 05119#CZECHIA \n\n"
                                                 "20  \n 02592#SLOVAKIA \n\n"
                                                 "20  \n 02002#SLOVAKIA "
                                                 );
    ASSERT_EQ(3,number_of_inserted);
    ASSERT_EQ(kurier[2].getShippingAddress(),"02002#SLOVAKIA");
    ASSERT_EQ(kurier[2].getTown(),"BRATISLAVA");

}
TEST(TestThirdTask,sort) {
    CourierCar kurier;
    kurier.putPackages( "45.03 \n 02649#SLOVAKIA \n\n"
                                                 "48  \n 05119#SLOVAKIA \n\n"
                                                 "35.6  \n 02592#SLOVAKIA \n\n"
                                                 "35.9  \n 02002#SLOVAKIA \n\n"
                                                 "35.98  \n 02662#SLOVAKIA \n\n"
    );
    kurier.sortPackages();
    ASSERT_EQ(kurier[0].getWeight(),float(35.6));
    ASSERT_EQ(kurier[2].getWeight(),float(35.98));
    ASSERT_EQ(kurier[kurier.getNumberOfpackages()-1].getWeight(),float(48));

}

TEST(TestThirdTask,readFromNoExistingFile) {
    CourierCar kurier;
    ASSERT_FALSE(kurier.readFromFile("NO.srt"));

}
TEST(TestThirdTask,readFromFile) {
    CourierCar kurier;
    ASSERT_TRUE(kurier.readFromFile("packages.srt"));
    ASSERT_EQ(16, kurier.getNumberOfpackages());
}
TEST(TestThirdTask, firstPackage) {
    CourierCar kurier;
    kurier.readFromFile("packages.srt");
    ASSERT_EQ("02649#SLOVAKIA", kurier[0].getShippingAddress());
    ASSERT_EQ("00000#UNDEFINED", kurier[-1].getShippingAddress());
}
TEST(TestThirdTask, lastPackage) {
    CourierCar kurier;
    kurier.readFromFile("packages.srt");
    ASSERT_EQ(float(97.3), kurier[15].getWeight());
    ASSERT_EQ(float(90.54), kurier[10].getWeight());
}
TEST(TestThirdTask,saveNothingIntoFile) {
    CourierCar kurier;
    ASSERT_FALSE(kurier.saveToFile("packages1.srt"));

}
TEST(TestThirdTask, writeInFile) {
    CourierCar kurier;
    kurier.readFromFile("packages.srt");
    ASSERT_EQ(16, kurier.getNumberOfpackages());
    ASSERT_TRUE(kurier.saveToFile("packages1.srt"));
    CourierCar kurier2;
    kurier2.readFromFile("packages1.srt");
    ASSERT_EQ(16, kurier2.getNumberOfpackages());
    ASSERT_EQ(float(97.3), kurier2[15].getWeight());
    ASSERT_EQ(float(90.54), kurier2[10].getWeight());
}