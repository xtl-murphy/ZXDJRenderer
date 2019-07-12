//
// Created by murphy on 2019-06-27.
//

/**
 * Vertex
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by murphy at 2019-06-27 11:27
 **/
#ifndef ZXDJRENDERER_VERTEX_HPP
#define ZXDJRENDERER_VERTEX_HPP

#include "Vector.hpp"

typedef Vector Point;
typedef struct { float r, g, b; } Color;
typedef struct { float u, v; } Texcoord;
typedef struct { Point pos; Texcoord tc; Color color; float rhw; } Vertex;
typedef struct { Vertex v, v1, v2; } Edge;
typedef struct { float top, bottom; Edge left, right; } Trapezoid;
typedef struct { Vertex v, step; int x, y, w; } Scanline;


void vertex_rhw_init(Vertex *v);
void vertex_interp(Vertex *y, const Vertex *x1, const Vertex *x2, float t);
void vertex_division(Vertex *y, const Vertex *x1, const Vertex *x2, float w);
void vertex_add(Vertex *y, const Vertex *x);
// 根据三角形生成 0-2 个梯形，并且返回合法梯形的数量
int trapezoid_init_triangle(Trapezoid *trap, const Vertex *p1, const Vertex *p2, const Vertex *p3);
// 按照 Y 坐标计算出左右两条边纵坐标等于 Y 的顶点
void trapezoid_edge_interp(Trapezoid *trap, float y);
// 根据左右两边的端点，初始化计算出扫描线的起点和步长
void trapezoid_init_scan_line(const Trapezoid *trap, Scanline *scanline, int y);
#endif //ZXDJRENDERER_VERTEX_HPP
