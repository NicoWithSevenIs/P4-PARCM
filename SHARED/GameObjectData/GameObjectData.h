#pragma once

#include "../Transform.h"
#include <string>
#include <iostream>

namespace Engine {
	class GameObjectData {
		protected:
			std::string unique_id;
			std::string name;

		protected:
			Transform transform;
			std::string mesh_id;

		public:
			inline GameObjectData(std::string unique_id, std::string name) : unique_id(unique_id), name(name), mesh_id("") {}
			inline GameObjectData(std::string unique_id, std::string name, Transform t, std::string mesh_id) :
				unique_id(unique_id), name(name), transform(t), mesh_id(mesh_id) {}

			inline void Print() {
				std::cout << "Name: " << name << std::endl;
				std::cout << "UID: " << unique_id << std::endl;
				std::cout << "Position: " << transform.position << std::endl;
				std::cout << "Scale: " << transform.scale << std::endl;
				std::cout << "Rotation: " << transform.rotation << std::endl;
				std::cout << "Mesh ID: " << mesh_id << std::endl;
			}
		public:
			inline std::string GetName() const {return this->name;}
			inline std::string GetUID() const {return this->unique_id;}
			inline Transform GetTransform() const {return this->transform;}
			inline std::string GetMeshID() const {return this->mesh_id;}
	};
}
