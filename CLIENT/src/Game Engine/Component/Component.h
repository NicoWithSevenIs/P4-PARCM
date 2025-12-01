#pragma once

#include "../../../../SHARED/IMediator.h"

namespace Engine {
	enum class ComponentType {
		INPUT,
		RENDERER,
		SCRIPT,
	};

	class Component {
		private:
			IMediator<Component>* owner;
			ComponentType type;
		public:
			inline Component(ComponentType type): type(type){}
		public:
			virtual void Update() = 0;
			inline virtual void Release(){}
		public:
			inline ComponentType GetType(){return this->type;}
			inline IMediator<Component>* GetOwner() {return this->owner;}
		public:
			inline void SetOwner(IMediator<Component>* new_owner){ this->owner = owner;}
	};
}

