//
// Created by murphy on 2019-07-01.
//

/**
 * Vector3
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by murphy at 2019-07-01 09:43
 **/
#ifndef ZXDJRENDERER_VECTOR3_HPP
#define ZXDJRENDERER_VECTOR3_HPP

#include <math.h>

class Vector3
{
public:
    float x, y, z;

    Vector3() {}

    Vector3(const Vector3 &a) : x(a.x), y(a.y), z(a.z) {}

    Vector3(float ox, float oy, float oz) : x(ox), y(oy), z(oz) {}

    Vector3 &operator=(const Vector3 &a)
    {
        x = a.x;
        y = a.y;
        z = a.z;
        return *this;
    }

    bool operator==(const Vector3 &a) const
    {
        return x == a.x && y == a.y && z == a.z;
    }

    bool operator!=(const Vector3 &a) const
    {
        return x != a.x || y != a.y || z != a.z;
    }

    void zero()
    {
        x = y = z = 0.0f;
    }

    Vector3 operator-() const
    {
        return Vector3(-x, -y, -z);
    }

    Vector3 operator-(const Vector3 &a) const
    {
        return Vector3(x - a.x, y - a.y, z - a.z);
    }

    Vector3 operator+(const Vector3 &a) const
    {
        return Vector3(x + a.x, y + a.y, z + a.z);
    }

    Vector3 operator*(float a) const
    {
        return Vector3(x * a, y * a, z * a);
    }

    Vector3 operator/(float a) const
    {
        return Vector3(x / a, y / a, z / a);
    }

    Vector3 operator+=(const Vector3 &a)
    {
        x += a.x;
        y += a.y;
        z += a.z;
        return *this;
    }

    Vector3 operator-=(const Vector3 &a)
    {
        x -= a.x;
        y -= a.y;
        z -= a.z;
        return *this;
    }

    Vector3 operator*=(float a)
    {
        x *= a;
        y *= a;
        z *= a;
        return *this;
    }

    Vector3 operator/=(float a)
    {
        float oneOverA = 1.0f / a;
        x *= oneOverA;
        y *= oneOverA;
        z *= oneOverA;
        return *this;
    }

    // 向量的标准化
    void normalize()
    {
        float magSq = x * x + y * y + z * z;
        if (magSq > 0.0f)
        {
            float oneOverMag = 1.0f / sqrt(magSq);
            x *= oneOverMag;
            y *= oneOverMag;
            z *= oneOverMag;
        }
    }

    float operator*=(const Vector3 &a) const
    {
        return x * a.x + y * a.y + z * a.z;
    }

    //////////////////////////////////////////////////
    //
    //非成员函数
    //
    //////////////////////////////////////////////////
    //求向量模
    inline float vectorMag(const Vector3 &a)
    {
        return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
    }

    //叉乘
    inline Vector3 crossProduct(const Vector3 &a, const Vector3 &b)
    {
        return Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
    }

//    inline Vector3 operator*(float k, const Vector3 &a)
//    {
//        return Vector3(k * a.x, k * a.y, k * a.z);
//    }

    inline float distance(const Vector3 &a, const Vector3 &b)
    {
        float dx = a.x - b.x;
        float dy = a.y - b.y;
        float dz = a.z - b.z;
        return sqrt(dx * dx + dy * dy + dz * dz);
    }
};

extern const Vector3 kZeroVector(0.0f, 0.0f, 0.0f);

#endif //ZXDJRENDERER_VECTOR3_HPP
