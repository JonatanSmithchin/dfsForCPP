#include "BlockIndexClashPoint.h"
BlockIndexClashPoint::BlockIndexClashPoint(string blockid, int Size, int GenerationTimeStamp)
    :BlockIndex(blockid, Size, GenerationTimeStamp) {
    next = NULL;
}
