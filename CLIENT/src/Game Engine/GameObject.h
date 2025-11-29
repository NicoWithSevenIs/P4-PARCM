#pragma once

#include "../../../SHARED/GameObjectData/GameObjectData.h"

namespace Engine {
	class GameObject {
		public:
			GameObjectData* data;
		public:
			GameObject(GameObjectData object) {}
			virtual void Update();
			virtual void Draw();
			void Release();
	};
}
