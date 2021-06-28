set(net_SRCS
 entity_system.cc
 entity.cc
 component.cc
)
add_library(net SHARED ${net_SRCS})

add_subdirectory(test)