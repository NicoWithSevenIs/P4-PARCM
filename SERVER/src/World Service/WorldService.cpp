#include "WorldService.h"

SceneData WorldService::GenerateScene(std::string client_id, std::string scene_id)
{
	SceneData scene;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(10, 25);

	std::uniform_real_distribution<float> pos_dist(-5.0f, 5.0f);
	std::uniform_real_distribution<float> scale_dist(0.3f, 0.8f);
	std::uniform_real_distribution<float> rot_dist(-89.0f, 89.0f);

	int count = dist(gen);

	for (int i = 0; i < count; i++) 
	{
		std::string model = MeshDispatcher::DrawLots();
		std::string unique_id = client_id + "_" + scene_id + "_" + std::to_string(i);

		auto random_pos = Math::Vector3f(pos_dist(gen), pos_dist(gen)/2, pos_dist(gen));

		float uniform_scale = scale_dist(gen);
		auto random_scale = Math::Vector3f(uniform_scale, uniform_scale, uniform_scale);

		Engine::GameObjectData data
		(
			unique_id,
			unique_id + "_" + model,
			Engine::Transform
				(
					random_pos,
					random_scale,
					Math::Vector3f(0, rot_dist(gen), 0) * 3.141592653589793 / 180.f
				),
			model
		);
		scene.push_back(data);
	}

	return scene;
}

Status WorldService::InitializeClient
(
	ServerContext* context, 
	const CLIENT_JOIN_REQUEST* request, 
	GRPC_SCENES_BATCH* response
) 
{
	std::string id = request->client_id();
	for (int i = 0; i < 5; i++) {
		GRPC_SCENE* scene = response->add_scenes();
		SceneData scene_data = GenerateScene(id, std::to_string(i));
		std::cout << "----------" << i << "---------" << std::endl;
		for (auto& go_data : scene_data) {
			GRPC_GAMEOBJECT* go = scene->add_gameobjects();
			go->set_unique_id(go_data.GetUID());
			go->set_name(go_data.GetName());
			go->set_mesh_id(go_data.GetMeshID());
			ConfigureTransform(go, go_data);
			go_data.Print();
			std::cout << "--------------------" << std::endl;
		}
	}
	std::cout << "Initialized " << id << std::endl;
	return Status::OK;
}

void WorldService::ConfigureTransform(GRPC_GAMEOBJECT* proto_go, Engine::GameObjectData engine_go)
{

	auto ConfigureVector = [&](GRPC_VECTOR3* proto_vec, Math::Vector3f math_vec)
	{
		proto_vec->set_x(math_vec.x);
		proto_vec->set_y(math_vec.y);
		proto_vec->set_z(math_vec.z);
	};

	GRPC_TRANSFORM* proto_t = proto_go->mutable_transform();

	GRPC_VECTOR3* pos = proto_t->mutable_position();
	ConfigureVector(pos, engine_go.GetTransform().position);

	GRPC_VECTOR3* scale = proto_t->mutable_scale();
	ConfigureVector(scale, engine_go.GetTransform().scale);

	GRPC_VECTOR3* rot = proto_t->mutable_rotation();
	ConfigureVector(rot, engine_go.GetTransform().rotation);
}
