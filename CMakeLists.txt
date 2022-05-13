cmake_minimum_required(VERSION 3.0.2)
project(wire_manipulation_bt)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  actionlib_msgs
  actionlib
  wire_mapping
  std_msgs
  BehaviorTreeV3
)


catkin_package(
   INCLUDE_DIRS
   #LIBRARIES 
   CATKIN_DEPENDS std_msgs actionlib actionlib_msgs behaviortree_cpp_v3 roscpp
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations

include_directories( ${catkin_INCLUDE_DIRS})


add_executable(${PROJECT_NAME}_node
   src/test_bt.cpp
   src/pick_bt_node.cpp
   )


set_target_properties(${PROJECT_NAME}_node PROPERTIES OUTPUT_NAME my_nodes PREFIX "")

## Add cmake target dependencies of the executable
## same as for the library above
add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
target_link_libraries(${PROJECT_NAME}_node 
BT::behaviortree_cpp_v3
  ${catkin_LIBRARIES}
)




