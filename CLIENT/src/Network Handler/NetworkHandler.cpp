#include "NetworkHandler.h"


void NetworkHandler::Initialize()
{
	/*
	auto channel = CreateChannel("localhost:50051", InsecureChannelCredentials());
	get().stub = World::NewStub(channel);
	*/
}


void NetworkHandler::MessageServer()
{
	/*
	WorldRequest request;
	request.set_msg("ASDADASDFASD");

	WorldData response;
	ClientContext context;

	Status status = get().stub->InitializeClient(&context, request, &response);

	int go_size = response.game_objects_size();
	for (int i = 0; i < go_size; i++) {
		GameObject proto_go = response.game_objects(i);
		Transform t = proto_go.t();

		Vector3 position = t.position();
		Vector3 scale = t.scale();
		Vector3 rotation = t.rotation();

		Math::Vector3f t_pos(position.x(), position.y(), position.z());
		Math::Vector3f t_scale(scale.x(), scale.y(), scale.z());
		Math::Vector3f t_rot(rotation.x(), rotation.y(), rotation.z());

		Engine::Transform e_t(t_pos, t_scale, t_rot);

		auto engine_go = Engine::GameObjectData(proto_go.unique_id(), proto_go.name(), e_t, proto_go.mesh_id());
		engine_go.Print();
	}
	*/
}
