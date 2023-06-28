#pragma once
#include"BlockIndex.h"
class BlockIndexClashPoint:BlockIndex
{
private:
    string name;
    BlockIndexClashPoint* next;
public:
    bool insert(string DataNodeID, string name);
    bool remove(string name);
    int inquire(string name);
    string inquireALL(string name);
    BlockIndexClashPoint(string blockid, int Size, int GenerationTimeStamp) :BlockIndex(blockid, Size, GenerationTimeStamp) {}
};

