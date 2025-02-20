#ifndef TILE_H
#define TILE_H

#include "mesh.h"
#include <vector>
#include <glm/glm.hpp>
#include <string>
enum TileTypes{GRASS,ROCK};
enum LAYER_TYPE{BOT,MID,TOP};
class TileMap{
    public: 
    std::vector<TileTypes> map ;//tile types same length as tilePos
    std::vector<glm::vec3> tilePos;//position of tiles
    std::vector<int> heights;//heights of tiles altitude of top tile calculated with: tilePos[i].y+heights
    int width=1;//width in z
    int height=1;//width i
    TileMap();
};
class Tile{
    public:
        Tile();
        //Tile(glm::vec3 pos_in);
        Tile(glm::vec3 pos_in,int number);
        std::string getTexturePath(){return texturePath;};
        Model getModel(){return meshModel;};
        glm::vec3 pos=glm::vec3(0.0,0.0,0.0);

        int textureNum = 0;
        void makeModel(int bottom,int top,int number);
        std::string objName="";
        bool useMultiModels=false;//checks if using multiple models
    private:
        Model loadMultiModel(int bottom,int top, int number);
        Model loadModel(std::string in);
        //generates square mesh
        void genSquare();
        //void initTexture();
        
        Model meshModel;
        std::string multiBasePath="./Models/rock/";
        std::string texturePath;
        

};
class Grass:public Tile{
    public:
        //Grass(glm::vec3 pos_in);
        Grass(glm::vec3 pos_in,int height,int number);
    private:
        std::string texturePath="./textures/grass.png";
};
class Rock:public Tile{
    public:
        //Rock(glm::vec3 pos_in);
        Rock(glm::vec3 pos_in,int height,int number);
        //std::string objName="./Models/Rock.obj";
        //textureNum = 1;
    private:
        
        std::string texturePath="./textures/rock.png";
};
#endif