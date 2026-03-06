#include "SGK/Math/Util.h"
#include "SGK/Math/vector.h"
#include "SGK/Math/matrix.h"

#include <cmath>

SGK_NAMESPACE_BEG

namespace Math {

	float dtor(float degree) { return static_cast<float>(3.1415926536 * degree / 180); }
	float Sinf(float rad) { return sinf(rad); }
	float Cosf(float rad) { return cosf(rad); }
	float Tanf(float rad) { return tanf(rad); }
	float Powf(float base, float index) { return powf(base, index); }
	float Maxf(float a, float b) { return a > b ? a : b; }
	float Minf(float a, float b) { return a > b ? b : a; }

	vec2::vec2() : vec2(0.f, 0.f) {}
	vec2::vec2(float x, float y) : mX(x), mY(y) {}
	vec2::vec2(const vec2& v) : vec2(v.mX, v.mY) {}

	vec2& vec2::set(float x, float y) { mX = x; mY = y; return *this; }
	float vec2::x() const { return mX; }
	float vec2::y() const { return mY; }
	float vec2::operator[](int index) const {
		if (index >= 0 && index < 2) {
			return *(&mX + index);
		}
		else {
			return mX;
		}
	}
	float& vec2::operator[](int index) {
		if (index >= 0 && index < 2) {
			return *(&mX + index);
		}
		else {
			return mX;
		}
	}
	const float* vec2::getVal_ptr() const { return &mX; }

	vec2& vec2::operator=(const vec2& v) {
		mX = v.x(); mY = v.y();
		return *this;
	}
	vec2 vec2::operator+(const vec2& v) const {
		return vec2(mX + v.x(), mY + v.y());
	}
	vec2 vec2::operator-(const vec2& v) const {
		return vec2(mX - v.x(), mY - v.y());
	}
	vec2 vec2::operator*(float s) const {
		return vec2(mX * s, mY * s);
	}
	vec2& vec2::operator+=(const vec2& v) { *this = *this + v; return *this; }
	vec2& vec2::operator-=(const vec2& v) { *this = *this - v; return *this; }
	vec2& vec2::operator*=(float s) { *this = *this * s; return *this; }


	vec3::vec3() : vec3(0.f, 0.f, 0.f) {}
	vec3::vec3(float x, float y, float z) : mX(x), mY(y), mZ(z) {}
	vec3::vec3(const vec3& v) : vec3(v.mX, v.mY, v.mZ) {}

	vec3& vec3::set(float x, float y, float z) { mX = x; mY = y; mZ = z; return *this; }
	float vec3::x() const { return mX; }
	float vec3::y() const { return mY; }
	float vec3::z() const { return mZ; }
	float vec3::operator[](int index) const {
		if (index >= 0 && index < 3) {
			return *(&mX + index);
		}
		else {
			return mX;
		}
	}
	float& vec3::operator[](int index) {
		if (index >= 0 && index < 3) {
			return *(&mX + index);
		}
		else {
			return mX;
		}
	}
	const float* vec3::getVal_ptr() const { return &mX; }

	vec3& vec3::operator=(const vec3& v) {
		mX = v.x(); mY = v.y(); mZ = v.z();
		return *this;
	}
	vec3 vec3::operator+(const vec3& v) const {
		return vec3(mX + v.x(), mY + v.y(), mZ + v.z());
	}
	vec3 vec3::operator-(const vec3& v) const {
		return vec3(mX - v.x(), mY - v.y(), mZ - v.z());
	}
	vec3 vec3::operator*(float s) const {
		return vec3(mX * s, mY * s, mZ * s);
	}
	vec3& vec3::operator+=(const vec3& v) { *this = *this + v; return *this; }
	vec3& vec3::operator-=(const vec3& v) { *this = *this - v; return *this; }
	vec3& vec3::operator*=(float s) { *this = *this * s; return *this; }


	vec4::vec4() : vec4(0.f, 0.f, 0.f, 0.f) {}
	vec4::vec4(float x, float y, float z, float w) : mX(x), mY(y), mZ(z), mW(w) {}
	vec4::vec4(const vec4& v) : vec4(v.mX, v.mY, v.mZ, v.mW) {}
	vec4::vec4(const vec3& v, float w) : vec4(v.x(), v.y(), v.z(), w) {}

	vec4& vec4::set(float x, float y, float z, float w) { mX = x; mY = y; mZ = z; mW = w; return *this; }
	float vec4::x() const { return mX; }
	float vec4::y() const { return mY; }
	float vec4::z() const { return mZ; }
	float vec4::w() const { return mW; }
	float vec4::operator[](int index) const {
		if (index >= 0 && index < 4) {
			return *(&mX + index);
		}
		else {
			return mX;
		}
	}
	float& vec4::operator[](int index) {
		if (index >= 0 && index < 4) {
			return *(&mX + index);
		}
		else {
			return mX;
		}
	}
	const float* vec4::getVal_ptr() const { return &mX; }

