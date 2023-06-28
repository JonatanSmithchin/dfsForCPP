#pragma once
#include"BlockIndexClashPoint.h"
#include"BlockIndexHash.h"
#include"BlockIndexRBTree.h"
#include <vector>
class BlockManager
{
private:
    vector<BlockIndexHash*>* HashTable;//使用该指针对hash表进行操作;
    vector<BlockIndexHash*> hashTable1;
    vector<BlockIndexHash*> hashTable2;
    //BlockIndexRBTree和BlockIndexClashPoint当创建时再使用指针相互连接。
    int hashTableSize, hashKey;
    bool clearHashTable(vector<BlockIndexHash*>* tablePoint);//该函数的目的是清除一个hash表的所有元素并释放内存
    bool initHashTable(int HashTableSize, int HashKey);//初始化hash表
public:
    bool addBlock(string DatanodeID, string Name);
    bool removeBlock(string Name);
    int getBlock(string Name);//
    bool refrashBlock(int Datanode, string Name);
    bool refrashHashTable();//该函数的目的是优化查询速度，扩大hash表
    string getBlockALL(string name);
    BlockManager(int HashTableSize, int HashKey);
};

