#pragma once

namespace Math {
	
	//ensures type is always an integer type or a floating point type
	template<typename T>
	concept Number = std::integral<T> || std::floating_point<T>;

	template<Number N>
	class Vector2 {
		public:
			N x;
			N y;
		public:
			Vector2() : x(0), y(0) {}
			Vector2(N x, N y): x(x), y(y){}
	};

	template<Number N>
	class Vector3 {
		public:
			N x;
			N y;
			N z;
		public:
			Vector3() : x(0), y(0), z(0) {}
			Vector3(N x, N y, N z) : x(x), y(y), z(z) {}
	};

	typedef Vector2<float> Vector2f;
	typedef Vector2<unsigned int> Vector2u;
	typedef Vector2<int> Vector2i;

	typedef Vector3<float> Vector3f;
	typedef Vector3<unsigned int> Vector3u;
	typedef Vector3<int> Vector3i;
}

