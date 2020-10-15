#include "EMalgorithm.h"
#include <algorithm>
#include <iostream>
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

float EMalgorithm::predProb()
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

            std::cout << it->f1 << " " << it->f2 << std::endl; // Qi(zi)
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

        for (int i = 0; i < 2; ++i)
            std::cout << "mean: " << sex[i].mean << ", variance: " << sex[i].variance << std::endl;
        std::cout << "percent: " << percent[0] << ", percent: " << percent[1] << std::endl
                  << std::endl;
    }
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

    return correctRate;
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

// template<typename T>
// T gaussian(const T xi, const T mean, const T variance)
// {
//     T gaussian = 0.0;
//     gaussian = exp(-((xi - mean) * (xi - mean)) / (2 * variance));
//     gaussian = gaussian / (sqrt(2 * PI) * sqrt(abs(variance)));
//     return gaussian;
// }

void EMalgorithm::solveEMProblem(bool todo)
{
    setNewPara();
    initModelparams();

    float t = 1e3;
    while (t>0.01)
    {
        doEStep();
    }
    

    

    
}

float getGM(const float xi, const float mean, const float variance)
{
    float gs = 0.0;
    gs = exp(-((xi - mean) * (xi - mean)) / (2 * variance));
    gs = gs / (sqrt(2 * PI) * sqrt(abs(variance)));
    return gs;
}

void EMalgorithm::setNewPara()
{
    // clusters = 2;
    // means[clusters];
    // prior[clusters];
    // variance[clusters];
    // wight[m_vecData.size()][clusters];
}

void EMalgorithm::initModelparams()
{
    int si = m_vecData.size();

    for (size_t i = 0; i < clusters; i++)
    {
        //TODO: means

        prior[i] = 1.0/clusters;
        std::cout<<" "<<prior[i]<<"\n";

        variance[i] = 1.0;
    }

    means[0] = 175.0;
    means[1] = 160.0;

    for (size_t i = 0; i < si; i++)
    {
        mean += m_vecData[i].height;
    }
    mean /= si;

    for (size_t i = 0; i < si; i++)
    {
        covariance += (m_vecData[i].height - mean) * (m_vecData[i].height - mean);
    }
    covariance /= si;
    
    
    
}

void EMalgorithm::doEStep()
{
    for (size_t i = 0; i < m_vecData.size(); i++)
    {
        float demon = 0.0;

        std::vector<float> wi(clusters,0);
        for (size_t j = 0; j < clusters; j++)
        {
            float wgt = prior[j] * getGM( m_vecData[i].height, means[j], variance[j]);

            demon += wgt;

            wi.at(j) = wgt;
            // std::cout<<" wgt: "<<wgt<<"\n";
        }

        wight.push_back(wi);

        for (size_t j = 0; j < clusters; j++)
        {
            wight[i][j] = wight[i][j] / demon;
            
        }
        
        
    }
    std::cout<<" wgt size: "<<wight[0].size()<<"\n";
    
}

// https://github.com/praveenramc/EMAlgorithm/blob/master/src/EM.java