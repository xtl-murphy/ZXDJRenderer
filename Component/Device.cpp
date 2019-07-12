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
#include <stdlib.h>
#include <assert.h>
#include <cstring>
#include "Device.hpp"


void device_init(Device *device, int width, int height, void *fb)
{
    int need = sizeof(void *) * (height * 2 + 1024) + width * height * 8;
    char *ptr = (char *) malloc(need + 64);
    char *framebuf, *zbuf;
    int j;
    assert(ptr);
    device->framebuffer = (IUINT32 **) ptr;
    device->zbuffer = (float **) (ptr + sizeof(void *) * height);
    ptr += sizeof(void *) * height * 2;
    device->texture = (IUINT32 **) ptr;
    ptr += sizeof(void *) * 1024;
    framebuf = (char *) ptr;
    zbuf = (char *) ptr + width * height * 4;
    ptr += width * height * 8;
    if (fb != nullptr) framebuf = (char*)fb;
    for (j = 0; j < height; j++)
    {
        device->framebuffer[j] = (IUINT32 *) (framebuf + width * 4 * j);
        device->zbuffer[j] = (float *) (zbuf + width * 4 * j);
    }
    device->texture[0] = (IUINT32 *) ptr;
    device->texture[1] = (IUINT32 *) (ptr + 16);
    memset(device->texture[0], 0, 64);
    device->tex_width = 2;
    device->tex_height = 2;
    device->max_u = 1.0f;
    device->max_v = 1.0f;
    device->width = width;
    device->height = height;
//    device->background = 0xc0c0c0;
    device->background = rgba2Color(255, 255, 255, 255);
    device->foreground = rgba2Color(255, 255, 0, 255);;
    transform_init(&device->transform, width, height);
    device->render_state = RENDER_STATE_WIREFRAME;
}

void device_destroy(Device *device)
{
    if (device->framebuffer)
        free(device->framebuffer);
    device->framebuffer = nullptr;
    device->zbuffer = nullptr;
    device->texture = nullptr;
}

void device_set_texture(Device *device, void *bits, long pitch, int w, int h)
{
    char *ptr = (char *) bits;
    int j;
    assert(w <= 1024 && h <= 1024);
    for (j = 0; j < h; ptr += pitch, j++)    // 重新计算每行纹理的指针
        device->texture[j] = (IUINT32 *) ptr;
    device->tex_width = w;
    device->tex_height = h;
    device->max_u = (float) (w - 1);
    device->max_v = (float) (h - 1);
}

void device_clear(Device *device, int mode)
{
    int y, x, height = device->height;
    for (y = 0; y < device->height; y++)
    {
        IUINT32 *dst = device->framebuffer[y];
        IUINT32 cc = (height - 1 - y) * 230 / (height - 1);
        cc = (cc << 16) | (cc << 8) | cc;

        if (mode == 0)
        {
            cc = device->background;
        }
        for (x = device->width; x > 0; dst++, x--)
        {
//            dst[0] = rgba2Color(255, 0, 0, 255);
            dst[0] = cc;
        }

//        for (int i = 0; i < device->width; i++)
//        {
//            dst[2] = rgba2Color(0, 255, 0, 255);
//        }
    }
//    for (y = 0; y < device->height; y++)
//    {
//        float *dst = device->zbuffer[y];
//        for (x = device->width; x > 0; dst++, x--)
//        {
//            dst[0] = 0.0f;
//        }
//    }
}

void device_pixel(Device *device, int x, int y, IUINT32 color)
{
    if (((IUINT32) x) < (IUINT32) device->width && ((IUINT32) y) < (IUINT32) device->height)
    {
//        LOGE("Device", "x = %d, y = %d", x, y);
        device->framebuffer[y][x] = rgba2Color(255, 0, 0, 255);
    }
}

void device_draw_line(Device *device, int x1, int y1, int x2, int y2, IUINT32 c)
{
    //Bresenham直线算法
    //会根据斜率的不同，绘制一些近似点
    //让线条感更好
    int x, y, rem = 0;
    if (x1 == x2 && y1 == y2)
    {
        device_pixel(device, x1, y1, c);
    }
    else if (x1 == x2)
    {
        int inc = (y1 <= y2) ? 1 : -1;
        for (y = y1; y != y2; y += inc)
        {
            device_pixel(device, x1, y, c);
        }
        device_pixel(device, x2, y2, c);
    }
    else if (y1 == y2)
    {
        int inc = (x1 <= x2) ? 1 : -1;
        for (x = x1; x != x2; x += inc)
        {
            device_pixel(device, x, y1, c);
        }
        device_pixel(device, x2, y2, c);
    }
    else
    {
        int dx = (x1 < x2) ? x2 - x1 : x1 - x2;
        int dy = (y1 < y2) ? y2 - y1 : y1 - y2;
        if (dx >= dy)
        {
            if (x2 < x1) x = x1, y = y1, x1 = x2, y1 = y2, x2 = x, y2 = y;
            for (x = x1, y = y1; x <= x2; x++)
            {
                device_pixel(device, x, y, c);
                rem += dy;
                if (rem >= dx)
                {
                    rem -= dx;
                    y += (y2 >= y1) ? 1 : -1;
                    device_pixel(device, x, y, c);
                }
            }
            device_pixel(device, x2, y2, c);
        }
        else
        {
            if (y2 < y1) x = x1, y = y1, x1 = x2, y1 = y2, x2 = x, y2 = y;
            for (x = x1, y = y1; y <= y2; y++)
            {
                device_pixel(device, x, y, c);
                rem += dx;
                if (rem >= dy)
                {
                    rem -= dy;
                    x += (x2 >= x1) ? 1 : -1;
                    device_pixel(device, x, y, c);
                }
            }
            device_pixel(device, x2, y2, c);
        }
    }
}

