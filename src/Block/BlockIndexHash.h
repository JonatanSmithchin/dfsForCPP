#pragma once
#include "BlockIndexRBTree.h"
#include "BlockIndex.h"
class BlockIndexHash:BlockIndex
{
private:
    BlockIndexRBTree* son;
    string name;
public:
    bool insert(string DataNodeID, string name);
    bool remove(string name);
    BlockIndexRBTree* checkRBTreeRoot();//检查有无红黑树根节点
    bool createRBTreeRoot(string DataNodeID, string name);//创建红黑树根节点
    int inquire(string name);
    string inquireALL(string name);
    BlockIndexHash() :BlockIndex() {}
    BlockIndexHash(string blockid, int Size, int GenerationTimeStamp) :BlockIndex(blockid, Size, GenerationTimeStamp) {}
};

