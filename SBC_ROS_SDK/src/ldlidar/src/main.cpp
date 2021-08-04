#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
//#include <wiringPi.h>
//#include <softPwm.h>
#include "cmd_interface_linux.h"
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include "lipkg.h"
#include "tofbf.h"
#include "signal.h"
#include "pid.h"

int main(int argc, char **argv)
{
	ros::init(argc, argv, "product");
	ros::NodeHandle nh;                    /* create a ROS Node */

	
	//int32_t pwm_out = 0;
	//PIDObjTyp LidarMotorPID(500, 50, 200, 0, 100, 0);
	//wiringPiSetup();
	//set pwm out frequency 24kHz
	//pinMode(LIDAR_PWM, PWM_OUTPUT);
	//pwmSetClock(8);
	//pwmSetMode(PWM_MODE_MS);
	//pwmSetRange(100);
	//pwmWrite(LIDAR_PWM, 70);

	LiPkg * lidar = new LiPkg;

	CmdInterfaceLinux cmd_port;
	std::string port_name("/dev/ttyS0");
	cmd_port.SetReadCallback([&lidar](const char *byte, size_t len) {
		if (lidar->Parse((uint8_t*)byte, len))
		{
			lidar->AssemblePacket();
		}
		});
	
	if(cmd_port.Open(port_name))
			std::cout<<"LiDAR_LD19 started successfully "  <<std::endl;

	ros::Publisher lidar_pub = nh.advertise<sensor_msgs::LaserScan>("LiDAR/LD19", 1); /*create a ROS topic */
	
	while (ros::ok())
	{
		if (lidar->IsFrameReady())
		{
			lidar_pub.publish(lidar->GetLaserScan());  // Fixed Frame:  lidar_frame
			lidar->ResetFrameReady();
		}

	}
	return 0;
}
