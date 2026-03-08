#ifndef BLOCK_H
#define BLOCK_H



#include "mesh.h"

class Block : public Mesh
{
public:
    Block();
    ~Block();
//    static const uint8_t VERTEX_COUNT = 8;
    static const uint8_t VERTEX_ARR_LENGTH = 24;

//    static const uint8_t TRIANGLE_COUNT = 12;
    static const uint8_t INDEX_ARR_LENGTH = 36;


};

#endif // BLOCK_H
