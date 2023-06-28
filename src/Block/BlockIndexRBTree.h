#pragma once
#include "BlockIndexClashPoint.h"
#include "BlockIndex.h"
#define red false 
#define black true 
class BlockIndexRBTree:BlockIndex {
private:
	BlockIndexRBTree* rson, * lson, * fa;
	BlockIndexClashPoint* son;
	string name;
	int key;
	bool RB;//0->red,1->black
	bool TF;
	void left_turn(BlockIndexRBTree** b);
	void right_turn(BlockIndexRBTree** b);
	BlockIndexRBTree* MakeNULLSon();
	BlockIndexRBTree* brother(BlockIndexRBTree** a);
	void incheck(BlockIndexRBTree** root, BlockIndexRBTree** a);
	BlockIndexRBTree* FindMidOrderSuccessorNode(BlockIndexRBTree** a);
	void movecheck(BlockIndexRBTree** root, BlockIndexRBTree** a);
public:
	void insert(BlockIndexRBTree** root, int x, string blockid, int Size, int GenerationTimeStamp);
	void remove(BlockIndexRBTree** root, int x);
	//	BlockIndexClashPoint* checkCPHead();//是否已有冲突节点
	bool createCPHead();//创建第一个冲突节点（链表头）
	int inquire(BlockIndexRBTree** root, int x, string name);
	string inquireALL(BlockIndexRBTree** root, int x, string name);
	BlockIndexRBTree() :BlockIndex() {}
	BlockIndexRBTree(BlockIndexRBTree* Fa, int Key, string blockid, int Size, int GenerationTimeStamp) :BlockIndex(blockid, Size, GenerationTimeStamp) {}
};

