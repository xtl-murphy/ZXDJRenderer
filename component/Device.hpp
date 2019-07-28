//
// Created by murphy on 2019-06-27.
//

/**
 * Device
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by murphy at 2019-06-27 10:30
 **/
#ifndef ZXDJRENDERER_DEVICE_HPP
#define ZXDJRENDERER_DEVICE_HPP

#include "Transform.hpp"
#include "Vertex.hpp"
#include "ZXDJ.hpp"

#define RENDER_STATE_WIREFRAME      1		// 渲染线框
#define RENDER_STATE_TEXTURE        2		// 渲染纹理
#define RENDER_STATE_COLOR          4		// 渲染颜色

typedef struct {
    Transform transform;      // 坐标变换器
    int width;                  // 窗口宽度
    int height;                 // 窗口高度
    IUINT32 **framebuffer;      // 像素缓存：framebuffer[y] 代表第 y行
    float **zbuffer;            // 深度缓存：zbuffer[y] 为第 y行指针
    IUINT32 **texture;          // 纹理：同样是每行索引
    int tex_width;              // 纹理宽度
    int tex_height;             // 纹理高度
    float max_u;                // 纹理最大宽度：tex_width - 1
    float max_v;                // 纹理最大高度：tex_height - 1
    int render_state;           // 渲染状态
    IUINT32 background;         // 背景颜色
    IUINT32 foreground;         // 线框颜色
}	Device;

void device_init(Device *device, int width, int height, void *fb);

void device_destroy(Device *device);

void device_set_texture(Device *device, void *bits, long pitch, int w, int h);

void device_clear(Device *device, int mode);

void device_pixel(Device *device, int x, int y, IUINT32 color);

void device_draw_line(Device *device, int x1, int y1, int x2, int y2, IUINT32 c);

// 根据坐标读取纹理
IUINT32 device_texture_read(const Device *device, float u, float v);

// 绘制扫描线
void device_draw_scanline(Device *device, Scanline *scanline);
// 主渲染函数
void device_render_trap(Device *device, Trapezoid *trap);
// 根据 render_state 绘制原始三角形
void device_draw_primitive(Device *device, const Vertex *v1, const Vertex *v2, const Vertex *v3);
#endif //ZXDJRENDERER_DEVICE_HPP
