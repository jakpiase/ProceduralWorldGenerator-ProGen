#include <iostream>
#include <glog/logging.h>

int main(int argc, char* argv[]) {
    google::InitGoogleLogging(argv[0]);
    FLAGS_logtostderr = 1;
    VLOG(1) << "Starting ProGen";


    VLOG(1) << "ProGen exited succesfully";
    return 0;
}
