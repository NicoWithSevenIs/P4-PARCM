#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(): Component(ComponentType::RENDERER)
{
}

void MeshRenderer::Initialize(std::string obj_path, std::string vs_path, std::string ps_path)
{
	
}


void MeshRenderer::Update()
{
	DrawArgs draw_args = {};

	GraphicsEngine::Draw(draw_args);
}
