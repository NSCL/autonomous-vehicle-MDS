/*
 * Copyright (c) 2020, stauto-seoultech.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <ros/ros.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/thread.hpp>

#include <tf2_ros/transform_listener.h>
#include <tf/transform_listener.h>
#include <nav_msgs/Path.h>
#include <std_msgs/UInt32.h>
#include <geometry_msgs/PoseStamped.h>
//#include <vision_msgs/BoundingBox2D.h>

using namespace std;

class PathPlan
{
    private:
        ros::NodeHandle nh;
        ros::Subscriber global_path_sub,lane_path_sub,gps_accuracy_sub,lane_accuracy_sub,robot_step_sub; //object_info
        ros::Publisher local_path_pub;
        ros::Timer timer1;

        nav_msgs::Path global_path,lane_path,local_path;
        std_msgs::UInt32 gps_accuracy, lane_accuracy;
        geometry_msgs::PoseStamped cur_step;
        bool global_path_flag, cur_step_flag, gps_accu_received, lane_accu_received;
        int controller_freq;


        void GlobalCB(const nav_msgs::Path::ConstPtr& GpathMsg);
        void LaneCB(const nav_msgs::Path::ConstPtr& LpathMsg);
        void GaccuracyCB(const std_msgs::UInt32::ConstPtr& GaccuracyMsg );
        void LaccuracyCB(const std_msgs::UInt32::ConstPtr& LaccuracyMsg );
        void RobotStepCB(const geometry_msgs::PoseStamped::ConstPtr& RobotStepMsg);
        void controlLoopCB(const ros::TimerEvent&);
        //void ObjectCB(const nav_msgs::Path::ConstPtr& GpathMsg);

    public:
        PathPlan();
        nav_msgs::Path LocalPathPlan(const nav_msgs::Path global_path, const geometry_msgs::PoseStamped cur_step);

};

PathPlan::PathPlan()
{
    ros::NodeHandle pn("~");
    pn.param("controller_freq",controller_freq,10);
    global_path_flag = true;
    cur_step_flag = true;

    global_path_sub = nh.subscribe("global_path", 1, &PathPlan::GlobalCB,this);
    lane_path_sub = nh.subscribe("lane_path", 1, &PathPlan::LaneCB,this);
    gps_accuracy_sub = nh.subscribe("/gps/accuracy", 1, &PathPlan::GaccuracyCB,this);
    lane_accuracy_sub = nh.subscribe("/lane/accuracy", 1, &PathPlan::LaccuracyCB,this);
    robot_step_sub = nh.subscribe("current_step", 1, &PathPlan::RobotStepCB,this);

    timer1 = nh.createTimer(ros::Duration((1.0)/controller_freq),&PathPlan::controlLoopCB,this);

    local_path_pub = nh.advertise<nav_msgs::Path>("/local_path",1);
}

nav_msgs::Path PathPlan::LocalPathPlan (const nav_msgs::Path global_path, const geometry_msgs::PoseStamped cur_step)
{
    local_path = nav_msgs::Path();
    geometry_msgs::PoseStamped pose = geometry_msgs::PoseStamped();
    int index = 0;

    //ROS_INFO("cur_step.pose.position.z : %d ", (int)cur_step.pose.position.z);

    for(int idx = (int)cur_step.pose.position.z ; idx < ((int)cur_step.pose.position.z + 4); idx++)
    {

        pose.header.seq = 0;
        pose.header.stamp = ros::Time::now();
        pose.header.frame_id = "base_link";

        pose.pose.position.x = global_path.poses[idx].pose.position.x;
        pose.pose.position.y = global_path.poses[idx].pose.position.y;
        pose.pose.position.z = global_path.poses[idx].pose.position.z;


        local_path.poses.push_back(pose);
        //local_path.poses[0].pose.position.y = global_path.poses[idx].pose.position.y;
        //local_path.poses[index].pose.position.z = global_path.poses[idx].pose.position.z;

        index++;
    }
    return local_path;
}

void PathPlan::GlobalCB(const nav_msgs::Path::ConstPtr& GpathMsg)
{
    if(global_path_flag)
    {
      this->global_path = *GpathMsg;
      global_path_flag = !global_path_flag;
      // for(int i=0; i<global_path.poses.size()-1; i++)
      // {
      //   ROS_INFO("The global_path %d :  %f", i,this->global_path.poses[i]);
      // }
    }
}

void PathPlan::LaneCB(const nav_msgs::Path::ConstPtr& LpathMsg)
{
    this->lane_path = *LpathMsg;
}

void PathPlan::GaccuracyCB(const std_msgs::UInt32::ConstPtr& GaccuracyMsg )
{
    this->gps_accuracy = *GaccuracyMsg;
}

void PathPlan::LaccuracyCB(const std_msgs::UInt32::ConstPtr& LaccuracyMsg )
{
    this->lane_accuracy = *LaccuracyMsg;
}

void PathPlan::RobotStepCB(const geometry_msgs::PoseStamped::ConstPtr& RobotStepMsg)
{
    this -> cur_step = *RobotStepMsg;
}

void PathPlan::controlLoopCB(const ros::TimerEvent&)
{
    if(gps_accuracy.data >= 1 && global_path.poses.size() != 0 && cur_step.pose.position.x !=0 )
    {

        local_path = LocalPathPlan(global_path,cur_step);
        //ROS_INFO("Local_path : %d", local_path.poses.size());
        local_path_pub.publish(local_path);
    }
    else if(gps_accuracy.data < 1 )
    {
        //ROS_INFO("%d",gps_accuracy.data);
    }

}

int main(int argc,char** argv)
{
    ros::init(argc,argv,"path_plan_node");
    PathPlan path_plan_node;
    ros::spin();
    return(0);
}
