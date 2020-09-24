
#include "DataHelper.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

DataHelper::DataHelper(/* args */)
{
}

DataHelper::~DataHelper()
{
}

bool DataHelper::getData(std::vector<EMData> &data)
{
        std::ifstream fin("em.txt");
        // fin.open("em.txt");
        if (!fin.is_open())
        {
                std::cout << "wrong data .. " << std::endl;
                return false;
        }
        std::string dataline;
        int cols, rows;
        // getline(fin, dataline);
        // std::stringstream fl(dataline);
        fin >> cols >> rows;
        // std::
        EMData aData;
        for (size_t i = 0; i < cols; i++)
        {
                std::string sex;
                int height;
                // getline(fin, dataline);
                fin >> sex >> height;
                aData.sex = sex;
                aData.height = height;

                // std::cout <<"=================="<< aData.sex <<"  "<<aData.height << std::endl;

                data.push_back(aData);
        }
        return true;
}