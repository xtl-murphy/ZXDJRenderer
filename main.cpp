#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <windows.h>

#include "Component/Device.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "external/stb/stb_image_write.h"

unsigned char *screen_fb = NULL;

void camera_at_zero(Device *device, float x, float y, float z)
{
    Point eye = {x, y, z, 1}, at = {0, 0, 0, 1}, up = {0, 0, 1, 1};
    matrix_set_lookat(&device->transform.view, &eye, &at, &up);
    transform_update(&device->transform);
}

void init_texture(Device *device)
{
    static IUINT32 texture[256][256];
    int i, j;
    for (j = 0; j < 256; j++)
    {
        for (i = 0; i < 256; i++)
        {
            int x = i / 32, y = j / 32;
            texture[j][i] = ((x + y) & 1) ? 0xffffff : 0x3fbcef;
        }
    }
    device_set_texture(device, texture, 256 * 4, 256, 256);
}

//=====================================================================
// 主程序
//=====================================================================
Vertex mesh[8] = {
        { { -1, -1,  1, 1 }, { 0, 0 }, { 1.0f, 0.2f, 0.2f }, 1 },
        { {  1, -1,  1, 1 }, { 0, 1 }, { 0.2f, 1.0f, 0.2f }, 1 },
        { {  1,  1,  1, 1 }, { 1, 1 }, { 0.2f, 0.2f, 1.0f }, 1 },
        { { -1,  1,  1, 1 }, { 1, 0 }, { 1.0f, 0.2f, 1.0f }, 1 },
        { { -1, -1, -1, 1 }, { 0, 0 }, { 1.0f, 1.0f, 0.2f }, 1 },
        { {  1, -1, -1, 1 }, { 0, 1 }, { 0.2f, 1.0f, 1.0f }, 1 },
        { {  1,  1, -1, 1 }, { 1, 1 }, { 1.0f, 0.3f, 0.3f }, 1 },
        { { -1,  1, -1, 1 }, { 1, 0 }, { 0.2f, 1.0f, 0.3f }, 1 },
};

void draw_plane(Device *device, int a, int b, int c, int d)
{
    Vertex p1 = mesh[a], p2 = mesh[b], p3 = mesh[c], p4 = mesh[d];
    p1.tc.u = 0, p1.tc.v = 0, p2.tc.u = 0, p2.tc.v = 1;
    p3.tc.u = 1, p3.tc.v = 1, p4.tc.u = 1, p4.tc.v = 0;
    device_draw_primitive(device, &p1, &p2, &p3);
    device_draw_primitive(device, &p3, &p4, &p1);
}

void draw_box(Device *device, float theta)
{
    Matrix m;
//    matrix_set_rotate(&m, -1, -0.5, 1, theta);
    matrix_set_identity(&m);
    device->transform.world = m;
    transform_update(&device->transform);
    draw_plane(device, 0, 1, 2, 3);
    draw_plane(device, 7, 6, 5, 4);
    draw_plane(device, 0, 4, 5, 1);
    draw_plane(device, 1, 5, 6, 2);
    draw_plane(device, 2, 6, 7, 3);
    draw_plane(device, 3, 7, 4, 0);
}

int main()
{
    const char* outputFilePath = "C:/Documents/WorkSpace/ZXDJRenderer/out.png";

    Device device;

    float alpha = 1;
    float pos = 3.0;

    int width = 800;
    int height = 600;
    int channel = 4;

    auto *outPutBuffer = (unsigned char *)malloc(width * height * channel);

    device_init(&device, width, height, outPutBuffer);
//    camera_at_zero(&device, 3, 0, 0);
    init_texture(&device);
    device.render_state = RENDER_STATE_WIREFRAME;

    device_clear(&device, 0);
    camera_at_zero(&device, 5, 0, 0);

    draw_box(&device, alpha);

    stbi_write_png(outputFilePath, width, height, channel, outPutBuffer, 0);
    device_destroy(&device);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}