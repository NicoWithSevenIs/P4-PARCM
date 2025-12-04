#pragma once


#include "../../../SHARED/Singleton.h"
#include "../../../proto/generated/PARCM-P4.grpc.pb.h"
#include "../../../SHARED/GameObjectData/GameObjectData.h"
#include "../Game Engine/GameObjectManager/Scene.h"
#include "../Game Engine/Component/Mesh Renderer/MeshRenderer.h"


#include <grpcpp/grpcpp.h>
#include <iostream>
#include <vector>

using namespace grpc;

class NetworkHandler: public Singleton<NetworkHandler>
{
	private:
		std::unique_ptr<WORLD::Stub> wrld_stub;
		std::unique_ptr<MESH_DISPATCHER::Stub> md_stub;

	public:
		std::vector<Scene*> scene_cache;
	
	public:
		static void Initialize();
		static void InformServer();
};