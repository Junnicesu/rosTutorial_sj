#include "ros/ros.h"
#include "carparksrvc/AllowParking.h"
#include "carparksrvc/CarType.h"
#include <string>

int main(int argc, char** argv)
{

    ros::init(argc, argv, "carpark_client");
    if(argc!=3){
        ROS_INFO("usage: carpark_client <park|leave> <bus|car|bicycle>");
        return -1;
    }

    int carType = -1;
    using std::string;
    if( string("bicycle") == argv[2] ) carType = 0;
    else if(string("car") == argv[2]) carType = 1;
    else if(string("bus") == argv[2]) carType = 2;
    else{
        ROS_INFO("Car typ error!");
        return -1;
    }

    ros::NodeHandle n; 
    //create client, request "carpark_req_parking" service
    ros::ServiceClient client = n.serviceClient<carparksrvc::AllowParking>("carpark_req_parking");

    carparksrvc::AllowParking msg;
    msg.request.carType = carType;
    if(client.call(msg)){
        ROS_INFO("Parking : %s", msg.response.isAllowed ? "allowed" : "refused");
    }
    else{
        ROS_ERROR("Failed to call service carpark_req_parking!");
        return -1;
    }

    ros::Duration(60.0).sleep(); //sj tmp

    return 0;
}