// delete that file after adding any other file to "/src" directory
// this file's only purpose is not to leave only main.cpp here, so
// my trick in cmake will be working

#include "tmp.h"

int log(void){
    VLOG(2) << "Delete this log";
}
