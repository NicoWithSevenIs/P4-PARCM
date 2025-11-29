#pragma once

#include "../../SHARED/GameObject/GameObject.h"

class GameObjectWrapper{
	public:
		Engine::GameObject* gameobject;
	public:
		GameObjectWrapper(Engine::GameObject object): gameobject(object){}
		virtual void Update();
		virtual void Draw();
};