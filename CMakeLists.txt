cmake_minimum_required(VERSION 3.20.2)

project(helios CXX)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/output/bin)

#set(CMAKE_CXX_FLAGS "-D_GNU_SOURCE -D__STDC_LIMIT_MACROS -O2 -g2 -pipe -W -Wall -fPIC -lpthread -lz -L -I -std=gnu++11 -lrt -ldl -lprotobuf -lprotobuf-lite -lsofa-pbrpc")
set(CMAKE_CXX_FLAGS "-std=c++11 -pipe -W -Wall -fPIC -lpthread -lz -D_GLIBCXX_USE_CXX11_ABI=0 -lprotobuf -lprotobuf-lite -lsofa-pbrpc -lsnappy")

set(ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/../..)
set(PROTO_DIR ${CMAKE_CURRENT_LIST_DIR}/proto)

execute_process(COMMAND ${CMAKE_CURRENT_LIST_DIR}/thirdparty/protobuf/bin/protoc --proto_path=${PROTO_DIR} -I${CMAKE_CURRENT_LIST_DIR}/thirdparty/protobuf/include --cpp_out=${PROTO_DIR} ${PROTO_DIR}/helios.proto)

link_directories("${CMAKE_CURRENT_LIST_DIR}/thirdparty/protobuf/lib")
link_directories("${CMAKE_CURRENT_LIST_DIR}/thirdparty/sofa-pbrpc/lib")
link_directories("${CMAKE_CURRENT_LIST_DIR}/thirdparty/snappy/lib")

include_directories(proto src thirdparty/protobuf/include thirdparty/protobuf/include thirdparty/sofa-pbrpc/include thirdparty/snappy/include)
file(GLOB SOURCE_FILES src/*.cc proto/*.cc)
add_executable(helios ${SOURCE_FILES})

#target_link_libraries(helios protobuf protobuf-lite protoc sofa-pbrpc snappy)
target_link_libraries(helios sofa-pbrpc protobuf snappy)
