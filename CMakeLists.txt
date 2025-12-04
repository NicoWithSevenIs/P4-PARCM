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
set(SHARED_PATH "${CMAKE_CURRENT_SOURCE_DIR}/SHARED"
    CACHE PATH "LIBRARY_PATH" FORCE)

file (GLOB_RECURSE SHARED_SRC CONFIGURE_DEPENDS "${SHARED_PATH}/*.[ch]pp")    

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
    ${SHARED_SRC}
)

target_compile_definitions(P4_SERVER PUBLIC "PROTOBUF_USE_DLLS")

target_link_libraries (P4_SERVER PUBLIC 
    protobuf::libprotobuf
    gRPC::grpc
    gRPC::grpc++
    gRPC::grpc++_reflection
)

#IMGUI
set (IMGUI_SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/IMGUI
    CACHE PATH "Project IMGUI SRC" FORCE)

file (GLOB_RECURSE IMGUI_SRC CONFIGURE_DEPENDS "${IMGUI_SRC_PATH}/*.[ch]pp")

#Client
set(CLIENT_SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CLIENT/src
    CACHE PATH "Project Client SRC" FORCE)

file (GLOB_RECURSE CLIENT_SRC CONFIGURE_DEPENDS "${CLIENT_SRC_PATH}/*.[ch]pp")

add_executable (P4_CLIENT 
    "CLIENT/Client-Main.cpp"  
    ${PROTO_SRC} 
    ${PROTO_HEADERS} 
    ${CLIENT_SRC}
    ${SHARED_SRC}
    ${IMGUI_SRC}
    "CLIENT/src/Imgui Handler/Imgui Component/SceneMiniWindow.h" 
    "CLIENT/src/Graphics Engine/Texture/Texture.cpp" 
    "CLIENT/src/Graphics Engine/Texture/Texture.h")

target_include_directories(P4_CLIENT PRIVATE 
    ${IMGUI_SRC_PATH}
)

target_compile_definitions(P4_CLIENT PUBLIC 
    "PROTOBUF_USE_DLLS"
)

target_compile_definitions(P4_CLIENT PRIVATE
    "WIN32_LEAN_AND_MEAN"
    "NOMINMAX"
)

target_link_libraries (P4_CLIENT
    PUBLIC 
    protobuf::libprotobuf
    gRPC::grpc
    gRPC::grpc++
    gRPC::grpc++_reflection
)

# ------------------------------------------------------------
# --------------------- DirectXTex Added ----------------------
# ------------------------------------------------------------

set(DIRECTXTEX_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CLIENT/DirectXTex")

# If DirectXTex has an include folder, add it
if (EXISTS "${DIRECTXTEX_DIR}/include")
    target_include_directories(P4_CLIENT PRIVATE
        "${DIRECTXTEX_DIR}/include"
    )
endif()

# Link the DirectXTex .lib file
target_link_libraries(P4_CLIENT PRIVATE
    "${DIRECTXTEX_DIR}/bin/DirectXTex.lib"
)

# Copy DLL if it exists
if (EXISTS "${DIRECTXTEX_DIR}/bin/DirectXTex.dll")
    add_custom_command(TARGET P4_CLIENT POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${DIRECTXTEX_DIR}/bin/DirectXTex.dll"
            $<TARGET_FILE_DIR:P4_CLIENT>
    )
endif()

# ------------------------------------------------------------
# ------------------------------------------------------------

target_link_libraries(P4_CLIENT
    PRIVATE
    d3d11
    dxgi
    d3dcompiler
)

#Copy Shaders and Models
add_custom_command(TARGET P4_CLIENT POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:P4_CLIENT>/SHADERS
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:P4_CLIENT>/MODELS
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:P4_CLIENT>/IMAGES
)

add_custom_target(COPY ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/SHADERS
    $<TARGET_FILE_DIR:P4_CLIENT>/SHADERS

    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/MODELS
    $<TARGET_FILE_DIR:P4_CLIENT>/MODELS

    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/IMAGES
    $<TARGET_FILE_DIR:P4_CLIENT>/IMAGES
)
add_dependencies(P4_CLIENT COPY)