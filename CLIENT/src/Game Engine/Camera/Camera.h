#pragma once

#include "../GameObject.h"
#include "../../../../SHARED/Math.h"

#include "../Component/Transform/TransformComponent.h"
#include "../../../../SHARED/Singleton.h"
#include "../../../../SHARED/Time/Time.h"

using namespace Math;


class Camera: public Engine::GameObject
{
	protected:
		float viewport_width;
		float viewport_height;

	public:
		float forward = 0;
		float right = 0;
		float up = 0;
		float x_rot = 0;
		float y_rot = 0;

	public:
		Camera(Engine::GameObjectData data, float viewport_width, float viewport_height);

	public:
		Matrix GetViewMatrix();
		Matrix GetProjectionMatrix();

	public:
		virtual void Update() override;
};

class CameraManager : public Singleton<CameraManager>
{
private:
	Camera* camera;
public:
	inline static Camera* GetCurrentCamera() { return get().camera; }
	inline static void SetCurrentCamera(Camera* current_camera) { get().camera = current_camera; }
};

