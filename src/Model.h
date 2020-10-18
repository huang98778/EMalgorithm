/*
 * @Author: hy
 * @Date: 2020-10-15 17:04:23
 * @LastEditTime: 2020-10-17 17:26:22
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /EMalgorithm/src/Model.h
 */
#ifndef _MODEL_H_
#define _MODEL_H_


#include <math.h>
#include <algorithm>
#include "Def.h"

#include <Eigen/Dense>

class Model
{
private:
    /* data */
public:
    Model(/* args */);
    ~Model();






static float getGM(const float xi, const float mean, const float variance)
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

// template <typename T>
static float getMultGM(const std::vector<float> &xi, const std::vector<float> &means, const std::vector<float> &variance)
{
    const int si = xi.size();
    Eigen::VectorXf Xi(si), Means(si);
    Eigen::MatrixXf Vars;   // = Eigen::MatrixXd::Identity();
    // Xi.setZero(1, si);
    Vars.setIdentity(si, si);

    for (int i = 0; i < si; i++)
    {
        Xi(i,0) = xi.at(i);
        Means(i,0) = means.at(i);
        Vars(i, i) = variance.at(i);
    }
    // Xi= Eigen::Map<Eigen::VectorXd, Eigen::Unaligned>(xi.data(), xi.size());
    // LOG(INFO) << "egn: " << Xi.transpose() << " xi: " << Means.transpose() <<" \n"<<Vars;    
    // 
    float multgs = 0.0;
    multgs =  exp(-(Xi - Means).transpose() * Vars.inverse() * (Xi - Means) );
    multgs = 1 / (pow(sqrt(2 * PI), si) * sqrt(Vars.determinant())) * multgs;

    return multgs;
}

// template <typename T>
// void vec2Eigenvectors(const std::vector<T> x, const Eigen::)
};

#endif