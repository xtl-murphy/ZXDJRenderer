cmake_minimum_required(VERSION 3.13)
project(ZXDJRenderer)

set(LOCAL_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -fPIC -Wall -Wno-deprecated-declarations")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -fPIC -Wall -Wno-deprecated-declarations")

include_directories(${LOCAL_PATH})
include_directories(${LOCAL_PATH}/libs/sdl2/include)


file(GLOB_RECURSE STB_FILE "${LOCAL_PATH}/external/stb/*.h")
file(GLOB_RECURSE CPP_FILE "${LOCAL_PATH}/Component/*.cpp")



set(SDL_LIBS "libSDL2main" "libSDL2")
foreach(name ${SDL_LIBS})
    add_library(${name} STATIC IMPORTED component/common/App.cpp component/common/App.hpp)
    set_target_properties(${name} PROPERTIES IMPORTED_LOCATION ${LOCAL_PATH}/libs/sdl2/lib/${name}.a)
endforeach()

add_executable(ZXDJRenderer main.cpp ${CPP_FILE} ${STB_FILE})
foreach(name ${SDL_LIBS})
    target_link_libraries(ZXDJRenderer ${name})
endforeach()
target_link_libraries(ZXDJRenderer mingw32 dinput8 dxguid dxerr8 user32 gdi32 winmm imm32 ole32 oleaut32 shell32 setupapi version uuid)