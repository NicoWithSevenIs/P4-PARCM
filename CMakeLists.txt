
cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project ("P4-PARCM")



#Proto
find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

set(PROTO_SRC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/proto/generated"
	CACHE PATH "PROTO_FILES" FORCE)

file (GLOB_RECURSE PROTO_SRC "${PROTO_SRC_PATH}/*.cc")
file (GLOB_RECURSE PROTO_HEADERS "${PROTO_SRC_PATH}/*.h")


#Library

set(LIBRARY_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Library"
	CACHE PATH "LIBRARY_PATH" FORCE)

file (GLOB_RECURSE LIBRARY_SRC CONFIGURE_DEPENDS "${LIBRARY_PATH}/*.[ch]pp")	

#Server

set (SERVER_SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/SERVER/src
	CACHE PATH "SERVER_SRC" FORCE)

file (GLOB_RECURSE SERVER_SRC CONFIGURE_DEPENDS 
	"${SERVER_SRC_PATH}/*.[ch]pp")

add_executable (P4_SERVER 
	"SERVER/Server-Main.cpp" 
	${PROTO_SRC} 
	${PROTO_HEADERS} 
	${SERVER_SRC} 
	${LIBRARY_SRC}
)

target_compile_definitions(P4_SERVER PUBLIC "PROTOBUF_USE_DLLS")

target_link_libraries (P4_SERVER PUBLIC 
	protobuf::libprotobuf
	gRPC::grpc
	gRPC::grpc++
	gRPC::grpc++_reflection
)

#Client

set(CLIENT_SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CLIENT/src
	CACHE PATH "Project Client SRC" FORCE)

file (GLOB_RECURSE CLIENT_SRC CONFIGURE_DEPENDS "${CLIENT_SRC_PATH}/*.[ch]pp")

add_executable (P4_CLIENT 
	"CLIENT/Client-Main.cpp"  
	${PROTO_SRC} 
	${PROTO_HEADERS} 
	${CLIENT_SRC}
	${LIBRARY_SRC}
)

target_compile_definitions(P4_CLIENT PUBLIC "PROTOBUF_USE_DLLS")

target_link_libraries (P4_CLIENT
	PUBLIC 
	protobuf::libprotobuf
	gRPC::grpc
	gRPC::grpc++
	gRPC::grpc++_reflection
)

target_link_libraries(P4_CLIENT
	PRIVATE
    d3d11
    dxgi
    d3dcompiler
)
