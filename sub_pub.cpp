#include <ros/ros.h>
#include <geometry_msgs/Point.h>
#include <visualization_msgs/Marker.h>

class SubscribeAndPublish
{
public:
  SubscribeAndPublish()
  {
    pub_ = n_.advertise<visualization_msgs::Marker>("/output", 1000);

    sub_ = n_.subscribe("/input", 1000, &SubscribeAndPublish::callback, this);
  }

  void callback(const geometry_msgs::Point& input)
  {
	visualization_msgs::Marker mrk;
	mrk.header.frame_id="points";
	mrk.ns="map";
	mrk.id=0;
	mrk.action=visualization_msgs::Marker::ADD;
	mrk.point.push_back(input);
    pub_.publish(mrk);
  }

private:
  ros::NodeHandle n_; 
  ros::Publisher pub_;
  ros::Subscriber sub_;

};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "sub_pub");

  SubscribeAndPublish SAPObject;

  ros::spin();

  return 0;
}