#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>

#include "DataBase.h"
#include "DataHelper.h"
#include "EMalgorithm.h"
// using DataHelper

int main( )
{        
        std::vector<EMData> infoData;
        DataHelper::getData(infoData);
        std::cout << infoData.size() << std::endl;

        std::shared_ptr<EMalgorithm> pEM = std::shared_ptr<EMalgorithm>(new EMalgorithm());
        pEM->setData(infoData);
        float rate = pEM->predProb();
        std::cout <<std::setprecision(5)<< rate << std::endl;
        return 0;
}
