set(echosvr_SRC
 message_handler.cc
 server.cc
 echosvr.cc
)
add_executable(echosvr ${echosvr_SRC})
target_link_libraries(echosvr net)
