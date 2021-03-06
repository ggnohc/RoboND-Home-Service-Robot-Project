#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
// #include <nav_msgs/Odometry.h>

// float odom_x = 0.0, odom_y = 0.0;
//
// void odomCallback(const nav_msgs::Odometry::ConstPtr& msg)
// {
//   ::odom_x = msg->pose.pose.position.x;
//   ::odom_y = msg->pose.pose.position.y;
// }

int main( int argc, char** argv )
{
    ros::init(argc, argv, "add_markers");
    ros::NodeHandle n;
    ros::Rate r(1);
    ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
    // ros::Subscriber odom_sub = n.subscribe("/odom", 100, odomCallback);

    uint32_t shape = visualization_msgs::Marker::CYLINDER;

    while (ros::ok())
    {
        visualization_msgs::Marker marker;
        marker.header.frame_id = "/map";
        marker.header.stamp = ros::Time::now();

        marker.ns = "add_markers";
        marker.id = 0;

        marker.type = shape;

        marker.action = visualization_msgs::Marker::ADD;

        marker.pose.position.x = 4.0;
        marker.pose.position.y = 0.0;
        marker.pose.position.z = 0;
        marker.pose.orientation.x = 0.0;
        marker.pose.orientation.y = 0.0;
        marker.pose.orientation.z = 0.0;
        marker.pose.orientation.w = 1.0;

        marker.scale.x = 1.00;
        marker.scale.y = 1.00;
        marker.scale.z = 1.00;

        marker.color.r = 1.0f;
        marker.color.g = 0.0f;
        marker.color.b = 0.0f;
        marker.color.a = 1.0;

        marker.lifetime = ros::Duration();

        // while ( marker_pub.getNumSubscribers() < 1 )
        // {
        //     if (!ros::ok())
        //     {
        //         return 0;
        //     }
        //     ROS_WARN_ONCE("Please create a subscriber to the marker");
        //     sleep(1);
        // }
        marker_pub.publish(marker);
        ROS_ERROR("Showing marker at pickup");
        // r.sleep();

        ROS_ERROR("Sleep 5 sec before remove marker");
        sleep(5);

        ROS_ERROR("Removing marker");
        marker.color.a = 0.0;
        marker_pub.publish(marker);

        ROS_ERROR("Sleep 5 sec before publish marker at dropff");
        sleep(5);

        ROS_ERROR("Showing marker at dropoff");
        marker.color.a = 1.0;
        marker.pose.position.x = -4.0;
        marker.pose.position.y = 7.0;
        marker.pose.position.z = 0;
        marker_pub.publish(marker);
    }
}
