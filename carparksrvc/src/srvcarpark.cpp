#include "ros/ros.h"
#include "carparksrvc/AllowParking.h"
#include "carpark.h"

//callback of allow parking
bool allow_parking(carparksrvc::AllowParking::Request &req, 
                    carparksrvc::AllowParking::Response &res )
{
    auto pCarPark_SI = carparksrvc::CarPark::GetInstance();
    res.isAllowed =  pCarPark_SI->ReqParking((carparksrvc::enumCarType)req.carType); 
    ROS_INFO("request, cartype : %d", req.carType);
    ROS_INFO("response, allowed parking : %s", res.isAllowed? "True": "False");
    return true;
}

carparksrvc::CarPark* carparksrvc::CarPark::pSI = nullptr;

int main(int argc, char** argv)
{
    ros::init(argc, argv, "carpark_service");
    ros::NodeHandle n;
    ros::ServiceServer service = n.advertiseService("carpark_req_parking", allow_parking);
    ROS_INFO("Ready for car park service.");
    ros::spin();
    return 0;
}
