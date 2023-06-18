#include <iostream>
#include "gtest/gtest.h"

#include "4_ShippingArea.h"
using namespace ::testing;

TEST(TestFifthTask,recursionDistance) {
    CourierCar kurier;
    std::set<std::string> prejdene;
    std::vector<std::string> cesta;
    ShippingArea oblast = ShippingArea("shippingarea1.srt",kurier);
    ASSERT_EQ(oblast.minimumCostPath("BRATISLAVA","TVRDOSIN").second,76);
    prejdene.clear();
    ASSERT_EQ(oblast.minimumCostPath("TVRDOSIN","TRENCIN").second,61);
    prejdene.clear();
    ASSERT_EQ(oblast.minimumCostPath("TRSTENA","BRATISLAVA").second,66);
    prejdene.clear();
    ASSERT_EQ(oblast.minimumCostPath("TVRDOSIN","TVRDOSIN").second,0);
}
TEST(TestFifthTask,shortestPathTowns) {
    CourierCar kurier;
    ShippingArea oblast = ShippingArea("shippingarea1.srt",kurier);
    auto najkratsiaCesta = oblast.minimumCostPath("BRATISLAVA","TVRDOSIN");
    ASSERT_EQ(najkratsiaCesta.second,76);
    ASSERT_EQ(najkratsiaCesta.first,"BRATISLAVA,POPRAD,TRSTENA,TVRDOSIN");

    najkratsiaCesta = oblast.minimumCostPath("TVRDOSIN","TRENCIN");
    ASSERT_EQ(najkratsiaCesta.first,"TVRDOSIN,TRSTENA,POPRAD,TRENCIN");

    najkratsiaCesta = oblast.minimumCostPath("TRSTENA","BRATISLAVA");
    ASSERT_EQ(najkratsiaCesta.first,"TRSTENA,POPRAD,BRATISLAVA");

    najkratsiaCesta = oblast.minimumCostPath("TVRDOSIN","TVRDOSIN");
    ASSERT_EQ(najkratsiaCesta.first,"TVRDOSIN");
}
TEST(TestFifthTask,shortestPathCourier) {
    CourierCar kurier;
    kurier.putPackages( "65 \n 05649#SLOVAKIA \n\n"
                        "20  \n 02592#SLOVAKIA \n\n"
                        "20  \n 02002#SLOVAKIA ");
    kurier.setLocationOfCar("TRSTENA");

    ShippingArea oblast = ShippingArea("shippingarea1.srt",kurier);
    auto najkratsiaCesta = oblast.courierMinimumCostPath();
    ASSERT_EQ(najkratsiaCesta.first,115);
    ASSERT_EQ(najkratsiaCesta.second,"TRSTENA,TVRDOSIN,TRENCIN,POPRAD,BRATISLAVA");

    kurier.setLocationOfCar("BRATISLAVA");
    oblast = ShippingArea("shippingarea1.srt",kurier);
    najkratsiaCesta = oblast.courierMinimumCostPath();
    ASSERT_EQ(najkratsiaCesta.first,76);
    ASSERT_EQ(najkratsiaCesta.second,"BRATISLAVA,POPRAD,TRSTENA,TVRDOSIN");

    kurier.setLocationOfCar("TRENCIN");
    oblast = ShippingArea("shippingarea1.srt",kurier);
    najkratsiaCesta = oblast.courierMinimumCostPath();
    ASSERT_EQ(najkratsiaCesta.first,126);
    ASSERT_EQ(najkratsiaCesta.second,"TRENCIN,BRATISLAVA,POPRAD,TRSTENA,TVRDOSIN");
}
TEST(TestFifthTask,area2) {
    CourierCar kurier;
    kurier.putPackages( "65 \n 05649#SLOVAKIA \n\n"
                        "20  \n 02592#SLOVAKIA \n\n"
                        "20  \n 02002#SLOVAKIA ");
    std::set<std::string>mesta{"TRSTENA","TVRDOSIN","BRATISLAVA"};

    ShippingArea oblast = ShippingArea("shippingarea2.srt", kurier);
    auto najkratsiaCesta = oblast.courierMinimumCostPath();
    ASSERT_EQ(oblast.townsToVisit(),mesta);
    ASSERT_EQ(najkratsiaCesta.first,140);
    ASSERT_EQ(najkratsiaCesta.second,"BRATISLAVA,LEOPOLDOV,MARTIN,TRSTENA,TVRDOSIN");

    kurier.putPackage("20  \n 02292#SLOVAKIA");
    oblast = ShippingArea("shippingarea2.srt", kurier);
    najkratsiaCesta = oblast.courierMinimumCostPath();
    ASSERT_EQ(najkratsiaCesta.first,742);
    ASSERT_EQ(najkratsiaCesta.second,"BRATISLAVA,TRENCIN,KOSICE,ZVOLEN,TVRDOSIN,TRSTENA");

}
TEST(TestFifthTask,area2PackagesFromFile ) {
    CourierCar kurier;
    kurier.readFromFile("packages.srt");
    std::set<std::string>mesta{"BRATISLAVA", "KOSICE", "MARTIN", "NITRA", "POPRAD", "TRSTENA", "TVRDOSIN", "ZILINA", "ZVOLEN"};

    ShippingArea oblast = ShippingArea("shippingarea2.srt", kurier);
    auto najkratsiaCesta = oblast.courierMinimumCostPath();
    ASSERT_EQ(oblast.townsToVisit(),mesta);
    ASSERT_EQ(najkratsiaCesta.first,903);
    ASSERT_EQ(najkratsiaCesta.second,"BRATISLAVA,LEOPOLDOV,MARTIN,TRENCIN,KOSICE,ZVOLEN,TVRDOSIN,TRSTENA,POPRAD,NITRA,ZILINA");

    kurier.setLocationOfCar("TVRDOSIN");
    oblast = ShippingArea("shippingarea2.srt", kurier);
    najkratsiaCesta = oblast.courierMinimumCostPath();
    ASSERT_EQ(najkratsiaCesta.first,947);
    ASSERT_EQ(najkratsiaCesta.second,"TVRDOSIN,ZVOLEN,KOSICE,TRENCIN,BRATISLAVA,LEOPOLDOV,MARTIN,TRSTENA,POPRAD,NITRA,ZILINA");

}