/*
 * @Author: your name
 * @Date: 2020-10-06 19:51:25
 * @LastEditTime: 2020-10-06 20:06:11
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /EMalgorithm/src/EMalgorithm.h
 */
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
        void solveEMProblem();
        void initEMparams();

private:
        std::vector<EMData> m_vHeightData;

        Gaussian sex[2];
        float percent[2];
        // float t;
        float tlimit;

        std::vector<Score> px;

};




#endif // _EM_ALGORITHM_