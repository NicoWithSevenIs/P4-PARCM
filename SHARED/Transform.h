#pragma once
#include "Math.h"

using namespace Math;

class Transform {
	public:
		Vector2f position;
		Vector2f scale;
		Vector2f rotation;

	public:
		Transform(): position(Vector2f()), scale(Vector2f(1,1,1), rotation(Vector2f()){}
};