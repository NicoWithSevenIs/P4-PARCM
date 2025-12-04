#pragma once

#include "../../../proto/generated/PARCM-P4.grpc.pb.h"
#include "../../../SHARED/GameObjectData/GameObjectData.h"

#include <vector>
#include <iostream>

using namespace grpc;

typedef std::vector<Engine::GameObjectData> SceneData;

class WorldService final : public World::Service
{
	private:
		std::vector<Engine::GameObjectData> gameobjects;

	private:
		inline void ConfigureTransform(GameObject* proto_go, Engine::GameObjectData engine_go) {
			auto ConfigureVector = [&](Vector3* proto_vec, Math::Vector3f math_vec)
			{
				proto_vec->set_x(math_vec.x);
				proto_vec->set_y(math_vec.y);
				proto_vec->set_z(math_vec.z);
			};
			Transform* proto_t = proto_go->mutable_t();

			Vector3* pos = proto_t->mutable_position();
			ConfigureVector(pos, engine_go.GetTransform().position);

			Vector3* scale = proto_t->mutable_scale();
			ConfigureVector(scale, engine_go.GetTransform().scale);

			Vector3* rot = proto_t->mutable_rotation();
			ConfigureVector(rot, engine_go.GetTransform().rotation);
		}
	public:
		inline Status InitializeClient(ServerContext* context, const WorldRequest* request, WorldData* response) {
			
			std::cout << "Request ID: " << request->msg() << std::endl;
			std::vector<GameObject> gos;
			
			for (auto& engine_go : this->gameobjects) {
				GameObject* proto_go = response->add_game_objects();
			
				proto_go->set_name(engine_go.GetName());
				proto_go->set_unique_id(engine_go.GetUID());
				proto_go->set_mesh_id(engine_go.GetMeshID());

				ConfigureTransform(proto_go, engine_go);
			}

			return Status::OK;
		}
		inline void AddGameObject(Engine::GameObjectData obj) {
			gameobjects.push_back(obj);
		}
};