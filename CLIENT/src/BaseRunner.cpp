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
