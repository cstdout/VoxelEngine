#include "region.h"

Region::Region()
{

}
uint32_t Region::getTotalBlockCount()
{
    return getTotalChunkCount() * Chunk::getTotalBlockCount();
}
uint32_t Region::getTotalChunkCount()
{
    return WIDTH_IN_CHUNKS * HEIGHT_IN_CHUNKS * DEPTH_IN_CHUNKS;
}
uint32_t Region::getAreaInBlocks()
{
    return getAreaInChunks() * Chunk::getAreaInBlocks();
}
uint32_t Region::getAreaInChunks()
{
    return WIDTH_IN_CHUNKS * DEPTH_IN_CHUNKS;
}
