//
// Created by murphy on 2019-07-04.
//

/**
 * MathUtil
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by murphy at 2019-07-04 15:22
 **/
#ifndef ZXDJRENDERER_MATHUTIL_HPP
#define ZXDJRENDERER_MATHUTIL_HPP

#include <math.h>

const float kPi = 3.14159265f;
const float k2Pi = kPi * 2.0f;
const float kPiOver2 = kPi / 2.0f;
const float k1OverPi = 1.0f / kPi;
const float k2Over2Pi = 1.0f / k2Pi;

// 通过加适当的2pi倍数讲角度限制在-pi到pi的区间
extern float wrapPi(float theta);
// 安全反三角函数
extern float safeAcos(float x);

inline void sinCos(float *returnSin, float *returnCos, float theta)
{
    *returnSin = sin(theta);
    *returnCos = cos(theta);
}

#endif //ZXDJRENDERER_MATHUTIL_HPP
