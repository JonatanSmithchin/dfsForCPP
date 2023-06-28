#include "BlockManager.h"
BlockManager::BlockManager(int HashTableSize, int HashKey) {
    hashTableSize = HashTableSize;
    hashKey = HashKey;
    if (!initHashTable(hashTableSize, hashKey)) {
        ///////////////////////////////////////////////////////////////////////////
    }
}
