//
// Created by murphy on 2019-06-27.
//

#ifndef ZXDJRENDERER_ZXDJ_HPP
#define ZXDJRENDERER_ZXDJ_HPP
/**
 * ZXDJ
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by murphy at 2019-06-27 09:28
 **/

#include "stdio.h"

typedef unsigned int IUINT32;


// 计算插值：t 为 [0, 1] 之间的数值
inline float interp(float x1, float x2, float t) { return x1 + (x2 - x1) * t; }
inline int CMID(int x, int min, int max) { return (x < min)? min : ((x > max)? max : x); }
inline IUINT32 rgba2Color(int r, int g, int b, int a)
{
    IUINT32 color = 0;
    color |= r 	<< 0;
    color |= g 	<< 8;
    color |= b 	<< 16;
    color |= a 	<< 24;
    return color;
}


#define LOGI(TAG, ...)  do{printf("%s: ", TAG); printf(__VA_ARGS__); printf("\n");}while(0)
#define LOGV(TAG, ...)  do{printf("%s: ", TAG); printf(__VA_ARGS__); printf("\n");}while(0)
#define LOGE(TAG, ...)  do{printf("%s: ", TAG); printf(__VA_ARGS__); printf("\n");}while(0)
#endif //ZXDJRENDERER_ZXDJ_HPP
