#include <ros/ros.h>


#include "behaviortree_cpp_v3/bt_factory.h"
//#include "my_robot_behavior_trees/move_rail_action.hpp"
#include "pick_bt_node.h"


BT::NodeStatus Pick::tick() {
  // if no server is present, fail after 2 seconds
  if (!_client.waitForServer(ros::Duration(2.0))) {
    ROS_ERROR("Can't contact move_base server");
    return BT::NodeStatus::FAILURE;
  }

  // Take the goal from the InputPort of the Node
  std::string object_id;


  if (!getInput<std::string>("object_id", object_id)) {
    // if I can't get this, there is something wrong with your BT.
    // For this reason throw an exception instead of returning FAILURE
    throw BT::RuntimeError("missing required input [goal]");
  }

  // Reset this flag
  _aborted = false;

  ROS_INFO("Sending goal ");

  wire_mapping::ManipulateGoal msg;

  std::string retreat = "+z"

  std::vector<std::string> axis_constraints(0);

  msg.object_id = object_id
  msg.retreat = retreat
  msg.axis_constraints = axis_constraints;

  _client.sendGoal(msg);

  while (!_aborted && !_client.waitForResult(ros::Duration(0.02))) {
    // polling at 50 Hz. No big deal in terms of CPU
  }

  if (_aborted) {
    // this happens only if method halt() was invoked
    //_client.cancelAllGoals();
    ROS_ERROR("MoveRail aborted");
    return BT::NodeStatus::FAILURE;
  }

  if (_client.getState() != actionlib::SimpleClientGoalState::SUCCEEDED) {
    ROS_ERROR("MoveRail failed");
    return BT::NodeStatus::FAILURE;
  }

  ROS_INFO("Target reached");
  return BT::NodeStatus::SUCCESS;
}