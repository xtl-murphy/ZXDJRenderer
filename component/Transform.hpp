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
#ifndef ZXDJRENDERER_TRANSFORM_HPP
#define ZXDJRENDERER_TRANSFORM_HPP

#include "Matrix.hpp"
#include "Vector.hpp"

typedef struct {
    Matrix world;         // 世界坐标变换
    Matrix view;          // 摄影机坐标变换
    Matrix projection;    // 投影变换
    Matrix transform;     // transform = world * view * projection
    float w, h;             // 屏幕大小
}	Transform;

// 矩阵更新，计算 transform = world * view * projection
void transform_update(Transform *ts);
// 初始化，设置屏幕长宽
void transform_init(Transform *ts, int width, int height);
// 将矢量 x 进行 project
void transform_apply(const Transform *ts, Vector *y, const Vector *x);
// 检查齐次坐标同 cvv 的边界用于视锥裁剪
int transform_check_cvv(const Vector *v);
// 归一化，得到屏幕坐标
void transform_homogenize(const Transform *ts, Vector *y, const Vector *x);
#endif //ZXDJRENDERER_TRANSFORM_HPP
