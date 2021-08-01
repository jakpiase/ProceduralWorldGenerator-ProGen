#include <iostream>
#include "glog/logging.h"
#include "tmp.h"

int main(int argc, char* argv[]) {
    google::InitGoogleLogging(argv[0]);
    FLAGS_logtostderr = 1;
    LOG(INFO) << "Starting ProGen";


    google::ShutdownGoogleLogging();
    LOG(INFO) << "ProGen exited succesfully";
    return 0;
}
