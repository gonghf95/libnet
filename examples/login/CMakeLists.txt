set(login_SRCS
 http_request_account.cc
 http_request.cc
 player_mgr.cc
 player.cc
 account.cc
 login_app.cc
 main.cc
)

add_executable(login ${login_SRCS})
target_link_libraries(login net jsoncpp curl)

add_subdirectory(robot)