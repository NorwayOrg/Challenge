#include <gnc_functions.hpp>
#include <cmath>

#define PI 3.14159265
//include API 

int main(int argc, char** argv)
{
	//initialize ros 
	ros::init(argc, argv, "gnc_node");
	ros::NodeHandle gnc_node("~");
	
	//initialize control publisher/subscribers
	init_publisher_subscriber(gnc_node);

  	// wait for FCU connection
	wait4connect();

	//wait for used to switch to mode GUIDED
	wait4start();

	//create local reference frame 
	initialize_local_frame();

	//request takeoff
	takeoff(3);

	//specify some waypoints 
	std::vector<gnc_api_waypoint> waypointList;
	gnc_api_waypoint nextWayPoint;

	int r = 5;
	int d = 3;
	int z = 3;

	nextWayPoint.x = 0;
	nextWayPoint.y = 0;
	nextWayPoint.z = z;
	nextWayPoint.psi = 0;
	waypointList.push_back(nextWayPoint);
	
	nextWayPoint.x = 0;
	nextWayPoint.y = r+d;
	nextWayPoint.z = z;
	nextWayPoint.psi = 180;
	waypointList.push_back(nextWayPoint);

	nextWayPoint.x = tan(18*PI/180)*(r+d);
	nextWayPoint.y = r+d;
	nextWayPoint.z = z;
	nextWayPoint.psi = 180;
	waypointList.push_back(nextWayPoint);
	
	nextWayPoint.x = tan(18*PI/180)*(r+d);
	nextWayPoint.y = r+d;
	nextWayPoint.z = z;
	nextWayPoint.psi = 144;
	waypointList.push_back(nextWayPoint);

	nextWayPoint.x = tan(18*PI/180)*(r+d) + 2*(r+d)*tan(18*PI/180)*sin(54*PI/180);
	nextWayPoint.y = r+d - 4*(r+d)*pow(sin(18*PI/180), 2);
	nextWayPoint.z = z;
	nextWayPoint.psi = 144;
	waypointList.push_back(nextWayPoint);

	nextWayPoint.x = tan(18*PI/180)*(r+d) + 2*(r+d)*tan(18*PI/180)*sin(54*PI/180);
	nextWayPoint.y = r+d - 4*(r+d)*pow(sin(18*PI/180), 2);
	nextWayPoint.z = z;
	nextWayPoint.psi = 108;
	waypointList.push_back(nextWayPoint);

	nextWayPoint.x = tan(18*PI/180)*(r+d) + 2*(r+d)*tan(18*PI/180)*sin(54*PI/180) + 2*(r+d)*tan(18*PI/180)*sin(18*PI/180);
	nextWayPoint.y = r+d - 4*(r+d)*pow(sin(18*PI/180), 2) - 2*(r+d)*sin(18*PI/180);
	nextWayPoint.z = z;
	nextWayPoint.psi = 108;
	waypointList.push_back(nextWayPoint);

	nextWayPoint.x = tan(18*PI/180)*(r+d) + 2*(r+d)*tan(18*PI/180)*sin(54*PI/180) + 2*(r+d)*tan(18*PI/180)*sin(18*PI/180);
	nextWayPoint.y = r+d - 4*(r+d)*pow(sin(18*PI/180), 2) - 2*(r+d)*sin(18*PI/180);
	nextWayPoint.z = z;
	nextWayPoint.psi = 72;
	waypointList.push_back(nextWayPoint);

	nextWayPoint.x = tan(18*PI/180)*(r+d) + 2*(r+d)*tan(18*PI/180)*sin(54*PI/180);
	nextWayPoint.y = r+d - 4*(r+d)*pow(sin(18*PI/180), 2) - 2*2*(r+d)*sin(18*PI/180);
	nextWayPoint.z = z;
	nextWayPoint.psi = 72;
	waypointList.push_back(nextWayPoint);

	nextWayPoint.x = tan(18*PI/180)*(r+d) + 2*(r+d)*tan(18*PI/180)*sin(54*PI/180);
	nextWayPoint.y = r+d - 4*(r+d)*pow(sin(18*PI/180), 2) - 2*2*(r+d)*sin(18*PI/180);
	nextWayPoint.z = z;
	nextWayPoint.psi = 36;
	waypointList.push_back(nextWayPoint);

	nextWayPoint.x = tan(18*PI/180)*(r+d);
	nextWayPoint.y = r+d - 2*4*(r+d)*pow(sin(18*PI/180), 2) - 2*2*(r+d)*sin(18*PI/180);
	nextWayPoint.z = z;
	nextWayPoint.psi = 36;
	waypointList.push_back(nextWayPoint);

	nextWayPoint.x = tan(18*PI/180)*(r+d);
	nextWayPoint.y = r+d - 2*4*(r+d)*pow(sin(18*PI/180), 2) - 2*2*(r+d)*sin(18*PI/180);
	nextWayPoint.z = z;
	nextWayPoint.psi = 0;
	waypointList.push_back(nextWayPoint);

	nextWayPoint.x = -tan(18*PI/180)*(r+d);
	nextWayPoint.y = r+d - 2*4*(r+d)*pow(sin(18*PI/180), 2) - 2*2*(r+d)*sin(18*PI/180);
	nextWayPoint.z = z;
	nextWayPoint.psi = 0;
	waypointList.push_back(nextWayPoint);

	nextWayPoint.x = -tan(18*PI/180)*(r+d);
	nextWayPoint.y = r+d - 2*4*(r+d)*pow(sin(18*PI/180), 2) - 2*2*(r+d)*sin(18*PI/180);
	nextWayPoint.z = z;
	nextWayPoint.psi = -36;
	waypointList.push_back(nextWayPoint);

	nextWayPoint.x = -tan(18*PI/180)*(r+d) - 2*(r+d)*tan(18*PI/180)*sin(54*PI/180);
	nextWayPoint.y = r+d - 4*(r+d)*pow(sin(18*PI/180), 2) - 2*2*(r+d)*sin(18*PI/180);
	nextWayPoint.z = z;
	nextWayPoint.psi = -36;
	waypointList.push_back(nextWayPoint);

	nextWayPoint.x = -tan(18*PI/180)*(r+d) - 2*(r+d)*tan(18*PI/180)*sin(54*PI/180);
	nextWayPoint.y = r+d - 4*(r+d)*pow(sin(18*PI/180), 2) - 2*2*(r+d)*sin(18*PI/180);
	nextWayPoint.z = z;
	nextWayPoint.psi = -72;
	waypointList.push_back(nextWayPoint);

	nextWayPoint.x = -tan(18*PI/180)*(r+d) - 2*(r+d)*tan(18*PI/180)*sin(54*PI/180) - 2*(r+d)*tan(18*PI/180)*sin(18*PI/180);
	nextWayPoint.y = r+d - 4*(r+d)*pow(sin(18*PI/180), 2) - 2*(r+d)*sin(18*PI/180);
	nextWayPoint.z = z;
	nextWayPoint.psi = -72;
	waypointList.push_back(nextWayPoint);

	nextWayPoint.x = -tan(18*PI/180)*(r+d) - 2*(r+d)*tan(18*PI/180)*sin(54*PI/180) - 2*(r+d)*tan(18*PI/180)*sin(18*PI/180);
	nextWayPoint.y = r+d - 4*(r+d)*pow(sin(18*PI/180), 2) - 2*(r+d)*sin(18*PI/180);
	nextWayPoint.z = z;
	nextWayPoint.psi = -108;
	waypointList.push_back(nextWayPoint);

	nextWayPoint.x = -tan(18*PI/180)*(r+d) - 2*(r+d)*tan(18*PI/180)*sin(54*PI/180);
	nextWayPoint.y = r+d - 4*(r+d)*pow(sin(18*PI/180), 2);
	nextWayPoint.z = z;
	nextWayPoint.psi = -108;
	waypointList.push_back(nextWayPoint);

	nextWayPoint.x = -tan(18*PI/180)*(r+d) - 2*(r+d)*tan(18*PI/180)*sin(54*PI/180);
	nextWayPoint.y = r+d - 4*(r+d)*pow(sin(18*PI/180), 2);
	nextWayPoint.z = z;
	nextWayPoint.psi = -144;
	waypointList.push_back(nextWayPoint);

	nextWayPoint.x = -tan(18*PI/180)*(r+d);
	nextWayPoint.y = r+d;
	nextWayPoint.z = z;
	nextWayPoint.psi = -144;
	waypointList.push_back(nextWayPoint);

	nextWayPoint.x = -tan(18*PI/180)*(r+d);
	nextWayPoint.y = r+d;
	nextWayPoint.z = z;
	nextWayPoint.psi = -180;
	waypointList.push_back(nextWayPoint);

	nextWayPoint.x = 0;
	nextWayPoint.y = r+d;
	nextWayPoint.z = z;
	nextWayPoint.psi = -180;
	waypointList.push_back(nextWayPoint);


	nextWayPoint.x = 0;
	nextWayPoint.y = 0;
	nextWayPoint.z = z;
	nextWayPoint.psi = 0;
	waypointList.push_back(nextWayPoint);


	//specify control loop rate. We recommend a low frequency to not over load the FCU with messages. Too many messages will cause the drone to be sluggish
	ros::Rate rate(3.0);
	int counter = 0;
	while(ros::ok())
	{
		ros::spinOnce();
		rate.sleep();
		if(check_waypoint_reached(.3) == 1)
		{
			if (counter < waypointList.size())
			{
				set_destination(waypointList[counter].x,waypointList[counter].y,waypointList[counter].z, waypointList[counter].psi);
				counter++;	
			}else{
				//land after all waypoints are reached
				land();
			}	
		}	
		
	}
	return 0;
}