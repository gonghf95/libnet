set(login_robot_SCRS
 robot_state_login.cc
 robot.cc
 robot_state.cc
 robot_app.cc
 main.cc
)

add_executable(login_robot ${login_robot_SCRS})
target_link_libraries(login_robot net)