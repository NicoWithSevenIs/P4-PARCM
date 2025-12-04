#pragma once

#include "../../../proto/generated/PARCM-P4.grpc.pb.h"
#include "../../../SHARED/GameObjectData/GameObjectData.h"

#include <vector>
#include <iostream>
#include <random>

#include "../Mesh Dispatcher/MeshDispatcher.h"

using namespace grpc;

typedef std::vector<Engine::GameObjectData> SceneData;


class WorldService final : public WORLD::Service
{
	
	std::vector<SceneData> scenes;

	public:
		SceneData GenerateScene(std::string client_id, std::string scene_id);
		Status InitializeClient(ServerContext* context, const CLIENT_JOIN_REQUEST* request, GRPC_SCENES_BATCH* response);
		void ConfigureTransform(GRPC_GAMEOBJECT* proto_go, Engine::GameObjectData engine_go);

};