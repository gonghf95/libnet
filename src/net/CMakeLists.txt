set(net_SRCS
 protobuf/msg.pb.cc
 protobuf/proto_id.pb.cc
 global.cc
 server_app.cc
 message_list.cc
 thread_mgr.cc
 thread.cc
 thread_obj.cc
 packet.cc
 network_buffer.cc
 base_buffer.cc
 network_listen.cc
 network_connector.cc
 network.cc
 connect_obj.cc
)

add_library(net SHARED ${net_SRCS})
target_link_libraries(net pthread protobuf)

add_subdirectory(tests)
