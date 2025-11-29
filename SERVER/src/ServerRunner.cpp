#include "ServerRunner.h"
#include "World Service/WorldService.h"


void ServerRunner::Run() 
{
	std::string add("0.0.0.0:50051");
	WorldService world;
	grpc::ServerBuilder builder;

	builder.AddListeningPort(add, grpc::InsecureServerCredentials());
	builder.RegisterService(&world);

	Engine::GameObjectData go = Engine::GameObjectData("some_id", "cube");
	go.Print();
	world.AddGameObject(go);

	auto server(builder.BuildAndStart());
	std::cout << "Server listening on " << add << std::endl;
	server->Wait();
}