/*
 * @Author: your name
 * @Date: 2020-10-06 19:51:25
 * @LastEditTime: 2020-10-15 18:26:24
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /EMalgorithm/src/EMalgorithm.h
 */
#ifndef _EM_ALGORITHM_
#define _EM_ALGORITHM_

#include "DataBase.h"
#include "Def.h"
#include <vector>


// #define clusters 2
// #define max(a,b) (a>b ? a : b)

// template<typename T>
class EMalgorithm
{
 
public:
        EMalgorithm(/* args */);
        ~EMalgorithm();

        void setData(const std::vector<EMData> data);
        void predProb();
        
        void solveEMProblem();
        void initEMparams();

        // template<typename T>
        // T gaussian(const T xi, const T mean, const T variance);

        void solveEMProblem(bool todo);
        // float getGM(const float xi, const float mean, const float variance);

private:
        void initModelparams();

        void doEStep();
        void doMStep();
        float calculateLogLikelyHood();

private:
        std::vector<EMData> m_vHeightData;

        std::vector<EMData> m_vecData;

        int clusters;

        std::vector<float> prior;
        std::vector<float> means;
        std::vector<float> variance;

        Gaussian sex[2];
        float percent[2];
        // float t;
        float tlimit;

        std::vector<Score> px;

        std::vector<std::vector<float>> weightMat;
};



#endif // _EM_ALGORITHM_