
cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project ("P4-PARCM")

find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

#Proto

set(PROTO_SRC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/proto/generated"
	CACHE PATH "Proto Files" FORCE)

file (GLOB_RECURSE PROTO_SRC "${PROTO_SRC_PATH}/*.cc")
file (GLOB_RECURSE PROTO_HEADERS "${PROTO_SRC_PATH}/*.h")

#Server

set (SERVER_SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src_server
	CACHE PATH "Project Server SRC" FORCE)

file (GLOB_RECURSE SERVER_SRC_PATH CONFIGURE_DEPENDS 
	"${SERVER_SRC_PATH}/*.[ch]pp")

add_executable (GRPC_SERVER "SERVER/Server-Main.cpp" 
	${PROTO_SRC} ${PROTO_HEADERS} ${SERVER_SRC} 
		"SERVER/P4/GameObjectManager.h" 
		"SERVER/P4/GameObjectManager.cpp"
)

target_compile_definitions(GRPC_SERVER PUBLIC "PROTOBUF_USE_DLLS")

target_link_libraries (GRPC_SERVER PUBLIC 
	protobuf::libprotobuf
	gRPC::grpc
	gRPC::grpc++
	gRPC::grpc++_reflection
)

#Client

set(CLIENT_SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src_client
	CACHE PATH "Project Client SRC" FORCE)

file (GLOB_RECURSE CLIENT_SRC CONFIGURE_DEPENDS "${CLIENT_SRC_PATH}/*.[ch]pp")

add_executable (GRPC_CLIENT "CLIENT/Client-Main.cpp"  
	${PROTO_SRC} ${PROTO_HEADERS} ${CLIENT_SRC})

target_compile_definitions(GRPC_CLIENT PUBLIC "PROTOBUF_USE_DLLS")

target_link_libraries (GRPC_CLIENT PUBLIC 
	protobuf::libprotobuf
	gRPC::grpc
	gRPC::grpc++
	gRPC::grpc++_reflection
)
