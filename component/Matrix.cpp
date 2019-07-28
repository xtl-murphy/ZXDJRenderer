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
#include "Matrix.hpp"


void matrix_add(Matrix *c, const Matrix *a, const Matrix *b)
{
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            c->m[i][j] = a->m[i][j] + b->m[i][j];
        }

    }
}

void matrix_sub(Matrix *c, const Matrix *a, const Matrix *b)
{
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            c->m[i][j] = a->m[i][j] - b->m[i][j];
        }
    }
}

void matrix_mul(Matrix *c, const Matrix *a, const Matrix *b)
{
    Matrix z;
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            z.m[j][i] = (a->m[j][0] * b->m[0][i]) +
                        (a->m[j][1] * b->m[1][i]) +
                        (a->m[j][2] * b->m[2][i]) +
                        (a->m[j][3] * b->m[3][i]);
        }
    }
    c[0] = z;
}

void matrix_scale(Matrix *c, const Matrix *a, float f)
{
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++)
            c->m[i][j] = a->m[i][j] * f;
    }
}

void matrix_apply(Vector *y, const Vector *x, const Matrix *m)
{
    float X = x->x, Y = x->y, Z = x->z, W = x->w;
    y->x = X * m->m[0][0] + Y * m->m[1][0] + Z * m->m[2][0] + W * m->m[3][0];
    y->y = X * m->m[0][1] + Y * m->m[1][1] + Z * m->m[2][1] + W * m->m[3][1];
    y->z = X * m->m[0][2] + Y * m->m[1][2] + Z * m->m[2][2] + W * m->m[3][2];
    y->w = X * m->m[0][3] + Y * m->m[1][3] + Z * m->m[2][3] + W * m->m[3][3];
}

void matrix_set_identity(Matrix *m) {
    m->m[0][0] = m->m[1][1] = m->m[2][2] = m->m[3][3] = 1.0f;
    m->m[0][1] = m->m[0][2] = m->m[0][3] = 0.0f;
    m->m[1][0] = m->m[1][2] = m->m[1][3] = 0.0f;
    m->m[2][0] = m->m[2][1] = m->m[2][3] = 0.0f;
    m->m[3][0] = m->m[3][1] = m->m[3][2] = 0.0f;
}

void matrix_set_zero(Matrix *m) {
    m->m[0][0] = m->m[0][1] = m->m[0][2] = m->m[0][3] = 0.0f;
    m->m[1][0] = m->m[1][1] = m->m[1][2] = m->m[1][3] = 0.0f;
    m->m[2][0] = m->m[2][1] = m->m[2][2] = m->m[2][3] = 0.0f;
    m->m[3][0] = m->m[3][1] = m->m[3][2] = m->m[3][3] = 0.0f;
}

void matrix_set_translate(Matrix *m, float x, float y, float z) {
    matrix_set_identity(m);
    m->m[3][0] = x;
    m->m[3][1] = y;
    m->m[3][2] = z;
}

void matrix_set_scale(Matrix *m, float x, float y, float z) {
    matrix_set_identity(m);
    m->m[0][0] = x;
    m->m[1][1] = y;
    m->m[2][2] = z;
}

void matrix_set_rotate(Matrix *m, float x, float y, float z, float theta) {
    float qsin = sin(theta * 0.5f);
    float qcos = cos(theta * 0.5f);
    Vector vec = { x, y, z, 1.0f };
    float w = qcos;
    vector_normalize(&vec);
    x = vec.x * qsin;
    y = vec.y * qsin;
    z = vec.z * qsin;
    m->m[0][0] = 1 - 2 * y * y - 2 * z * z;
    m->m[1][0] = 2 * x * y - 2 * w * z;
    m->m[2][0] = 2 * x * z + 2 * w * y;
    m->m[0][1] = 2 * x * y + 2 * w * z;
    m->m[1][1] = 1 - 2 * x * x - 2 * z * z;
    m->m[2][1] = 2 * y * z - 2 * w * x;
    m->m[0][2] = 2 * x * z - 2 * w * y;
    m->m[1][2] = 2 * y * z + 2 * w * x;
    m->m[2][2] = 1 - 2 * x * x - 2 * y * y;
    m->m[0][3] = m->m[1][3] = m->m[2][3] = 0.0f;
    m->m[3][0] = m->m[3][1] = m->m[3][2] = 0.0f;
    m->m[3][3] = 1.0f;
}

void matrix_set_lookat(Matrix *m, const Vector *eye, const Vector *at, const Vector *up)
{
    Vector xaxis, yaxis, zaxis;

    vector_sub(&zaxis, at, eye);
    vector_normalize(&zaxis);
    vector_crossproduct(&xaxis, up, &zaxis);
    vector_normalize(&xaxis);
    vector_crossproduct(&yaxis, &zaxis, &xaxis);

    m->m[0][0] = xaxis.x;
    m->m[1][0] = xaxis.y;
    m->m[2][0] = xaxis.z;
    m->m[3][0] = -vector_dotproduct(&xaxis, eye);

    m->m[0][1] = yaxis.x;
    m->m[1][1] = yaxis.y;
    m->m[2][1] = yaxis.z;
    m->m[3][1] = -vector_dotproduct(&yaxis, eye);

    m->m[0][2] = zaxis.x;
    m->m[1][2] = zaxis.y;
    m->m[2][2] = zaxis.z;
    m->m[3][2] = -vector_dotproduct(&zaxis, eye);

    m->m[0][3] = m->m[1][3] = m->m[2][3] = 0.0f;
    m->m[3][3] = 1.0f;
}

void matrix_set_perspective(Matrix *m, float fovy, float aspect, float zn, float zf)
{
    float fax = 1.0f / tan(fovy * 0.5f);
    matrix_set_zero(m);
    m->m[0][0] = (fax / aspect);
    m->m[1][1] = (fax);
    m->m[2][2] = zf / (zf - zn);
    m->m[3][2] = - zn * zf / (zf - zn);
    m->m[2][3] = 1;
}