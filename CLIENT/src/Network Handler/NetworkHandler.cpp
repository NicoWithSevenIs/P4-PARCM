#include "NetworkHandler.h"


void NetworkHandler::Initialize()
{
	auto channel = CreateChannel("localhost:50051", InsecureChannelCredentials());
	get().stub = World::NewStub(channel);
}


void NetworkHandler::MessageServer()
{
	WorldRequest request;
	request.set_msg("ASDADASDFASD");

	WorldData response;
	ClientContext context;

	Status status = get().stub->InitializeClient(&context, request, &response);
}
