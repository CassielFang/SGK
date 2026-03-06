#ifndef _SGK_MATH_VECTOR_H_
#define _SGK_MATH_VECTOR_H_

#include "SGK/Base/BasicDefinitions.h"

SGK_NAMESPACE_BEG

namespace Math {
	// 二维列向量
	class vec2 {
	public:
		vec2();
		vec2(float x, float y);
		vec2(const vec2& v);

		vec2& set(float x, float y);
		float x() const;
		float y() const;
		float operator[](int index) const;
		float& operator[](int index);
		const float* getVal_ptr() const;

		vec2& operator=(const vec2& v);
		vec2 operator+(const vec2& v) const;
		vec2 operator-(const vec2& v) const;
		vec2 operator*(float s) const;
		vec2& operator+=(const vec2& v);
		vec2& operator-=(const vec2& v);
		vec2& operator*=(float s);

	private:
		float mX, mY;
	};
	// 三维列向量
	class vec3 {
	public:
		vec3();
		vec3(float x, float y, float z);
		vec3(const vec3& v);

		vec3& set(float x, float y, float z);
		float x() const;
		float y() const;
		float z() const;
		float operator[](int index) const;
		float& operator[](int index);
		const float* getVal_ptr() const;

		vec3& operator=(const vec3& v);
		vec3 operator+(const vec3& v) const;
		vec3 operator-(const vec3& v) const;
		vec3 operator*(float s) const;
		vec3& operator+=(const vec3& v);
		vec3& operator-=(const vec3& v);
		vec3& operator*=(float s);

private:
		float mX, mY, mZ;
	};
	// 四维列向量
	class vec4 {
	public:
		vec4();
		vec4(float x, float y, float z, float w = 1.f);
		vec4(const vec4& v);
		vec4(const vec3& v, float w);

		vec4& set(float x, float y, float z, float w = 1.f);
		float x() const;
		float y() const;
		float z() const;
		float w() const;
		float operator[](int index) const;
		float& operator[](int index);
		const float* getVal_ptr() const;

		vec4& operator=(const vec4& v);
		vec4 operator+(const vec4& v) const;
		vec4 operator-(const vec4& v) const;
		vec4 operator*(float s) const;
		vec4& operator+=(const vec4& v);
		vec4& operator-=(const vec4& v);
		vec4& operator*=(float s);

	private:
		float mX, mY, mZ, mW;
	};

}

SGK_NAMESPACE_END

#endif