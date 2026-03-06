#ifndef _SGK_MATH_MATRIX_H_
#define _SGK_MATH_MATRIX_H_

#include "SGK/Base/BasicDefinitions.h"

SGK_NAMESPACE_BEG

namespace Math {

	class vec3;
	class vec4;

	// 四阶方阵
	class mat4 {
	public:
		mat4(float a = 1.f);

		mat4& set(float a = 1.f);
		float* getVal_ptr();
		const float* getVal_ptr() const;

		mat4& operator=(const mat4& m);
		mat4 operator*(const mat4& m) const;
		mat4& operator*=(const mat4& m);
		vec4 operator*(const vec4& v) const;

		mat4 operator+(const mat4& m) const;
		mat4& operator+=(const mat4& m);
		mat4 operator-(const mat4& m) const;
		mat4& operator-=(const mat4& m);

		// 对现在的方阵右乘指定平移矩阵
		mat4& translate(float tx, float ty, float tz);
		// 对现在的方阵右乘指定平移矩阵
		mat4& translate(const vec3& t);
		// 对现在的方阵右乘指定缩放矩阵
		mat4& scale(float sx, float sy, float sz);
		// 对现在的方阵右乘指定缩放矩阵
		mat4& scale(const vec3& s);
		// 旋转顺序是rx*ry*rz
		mat4& rotate(float xrad, float yrad, float zrad);
		// 旋转顺序是rx*ry*rz
		mat4& rotate(const vec3& r);

		void perspective(float FOV, float aspect, float znear, float zfar);

	private:
		float m11, m21, m31, m41;
		float m12, m22, m32, m42;
		float m13, m23, m33, m43;
		float m14, m24, m34, m44;
	};

}

SGK_NAMESPACE_END

#endif
