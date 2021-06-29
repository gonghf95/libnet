set(net_SRCS
 test_c_update.cc
 test_entity.cc
 entity_system.cc
 entity.cc
 component.cc
)
add_library(net SHARED ${net_SRCS})

add_subdirectory(test)