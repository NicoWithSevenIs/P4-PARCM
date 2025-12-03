#include "GameObjectManager.h"

using namespace Engine;



GameObjectManager::GameObjectManager()
{

}

GameObject* GameObjectManager::AddGameObject(GameObjectData gameobject)
{
	if (get().object_map.contains(gameobject.GetUID()))
		return nullptr;

	auto go = new GameObject(gameobject);
	get().object_map[gameobject.GetUID()] = go;
	return go;
}

void GameObjectManager::AddGameObject(GameObject* gameobject)
{
	if (!get().object_map.contains(gameobject->data.GetUID()))
		get().object_map[gameobject->data.GetUID()] = gameobject;
}

void GameObjectManager::AddGameObjects(std::vector<GameObjectData> gameobjects)
{
	for (auto& go : gameobjects) {
		this->AddGameObject(go);
	}
}

void GameObjectManager::Update()
{
	for (auto& [uid, go_ptr] : get().object_map) {
		go_ptr->Update();
	}
}

void GameObjectManager::Draw()
{
	for (auto& [uid, go_ptr] : get().object_map) {
		go_ptr->Draw();
	}
}

void GameObjectManager::Release() {
	for (auto& [uid, go_ptr] : get().object_map) {
		go_ptr->Release();
		delete go_ptr;
	}
	get().object_map.clear();
}
