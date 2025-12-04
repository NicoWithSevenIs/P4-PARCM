#include "MeshDispatcher.h"

std::vector<std::string> 
MeshDispatcher::model_pool = {
	"lucy.obj",
	"cow.obj",
	"homer.obj"
};

std::string MeshDispatcher::DrawLots()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, model_pool.size() - 1);
	return model_pool[dist(gen)];
}

Status MeshDispatcher::DownloadMesh
(
	ServerContext* context, 
	const MESH_REQUEST* request, 
	ServerWriter<MESH>* response
) 
{
	std::string filename = "MODELS/" + request->mesh_id();
	std::ifstream obj(filename);

	if (!obj.is_open()) {
		std::cerr << "Failed to open OBJ file: " << filename;
		return Status::ABORTED;
	}

	std::stringstream stream;
	stream << obj.rdbuf();

	std::string line;
	std::vector<std::string> partitioned;

	while (std::getline(stream, line)) {
		partitioned.push_back(line);
	}

	for (auto& line : partitioned) {
		batch += line + "\n";              
		MESH chunk;
		chunk.set_mesh_data(batch);    
		response->Write(chunk);
		batch.clear();
	}

	return Status::OK;
}