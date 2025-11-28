#include "BaseRunner.h"

BaseRunner::BaseRunner(): Window()
{
}

void BaseRunner::OnCreate()
{
	GraphicsEngine::Initialize(this);
}

void BaseRunner::OnUpdate()
{
	GraphicsEngine::Clear(Math::Color::NICO_BLUE);
	std::cout << Time::deltaTime() << std::endl;
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
