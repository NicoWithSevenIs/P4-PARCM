#pragma once

#include "../../../proto/generated/PARCM-P4.grpc.pb.h"
#include <vector>


using namespace grpc;

class WorldService final : public World::Service
{
	Status InitializeClient(ServerContext* context, const WorldRequest* request, WorldData* response) {
		std::cout << "Request ID: " << request->msg() << std::endl;
		return Status::OK;
	}
};