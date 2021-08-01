#include <iostream>
#include "glog/logging.h"
#include "tmp.h"

int main(int argc, char* argv[]) {
    google::InitGoogleLogging(argv[0]);
    FLAGS_logtostderr = true;
    LOG(INFO) << "Starting ProGen";


    LOG(INFO) << "ProGen exited succesfully";
    google::ShutdownGoogleLogging();
    return 0;
}
