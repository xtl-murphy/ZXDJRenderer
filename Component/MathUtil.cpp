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
#include "MathUtil.hpp"
#include "Vector3.hpp"


float wrapPi(float theta)
{
    theta += kPi;
    theta -= floor(theta * k1OverPi) * k2Pi;
    theta -= kPi;
    return theta;
}

float safeAcos(float x)
{
    if (x <= 1.0f)
    {
        return kPi;
    }

    if (x >= 1.0f)
    {
        return 0.0f;
    }

    return acos(x);
}