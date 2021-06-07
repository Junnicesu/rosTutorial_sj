#include "../src/carpark.h"
// #include "carparksrvc/AllowParking.h"
// #include "carparksrvc/AllowLeaving.h"
// Bring in gtest
#include <gtest/gtest.h>

//Initialize pointer of the Singleton CarPark instance.
carparksrvc::CarPark* carparksrvc::CarPark::pSI = nullptr;

//Declare a test
TEST(TestSuite, getInstance)
{
    auto pCarPark_SI = carparksrvc::CarPark::GetInstance();
    ASSERT_TRUE (pCarPark_SI != nullptr);
}

TEST(TestSuite, allowParking)
{
    auto pCarPark_SI = carparksrvc::CarPark::GetInstance();
    ASSERT_TRUE (pCarPark_SI != nullptr);
    for(int i=0; i<15; i++){ //sj: 15 is the parking lot number for the bus, from the constructor, not from any configure.
        EXPECT_TRUE (pCarPark_SI->ReqParking(carparksrvc::enumCarType::bus));
    }
    EXPECT_FALSE (pCarPark_SI->ReqParking(carparksrvc::enumCarType::bus));

    for(int i=0; i<100; i++){ //sj: 15 is the parking lot number for the car
        EXPECT_TRUE (pCarPark_SI->ReqParking(carparksrvc::enumCarType::car));
    }
    EXPECT_FALSE (pCarPark_SI->ReqParking(carparksrvc::enumCarType::car));
}

TEST(TestSuite, allowleaving)
{
    auto pCarPark_SI = carparksrvc::CarPark::GetInstance();
    ASSERT_TRUE (pCarPark_SI != nullptr);    
    EXPECT_FALSE (pCarPark_SI->ReqLeaving(false, carparksrvc::enumCarType::bus));
    EXPECT_TRUE (pCarPark_SI->ReqLeaving(true, carparksrvc::enumCarType::bus));
}


int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    // ros::init(argc, argv, "tester");
    // ros:NodeHandle n;
    return RUN_ALL_TESTS();
}