#include "ros/ros.h"
#include "carparksrvc/AllowParking.h"
#include "carparksrvc/AllowLeaving.h"
#include "carparksrvc/CarType.h"
#include <string>

int main(int argc, char** argv)
{

    ros::init(argc, argv, "carpark_client");
    if(argc < 3){
        ROS_INFO("usage: carpark_client <park|leave> <bus|car|bicycle> [unpaid|paid(default)]");
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

    if(string("park") == argv[1]){
        //create client, request "carpark_req_parking" service
        ros::ServiceClient clientPark = n.serviceClient<carparksrvc::AllowParking>("carpark_req_parking");
        
        carparksrvc::AllowParking msg;
        msg.request.carType = carType;
        if(clientPark.call(msg)){
            ROS_INFO("Parking : %s", msg.response.isAllowed ? "allowed" : "refused");
        }
        else{
            ROS_ERROR("Failed to call service carpark_req_parking!");
            return -1;
        }
    }
    else if(string("leave") == argv[1]){
        ros::ServiceClient clientLeave = n.serviceClient<carparksrvc::AllowLeaving>("carpark_req_leaving");
        carparksrvc::AllowLeaving msg;
        msg.request.isPaid = true; 
        if(argc == 4){
            msg.request.isPaid = string("unpaid") == argv[3] ? false : true; 
        }
        msg.request.carType = carType;
        if(clientLeave.call(msg)){
            ROS_INFO("Leaving : %s", msg.response.isAllowed ? "allowed" : "refused");
        }
        else{
            ROS_ERROR("Failed to call service carpark_req_leaving!");
            return -1;            
        }
    }

    ros::Duration(10.0).sleep(); //sj tmp, wait 10 sec before quit 

    return 0;
}