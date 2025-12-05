#include "NetworkHandler.h"

const int NetworkHandler::TIMEOUT = 30;
const int NetworkHandler::MAX_RETRIES = 3;


void NetworkHandler::Initialize()
{
	get().channel = CreateChannel("localhost:50051", InsecureChannelCredentials());
	get().wrld_stub = WORLD::NewStub(get().channel);
	get().md_stub = MESH_DISPATCHER::NewStub(get().channel);
}


void NetworkHandler::InformServer()
{
	CLIENT_JOIN_REQUEST request;
	request.set_client_id("CLIENT_SAMPLE");

	GRPC_SCENES_BATCH response;
	ClientContext context;

	Status status = get().wrld_stub->InitializeClient(&context, request, &response);
	int scenes_size = response.scenes_size();
	
	

	for (int i = 0; i < scenes_size; i++) 
	{
		GRPC_SCENE scene = response.scenes(i);
		Scene* s = new Scene();
		//std::cout << "----------" << i << "---------" << std::endl;
		int game_object_count = scene.gameobjects_size();
		for (int j = 0; j < game_object_count; j++) 
		{
			GRPC_GAMEOBJECT go = scene.gameobjects(j);
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

			//go_data.Print();
			//std::cout << "--------------------" << std::endl;

			auto new_go = new Engine::GameObject(go_data);
			auto mesh_renderer = new MeshRenderer();
			new_go->AddComponent(mesh_renderer);
			*s += new_go;
		}
		get().scene_cache.push_back(s);
	}
}


void NetworkHandler::ConfigureAllScenes()
{
	int i =0;
	for (auto& scene : get().scene_cache) {
		get().outputs[scene] = std::vector<std::string>();

		Task::Spawn([&, i]() {
						
			for (auto& [UID, GO] : scene->scene_objects) {
				Task::Sleep(100);

				int tries = 0;
				bool success ;

				do 
				{
					success = RequestMesh(get().channel, GO->data.GetMeshID(), scene);
					tries += 1;
				}
				while(!success && tries < MAX_RETRIES);

		
				{
					std::lock_guard<std::mutex> mtx(get().download_mutex);

					auto mesh_renderer = (MeshRenderer*)GO->Get("MESH RENDERER");
					mesh_renderer->InitializeFromString(get().outputs[scene].back());

					get().progress[i] = get().outputs[scene].size() / (float)scene->scene_objects.size();
				}
			}
			
	
		});

		i++;
	}


}

bool NetworkHandler::RequestMesh(std::shared_ptr<Channel> channel, std::string mesh_id, Scene* scene)
{
	MESH_REQUEST request;
	request.set_mesh_id(mesh_id);


	ClientContext context;
	auto deadline = std::chrono::system_clock::now() + std::chrono::seconds(TIMEOUT);
	context.set_deadline(deadline);


	std::unique_ptr<grpc::ClientReader<MESH>> reader(get().md_stub->DownloadMesh(&context, request));

	MESH meshChunk;
	std::string downloaded;
	

	while (reader->Read(&meshChunk))
	{
		downloaded += meshChunk.mesh_data();
	}

	std::lock_guard<std::mutex> mtx(get().download_mutex);
	get().outputs[scene].push_back(downloaded);
		
	grpc::Status status = reader->Finish();
	
	if (!status.ok())
	{
		std::cerr << "[ERROR] Mesh Download Failed: " << status.error_message() << "." << std::endl;
		return false;
	}
	return true;
}