IUINT32 device_texture_read(const Device *device, float u, float v)
{
    int x, y;
    u = u * device->max_u;
    v = v * device->max_v;
    x = (int) (u + 0.5f);
    y = (int) (v + 0.5f);
    x = CMID(x, 0, device->tex_width - 1);
    y = CMID(y, 0, device->tex_height - 1);
    return device->texture[y][x];
}

void device_draw_scanline(Device *device, Scanline *scanline)
{
    IUINT32 *framebuffer = device->framebuffer[scanline->y];
    float *zbuffer = device->zbuffer[scanline->y];
    int x = scanline->x;
    int w = scanline->w;
    int width = device->width;
    int render_state = device->render_state;
    for (; w > 0; x++, w--)
    {
        if (x >= 0 && x < width)
        {
            float rhw = scanline->v.rhw;
            if (rhw >= zbuffer[x])
            {
                float w = 1.0f / rhw;
                zbuffer[x] = rhw;
                if (render_state & RENDER_STATE_COLOR)
                {
                    float r = scanline->v.color.r * w;
                    float g = scanline->v.color.g * w;
                    float b = scanline->v.color.b * w;
                    int R = (int) (r * 255.0f);
                    int G = (int) (g * 255.0f);
                    int B = (int) (b * 255.0f);
                    R = CMID(R, 0, 255);
                    G = CMID(G, 0, 255);
                    B = CMID(B, 0, 255);
                    framebuffer[x] = (R << 16) | (G << 8) | (B);
                }
                if (render_state & RENDER_STATE_TEXTURE)
                {
                    float u = scanline->v.tc.u * w;
                    float v = scanline->v.tc.v * w;
                    IUINT32 cc = device_texture_read(device, u, v);
                    framebuffer[x] = cc;
                }
            }
        }
        vertex_add(&scanline->v, &scanline->step);
        if (x >= width) break;
    }
}

void device_render_trap(Device *device, Trapezoid *trap)
{
    Scanline scanline;
    int j, top, bottom;
    top = (int) (trap->top + 0.5f);
    bottom = (int) (trap->bottom + 0.5f);
    for (j = top; j < bottom; j++)
    {
        if (j >= 0 && j < device->height)
        {
            trapezoid_edge_interp(trap, (float) j + 0.5f);
            trapezoid_init_scan_line(trap, &scanline, j);
            device_draw_scanline(device, &scanline);
        }
        if (j >= device->height) break;
    }
}

void device_draw_primitive(Device *device, const Vertex *v1,
                           const Vertex *v2, const Vertex *v3)
{
    Point p1, p2, p3, c1, c2, c3;
    int render_state = device->render_state;

    // 按照 Transform 变化
    transform_apply(&device->transform, &c1, &v1->pos);
    transform_apply(&device->transform, &c2, &v2->pos);
    transform_apply(&device->transform, &c3, &v3->pos);

    // 裁剪，注意此处可以完善为具体判断几个点在 cvv内以及同cvv相交平面的坐标比例
    // 进行进一步精细裁剪，将一个分解为几个完全处在 cvv内的三角形
    if (transform_check_cvv(&c1) != 0) return;
    if (transform_check_cvv(&c2) != 0) return;
    if (transform_check_cvv(&c3) != 0) return;

    // 归一化
    transform_homogenize(&device->transform, &p1, &c1);
    transform_homogenize(&device->transform, &p2, &c2);
    transform_homogenize(&device->transform, &p3, &c3);

    // 纹理或者色彩绘制
    if (render_state & (RENDER_STATE_TEXTURE | RENDER_STATE_COLOR))
    {
        Vertex t1 = *v1, t2 = *v2, t3 = *v3;
        Trapezoid traps[2];
        int n;

        t1.pos = p1;
        t2.pos = p2;
        t3.pos = p3;
        t1.pos.w = c1.w;
        t2.pos.w = c2.w;
        t3.pos.w = c3.w;

        vertex_rhw_init(&t1);    // 初始化 w
        vertex_rhw_init(&t2);    // 初始化 w
        vertex_rhw_init(&t3);    // 初始化 w

        // 拆分三角形为0-2个梯形，并且返回可用梯形数量
        n = trapezoid_init_triangle(traps, &t1, &t2, &t3);

        if (n >= 1) device_render_trap(device, &traps[0]);
        if (n >= 2) device_render_trap(device, &traps[1]);
    }

    if (render_state & RENDER_STATE_WIREFRAME)
    {        // 线框绘制
        device_draw_line(device, (int) p1.x, (int) p1.y, (int) p2.x, (int) p2.y,
                         device->foreground);
        device_draw_line(device, (int) p1.x, (int) p1.y, (int) p3.x, (int) p3.y,
                         device->foreground);
        device_draw_line(device, (int) p3.x, (int) p3.y, (int) p2.x, (int) p2.y,
                         device->foreground);
    }
}
