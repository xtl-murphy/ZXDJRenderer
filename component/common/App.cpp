//
// Created by Murphy on 2019/7/14.
//

/**
 * App
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2019/7/14 12:27
 **/

#include <time.h>

#include "App.hpp"
#include "ZXDJ.hpp"


#define TITLE "ZXDJ"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720


long getCurrentMillSecond()
{
    long lLastTime = 0;
    struct timeval stCurrentTime;

    mingw_gettimeofday(&stCurrentTime, NULL);
    lLastTime = stCurrentTime.tv_sec * 1000 + stCurrentTime.tv_usec * 0.001;
    return lLastTime;
}

void camera_at_zero(Device *device, float x, float y, float z)
{
    Point eye = {x, y, z, 1}, at = {0, 0, 0, 1}, up = {0, 1, 0, 1};
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


App::App():window(nullptr), renderer(nullptr), running(false)
{

}

App::~App()
{
    device_destroy(&this->device);

    free(this->tempPtr);

    if (this->surface != nullptr)
    {
        SDL_FreeSurface(this->surface);
        this->surface = NULL;
    }

    if (renderer != nullptr)
    {
        SDL_DestroyRenderer(renderer);
        this->renderer = NULL;
    }

    if (window != nullptr)
    {
        SDL_DestroyWindow(window);
        this->window = NULL;
    }

    SDL_Quit();
}

int App::onPostExecute()
{
    int state = this->onInit();
    if (state < 0)
    {
        return state;
    }

    this->running = true;

    SDL_Event event;
    long _time = 0;



    while (this->running)
    {
        auto currentTime = getCurrentMillSecond();
        auto dt = (currentTime - _time) * 1.0f / 1000;
        while (SDL_PollEvent(&event))
        {
            onEvent(&event);
        }
        this->onRender();
        //LOGE("App", "fps %d", int(1 / dt));
        _time = currentTime;
    }

    return 1;
}

int App::onInit()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        LOGE("MAIN", "初始化失败。");
        return -1;
    }

    this->window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);


    if (this->window != nullptr)
    {
        this->surface = SDL_GetWindowSurface(this->window);

        this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);


        this->tempPtr = (char *)malloc(WINDOW_WIDTH * WINDOW_WIDTH * 4);

        device_init(&device, WINDOW_WIDTH, WINDOW_HEIGHT, this->tempPtr);
        camera_at_zero(&device, 3, 0, 0);
        init_texture(&device);
        device.render_state = RENDER_STATE_WIREFRAME;

        return 0;
    }
    return -1;
}

void App::onEvent(SDL_Event *event)
{
    switch (event->type)
    {
        case SDL_QUIT:
            this->running = false;
            break;
        case SDL_KEYDOWN:
            this->onKeyPress(event->key.keysym.sym);
            break;
        default:
            break;
    }
}

float x = 0, y = 0, z = 3;

void App::onRender()
{
    SDL_RenderClear(this->renderer);


    device_clear(&device, 0);
    camera_at_zero(&device, x, y, z);
    draw_box(&device, 1);

    SDL_LockSurface(this->surface);
    memcpy(this->surface->pixels, this->tempPtr, WINDOW_WIDTH * WINDOW_HEIGHT * 4);
    SDL_UnlockSurface(this->surface);

    SDL_UpdateWindowSurface(this->window);
    //SDL_RenderPresent(this->renderer);
}

void App::onKeyPress(SDL_Keycode key)
{
    float offset = 0.05;
    switch (key)
    {
        case SDLK_ESCAPE:
            this->running = false;
            break;
        case SDLK_w:
            //前
            break;
        case SDLK_s:
            //后
            break;
        case SDLK_a:
            //左
            break;
        case SDLK_d:
            //右
            break;
        case SDLK_z:
            //上
            break;
        case SDLK_x:
            //下
            break;
        case SDLK_UP:
            y += offset;
            break;
        case SDLK_DOWN:
            y -= offset;
            break;
        case SDLK_LEFT:
            x -= offset;
            break;
        case SDLK_RIGHT:
            x += offset;
            break;
    }
}
