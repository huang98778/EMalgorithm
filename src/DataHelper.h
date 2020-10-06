/*
 * @Author: your name
 * @Date: 2020-10-06 11:51:54
 * @LastEditTime: 2020-10-06 11:51:55
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: /EMalgorithm/src/DataHelper.h
 */
#ifndef _DATA_HELPER_H_
#define _DATA_HELPER_H_

#include <vector>

#include "DataBase.h"

class DataHelper
{
private:
        /* data */
public:
        DataHelper(/* args */);
        ~DataHelper();

        static bool getData(const std::string &dataDir, std::vector<EMData> &data);
};

#endif /* _DATA_HELPER_H_ */
