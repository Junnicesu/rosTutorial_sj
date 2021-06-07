#include "../src/carpark.h"
#include "carparksrvc/AllowParking.h"
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
    for(int i=0; i<15; i++){
        EXPECT_TRUE (pCarPark_SI->ReqParking(carparksrvc::enumCarType::bus));
    }
    EXPECT_FALSE (pCarPark_SI->ReqParking(carparksrvc::enumCarType::bus));
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    // ros::init(argc, argv, "tester");
    // ros:NodeHandle n;
    return RUN_ALL_TESTS();
}