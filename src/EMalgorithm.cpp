
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <glog/logging.h>

#include "EMalgorithm.h"
#include "Model.h"

#define max(a, b) (a > b ? a : b)
EMalgorithm::EMalgorithm(/* args */)
{
}

EMalgorithm::~EMalgorithm()
{
}

void EMalgorithm::setData(const std::vector<EMData> data)
{
    m_vHeightData = data;
    m_vecData = data;
}

void EMalgorithm::predProb()
{
    Gaussian sex[2];
    float percent[2];
    float t = 1.0;
    float tlimit = 0.000001;

    sex[0].mean = 165;
    sex[0].variance = 10.0;

    sex[1].mean = 150;
    sex[1].variance = 10.0;

    percent[0] = 0.5;
    percent[1] = 0.5;

    while (t > tlimit)
    {
        Gaussian sex_old[2];
        float percent_old[2];
        sex_old[0] = sex[0];
        sex_old[1] = sex[1];
        percent_old[0] = percent[0];
        percent_old[1] = percent[1];

        std::vector<Score> px;

        std::vector<EMData>::const_iterator iter;

        for (iter = m_vHeightData.begin(); iter != m_vHeightData.end(); ++iter)
        {
            Score sp;
            sp.f1 = 1 / (sqrt(2 * PI * sex[0].variance)) * exp(-(iter->height - sex[0].mean) * (iter->height - sex[0].mean) / (2 * sex[0].variance));
            sp.f2 = 1 / (sqrt(2 * PI * sex[1].variance)) * exp(-(iter->height - sex[1].mean) * (iter->height - sex[1].mean) / (2 * sex[1].variance));

            px.push_back(sp);
        }

        //E step
        std::vector<Score>::iterator it;
        for (it = px.begin(); it < px.end(); it++)
        {
            float sum = 0.0;
            it->f1 *= percent[0];
            sum += it->f1;
            it->f2 *= percent[1];
            sum += it->f2;

            it->f1 /= sum;
            it->f2 /= sum;

            // std::cout << it->f1 << " " << it->f2 << std::endl; // Qi(zi)
        }

        // M step
        float sumMale = 0;
        float sumFemale = 0;
        float meanMale = 0;
        float meanFemale = 0;

        for (it = px.begin(), iter = m_vHeightData.begin(); it < px.end(); it++, iter++)
        {
            sumMale += it->f1;
            sumFemale += it->f2;

            meanMale += it->f1 * iter->height;
            meanFemale += it->f2 * iter->height;
        }

        //**************EM update**************//
        // update percent
        percent[0] = sumMale / (sumMale + sumFemale);
        percent[1] = sumFemale / (sumMale + sumFemale);

        // update mean
        sex[0].mean = meanMale / sumMale;
        sex[1].mean = meanFemale / sumFemale;

        // update variance
        float sumVarMale = 0, sumVarFemale = 0;
        for (it = px.begin(), iter = m_vHeightData.begin(); it < px.end(); it++, iter++)
        {
            sumVarMale += it->f1 * (iter->height - sex[0].mean) * (iter->height - sex[0].mean);
            sumVarFemale += it->f2 * (iter->height - sex[1].mean) * (iter->height - sex[1].mean);
        }
        sex[0].variance = sumVarMale / sumMale;
        sex[1].variance = sumVarFemale / sumFemale;

        // cacl rate
        // t
        t = max((percent[0] - percent_old[0]) / percent_old[0], (percent[1] - percent_old[1]) / percent_old[1]);
        t = max(t, (sex[0].mean - sex_old[0].mean) / sex_old[0].mean);
        t = max(t, (sex[1].mean - sex_old[1].mean) / sex_old[1].mean);
        t = max(t, (sex[0].variance - sex_old[0].variance) / sex_old[0].variance);
        t = max(t, (sex[1].variance - sex_old[1].variance) / sex_old[1].variance);

    }

    for (int i = 0; i < 2; ++i)
    {
        LOG(INFO) << "mean: " << sex[i].mean << ", variance: " << sex[i].variance;
    }
    //     std::cout << "mean: " << sex[i].mean << ", variance: " << sex[i].variance << std::endl;
    // std::cout << "percent: " << percent[0] << ", percent: " << percent[1] << std::endl
    //             << std::endl;

    // cacl accuracy
    int correctNum = 0;
    float correctRate = 0;
    std::vector<EMData>::iterator itt;
    for (itt = m_vHeightData.begin(); itt < m_vHeightData.end(); ++itt)
    {
        float p[2];
        std::string csex;
        // char csex;
        p[0] = 1 / sqrt(2 * PI * sex[0].variance) * exp(-(itt->height - sex[0].mean) * (itt->height - sex[0].mean) / (2 * sex[0].variance));
        p[1] = 1 / sqrt(2 * PI * sex[1].variance) * exp(-(itt->height - sex[1].mean) * (itt->height - sex[1].mean) / (2 * sex[1].variance));

        csex = (p[0] > p[1]) ? "male" : "female";
        // std::cout <<"em :" <<csex <<std::endl;
        // std::cout <<"itt :"<<itt->sex<< std::endl;
        if (csex == itt->sex)
            correctNum++;
    }

    correctRate = float(correctNum) / m_vHeightData.size();
    // for (int i = 0; i < 2; ++i)
    // {
    //         std::cout << "mean: " << sex[i].mean << ", variance: " << sex[i].variance << std::endl;
    //         std::cout << "percent: " << percent[0] << ", percent: " << percent[1] << std::endl;
    //         // std::cout << "mean: " << sex[i].mean << ", variance: " << sex[i].variance << std::endl;
    // }

    LOG(INFO) << " rate: " << std::setprecision(5) << correctRate;
}