	vec4& vec4::operator=(const vec4& v) {
		mX = v.x(); mY = v.y(); mZ = v.z(); mW = v.w();
		return *this;
	}
	vec4 vec4::operator+(const vec4& v) const {
		return vec4(mX + v.x(), mY + v.y(), mZ + v.z(), mW + v.w());
	}
	vec4 vec4::operator-(const vec4& v) const {
		return vec4(mX - v.x(), mY - v.y(), mZ - v.z(), mW - v.w());
	}
	vec4 vec4::operator*(float s) const {
		return vec4(mX * s, mY * s, mZ * s, mW * s);
	}
	vec4& vec4::operator+=(const vec4& v) { *this = *this + v; return *this; }
	vec4& vec4::operator-=(const vec4& v) { *this = *this - v; return *this; }
	vec4& vec4::operator*=(float s) { *this = *this * s; return *this; }


	mat4::mat4(float a) : m11(a), m12(0.f), m13(0.f), m14(0.f),
		m21(0.f), m22(a), m23(0.f), m24(0.f),
		m31(0.f), m32(0.f), m33(a), m34(0.f),
		m41(0.f), m42(0.f), m43(0.f), m44(a) {
	}

	mat4& mat4::set(float a) {
		m11 = a, m12 = 0.f, m13 = 0.f, m14 = 0.f;
		m21 = 0.f, m22 = a, m23 = 0.f, m24 = 0.f;
		m31 = 0.f, m32 = 0.f,m33 = a, m34 = 0.f;
		m41 = 0.f, m42 = 0.f, m43 = 0.f, m44 = a;
		return *this;
	}
	float* mat4::getVal_ptr() { return &m11; }
	const float* mat4::getVal_ptr() const { return &m11; }

	mat4& mat4::operator=(const mat4& m) {
		m11 = m.m11, m12 = m.m12, m13 = m.m13, m14 = m.m14;
		m21 = m.m21, m22 = m.m22, m23 = m.m23, m24 = m.m24;
		m31 = m.m31, m32 = m.m32, m33 = m.m33, m34 = m.m34;
		m41 = m.m41, m42 = m.m42, m43 = m.m43, m44 = m.m44;
		return *this;
	}
	mat4 mat4::operator*(const mat4& m) const {
		mat4 tmp;
		tmp.m11 = this->m11 * m.m11 + this->m12 * m.m21 + this->m13 * m.m31 + this->m14 * m.m41;
		tmp.m12 = this->m11 * m.m12 + this->m12 * m.m22 + this->m13 * m.m32 + this->m14 * m.m42;
		tmp.m13 = this->m11 * m.m13 + this->m12 * m.m23 + this->m13 * m.m33 + this->m14 * m.m43;
		tmp.m14 = this->m11 * m.m14 + this->m12 * m.m24 + this->m13 * m.m34 + this->m14 * m.m44;
		tmp.m21 = this->m21 * m.m11 + this->m22 * m.m21 + this->m23 * m.m31 + this->m24 * m.m41;
		tmp.m22 = this->m21 * m.m12 + this->m22 * m.m22 + this->m23 * m.m32 + this->m24 * m.m42;
		tmp.m23 = this->m21 * m.m13 + this->m22 * m.m23 + this->m23 * m.m33 + this->m24 * m.m43;
		tmp.m24 = this->m21 * m.m14 + this->m22 * m.m24 + this->m23 * m.m34 + this->m24 * m.m44;
		tmp.m31 = this->m31 * m.m11 + this->m32 * m.m21 + this->m33 * m.m31 + this->m34 * m.m41;
		tmp.m32 = this->m31 * m.m12 + this->m32 * m.m22 + this->m33 * m.m32 + this->m34 * m.m42;
		tmp.m33 = this->m31 * m.m13 + this->m32 * m.m23 + this->m33 * m.m33 + this->m34 * m.m43;
		tmp.m34 = this->m31 * m.m14 + this->m32 * m.m24 + this->m33 * m.m34 + this->m34 * m.m44;
		tmp.m41 = this->m41 * m.m11 + this->m42 * m.m21 + this->m43 * m.m31 + this->m44 * m.m41;
		tmp.m42 = this->m41 * m.m12 + this->m42 * m.m22 + this->m43 * m.m32 + this->m44 * m.m42;
		tmp.m43 = this->m41 * m.m13 + this->m42 * m.m23 + this->m43 * m.m33 + this->m44 * m.m43;
		tmp.m44 = this->m41 * m.m14 + this->m42 * m.m24 + this->m43 * m.m34 + this->m44 * m.m44;
		return tmp;
	}
	mat4& mat4::operator*=(const mat4& m) { *this = *this * m; return *this; }
	vec4 mat4::operator*(const vec4& v) const {
		vec4 tmp;
		tmp.set(
			this->m11 * v.x() + this->m12 * v.y() + this->m13 * v.z() + this->m14 * v.w(),
			this->m21 * v.x() + this->m22 * v.y() + this->m23 * v.z() + this->m24 * v.w(),
			this->m31 * v.x() + this->m32 * v.y() + this->m33 * v.z() + this->m34 * v.w(),
			this->m41 * v.x() + this->m42 * v.y() + this->m43 * v.z() + this->m44 * v.w()
		);
		return tmp;
	}

