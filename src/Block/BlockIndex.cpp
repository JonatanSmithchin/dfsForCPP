#include "BlockIndex.h"
BlockIndex::BlockIndex() {
    size = 0;
    generationTimestamp = 0;
}
BlockIndex::BlockIndex(string blockid, int Size, int GenerationTimeStamp) {
    blockId = blockid;
    size = Size;
    generationTimestamp = GenerationTimeStamp;
}