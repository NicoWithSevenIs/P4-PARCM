#pragma once

#include <array>
#include <memory>
#include <iostream>
#include <cmath>
#include <cassert>
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


	typedef Vector2<float> Vector2f;
	typedef Vector2<unsigned int> Vector2u;
	typedef Vector2<int> Vector2i;


	template<Number N>
	class Vector3 {
		public:
			N x;
			N y;
			N z;
		public:
			Vector3() : x(0), y(0), z(0) {}
			Vector3(N x, N y, N z) : x(x), y(y), z(z) {}
		public:
			inline friend std::ostream& operator << (std::ostream& os, const Vector3<N>& vec) {
				os << "(" << vec.x << "," << vec.y << "," << vec.z << ")";
				return os;
			}

			Vector3 operator+(const Vector3& rhs) {
				return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
			}

			Vector3 operator-(const Vector3& rhs) {
				return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
			}

			Vector3 operator*(const N& scalar) {
				return Vector3(x * scalar, y * scalar, z*scalar);
			}

			Vector3 operator/(const N& scalar) {
				assert(scalar != 0);
				return (*this) * (1/scalar);
			}

	};


	typedef Vector3<float> Vector3f;
	typedef Vector3<unsigned int> Vector3u;
	typedef Vector3<int> Vector3i;


	class Color {
		public:
			unsigned int r;
			unsigned int g;
			unsigned int b;
			unsigned int a;
		public:
			Color(): r(0), g(0), b(0), a(255){}
			Color(unsigned int r, unsigned int g, unsigned int b): r(r), g(g), b(b), a(1){}
			Color(unsigned int r, unsigned int g, unsigned int b, unsigned int a) : r(r), g(g), b(b), a(a) {}
		public:
			inline std::array<float, 4> Scalar() const{
				return {r/255.f, g/255.f, b/255.f, a/255.f};
			}
		public:
			static Color WHITE;
			static Color BLACK;
			static Color GRAY;
			static Color RED;
			static Color GREEN;
			static Color BLUE;
			static Color CYAN;
			static Color YELLOW;
			static Color MAGENTA;
			static Color NICO_BLUE;
	};

	template<Number N>
	class Vector4 {
	public:
		N x;
		N y;
		N z;
		N w;
	public:
		Vector4() : x(0), y(0), z(0), w(0) {}
		Vector4(N x, N y, N z, N w) : x(x), y(y), z(z), w(w) {}
	public:
		inline friend std::ostream& operator << (std::ostream& os, const Vector4<N>& vec) {
			os << "(" << vec.x << "," << vec.y << "," << vec.z << vec.w << ")";
			return os;
		}
	};

	typedef Vector4<float> Vector4f;
	typedef Vector4<unsigned int> Vector4u;
	typedef Vector4<int> Vector4i;

	inline Vector4f Cross(Vector4f& v1, Vector4f& v2, Vector4f& v3)
	{
		Vector4f vec;
		
		vec.x = v1.y * (v2.z * v3.w - v3.z * v2.w)
			- v1.z * (v2.y * v3.w - v3.y * v2.w)
			+ v1.w * (v2.y * v3.z - v2.z * v3.y);

		vec.y = -(v1.x * (v2.z * v3.w - v3.z * v2.w)
			- v1.z * (v2.x * v3.w - v3.x * v2.w)
			+ v1.w * (v2.x * v3.z - v3.x * v2.z));

		vec.z = v1.x * (v2.y * v3.w - v3.y * v2.w)
			- v1.y * (v2.x * v3.w - v3.x * v2.w)
			+ v1.w * (v2.x * v3.y - v3.x * v2.y);

		vec.w = -(v1.x * (v2.y * v3.z - v3.y * v2.z)
			- v1.y * (v2.x * v3.z - v3.x * v2.z)
			+ v1.z * (v2.x * v3.y - v3.x * v2.y));

		return vec;
	}

	class Matrix{
		public:
			float values[4][4] = {};

		public:
			inline Matrix() {
				Identity();
			}

			inline void Identity() {
				::memset(values, 0, sizeof(float) * 16);
				for (int i = 0; i < 4; i++)
					values[i][i] = 1;
			}

			inline float* operator[](size_t col) {
				return values[col];
			}

			inline const float* operator[](size_t col) const {
				return values[col];
			}
			
			inline Matrix operator* (const Matrix& rhs) {
				Matrix out;
				Matrix lhs = *this;

				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						out.values[i][j] =
							lhs[i][0] * rhs[0][j] +
							lhs[i][1] * rhs[1][j] +
							lhs[i][2] * rhs[2][j] +
							lhs[i][3] * rhs[3][j];
					}
				}

				return out;
			}

			inline void operator *= (const Matrix& rhs) {
				*this = *this * rhs;
			}
		
			inline static Matrix Translation(const Vector3f& vec) {
				auto m = Matrix();
				m[3][0] = vec.x;
				m[3][1] = vec.y;
				m[3][2] = vec.z;
				return m;
			}

			inline static Matrix Scale(const Vector3f& vec) {
				auto m = Matrix();
				m[0][0] = vec.x;
				m[1][1] = vec.y;
				m[2][2] = vec.z;
				return m;
			}

			inline static Matrix Rotation(const Vector3f& vec) {
				auto rot = Matrix();

				auto x = Matrix();
				x[1][1] = cos(vec.x);
				x[1][2] = -sin(vec.x);
				x[2][1] = sin(vec.x);
				x[2][2] = cos(vec.x);

				auto y = Matrix();
				y[0][0] = cos(vec.y);
				y[0][2] = sin(vec.y);
				y[2][0] = -sin(vec.y);
				y[2][2] = cos(vec.y);

				auto z = Matrix();
				z[0][0] = cos(vec.z);
				z[0][2] = sin(vec.z);
				z[2][0] = -sin(vec.z);
				z[2][2] = cos(vec.z);


				return (x*y)*z;
			}

			inline static Matrix  OrthographicProjection(float width, float height, float near_plane, float far_plane)
			{
				Matrix ortho;
				ortho[0][0] = 2.f / width;
				ortho[1][1] = 2.f / height;
				ortho[2][2] = 1.f / (far_plane - near_plane);
				ortho[3][2] = -(near_plane / (far_plane - near_plane));
				return ortho;
			}

			inline static Matrix PerspectiveProjection(float fov, float aspect, float znear, float zfar)
			{
				Matrix persp;

				float yscale = 1.0f / tan(fov / 2.0f);
				float xscale = yscale / aspect;

				persp[0][0] = xscale;
				persp[1][1] = yscale;
				persp[2][2] = zfar / (zfar - znear);
				persp[2][3] = 1.0f;
				persp[3][2] = (-znear * zfar) / (zfar - znear);

				return persp;
			}

			inline float Determinant()
			{
				Vector4f minor, v1, v2, v3;
				float det;

				v1 = Vector4f((*this)[0][0], (*this)[1][0], (*this)[2][0], (*this)[3][0]);
				v2 = Vector4f((*this)[0][1], (*this)[1][1], (*this)[2][1], (*this)[3][1]);
				v3 = Vector4f((*this)[0][2], (*this)[1][2], (*this)[2][2], (*this)[3][2]);


				minor = Cross(v1, v2, v3);

				det = -	(
							(*this)[0][3] * minor.x +
							(*this)[1][3] * minor.y +
							(*this)[2][3] * minor.z +
							(*this)[3][3] * minor.w
						);

				return det;
			}


			inline void Inverse()
			{
				int a, i, j;
				Matrix out;
				Vector4f v, vec[3];
				float det = 0.0f;

				det = Determinant();

				if (!det) return;

				for (i = 0; i < 4; i++)
				{
					for (j = 0; j < 4; j++)
					{
						if (j != i)
						{
							a = j;
							if (j > i) a = a - 1;
							vec[a].x = (*this)[j][0];
							vec[a].y = (*this)[j][1];
							vec[a].z = (*this)[j][2];
							vec[a].w = (*this)[j][3];
						}
					}
					v = Cross(vec[0], vec[1], vec[2]);

					out[0][i] = pow(-1.0f, i) * v.x / det;
					out[1][i] = pow(-1.0f, i) * v.y / det;
					out[2][i] = pow(-1.0f, i) * v.z / det;
					out[3][i] = pow(-1.0f, i) * v.w / det;
				}

				*this = out;
			}

			void Print()
			{
				for (int i = 0; i < 4; ++i)
				{
					std::cout << "[ ";
					for (int j = 0; j < 4; ++j)
					{
						std::cout << (*this)[i][j] << (j < 3 ? ", " : " ");
					}
					std::cout << "]" << std::endl;
				}
			}


	};



}

