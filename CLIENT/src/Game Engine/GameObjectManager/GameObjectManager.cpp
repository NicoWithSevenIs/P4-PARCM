#include "GameObjectManager.h"

using namespace Engine;



GameObjectManager::GameObjectManager()
{

}

void Engine::GameObjectManager::UnloadCurrentScene()
{
	get().current_scene = nullptr;
}

void GameObjectManager::Update()
{
	for (auto& [uid, go_ptr] : get().main.scene_objects) 
		go_ptr->Update();
	
	if(!get().current_scene)
		return;
	
	for (auto& [uid, go_ptr] : get().current_scene->scene_objects)
		go_ptr->Update();
}

void GameObjectManager::Draw()
{
	for (auto& [uid, go_ptr] : get().main.scene_objects) {
		go_ptr->Draw();
	}

	if (!get().current_scene)
		return;

	for (auto& [uid, go_ptr] : get().current_scene->scene_objects)
		go_ptr->Draw();
}

void GameObjectManager::Release() {
	for (auto& [uid, go_ptr] : get().main.scene_objects) {
		go_ptr->Release();
		delete go_ptr;
	}
	get().main.scene_objects.clear();
}
