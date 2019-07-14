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
#ifndef ZXDJRENDERER_APP_HPP
#define ZXDJRENDERER_APP_HPP


#include "SDL2/SDL.h"
#include "component/Device.hpp"

class App
{
public:
    App();
    ~App();

    int onPostExecute();

private:
    SDL_Window*   window;
    SDL_Renderer* renderer;
    SDL_Surface*  surface;
    bool          running;

    Device device;

    int onInit();

    void onEvent(SDL_Event* event);
    void onRender();

};


#endif //ZXDJRENDERER_APP_HPP
