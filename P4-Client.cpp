#include "P4-Client.h"
#include <grpcpp/grpcpp.h>
#include "proto/generated/hello.grpc.pb.h"

class HelloClient {
	private:
		std::unique_ptr<HelloGRPC::Stub> stub;
	public:
		HelloClient(std::shared_ptr<grpc::Channel> channel):
			stub(HelloGRPC::NewStub(channel)){}

		inline void SayHello(const std::string& name) {
			HelloRequest request;
			request.set_name(name);

			HelloReply response;
			grpc::ClientContext context;

			grpc::Status status = stub->SayHello(&context, request, &response);

			if (status.ok()) {
				std::cout << "Success: " << response.status() << std::endl;
				std::cout << "Message: " << response.msg() << std::endl;
			}
			else {
				std::cout << "Fail" << std::endl;
			}
		}
};

int main() {
	auto channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
	HelloClient client(channel);

	std::string msg = "";
	while (msg != "[END]") {
		std::cout << "Your Message: ";
		std::cin >> msg;
		client.SayHello(msg);
	}

	return 0;
}