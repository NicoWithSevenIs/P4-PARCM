#include "NetworkHandler.h"


void NetworkHandler::Initialize()
{
	auto channel = CreateChannel("localhost:50051", InsecureChannelCredentials());
	get().stub = WORLD::NewStub(channel);
}


void NetworkHandler::InformServer()
{
	CLIENT_JOIN_REQUEST request;
	request.set_client_id("CLIENT_SAMPLE");

	GRPC_SCENES_BATCH response;
	ClientContext context;

	Status status = get().stub->InitializeClient(&context, request, &response);
	int scenes_size = response.scenes_size();
	
	for (int i = 0; i < scenes_size; i++) 
	{
		GRPC_SCENE scene = response.scenes(i);
		Scene* s = new Scene();

		int game_object_count = scene.gameobjects_size();
		for (int j = 0; j < game_object_count; j++) 
		{
			GRPC_GAMEOBJECT go = scene.gameobjects(i);
			GRPC_TRANSFORM t = go.transform();

			GRPC_VECTOR3 pos = t.position();
			GRPC_VECTOR3 scale = t.scale();
			GRPC_VECTOR3 rot = t.rotation();

			Engine::Transform t_data(
				Math::Vector3f(pos.x(), pos.y(), pos.z()),
				Math::Vector3f(scale.x(), scale.y(), scale.z()),
				Math::Vector3f(rot.x(), rot.y(), rot.z())
			);

			Engine::GameObjectData go_data(
				go.unique_id(),
				go.name(),
				t_data,
				go.mesh_id()
			);

			auto new_go = new Engine::GameObject(go_data);
			auto mesh_renderer = new MeshRenderer();
			new_go->AddComponent(mesh_renderer);
			*s += new_go;
		}
		get().scene_cache.push_back(s);
	}
}
