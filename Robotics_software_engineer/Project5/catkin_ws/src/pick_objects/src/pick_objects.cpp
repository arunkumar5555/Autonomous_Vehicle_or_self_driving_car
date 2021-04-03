#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

namespace local{

typedef std::vector<double> Point;
typedef enum _STATE{
  STATE_INIT,
  STATE_GO_PICKUP_ZONE,
  STATE_PICKUP,
  STATE_GO_DROPOFF_ZONE,
  STATE_GOL,
  STATE_ERROR
} STATE;

}

local::Point pickup_zone_position{ 0.0, -4.0, 0.0, 1.0 };
local::Point dropoff_zone_position{ 2.25, 0.0, 0.0, 1.0 }; //M_PI/2
local::STATE state = local::STATE_GO_PICKUP_ZONE;


bool move(MoveBaseClient & ac, const local::Point & x ){

    move_base_msgs::MoveBaseGoal goal;

    // set up the frame parameters
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();

    // Define a position and orientation for the robot to reach
    goal.target_pose.pose.position.x = x[0];
    goal.target_pose.pose.position.y = x[1];
    goal.target_pose.pose.position.z = x[2];
    goal.target_pose.pose.orientation.w = x[3];

    // Send the goal position and orientation for the robot to reach
    // ROS_INFO("Sending goal");
    ac.sendGoal(goal);

    // Wait an infinite time for the results
    ac.waitForResult();

    // Check if the robot reached its goal
    return ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED;

}

int main(int argc, char** argv){

  // Initialize the pick_objects node
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  bool oo = true;
  while( oo ){
    switch (state)
    {
    case local::STATE_INIT:
      state = local::STATE_GO_PICKUP_ZONE;
      break;

    case local::STATE_GO_PICKUP_ZONE:
      state = local::STATE_PICKUP;
      ROS_INFO("Robo traveling for to the pickup zone");
      if(!move(ac, pickup_zone_position )) state = local::STATE_ERROR;
      break;

    case local::STATE_PICKUP:
      state = local::STATE_GO_DROPOFF_ZONE;
      ROS_INFO("Robot pickup up the virtual object");
      // Simulate pickup
      ros::Duration(5.0).sleep(); // sec
      break;

    case local::STATE_GO_DROPOFF_ZONE:
      state = local::STATE_GOL;
      ROS_INFO("Robo traveling for to the drop off zone");
      if(!move(ac, dropoff_zone_position )) state = local::STATE_ERROR;
      break;

    case local::STATE_GOL:
      oo = false;
      ROS_INFO("Robo droped the virtual object");
      ROS_INFO("GOL!!!");
      break;

    default:
      oo = false;
      break;
    }
  }


  return 0;
}
