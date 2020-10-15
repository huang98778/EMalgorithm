
#ifndef _DISTRIBUTE_MODEL_
#define _DISTRIBUTE_MODEL_

#include <float.h>
#include <math.h>

#define PI  3.1415926

class Model
{
private:
    
public:
    Model(/* args */);
    ~Model();
};

// Model::Model(/* args */)
// {
// }

// Model::~Model()
// {
// }


class GMmodel // : public Model
{
private:
    
    float m_mean;
    float m_variance;

public:
    GMmodel(float mean, float variance);
    ~GMmodel();

    void updateProbility(const float &data,  float &prob);
};



#endif