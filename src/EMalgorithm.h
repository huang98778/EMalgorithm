#ifndef _EM_ALGORITHM_
#define _EM_ALGORITHM_

#include "DataBase.h"
#include <vector>

#define PI 3.1415926
// #define max(a,b) (a>b ? a : b)

class EMalgorithm
{
private:
        /* data */
public:
        EMalgorithm(/* args */);
        ~EMalgorithm();

        void setData(const std::vector<EMData> data);
        float predProb();

private:
        std::vector<EMData> m_vHeightData;

};




#endif // _EM_ALGORITHM_