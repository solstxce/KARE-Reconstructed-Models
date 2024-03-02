/*
 * Copyright (C) 2015 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <iostream>
#include <ignition/math/Pose3.hh>

#include "gazebo/common/common.hh"
#include "gazebo/gazebo.hh"
#include "gazebo/msgs/msgs.hh"
#include "gazebo/physics/physics.hh"
#include "gazebo/transport/transport.hh"

using namespace gazebo;

int main(int _argc, char *_argv[])
{
  msgs::PoseAnimation msg;

  msg.set_model_name("kare-man");
  msgs::Pose *p = msg.add_pose();
  //       -21.605234819116983
      // 2.5500000000000003
  // msgs::Set(p, ignition::math::Pose3d( 0, 0, 0.0, 0.0, 0.0, 0.0 ));
  // p = msg.add_pose();
  // msgs::Set(p, ignition::math::Pose3d(10, , 0, 0, 0, 0));
  // p = msg.add_pose();
  msgs::Set(p, ignition::math::Pose3d(50.0, 0, 0, 0, 0, 0));

  transport::init();
  transport::run();
  transport::NodePtr node(new gazebo::transport::Node());
  node->Init("default");

  // modelmove_world is the name of the testing world
  const std::string topicName = "/gazebo/smoll_world/" + msg.model_name()
    + "/man_slide";
  gazebo::transport::PublisherPtr pathPub =
    node->Advertise<msgs::PoseAnimation>(topicName);

  std::cout << "Waiting for connection in " << topicName << std::endl;
  pathPub->WaitForConnection();
  pathPub->Publish(msg);

  std::cout << "Path published!" << std::endl;

  gazebo::transport::fini();
  return 0;
}
