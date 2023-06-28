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
    BlockIndexRBTree* checkRBTreeRoot();//������޺�������ڵ�
    bool createRBTreeRoot(string DataNodeID, string name);//������������ڵ�
    int inquire(string name);
    string inquireALL(string name);
    BlockIndexHash() :BlockIndex() {}
    BlockIndexHash(string blockid, int Size, int GenerationTimeStamp) :BlockIndex(blockid, Size, GenerationTimeStamp) {}
};

