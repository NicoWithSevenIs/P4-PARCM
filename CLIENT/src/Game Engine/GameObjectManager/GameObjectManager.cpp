#include "GameObjectManager.h"

using namespace Engine;


void GameObjectManager::AddGameObject(GameObjectData gameobject)
{
	if (this->object_map.contains(gameobject.GetUID()))
		return;

	auto go = new GameObject(gameobject);
	this->object_map[gameobject.GetUID()] = go;
}

void GameObjectManager::AddGameObjects(std::vector<GameObjectData> gameobjects)
{
	for (auto& go : gameobjects) {
		this->AddGameObject(go);
	}
}

void GameObjectManager::Update()
{
	for (auto& [uid, go_ptr] : this->object_map) {
		go_ptr->Update();
	}
}

void GameObjectManager::Draw()
{
	for (auto& [uid, go_ptr] : this->object_map) {
		go_ptr->Draw();
	}
}
