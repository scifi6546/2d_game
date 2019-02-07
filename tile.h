#ifndef TILE_H
#define TILE_H

#include "mesh.h"
#include "block.h"
#include <vector>
#include <glm/glm.hpp>
#include <string>

class Tile{
    public:
        Tile();
        TILE_TYPES tileType;
    private:
        void initTexture();
        Model meshModel;
        std::string texturePath;
};
class Grass:public Tile{
    
};
#endif