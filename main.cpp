

#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#include "SDL2/SDL.h"


#include "Component/Device.hpp"

#include "component/common/App.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "external/stb/stb_image_write.h"
#ifdef main
# undef main
#endif /* main */

int main(int argc, char* argv[])
{

    App app;
    app.onPostExecute();

//    const char* outputFilePath = "C:/Documents/WorkSpace/ZXDJRenderer/out.png";
    return 0;
}