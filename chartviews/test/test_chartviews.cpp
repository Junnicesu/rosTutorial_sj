#include "../include/chartviews/charts.h"
#include <gtest/gtest.h>

using namespace nav_chartviews; 
TEST(TestSuite, colorOperator)
{
    Color red{255,0,0};
    Color green{0,255, 0};
    Color tea{127,127, 0};
    ASSERT_TRUE( red+green == tea );
}

TEST(TestSuite, chartCtor)
{
    auto ch1 = Chart(10, 20, 90, 80, 0, 0, 255);
    auto blue = Color{0,0,255};
    auto p1= Coordinate{90,20};
    auto p2= Coordinate{10,80};
    auto ch2 = Chart(p1, p2, blue);
    ASSERT_TRUE(ch1 == ch2); 
}

TEST(TestSuite, isOverLap)
{
    auto centre = Chart(45, 45, 55, 55);
    auto topLeft = Chart(10, 10, 20, 20);
    ASSERT_FALSE(View(&topLeft, &centre).DoChartsOverlap()); 

    auto topLeftBig = Chart(10,10, 50, 50); 
    ASSERT_TRUE(View(&topLeftBig, &centre).DoChartsOverlap()); 

    auto topRight = Chart(90, 10, 60, 70); 
    ASSERT_FALSE(View(&topRight, &centre).DoChartsOverlap()); 

    auto toRightBig = Chart(90, 10, 46, 50);
    ASSERT_TRUE(View(&toRightBig, &centre).DoChartsOverlap()); 

    auto bottomLeft = Chart(0, 85, 40, 60); 
    ASSERT_FALSE(View(&bottomLeft, &centre).DoChartsOverlap()); 

    auto bottomLeftBig = Chart(0,85, 50, 50);
    ASSERT_TRUE(View(&bottomLeftBig, &centre).DoChartsOverlap());

    auto bottomLeftBiger = Chart(0,85, 100, 10);
    ASSERT_TRUE(View(&bottomLeftBiger, &centre).DoChartsOverlap());

    auto bottomRight = Chart(70, 70, 60, 60);
    ASSERT_FALSE(View(&bottomRight, &centre).DoChartsOverlap());

    auto bottomRightBig = Chart(70, 70, 50, 50);
    ASSERT_TRUE(View(&bottomRightBig, &centre).DoChartsOverlap());

    auto bottomRightBiger = Chart(70, 70, 0, 0);
    ASSERT_TRUE(View(&bottomRightBiger, &centre).DoChartsOverlap());

    auto lineSeg = Chart(47, 10, 47, 90);
    ASSERT_TRUE(View(&lineSeg, &centre).DoChartsOverlap());

    auto lineSeg2 = Chart(30, 20, 87, 20); 
    ASSERT_TRUE(View(&lineSeg, &lineSeg2).DoChartsOverlap());
}

TEST(TestSuite, getColor)
{
    Color black{0,0,0}; 
    Color red{255, 0, 0};
    Color blue{0, 0, 255}; 
    Color green{0, 255, 0}; 
     //no intersection
    auto centre = Chart(45, 45, 55, 55, blue);
    auto bottomRight = Chart(90, 80, 70, 70, red);    
    auto view1 = View(&centre, &bottomRight); 
    ASSERT_TRUE(view1.GetColor(60, 60) == black); 
    ASSERT_TRUE(view1.GetColor(50, 50) == centre.color); 
    ASSERT_TRUE(view1.GetColor(75, 75) == bottomRight.color);
    ASSERT_TRUE(view1.GetColor(0, 0) == black); 
    
    //intersected
    auto topLeftBig = Chart(10, 20, 50, 50, green);
    auto view2 = View(&centre, &topLeftBig);
    ASSERT_TRUE(view2.GetColor(50, 50) == (centre.color + topLeftBig.color)); 
    ASSERT_TRUE(view2.GetColor(20, 30) == topLeftBig.color); 
    ASSERT_TRUE(view2.GetColor(53, 53) == centre.color);
    ASSERT_TRUE(view2.GetColor(90, 90) == black);

    //contain
    auto topRightBigger = Chart(90, 80, 30, 20, red);
    auto view3 = View(&centre, &topRightBigger); 
    ASSERT_TRUE(view3.GetColor(50, 50) == (centre.color + topRightBigger.color)); 
    ASSERT_TRUE(view3.GetColor(40, 40) == topRightBigger.color); 
    ASSERT_TRUE(view3.GetColor(100, 100) == black); 

    //chartB is null
    auto view4 = View(nullptr, &centre); 
    ASSERT_TRUE(view4.GetColor(50, 50) == centre.color); 
    ASSERT_TRUE(view4.GetColor(100, 100) == black); 
    
    //line
    auto lineSeg = Chart(47, 10, 47, 90, red);
    auto lineSeg2 = Chart(30, 20, 87, 20, green); 
    ASSERT_TRUE(View(&lineSeg, &lineSeg2).GetColor(47, 20) == (lineSeg.color + lineSeg2.color)); 

}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}