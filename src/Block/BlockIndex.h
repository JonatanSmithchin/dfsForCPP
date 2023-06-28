#pragma once
#include <iostream>
#include <cstring>
using namespace std;
class BlockIndex
{
private:
    string blockId;
    long size;
    long generationTimestamp;//
public:
    BlockIndex();
    BlockIndex(string blockid, int Size, int GenerationTimeStamp);
};

