#pragma once


#include "../../../SHARED/Singleton.h"
#include "../../../proto/generated/PARCM-P4.grpc.pb.h"

#include <memory>
#include <iostream>

using namespace grpc;

class NetworkHandler{
	private:
		std::unique_ptr<World::Stub> stub;
	
	public:
		inline NetworkHandler(std::shared_ptr<grpc::Channel> channel) :
			stub(World::NewStub(channel)) {
			
		}
	public:
		static void Initialize(std::shared_ptr<Channel> channel);
		static void MessageServer();
};