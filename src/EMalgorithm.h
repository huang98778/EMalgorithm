/*
 * @Author: your name
 * @Date: 2020-10-06 19:51:25
 * @LastEditTime: 2020-10-14 19:47:55
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /EMalgorithm/src/EMalgorithm.h
 */
#ifndef _EM_ALGORITHM_
#define _EM_ALGORITHM_

#include "DataBase.h"
#include <vector>

#define PI 3.1415926
#define clusters 2
#define SIZE 100
// #define max(a,b) (a>b ? a : b)

// template<typename T>
class EMalgorithm
{

public:
    EMalgorithm(/* args */);
    ~EMalgorithm();

    void setData(const std::vector<EMData> data);
    float predProb();

    void solveEMProblem();
    void initEMparams();

    // template<typename T>
    // T gaussian(const T xi, const T mean, const T variance);

    void solveEMProblem(bool todo);
    // float getGM(const float xi, const float mean, const float variance);

private:
    void setNewPara();
    void initModelparams();

    void doEStep();

private:
    std::vector<EMData> m_vHeightData;

    Gaussian sex[2];
    float percent[2];
    // float t;
    float tlimit;

    std::vector<Score> px;

    // int clusters;
    // float means[];
    // float prior[];
    // float variance[];
    // std::vector<std::vector<float>> wight;
    float mean = 0;
    float covariance = 0;

    float means[clusters];
    float prior[clusters];
    float variance[clusters];
    std::vector<std::vector<float>> wight; //[SIZE][clusters];

    std::vector<EMData> m_vecData;
};

#endif // _EM_ALGORITHM_