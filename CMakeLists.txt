
cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project ("P4-PARCM")

find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

set(PROTO_SRC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/proto/generated"
	CACHE PATH "Proto Files" FORCE)

file (GLOB_RECURSE PROTO_SRC "${PROTO_SRC_PATH}/*.cc")
file (GLOB_RECURSE PROTO_HEADERS "${PROTO_SRC_PATH}/*.h")

set (SERVER_SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src_server
	CACHE PATH "Project Server SRC" FORCE)

file (GLOB_RECURSE SERVER_SRC_PATH CONFIGURE_DEPENDS 
	"${SERVER_SRC_PATH}/*.[ch]pp")

add_executable (GRPC_SERVER "P4-PARCM.cpp" "P4-PARCM.h"
	${PROTO_SRC} ${PROTO_HEADERS} ${SERVER_SRC})

target_compile_definitions(GRPC_SERVER PUBLIC "PROTOBUF_USE_DLLS")

target_link_libraries (GRPC_SERVER PUBLIC 
	protobuf::libprotobuf
	gRPC::grpc
	gRPC::grpc++
	gRPC::grpc++_reflection
)

set(CLIENT_SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src_client
	CACHE PATH "Project Client SRC" FORCE)

file (GLOB_RECURSE CLIENT_SRC CONFIGURE_DEPENDS "${CLIENT_SRC_PATH}/*.[ch]pp")

add_executable (GRPC_CLIENT "P4-Client.cpp" "P4-Client.h" 
	${PROTO_SRC} ${PROTO_HEADERS} ${CLIENT_SRC})

target_compile_definitions(GRPC_CLIENT PUBLIC "PROTOBUF_USE_DLLS")

target_link_libraries (GRPC_CLIENT PUBLIC 
	protobuf::libprotobuf
	gRPC::grpc
	gRPC::grpc++
	gRPC::grpc++_reflection
)
