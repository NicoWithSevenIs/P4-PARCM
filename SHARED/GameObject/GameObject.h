#pragma once

#include "../Transform.h"
#include <string>

class GameObject {
	private:
		std::string unique_id;
		std::string name;

	private:
		Transform transform;
		std::string mesh_id;

	public:
		inline GameObject(std::string unique_id, std::string name): unique_id(unique_id), name(name), mesh_id(""){}

};