#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

namespace local{
typedef std::vector<double> Point;
typedef enum _ACTION{
  ACTION_INIT,
  ACTION_PICKUP,
  ACTION_GO,
  ACTION_DROPOFF,
  ACTION_END
} ACTION;

}

local::Point pickup_zone_position{  0.0, -4.0, 0.0, 1.0 };
local::Point dropoff_zone_position{ 2.25, 0.0, 0.0, 1.0 }; //M_PI/2
local::ACTION action = local::ACTION_INIT;
double e = 0.5;



int main( int argc, char** argv )
{
  ros::init(argc, argv, "cube_node_simulate");
  ros::NodeHandle n;
  ros::Rate r(1);

  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

  while (ros::ok())
  {

    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "cube_node_simulate";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = pickup_zone_position[0];
    marker.pose.position.y = pickup_zone_position[1];
    marker.pose.position.z = pickup_zone_position[2];
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = pickup_zone_position[3];


    switch (action)
    {
    case local::ACTION_INIT:
      marker.action = visualization_msgs::Marker::ADD;
      action = local::ACTION_PICKUP;
      break;

    case local::ACTION_PICKUP:
      action = local::ACTION_GO;
      ros::Duration(5.0).sleep(); // sec
      marker.action = visualization_msgs::Marker::DELETE;
      action = local::ACTION_GO;
      break;

    case local::ACTION_GO:
      marker.action = visualization_msgs::Marker::DELETE;
      action = local::ACTION_DROPOFF;
      break;

    case local::ACTION_DROPOFF:
      action = local::ACTION_END;
      marker.action = visualization_msgs::Marker::ADD;
      marker.pose.position.x = dropoff_zone_position[0];
      marker.pose.position.y = dropoff_zone_position[1];
      marker.pose.position.z = dropoff_zone_position[2];
      marker.pose.orientation.w = dropoff_zone_position[3];
      ros::Duration(5.0).sleep(); // sec
      break;

    case local::ACTION_END:
      marker.action = visualization_msgs::Marker::ADD;
      marker.pose.position.x = dropoff_zone_position[0];
      marker.pose.position.y = dropoff_zone_position[1];
      marker.pose.position.z = dropoff_zone_position[2];
      marker.pose.orientation.w = dropoff_zone_position[3];
      break;

    }

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.3;
    marker.scale.y = 0.3;
    marker.scale.z = 0.3;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 0.0f;
    marker.color.b = 1.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok()){
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }

    marker_pub.publish(marker);

    ros::spinOnce();
    r.sleep();

  }


}
