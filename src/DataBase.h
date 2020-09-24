#ifndef _DATA_BASE_
#define _DATA_BASE_

#include <string>
#include <vector>

typedef struct tag_EMData
{
        // char sex;
        std::string sex;
        int height;
}EMData;


typedef struct tag_Gaussian
{
        float mean;
        float variance;
}Gaussian;

typedef struct tag_float2
{
        float f1;
        float f2;
} Score;

#endif