void EMalgorithm::initEMparams()
{
    // t = 1.0;
    tlimit = 0.000001;

    sex[0].mean = 165;
    sex[0].variance = 10.0;

    sex[1].mean = 150;
    sex[1].variance = 10.0;

    percent[0] = 0.5;
    percent[1] = 0.5;
}

// template<typename T>
void EMalgorithm::solveEMProblem()
{
    //
    std::vector<EMData>::const_iterator iter = m_vHeightData.begin();
    for (; iter != m_vHeightData.end(); ++iter)
    {
        // T a = gaussian(iter->height, 170, 10);
        Score sp;
        sp.f1 = 1 / (sqrt(2 * PI * sex[0].variance)) * exp(-(iter->height - sex[0].mean) * (iter->height - sex[0].mean) / (2 * sex[0].variance));
        sp.f2 = 1 / (sqrt(2 * PI * sex[1].variance)) * exp(-(iter->height - sex[1].mean) * (iter->height - sex[1].mean) / (2 * sex[1].variance));

        px.push_back(sp);
    }
    //E step  : calculate Qi
}



void EMalgorithm::solveEMProblem(bool todo)
{
    initModelparams();

    float preLLH = 5;
    float updateLLH = 1;
    float endlimit = 0.000001;

    float diff = preLLH - updateLLH;

    // iteration solve
    while (diff > endlimit)
    {
        doEStep();
        preLLH = calculateLogLikelyHood();

        doMStep();
        updateLLH = calculateLogLikelyHood();

        diff = preLLH - updateLLH;
    }

    for (int i = 0; i < clusters; i++)    
        LOG(INFO) << "mean: " << means[i] << " ,variance: " << variances[i]<< " \n";
    
    // cacl accuracy
    int correctNum = 0;
    float correctRate = 0;
    std::vector<EMData>::iterator itt;
    for (itt = m_vecData.begin(); itt < m_vecData.end(); ++itt)
    {
        float p[clusters];
        std::string csex;
        // char csex;
        for (int i = 0; i < clusters; i++)
        {
            p[i] = Model::getGM(itt->height, means[i], variances[i]);
        }


        csex = (p[0] > p[1]) ? "male" : "female";
        // std::cout <<"em :" <<csex <<std::endl;
        // std::cout <<"itt :"<<itt->sex<< std::endl;
        if (csex == itt->sex)
            correctNum++;
    }

    correctRate = float(correctNum) / m_vecData.size();
    LOG(INFO) << "correctRate :" << correctRate;
}

