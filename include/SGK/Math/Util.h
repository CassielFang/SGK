#ifndef _SGK_MATH_UTIL_H_
#define _SGK_MATH_UTIL_H_

#include "SGK/Base/BasicDefinitions.h"

SGK_NAMESPACE_BEG

namespace Math {

	// 角度转弧度
	float dtor(float degree);
	// 计算正弦
	float Sinf(float rad);
	// 计算余弦
	float Cosf(float rad);
	// 计算正切
	float Tanf(float rad);
	// 计算幂
	float Powf(float base, float index);
	// 取较大值
	float Maxf(float a, float b);
	// 取较小值
	float Minf(float a, float b);

}

SGK_NAMESPACE_END

#endif
