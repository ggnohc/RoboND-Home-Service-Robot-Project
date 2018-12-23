#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>

const float dropoff_x = -3.3;
const float dropoff_y = 0.0;
const float pickup_x = 4.0;
const float pickup_y = 0.0;

enum goalState {
    TOWARDS_PICKUP = 0,
    AT_PICKUP,
    TOWARDS_DROPOFF,
    AT_DROPOFF
};

goalState state = TOWARDS_PICKUP;

visualization_msgs::Marker init_marker() {
    visualization_msgs::Marker marker;
    marker.header.frame_id = "/map";
    marker.header.stamp = ros::Time::now();

    marker.ns = "add_markers";
    marker.id = 0;

    uint32_t shape = visualization_msgs::Marker::CYLINDER;
    marker.type = shape;

    marker.action = visualization_msgs::Marker::ADD;

    marker.pose.position.x = pickup_x;
    marker.pose.position.y = pickup_y;
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

    return marker;
}


void odomCallback(const nav_msgs::Odometry::ConstPtr& odom)
{
    ROS_INFO("I received odom: [%f,%f]", odom->pose.pose.position.y, odom->pose.pose.position.x); //store x,y,z position values

    float curPoseX = odom->pose.pose.position.x;
    float curPoseY = odom->pose.pose.position.y;
    if ( state == TOWARDS_PICKUP &&
            ( curPoseX <= pickup_x + 0.7 && curPoseX >= pickup_x - 0.7 ) &&
            ( curPoseY <= pickup_y + 0.7 && curPoseY >= pickup_y - 0.7 )
       ) {
        state = AT_PICKUP;
        ROS_WARN("arrived at pickup position [%f, %f]", curPoseX, curPoseY);
    }

    if ( state == TOWARDS_DROPOFF &&
            ( curPoseX <= dropoff_x + 0.7 && curPoseX >= dropoff_x - 0.7 ) &&
            ( curPoseY <= dropoff_y + 0.7 && curPoseY >= dropoff_y - 0.7 )
       ) {
        state = AT_DROPOFF;
        ROS_WARN("arrived at dropoff position [%f, %f]", curPoseX, curPoseY);
    }
}

int main( int argc, char** argv )
{
    ros::init(argc, argv, "add_markers");
    ros::NodeHandle n;
    ros::Rate r(1);
    ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
    ros::Subscriber odom_sub = n.subscribe("/odom", 100, odomCallback);


    visualization_msgs::Marker marker = init_marker();

    while (ros::ok())
    {

        while ( marker_pub.getNumSubscribers() < 1 )
        {
            if (!ros::ok())
            {
                return 0;
            }
            ROS_WARN_ONCE("Please create a subscriber to the marker");
            sleep(1);
        }

        ROS_WARN_ONCE("Successfully found a subscriber");

        ros::spinOnce();

        switch (state) {
        case TOWARDS_PICKUP:
        {
            // Do nothing
            break;
        }
        case AT_PICKUP:
        {
            marker.color.a = 0.0;
            marker.pose.position.x = dropoff_x;
            marker.pose.position.y = dropoff_y;
            marker_pub.publish(marker);
            sleep(5);
            state = TOWARDS_DROPOFF;
            ROS_ERROR("removing marker");
            break;
        }
        case TOWARDS_DROPOFF:
        {
            marker.color.a = 0.0;
            break;
        }
        case AT_DROPOFF:
        {
            ROS_ERROR("Showing marker");
            marker.color.a = 1.0;
            marker.pose.position.x = dropoff_x;
            marker.pose.position.y = dropoff_y;
            marker_pub.publish(marker);
            sleep(5);

            break;
        }
        default:
        {
            break;
        }
        }

        marker_pub.publish(marker);

        r.sleep();

    }
}
