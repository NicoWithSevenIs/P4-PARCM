#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(): Component("MESH RENDERER", ComponentType::RENDERER) {}

void MeshRenderer::Initialize(std::string obj_path, std::string vs_path, std::string ps_path)
{	
	tinyobj::attrib_t attribs;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;

	std::cout << "Started" << std::endl;

	bool success = tinyobj::LoadObj(&attribs, &shapes, &materials, &warn, &err, ("MODELS/" + obj_path).c_str());

	if (!err.empty() || !success || shapes.size() > 1) {
		std::cout << "[ERROR] Mesh Config Error: " << err << std::endl;
		return;
	}

	for (size_t s = 0; s < shapes.size(); s++) {
		size_t index_offset = 0;

		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
			unsigned char num_face_verts = shapes[s].mesh.num_face_vertices[f];

			for (unsigned char v = 0; v < num_face_verts; v++) {

				tinyobj::index_t index = shapes[s].mesh.indices[index_offset + v];

				tinyobj::real_t vx = attribs.vertices[index.vertex_index * 3 + 0];
				tinyobj::real_t vy = attribs.vertices[index.vertex_index * 3 + 1];
				tinyobj::real_t vz = attribs.vertices[index.vertex_index * 3 + 2];

				auto vert = Math::Vector3f(vx, vy, vz);

				Math::Vector2f tex;
				if (index.texcoord_index >= 0) {
					tinyobj::real_t tx = attribs.texcoords[index.texcoord_index * 2 + 0];
					tinyobj::real_t ty = attribs.texcoords[index.texcoord_index * 2 + 1];
					tex = Math::Vector2f(tx, ty);
				}

				Math::Vector3f norms;
				if (index.normal_index >= 0) {
					tinyobj::real_t nx = attribs.normals[index.normal_index * 3 + 0];
					tinyobj::real_t ny = attribs.normals[index.normal_index * 3 + 1];
					tinyobj::real_t nz = attribs.normals[index.normal_index * 3 + 2];
					norms = Math::Vector3f(nx, ny, nz);
				}

				list_vertices.push_back(Vertex(vert, tex, norms));
				list_indices.push_back(index_offset + v);

			}

			index_offset += num_face_verts;
		}

	}

	std::cout << "Vertices: " << this->list_vertices.size() << std::endl;
	std::cout << "Indices: " << this->list_indices.size() << std::endl;

	std::cout << "Model Loaded" << std::endl;

	draw_args.vertex_shader		= GraphicsEngine::CompileVertexShader("mesh_vertex.hlsl");
	draw_args.pixel_shader		= GraphicsEngine::CompilePixelShader("mesh_pixel.hlsl");


	std::cout << "Creating Vertex Buffer" << std::endl;
	draw_args.vertex_buffer		= GraphicsEngine::CreateVertexBuffer(
												&this->list_vertices[0],
												sizeof(Vertex),
												this->list_vertices.size(),
												draw_args.vertex_shader->GetBlob()
											);
	std::cout << "Created Vertex Buffer" << std::endl;

	std::cout << "Creating Index Buffer" << std::endl;
	draw_args.index_buffer		= GraphicsEngine::CreateIndexBuffer(
												&this->list_indices[0],
												this->list_indices.size()
											);
	std::cout << "Created Index Buffer" << std::endl;

	std::cout << "Creating Constant Buffer" << std::endl;
	draw_args.constant_buffer	= GraphicsEngine::CreateConstantBuffer(
												&this->constant,
												sizeof(Constant)
											);
	std::cout << "Created Constant Buffer" << std::endl;
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