void EMalgorithm::initModelparams()
{
    clusters = 2;

    // for (int i = 0; i < clusters; i++)
    // {
    //     prior.push_back(1.0 / clusters);
    // }

    // means.push_back(165);
    // means.push_back(150);

    // variances.push_back(10);
    // variances.push_back(10);

    prior = new float[clusters];
    means = new float[clusters];
    variances = new float[clusters];

   // init 
    float mean, variance;
    for (int i = 0; i < clusters; i++)
    {
         // init mean variance
        for (size_t j = 0; j < m_vecData.size(); j++)
        {
            mean += m_vecData[j].height;
        }
        mean /= m_vecData.size();

        for (size_t j = 0; j < m_vecData.size(); j++)
        {
            variance += (m_vecData[j].height - mean) * (m_vecData[j].height - mean);
        }
        variance /= m_vecData.size();


        // init mixing para
        prior[i] = 1.0 / clusters;

        // means[i] = mean;
        variances[i] = variance;
    }
    means[0] = 165;
    means[1] = 150;
    LOG(INFO) << "variance: " << variances[0];
}

void EMalgorithm::doEStep()
{
    for (int i = 0; i < m_vecData.size(); i++)
    {
        float denom = 0.0;
        std::vector<float> wgt;
        for (int j = 0; j < clusters; j++)
        {
            float weight = prior[j] * Model::getGM(m_vecData[i].height, means[j], variances[j]);
            // LOG(INFO) << "weight: "<<std::setprecision(3)<<prior[j]<<" " << weight;
            denom = denom + weight;
            wgt.push_back(weight);
        }
        weightMat.push_back(wgt);

        for (int j = 0; j < clusters; j++)
        {
            weightMat[i][j] = weightMat[i][j] / denom;
            // LOG(INFO) << "weightMat: "<< weightMat[i][j] <<"\n";
        }
    }
}

void EMalgorithm::doMStep()
{
    // alpha  mixing coefficients
    std::vector<float> nalpha;
    for (int i = 0; i < clusters; i++)
    {
        double nj = 0.0;
        for (int j = 0; j < m_vecData.size(); j++)
        {
            nj += weightMat[j][i];
            // LOG(INFO) << "wm: "<<weightMat[j][i];
        }
        // std::cout << "nj: " << nj << "\n";
        nalpha.push_back(nj);

        prior[i] = nj / float(m_vecData.size());
        // std::cout << "prior: " << prior.at(i) << "\n";
    }

    //  miu
    for (int i = 0; i < clusters; i++)
    {
        float sum = 0.0;
        for (int j = 0; j < m_vecData.size(); j++)
        {
            sum += weightMat[j][i] * m_vecData[j].height;
        }
        means[i] = sum / nalpha.at(i);
        // std::cout << "mean: " << means[i] << "\n";
    }

    // sigma
    for (int i = 0; i < clusters; i++)
    {
        float sum = 0.0;
        for (int j = 0; j < m_vecData.size(); j++)
        {
            sum += weightMat[j][i] * (m_vecData[j].height - means[i]) * (m_vecData[j].height - means[i]);
        }
        variances[i] = sum / nalpha.at(i);
        // std::cout << "variances: " << variances[i] << "\n";
    }
}

float EMalgorithm::calculateLogLikelyHood()
{
    float result = 0.0;
    for (int i = 0; i < m_vecData.size(); i++)
    {
        float sum = 0.0;
        for (int j = 0; j < clusters; j++)
        {
            sum += prior[j] * Model::getGM(m_vecData[i].height, means[j], variances[j]);
        }
        result += log(sum);
    }
    return result;
}

// https://github.com/praveenramc/EMAlgorithm/blob/master/src/EM.java  code
// https://www.cnblogs.com/qizhou/p/13100817.html  theory