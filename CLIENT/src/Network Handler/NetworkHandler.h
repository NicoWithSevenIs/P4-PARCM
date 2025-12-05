#pragma once


#include "../../../SHARED/Singleton.h"
#include "../../../proto/generated/PARCM-P4.grpc.pb.h"
#include "../../../SHARED/GameObjectData/GameObjectData.h"
#include "../Game Engine/GameObjectManager/Scene.h"
#include "../Game Engine/Component/Mesh Renderer/MeshRenderer.h"
#include "../../../SHARED/Threading/Task.h"

#include <grpcpp/grpcpp.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <mutex>

using namespace grpc;



class NetworkHandler: public Singleton<NetworkHandler>
{
	public:
		static const int TIMEOUT;
		static const int MAX_RETRIES;

	private:
		std::unique_ptr<WORLD::Stub> wrld_stub;
		std::unique_ptr<MESH_DISPATCHER::Stub> md_stub;

	private:
		std::unordered_map<Scene*, std::vector<std::string>> outputs;
		std::mutex download_mutex;

	public:
		std::vector<Scene*> scene_cache;
		std::shared_ptr<Channel> channel;

	public:
		std::vector<float> progress = {0,0,0,0,0};

	public:
		static void Initialize();
		static void InformServer();
		static void ConfigureAllScenes();
		static bool RequestMesh(std::shared_ptr<Channel> channel, std::string mesh_id, Scene* scene);
};