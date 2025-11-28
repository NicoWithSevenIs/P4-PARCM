#pragma once


#include "../../../SHARED/Singleton.h"

#include <grpcpp/grpcpp.h>
#include "../../../proto/generated/PARCM-P4.grpc.pb.h"

#include <iostream>


using namespace grpc;

class NetworkHandler: public Singleton<NetworkHandler>{

	private:
		std::unique_ptr<World::Stub> stub;
	
	public:
		static void Initialize();
		static void MessageServer();
};