#include "ServerRunner.h"

void ServerRunner::Run() 
{
	


	std::string add("0.0.0.0:50051");
	WorldService world;
	grpc::ServerBuilder builder;

	builder.AddListeningPort(add, grpc::InsecureServerCredentials());
	builder.RegisterService(&world);

	auto server(builder.BuildAndStart());
	std::cout << "Server listening on " << add << std::endl;
	server->Wait();
	
}