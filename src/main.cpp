/*
 * @Author: your name
 * @Date: 2020-10-06 11:52:42
 * @LastEditTime: 2020-10-17 17:26:36
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /EMalgorithm/src/main.cpp
 */
#include <iostream>
#include <vector>
#include <memory>
#include <glog/logging.h>
#include <boost/filesystem.hpp>
// #include <boost/filesystem/fstream.hpp>

#include "DataBase.h"
#include "DataHelper.h"
#include "EMalgorithm.h"
// using DataHelper

#include "Model.h"

int main(int argc, char* argv[])
{
        // google::ParseCommandLineFlags(&argc, &argv, true);
        google::InitGoogleLogging("EM Algorithm  ");
        LOG(INFO) << "EM Algorithm  ============>";

        std::string logMainDir = "hy_EMlog";
        LOG(INFO) << "log dir :" << logMainDir;
        boost::filesystem::path logPath(logMainDir);
        if ( !boost::filesystem::exists(logMainDir))
        {
                boost::filesystem::create_directory(logMainDir);
        }
        google::SetLogDestination(google::GLOG_INFO, (logMainDir + "/INFO").c_str());
        google::SetLogDestination(google::GLOG_WARNING, (logMainDir + "/WARNING").c_str());
        google::SetLogDestination(google::GLOG_ERROR, (logMainDir + "/ERROR").c_str());

        google::SetStderrLogging(google::INFO);

        std::string dir = "em.txt";
        std::vector<EMData> infoData;
        DataHelper::getData(dir, infoData);
        std::cout << infoData.size() << std::endl;

        std::shared_ptr<EMalgorithm> pEM = std::shared_ptr<EMalgorithm>(new EMalgorithm());
        pEM->setData(infoData);
        pEM->predProb();
        // std::cout << std::setprecision(5) << rate << std::endl;
        // pEM->initEMparams();
        // pEM->solveEMProblem();

        LOG(INFO) << "========================================\n";
        LOG(INFO) << "========================================\n";

        LOG(INFO) << "=============  optmize EM  =============\n";
        LOG(INFO) << "========================================\n";

        // test
        // std::vector<float> xi {4, 4, 4, 7, 7};
        // std::vector<float> mi {4, 4, 4, 7, 7};
        // std::vector<float> vi {1, 1, 1, 1, 1};
        // float t = Model::getMultGM(xi, mi, vi);
        // LOG(INFO) << " multGM: " << t;

        pEM->solveEMProblem(true);




        google::ShutdownGoogleLogging();
        return 0;
}
