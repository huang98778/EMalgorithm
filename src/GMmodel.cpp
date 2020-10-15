#include "Model.h"

GMmodel::GMmodel(float mean, float variance):m_mean(mean),m_variance(variance)
{
}

GMmodel::~GMmodel()
{
}

void GMmodel::updateProbility( const float &data, float &prob)
{
    float dis = data - m_mean;
    float xd = -dis*dis;
    float ex = exp( xd /  (2 * m_variance));

    float sqv = 1 / (sqrt(2 * PI * m_variance));

    prob =  sqv*ex;    
    
}