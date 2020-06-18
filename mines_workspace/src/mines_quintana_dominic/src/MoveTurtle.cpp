#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"

//Topic messages callback
void poseCallback(const turtlesim::PoseConstPtr& msg) {
	ROS_INFO("x: %.2f, y: %.2f", msg->x, msg->y);
}

int main(int argc, char **argv) {
	const double FORWARD_SPEED_MPS = 2;
	const double TURN_SPEED_MPS = 0.5;
	//Initialize nodes
	ros::init(argc, argv, "mines_quintana_dominic");
	ros::NodeHandle node;
	ros::Publisher pub = node.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 10);
	ros::Subscriber sub = node.subscribe("turtle1/pose", 10, poseCallback);
	
	geometry_msgs::Twist msg;
	int count = 0;
	int i = 0;
	int moveArray[] = {17, 20, 16, 10, 31, 5, 32, 2, 32, 22, 31, 2, 31, 6, 32, 13, 31, 6, 31, 4, 31, 17, 46, 23, 29, 21, 47, 16, 31, 4, 31, 6, 31, 13, 31, 6, 31, 2, 30, 22, 31, 2, 31, 5, 31, 10, 16, 23, 31, 0};
	char direction[] = {'L', 'F', 'R', 'F', 'R', 'F', 'R', 'F', 'L', 'F', 'L', 'F', 'R', 'F', 'R', 'F', 'R', 'F', 'R', 'F', 'L', 'F', 'L', 'F', 'R', 'F', 'L', 'F', 'L', 'F', 'R', 'F', 'R', 'F', 'R', 'F', 'R', 'F', 'L', 'F', 'L', 'F', 'R', 'F', 'R', 'F', 'R', 'F', 'L', 'E'};
	//msg.angular.z = 1;
	ros::Rate rate(10);
	ROS_INFO("Starting route");
	/*pub.publish(msg);
	ros::spinOnce();
	rate.sleep();*/
	while (ros::ok()) {
		pub.publish(msg);
		ros::spinOnce();
		if (direction[i] == 'L') {
			msg.linear.x = 0;
			msg.angular.z = TURN_SPEED_MPS;
		}
		else if (direction[i] == 'R') {
			msg.linear.x = 0;
			msg.angular.z = -TURN_SPEED_MPS;	
		}
		else if (direction[i] == 'F') {
			msg.angular.z = 0;
			msg.linear.x = FORWARD_SPEED_MPS;
		}
		else if (direction[i] == 'E') {
			msg.angular.z = 0;
			msg.linear.x = 0;
		}
		if (count == moveArray[i]) {
			count = 0;
			i++;
		}
		count++;
		//rate.sleep();
		/*msg.angular.z = 1;
		msg.linear.x = 0;
		msg.angular.z = 0;
		msg.linear.x = 1;*/
		rate.sleep();
	}
}
