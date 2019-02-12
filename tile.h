#ifndef TILE_H
#define TILE_H

#include "mesh.h"
#include <vector>
#include <glm/glm.hpp>
#include <string>

class Tile{
    public:
        Tile();
        Tile(glm::vec3 pos_in);
        std::string getTexturePath(){return texturePath;};
        Model getModel(){return meshModel;};
        glm::vec3 pos=glm::vec3(0.0,0.0,0.0);
        int textureNum = 0;
        void makeModel();
        std::string objName="";
    private:
        
        void loadModel();
        //generates square mesh
        void genSquare();
        //void initTexture();
        
        Model meshModel;
        std::string texturePath;

};
class Grass:public Tile{
    public:
        Grass(glm::vec3 pos_in);
    private:
        std::string texturePath="./textures/grass.png";
};
class Rock:public Tile{
    public:
        Rock(glm::vec3 pos_in);
        //std::string objName="./Models/Rock.obj";
    private:
       
        std::string texturePath="./textures/rock.png";
};
#endif