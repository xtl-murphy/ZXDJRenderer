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
#ifndef ZXDJRENDERER_VECTOR_HPP
#define ZXDJRENDERER_VECTOR_HPP

#include <math.h>
#include "ZXDJ.hpp"

typedef struct
{
    float x, y, z, w;
} Vector;

float vector_length(const Vector *v);
// z = x + y
void vector_add(Vector *z, const Vector *x, const Vector *y);
// z = x - y
void vector_sub(Vector *z, const Vector *x, const Vector *y);
// 矢量点乘
float vector_dotproduct(const Vector *x, const Vector *y);
// 矢量叉乘
void vector_crossproduct(Vector *z, const Vector *x, const Vector *y);
// 矢量插值，t取值 [0, 1]
void vector_interp(Vector *z, const Vector *x1, const Vector *x2, float t);
// 矢量归一化
void vector_normalize(Vector *v);

#endif //ZXDJRENDERER_VECTOR_HPP