	mat4 mat4::operator+(const mat4& m) const {
		mat4 tmp;
		tmp.m11 = this->m11 + m.m11; tmp.m12 = this->m12 + m.m12; tmp.m13 = this->m13 + m.m13; tmp.m14 = this->m14 + m.m14;
		tmp.m21 = this->m21 + m.m21; tmp.m22 = this->m22 + m.m22; tmp.m23 = this->m23 + m.m23; tmp.m24 = this->m24 + m.m24;
		tmp.m31 = this->m31 + m.m31; tmp.m32 = this->m32 + m.m32; tmp.m33 = this->m33 + m.m33; tmp.m34 = this->m34 + m.m34;
		tmp.m41 = this->m41 + m.m41; tmp.m42 = this->m42 + m.m42; tmp.m43 = this->m43 + m.m43; tmp.m44 = this->m44 + m.m44;
		return tmp;
	}
	mat4& mat4::operator+=(const mat4& m) { *this = *this + m; return *this; }
	mat4 mat4::operator-(const mat4& m) const {
		mat4 tmp;
		tmp.m11 = this->m11 - m.m11; tmp.m12 = this->m12 - m.m12; tmp.m13 = this->m13 - m.m13; tmp.m14 = this->m14 - m.m14;
		tmp.m21 = this->m21 - m.m21; tmp.m22 = this->m22 - m.m22; tmp.m23 = this->m23 - m.m23; tmp.m24 = this->m24 - m.m24;
		tmp.m31 = this->m31 - m.m31; tmp.m32 = this->m32 - m.m32; tmp.m33 = this->m33 - m.m33; tmp.m34 = this->m34 - m.m34;
		tmp.m41 = this->m41 - m.m41; tmp.m42 = this->m42 - m.m42; tmp.m43 = this->m43 - m.m43; tmp.m44 = this->m44 - m.m44;
		return tmp;
	}
	mat4& mat4::operator-=(const mat4& m) { *this = *this - m; return *this; }

	mat4& mat4::translate(float tx, float ty, float tz) {
		mat4 tmp;
		tmp.m11 = 1.f, tmp.m12 = 0.f, tmp.m13 = 0.f, tmp.m14 = tx;
		tmp.m21 = 0.f, tmp.m22 = 1.f, tmp.m23 = 0.f, tmp.m24 = ty;
		tmp.m31 = 0.f, tmp.m32 = 0.f, tmp.m33 = 1.f, tmp.m34 = tz;
		tmp.m41 = 0.f, tmp.m42 = 0.f, tmp.m43 = 0.f, tmp.m44 = 1.f;
		*this *= tmp;
		return *this;
	}
	mat4& mat4::translate(const vec3& t) {
		return this->translate(t.x(), t.y(), t.z());
	}
	mat4& mat4::scale(float sx, float sy, float sz) {
		mat4 tmp;
		tmp.m11 = sx, tmp.m12 = 0.f, tmp.m13 = 0.f, tmp.m14 = 0.f;
		tmp.m21 = 0.f, tmp.m22 = sy, tmp.m23 = 0.f, tmp.m24 = 0.f;
		tmp.m31 = 0.f, tmp.m32 = 0.f, tmp.m33 = sz, tmp.m34 = 0.f;
		tmp.m41 = 0.f, tmp.m42 = 0.f, tmp.m43 = 0.f, tmp.m44 = 1.f;
		*this *= tmp;
		return *this;
	}
	mat4& mat4::scale(const vec3& s) {
		return this->scale(s.x(), s.y(), s.z());
	}
	mat4& mat4::rotate(float xrad, float yrad, float zrad) {
		mat4 rx;
		rx.m11 = 1;
		rx.m22 = Cosf(xrad), rx.m23 = -Sinf(xrad);
		rx.m32 = Sinf(xrad), rx.m33 = Cosf(xrad);
		rx.m44 = 1;
		mat4 ry;
		ry.m11 = Cosf(yrad), ry.m13 = Sinf(yrad);
		ry.m22 = 1;
		ry.m31 = -Sinf(yrad), ry.m33 = Cosf(yrad);
		ry.m44 = 1;
		mat4 rz;
		rz.m11 = Cosf(zrad), rz.m12 = -Sinf(zrad);
		rz.m21 = Sinf(zrad), rz.m22 = Cosf(zrad);
		rz.m33 = 1;
		rz.m44 = 1;
		*this *= rx * ry * rz;
		return *this;
	}
	mat4& mat4::rotate(const vec3& r) {
		return this->rotate(r.x(), r.y(), r.z());
	}
	void mat4::perspective(float FOV, float aspect, float znear, float zfar) {
		mat4 tmp;
		float q = 1.f / Tanf(FOV / 2);
		float A = q / aspect;
		float B = (znear + zfar) / (znear - zfar);
		float C = 2 * znear * zfar / (znear - zfar);
		tmp.m11 = A, tmp.m22 = q, tmp.m33 = B, tmp.m34 = C, tmp.m43 = -1;
		*this = tmp;
		return;
	}

}

SGK_NAMESPACE_END
