#pragma once
#include "Math.h"

namespace Engine {
	using namespace Math;

	class Transform {
	public:
		Vector3f position;
		Vector3f scale;
		Vector3f rotation;

	public:
		Transform() :
			position(Vector3f()),
			scale(Vector3f(1.f, 1.f, 1.f)),
			rotation(Vector3f())
		{
		}
		Transform(Vector3f position, Vector3f scale, Vector3f rotation):
			position(position), scale(scale), rotation(rotation){}
	};
}
