/*
 * @Author: hy
 * @Date: 2020-10-15 17:04:23
 * @LastEditTime: 2020-10-15 17:07:05
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /EMalgorithm/src/Model.h
 */

#include <math.h>
#include <algorithm>
#include "Def.h"

float getGM(const float xi, const float mean, const float variance)
{
    float gs = 0.0;
    gs = exp(-((xi - mean) * (xi - mean)) / (2 * variance));
    gs = gs / (sqrt(2 * PI) * sqrt(abs(variance)));
    return gs;
}

template <typename T>
T gaussian(const T xi, const T mean, const T variance)
{
    T gaussian = 0.0;
    gaussian = exp(-((xi - mean) * (xi - mean)) / (2 * variance));
    gaussian = gaussian / (sqrt(2 * PI) * sqrt(abs(variance)));
    return gaussian;
}