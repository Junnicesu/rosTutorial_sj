#include "ros/ros.h"
#include "carparksrvc/AllowParking.h"
#include "carparksrvc/AllowLeaving.h"
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

bool allow_leaving(carparksrvc::AllowLeaving::Request &req, 
                    carparksrvc::AllowLeaving::Response &res )
{
    auto pCarPark_SI = carparksrvc::CarPark::GetInstance();
    res.isAllowed = pCarPark_SI->ReqLeaving(req.isPaid, (carparksrvc::enumCarType)req.carType);  
    ROS_INFO("request, cartype : %d,  %s", req.carType, req.isPaid? "Paid": "UnPaid");
    ROS_INFO("response, allowed leaving : %s", res.isAllowed? "True": "False");    
    return true;
}

carparksrvc::CarPark* carparksrvc::CarPark::pSI = nullptr;

int main(int argc, char** argv)
{
    ros::init(argc, argv, "carpark_service");
    ros::NodeHandle n;
    ros::ServiceServer service = n.advertiseService("carpark_req_parking", allow_parking);
    ros::ServiceServer service2 = n.advertiseService("carpark_req_leaving", allow_leaving);
    ROS_INFO("Ready for car park service.");
    ros::spin();
    return 0;
}
