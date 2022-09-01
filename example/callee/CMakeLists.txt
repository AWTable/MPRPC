set(SRC_LIST userservice.cc ../user.pb.cc)

add_executable(provider ${SEC_LIST})
target_link_libraries(provider mprpc protobuf)