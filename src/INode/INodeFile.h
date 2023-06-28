//
// Created by 刘骁 on 2023/4/10.
//

#ifndef DFSFORCPP_INODEFILE_H
#define DFSFORCPP_INODEFILE_H
#include "INode.h"
#include "../common/Block/BlockInfo.h"

class INodeFile :public INode{
private:
    long header;
    BlockInfo blocks[];
public:
bool isFile();

private:
    bool isDir() override;

    bool isRoot() override;

    bool isSymlink() override;
};


#endif //DFSFORCPP_INODEFILE_H
