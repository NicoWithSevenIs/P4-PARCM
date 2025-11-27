#include "P4-PARCM.h"
#include <grpcpp//grpcpp.h>

using namespace grpc;

/*
class temp final : public HelloGRPC::Service {
	public:
		Status SayHello(ServerContext* context, const HelloRequest* request, HelloReply* response) {
			std::cout << "MSG:" << request->name() << std::endl;
			response->set_status(true);
			response->set_msg("Hello from Server");
			return Status::OK;
		}
};

void RunServer() {
	std::string add("0.0.0.0:50051");
	temp service;
	ServerBuilder builder;

	builder.AddListeningPort(add, InsecureServerCredentials());
	builder.RegisterService(&service);

	auto server(builder.BuildAndStart());
	std::cout << "Server listening on " << add << std::endl;

	server->Wait();
}
*/
int main()
{
	//RunServer();
	return 0;
}
