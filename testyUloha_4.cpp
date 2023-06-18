#include <iostream>
#include "gtest/gtest.h"

#include "4_ShippingArea.h"
using namespace ::testing;

TEST(TestFourthTask,LocationOfCar) {
    CourierCar kurier;
    kurier.setLocationOfCar("");
    ASSERT_EQ(kurier.getLocation(),"BRATISLAVA");
    kurier.setLocationOfCar("NITRA");
    ASSERT_EQ(kurier.getLocation(),"NITRA");

}
TEST(TestFourthTask,readFromNoExistingFile) {
    CourierCar kurier;
    CourierCar emptyCourier;
    kurier.putPackages( "65 \n 05649#SLOVAKIA \n\n"
                        "500  \n 05119#CZECHIA \n\n"
                        "20  \n 02592#SLOVAKIA \n\n"
                        "20  \n 02002#SLOVAKIA "
    );
    ShippingArea oblast = ShippingArea("no.srt",kurier);
    ASSERT_EQ(0,oblast.getCourier().getNumberOfpackages());
}
TEST(TestFourthTask,MapOfNeighbours) {
    CourierCar emptyCourier;
    ShippingArea oblast = ShippingArea("no.srt",emptyCourier);
    std::map<std::string,int> susedia;
    susedia.insert(std::pair<std::string,int>("TRENCIN",78));
    susedia.insert(std::pair<std::string,int>("TRSTENA",10));
    ASSERT_TRUE(oblast.getMapOfneighbours("TVRDOSIN").empty());
    ASSERT_TRUE(oblast.makeGraphFromFile("shippingarea1.srt"));
    ASSERT_EQ(oblast.getMapOfneighbours("TVRDOSIN"),susedia);
    ASSERT_TRUE(oblast.getMapOfneighbours("").empty());

}
TEST(TestFourthTask,neighboursInString) {
    CourierCar emptyCourier;
    ShippingArea oblast = ShippingArea("shippingarea1.srt",emptyCourier);
    ASSERT_FALSE(oblast.getMapOfneighbours("TVRDOSIN").empty());
    ASSERT_EQ(oblast.getNeighbours("TVRDOSIN"),"TRENCIN,TRSTENA");
    ASSERT_EQ(oblast.getNeighbours("POPRAD"),"BRATISLAVA,TRENCIN,TRSTENA");
}
TEST(TestFourthTask,zeroDistance) {
    CourierCar emptyCourier;
    ShippingArea oblast = ShippingArea("shippingarea1.srt",emptyCourier);
    ASSERT_EQ(oblast.getDistance(" ","BRATISLAVA"),0);
    ASSERT_EQ(oblast.getDistance("TRSTENA"," "),0);
    ASSERT_EQ(oblast.getDistance("TRSTENA","TRSTENA"),0);

}

TEST(TestFourthTask,distances) {
    CourierCar emptyCourier;
    ShippingArea oblast = ShippingArea("shippingarea1.srt",emptyCourier);

    ASSERT_EQ(oblast.getNeighbours("TRENCIN"),"BRATISLAVA,POPRAD,TVRDOSIN");
    ASSERT_EQ(oblast.getDistance("TRENCIN","BRATISLAVA"),50);
    ASSERT_EQ(oblast.getDistance("TRSTENA","POPRAD"),45);
    ASSERT_EQ(oblast.getDistance("POPRAD","TRSTENA"),oblast.getDistance("TRSTENA","POPRAD"));
}
TEST(TestFourthTask,townsToVisit) {
    CourierCar kurier;
    std::set<std::string>mesta {"TVRDOSIN","TRSTENA","BRATISLAVA"};
    kurier.putPackages( "65 \n 05649#SLOVAKIA \n\n"
                        "20  \n 02592#SLOVAKIA \n\n"
                        "20  \n 02002#SLOVAKIA ");
    ShippingArea oblast = ShippingArea("shippingarea1.srt",kurier);
    ASSERT_EQ(oblast.townsToVisit(),mesta);
}
TEST(TestFourthTask,subsets) {
    CourierCar kurier;
    std::vector<std::string> mesta1{"BRATISLAVA","POPRAD","NITRA","TVRDOSIN"};
    std::set<std::string> mesta2{"BRATISLAVA","TVRDOSIN"};
    std::vector<std::string> mesta3{"BRATISLAVA","POPRAD","NITRA","MARTIN"};
    ShippingArea oblast = ShippingArea("shippingarea1.srt",kurier);
    ASSERT_TRUE(oblast.isSubset(mesta2,mesta1));
    ASSERT_FALSE(oblast.isSubset(mesta2,mesta3));
}
TEST(TestFourthTask,possiblePath) {
    CourierCar kurier;
    kurier.putPackages( "65 \n 05649#SLOVAKIA \n\n"
                        "20  \n 02592#SLOVAKIA \n\n"
                        "20  \n 02002#SLOVAKIA ");
    ShippingArea oblast = ShippingArea("shippingarea1.srt",kurier);
    ASSERT_EQ(oblast.findPossiblePathForCourier(),"BRATISLAVA,TRENCIN,TVRDOSIN,TRSTENA");
}
TEST(TestFourthTask,possiblePath2) {
    CourierCar kurier;
    kurier.setLocationOfCar("TRSTENA");
    std::set<std::string>mesta {"TVRDOSIN","POPRAD"};
    kurier.putPackages( "65 \n 09649#SLOVAKIA \n\n"
                        "20  \n 02001#SLOVAKIA");
    ShippingArea oblast = ShippingArea("shippingarea1.srt",kurier);
    ASSERT_EQ(oblast.townsToVisit(),mesta);
    ASSERT_EQ(oblast.findPossiblePathForCourier(),"TRSTENA,TVRDOSIN,TRENCIN,POPRAD");
}