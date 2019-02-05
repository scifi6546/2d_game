#ifndef Block_h
#define Block_h
#include <string>
#include <glm/glm.hpp>
#include <vector>
#include "mesh.h"
const bool DEBUG=false;
class TileMesh{
    public:
        TileMesh();
        std::vector<Model> getModel();
    private:
        std::vector<Model> model;
};
enum TILE_TYPES{GRASS,ROCK};
const int NUM_BLOCKS=4;
class Tile{
    public:
        Tile(glm::vec3 pos,TILE_TYPES tiletype){this->pos=pos;this->tileType=tileType;}
        void setTile(TILE_TYPES tile){this->tileType=tile;}
        glm::vec3 pos;
        TILE_TYPES tileType;
};
extern TileMesh tileMesh; //mesh containing all faces of block
extern std::vector<RunTimeModel>models;
const int chunkSize=32;
const int renderChunkSize = chunkSize;//renderChunkSize has to equal chunk size I do not know why
const int CHUNK_RENDER_DIST=5;
const int numVertChunks = 6;//height of vertical chunks
class Chunk{
    public:
        Chunk();
        Chunk(std::vector<Tile*> tiles,glm::vec3 root_pos);//heights 2 by 2 grid  x cols z rows
        /*
        Array Example
         XXXXXXXX
        Z
        Z
        Z
        Z

        */
        void setMeshes();
        void draw();
        TILE_TYPES getTile(int x, int z);
        //sets block in chunk
        void setTile(int x, int z, TILE_TYPES tile);
        ~Chunk();
        glm::vec3 getRoot(){
            return this->root_pos;
        }
    private:
        std::vector<Tile> tiles;
        glm::vec3 root_pos;
        int isBlock = 0;//checks if there is any air in block if there is then int >=1
        Model mesh; 
        std::vector<RunTimeModel> runModel;
};
class World{
    public:
        Chunk loadedChunk;//outer vector is layers of inner layer
        void draw();
        World(glm::vec3 pos_in);
        glm::vec3 tick(glm::vec3 input_move,float delta_time);//delta time measured in seconds
        TILE_TYPES getTile(int x, int z);//gets a block at x y z 
        //sets the block at x,y,z to block
        void setTile(int x, int z, TILE_TYPES block);

    private:
        glm::vec3 player_pos=glm::vec3(-0.1,1.5,-0.1);
        int rootx=0;
        int rootz=0;

};

#endif