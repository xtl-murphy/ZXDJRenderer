//
// Created by murphy on 2019-06-26.
//

/**
 * Vector
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by murphy at 2019-06-26 18:18
 **/
#include "Vector.hpp"
float vector_length(const Vector *v)
{
    float sq = v->x * v->x + v->y * v->y + v->z * v->z;
    return sqrt(sq);
}

void vector_add(Vector *z, const Vector *x, const Vector *y)
{
    z->x = x->x + y->x;
    z->y = x->y + y->y;
    z->z = x->z + y->z;
    z->w = 1.0;
}

void vector_sub(Vector *z, const Vector *x, const Vector *y)
{
    z->x = x->x - y->x;
    z->y = x->y - y->y;
    z->z = x->z - y->z;
    z->w = 1.0;
}

float vector_dotproduct(const Vector *x, const Vector *y) {
    return x->x * y->x + x->y * y->y + x->z * y->z;
}

// 矢量叉乘
void vector_crossproduct(Vector *z, const Vector *x, const Vector *y) {
    float m1, m2, m3;
    m1 = x->y * y->z - x->z * y->y;
    m2 = x->z * y->x - x->x * y->z;
    m3 = x->x * y->y - x->y * y->x;
    z->x = m1;
    z->y = m2;
    z->z = m3;
    z->w = 1.0f;
}

void vector_interp(Vector *z, const Vector *x1, const Vector *x2, float t)
{
    z->x = interp(x1->x, x2->x, t);
    z->y = interp(x1->y, x2->y, t);
    z->z = interp(x1->z, x2->z, t);
    z->w = 1.0f;
}

// 矢量归一化
void vector_normalize(Vector *v)
{
    float length = vector_length(v);
    if (length != 0.0f) {
        float inv = 1.0f / length;
        v->x *= inv;
        v->y *= inv;
        v->z *= inv;
    }
}