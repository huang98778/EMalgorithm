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

        static bool getData(std::vector<EMData> &data);
};

#endif /* _DATA_HELPER_H_ */
