#pragma once

#include "../../../../SHARED/IMediator.h"

namespace Engine {
	enum class ComponentType {
		INPUT,
		RENDERER,
		SCRIPT,
	};

	class Component {
		protected:
			IMediator<Component>* owner;
			bool initialized;
			std::string name;
			ComponentType type;
		public:
			inline Component(std::string name, ComponentType type): name(name), type(type), initialized(false), owner(nullptr){}
		public:
			virtual void Update() = 0;
			inline virtual void Release(){}
		public:
			inline std::string GetName() const {return this->name;}
			inline ComponentType GetType()  const {return this->type;}
			inline IMediator<Component>* GetOwner() const {return this->owner;}
		public:
			inline void SetOwner(IMediator<Component>* new_owner){ this->owner = new_owner;}
	};
}

