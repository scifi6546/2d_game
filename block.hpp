#ifndef Block_h
#define Block_h
#include <string>
#include <glm/glm.hpp>
#include <vector>
#include "entity.h"
#include "mesh.h"
#include "tile.hpp"
const bool DEBUG=false;


class TileMesh{
    public:
        TileMesh();
        Model getModel();
    private:
        std::vector<Model> model;
};

const int NUM_BLOCKS=4;

extern TileMesh tileMesh; //mesh containing all faces of block
extern std::vector<RunTimeModel>models;
const int chunkSize=8;
const int renderChunkSize = chunkSize;//renderChunkSize has to equal chunk size I do not know why
const int CHUNK_RENDER_DIST=5;
const int numVertChunks = 6;//height of vertical chunks
class Chunk{
    public:
        Chunk();
        //Chunk(std::vector<Tile*> tiles,glm::vec3 root_pos);//heights 2 by 2 grid  x cols z rows
        /*
        Array Example
         XXXXXXXX
        Z
        Z
        Z
        Z

        */
        void setMeshes();
        std::vector<int> genHeights(TileMap in);//generates array of height vectors
        void draw();
        Tile getTile(int x, int z);
        //sets block in chunk
        void setTile(int x, int z, Tile tile_in);
        ~Chunk();
        glm::vec3 getRoot(){
            return this->root_pos;
        }
    private:
        TileMap loadTiles(std::string file);//loads Tiles from file ./maps/default.map
        void makeMap(TileMap in,std::vector<int> number);//generates map based on input tile map and number array containing similar blocks (see map.md)
        std::vector<Tile> tiles;
        glm::vec3 root_pos;
        int isBlock = 0;//checks if there is any air in block if there is then int >=1
        Model mesh; 
        std::vector<RunTimeModel> runModel;
};
class World{
    public:
        Chunk loadedChunk= Chunk();//outer vector is layers of inner layer
        void draw();
        World(glm::vec3 pos_in);
        glm::vec3 tick(glm::vec3 input_move,float delta_time);//delta time measured in seconds
        Tile getTile(int x, int z);//gets a block at x y z 
        //sets the block at x,y,z to block
        void setTile(int x, int z, Tile block);
        void setCamPos(glm::vec3 pos);
        void setCamPersp(float rotx, float roty);
        Entity player;
    private:
        glm::vec3 cam_pos=glm::vec3(16.0,2.0,16.0);
        int rootx=0;
        int rootz=0;

};

#endif