//
// Created by murphy on 2019-06-27.
//

/**
 * Transform
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by murphy at 2019-06-27 10:17
 **/
#include "Transform.hpp"


void transform_update(Transform *ts)
{
    Matrix m;
    matrix_mul(&m, &ts->world, &ts->view);
    matrix_mul(&ts->transform, &m, &ts->projection);
}

void transform_init(Transform *ts, int width, int height)
{
    float aspect = (float) width / ((float) height);
    matrix_set_identity(&ts->world);
    matrix_set_identity(&ts->view);
    matrix_set_perspective(&ts->projection, 3.1415926f * 0.5f, aspect, 1.0f, 500.0f);
    ts->w = (float) width;
    ts->h = (float) height;
    transform_update(ts);
}

void transform_apply(const Transform *ts, Vector *y, const Vector *x)
{
    matrix_apply(y, x, &ts->transform);
}

int transform_check_cvv(const Vector *v) {
    float w = v->w;
    int check = 0;
    if (v->z < 0.0f) check |= 1;
    if (v->z >  w) check |= 2;
    if (v->x < -w) check |= 4;
    if (v->x >  w) check |= 8;
    if (v->y < -w) check |= 16;
    if (v->y >  w) check |= 32;
    return check;
}

void transform_homogenize(const Transform *ts, Vector *y, const Vector *x) {
    float rhw = 1.0f / x->w;
    y->x = (x->x * rhw + 1.0f) * ts->w * 0.5f;
    y->y = (1.0f - x->y * rhw) * ts->h * 0.5f;
    y->z = x->z * rhw;
    y->w = 1.0f;
}