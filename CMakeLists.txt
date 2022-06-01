cmake_minimum_required(VERSION 3.20.2)

project(helios CXX)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/output/bin)

set(CMAKE_CXX_FLAGS "-std=c++11 -pipe -W -Wall -fPIC -lpthread -lz -D_GLIBCXX_USE_CXX11_ABI=0 -lprotobuf -lprotobuf-lite -lsofa-pbrpc -lsnappy -lcurl -lssl -lcrypto -luuid")

set(ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/../..)
set(PROTO_DIR ${CMAKE_CURRENT_LIST_DIR}/proto)

execute_process(COMMAND ${CMAKE_CURRENT_LIST_DIR}/thirdparty/protobuf/bin/protoc --proto_path=${PROTO_DIR} -I${CMAKE_CURRENT_LIST_DIR}/thirdparty/protobuf/include --cpp_out=${PROTO_DIR} ${PROTO_DIR}/helios.proto)

link_directories("${CMAKE_CURRENT_LIST_DIR}/thirdparty/protobuf/lib")
link_directories("${CMAKE_CURRENT_LIST_DIR}/thirdparty/sofa-pbrpc/lib")
link_directories("${CMAKE_CURRENT_LIST_DIR}/thirdparty/snappy/lib")
link_directories("${CMAKE_CURRENT_LIST_DIR}/thirdparty/libcurl/lib")
link_directories("${CMAKE_CURRENT_LIST_DIR}/thirdparty/openssl/lib")

include_directories(proto src thirdparty/protobuf/include thirdparty/protobuf/include thirdparty/sofa-pbrpc/include thirdparty/snappy/include thirdparty/bossdk/include thirdparty/libcurl/include thirdparty/jsoncpp/include)
file(GLOB SOURCE_FILES src/*.cc proto/*.cc thirdparty/bossdk/src/*/*.cpp thirdparty/bossdk/src/*/*/*.cpp thirdparty/jsoncpp/src/lib_json/*.cpp)
add_executable(helios ${SOURCE_FILES})

target_link_libraries(helios sofa-pbrpc protobuf snappy curl ssl)
