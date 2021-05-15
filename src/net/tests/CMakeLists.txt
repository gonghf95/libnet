set(robot_SRCS
 robot.cc
 robot_app.cc
 main.cc
)
add_executable(robot ${robot_SRCS})
target_link_libraries(robot net)