//
// Created by 刘骁 on 2023/4/10.
//

#ifndef DFSFORCPP_DATANODEDESCRIPTOR_H
#define DFSFORCPP_DATANODEDESCRIPTOR_H

#include "../common/Datanode/DatanodeInfo.h"
#include "../common/Block/BlockInfo.h"
#include "queue"
using namespace std;
class DatanodeDescriptor :public datanodeInfo {
private:
    bool isAlive;
    queue<BlockInfo> replicateBlocks;
    queue<BlockInfo> recoverBlocks;
};


#endif //DFSFORCPP_DATANODEDESCRIPTOR_H
