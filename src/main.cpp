/*
 * @Author: your name
 * @Date: 2020-10-06 11:52:42
 * @LastEditTime: 2020-10-06 19:54:36
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /EMalgorithm/src/main.cpp
 */
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
        std::string dir = "em.txt";
        std::vector<EMData> infoData;
        DataHelper::getData(dir, infoData);
        std::cout << infoData.size() << std::endl;

        std::shared_ptr<EMalgorithm> pEM = std::shared_ptr<EMalgorithm>(new EMalgorithm());
        pEM->setData(infoData);
        float rate = pEM->predProb();

        pEM->initEMparams();
        pEM->solveEMProblem();
        std::cout << std::setprecision(5) << rate << std::endl;
        return 0;
}
