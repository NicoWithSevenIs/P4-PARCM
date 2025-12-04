#pragma once

#include "../../../proto/generated/PARCM-P4.grpc.pb.h"

#include <vector>
#include <random>
#include <fstream>
#include <sstream>

using namespace grpc;



class MeshDispatcher final: public MESH_DISPATCHER::Service 
{
	public:
		static std::vector<std::string> model_pool;
	
	public:
		static std::string DrawLots();
		Status DownloadMesh(ServerContext* context, const MESH_REQUEST* request, ServerWriter<MESH>* response);
};