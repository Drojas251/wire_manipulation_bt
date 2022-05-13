#include <ros/ros.h>

#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>

#include <wire_mapping/ManipulateAction.h>
#include <wire_mapping/ManipulateGoal.h>
#include <wire_mapping/ManipulateResult.h>
#include <wire_mapping/ManipulateFeedback.h>

#include "behaviortree_cpp_v3/behavior_tree.h"

#include <std_msgs/Float64.h>

class Pick : public BT::AsyncActionNode{
  public:

   MoveRail(const std::string& name, const BT::NodeConfiguration& config): BT::AsyncActionNode(name, config),
          _client("pick", true)
   {

   }

   static BT::PortsList providedPorts()
    {
        return{ BT::InputPort<double>("object_id") };
    }

    BT::NodeStatus tick() override;

    virtual void halt() override
    {
        _aborted = true;
    }

  private:
    typedef actionlib::SimpleActionClient<wire_mapping::ManipulateAction> PickClient;
    PickClient _client;
    bool _aborted;

};