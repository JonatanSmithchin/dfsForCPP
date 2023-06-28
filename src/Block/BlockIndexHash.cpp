#include "BlockIndexHash.h"
BlockIndexHash::BlockIndexHash() :BlockIndex() {
	son = NULL;
}
BlockIndexHash::BlockIndexHash(string blockid, int Size, int GenerationTimeStamp) :BlockIndex(blockid, Size, GenerationTimeStamp) {
	son = NULL;
}
