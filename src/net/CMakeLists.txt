set(net_SRCS
 entity.cc
 component.cc
)
add_library(net SHARED ${net_SRCS})

add_subdirectory(test)