#include "BaseRunner.h"

BaseRunner::BaseRunner(): Window()
{
}

void BaseRunner::OnCreate()
{
	GraphicsEngine::Initialize(this);
	NetworkHandler::Initialize();
	NetworkHandler::MessageServer();
}

void BaseRunner::OnUpdate()
{
	GraphicsEngine::Clear(Math::Color::NICO_BLUE);
	GraphicsEngine::Present(this);
}

void BaseRunner::OnDestroy()
{
}

void BaseRunner::OnFocus()
{
}

void BaseRunner::OnUnfocus()
{
}
