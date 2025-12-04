#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(): Component("MESH RENDERER", ComponentType::RENDERER) {}

void MeshRenderer::Initialize(std::string obj_path, std::string vs_path, std::string ps_path)
{	
	tinyobj::attrib_t attribs;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;

	bool success = tinyobj::LoadObj(&attribs, &shapes, &materials, &warn, &err, ("MODELS/" + obj_path).c_str());

	if (!err.empty() || !success || shapes.size() > 1) {
		std::cout << "[ERROR] Mesh Config Error: " << err << std::endl;
		return;
	}

	for (int i = 0; i < shapes[0].mesh.indices.size(); i++) {
		tinyobj::index_t vData = shapes[0].mesh.indices[i];

		tinyobj::real_t x = attribs.vertices[vData.vertex_index * 3];
		tinyobj::real_t y = attribs.vertices[vData.vertex_index * 3 + 1];
		tinyobj::real_t z = attribs.vertices[vData.vertex_index * 3 + 2];

		list_vertices.push_back(Vector3f(x,y,z));
	}

	Vector3f min, max;

	for (auto& v : list_vertices) {
		if (v.x < min.x) min.x = v.x;
		if (v.y < min.y) min.y = v.y;
		if (v.z < min.z) min.z = v.z;

		if (v.x > max.x) max.x = v.x;
		if (v.y > max.y) max.y = v.y;
		if (v.z > max.z) max.z = v.z;
	}
	
	Vector3f center = (min + max) / 2;
	for (auto& v : list_vertices) {
		v = v -  center; 
	}

	draw_args.vertex_shader		= GraphicsEngine::CompileVertexShader("mesh_vertex.hlsl");
	draw_args.pixel_shader		= GraphicsEngine::CompilePixelShader("mesh_pixel.hlsl");
	draw_args.vertex_buffer		= GraphicsEngine::CreateVertexBuffer(
												&this->list_vertices[0],
												sizeof(Vector3f),
												this->list_vertices.size(),
												draw_args.vertex_shader->GetBlob()
											);
	draw_args.constant_buffer	= GraphicsEngine::CreateConstantBuffer(
												&this->constant,
												sizeof(Constant)
											);

	initialized = true;
}

bool once = false;

void MeshRenderer::Update()
{
	if(!initialized)
		return;
	
	auto transform = (TransformComponent*)owner->Get("TRANSFORM");

	constant.transform_matrix = transform->transform_matrix;
	constant.deltaTime = Time::deltaTime();
	constant.projection_matrix = CameraManager::GetCurrentCamera()->GetProjectionMatrix();
	constant.view_matrix = CameraManager::GetCurrentCamera()->GetViewMatrix();

	draw_args.constant_buffer->Update(GraphicsEngine::GetDeviceContext(), &constant);
	GraphicsEngine::Draw(draw_args);
}
