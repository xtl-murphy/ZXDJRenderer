//
// Created by murphy on 2019-06-26.
//

/**
 * Matrix
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by murphy at 2019-06-26 18:11
 **/
#ifndef ZXDJRENDERER_MATRIX_HPP
#define ZXDJRENDERER_MATRIX_HPP

#include "Vector.hpp"

typedef struct
{
    float m[4][4];
} Matrix;

// c = a + b
void matrix_add(Matrix *c, const Matrix *a, const Matrix *b);
// c = a - b
void matrix_sub(Matrix *c, const Matrix *a, const Matrix *b);
// c = a * b
void matrix_mul(Matrix *c, const Matrix *a, const Matrix *b);
// c = a * f
void matrix_scale(Matrix *c, const Matrix *a, float f);
// y = x * m
void matrix_apply(Vector *y, const Vector *x, const Matrix *m);

void matrix_set_identity(Matrix *m);

void matrix_set_zero(Matrix *m);

void matrix_set_translate(Matrix *m, float x, float y, float z);
// 缩放变换
void matrix_set_scale(Matrix *m, float x, float y, float z);
// 旋转矩阵
void matrix_set_rotate(Matrix *m, float x, float y, float z, float theta);
// 设置摄像机
void matrix_set_lookat(Matrix *m, const Vector *eye, const Vector *at, const Vector *up);

// D3DXMatrixPerspectiveFovLH
void matrix_set_perspective(Matrix *m, float fovy, float aspect, float zn, float zf);

#endif //ZXDJRENDERER_MATRIX_HPP
