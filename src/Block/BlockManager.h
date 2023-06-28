#pragma once
#include"BlockIndexClashPoint.h"
#include"BlockIndexHash.h"
#include"BlockIndexRBTree.h"
#include <vector>
class BlockManager
{
private:
    vector<BlockIndexHash*>* HashTable;//ʹ�ø�ָ���hash����в���;
    vector<BlockIndexHash*> hashTable1;
    vector<BlockIndexHash*> hashTable2;
    //BlockIndexRBTree��BlockIndexClashPoint������ʱ��ʹ��ָ���໥���ӡ�
    int hashTableSize, hashKey;
    bool clearHashTable(vector<BlockIndexHash*>* tablePoint);//�ú�����Ŀ�������һ��hash�������Ԫ�ز��ͷ��ڴ�
    bool initHashTable(int HashTableSize, int HashKey);//��ʼ��hash��
public:
    bool addBlock(string DatanodeID, string Name);
    bool removeBlock(string Name);
    int getBlock(string Name);//
    bool refrashBlock(int Datanode, string Name);
    bool refrashHashTable();//�ú�����Ŀ�����Ż���ѯ�ٶȣ�����hash��
    string getBlockALL(string name);
    BlockManager(int HashTableSize, int HashKey);
};

