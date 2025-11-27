set protobuf_cmd="C:\VCPKG\vcpkg\packages\protobuf_x64-windows\tools\protobuf\protoc"
set grpc_exe_dir="C:\VCPKG\vcpkg\installed\x64-windows\tools\grpc\grpc_cpp_plugin.exe"
set src="%cd%"
set proto_file="%cd%\hello.proto"
set dest="%cd%\generated"
%protobuf_cmd% --proto_path=%src% --cpp_out=%dest% --grpc_out=%dest% --plugin=protoc-gen-grpc=%grpc_exe_dir% %proto_file%