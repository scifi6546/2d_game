#include "block.h"
#include "texture.h"
#include "physics.h"
#include "tile.h"
#include "loadfile.h"
#include <stdlib.h> 
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

std::vector<RunTimeModel>models;
TileMesh tileMesh;

TileMesh::TileMesh(){
    model.reserve(1);
    std::vector<glm::vec3> pos;
    pos.reserve(4);
    std::vector<glm::vec2> texcoord;
    texcoord.reserve(4);
    std::vector<unsigned int> indicies;
    indicies.reserve(6);
    std::vector<glm::vec3> normal;
    normal.reserve(6);
//face 0
    pos.push_back(glm::vec3(0,0,0));
    pos.push_back(glm::vec3(1,0,0));
    pos.push_back(glm::vec3(1,0,1));
    pos.push_back(glm::vec3(0,0,1));

    texcoord.push_back(glm::vec2(0,0));
    texcoord.push_back(glm::vec2(1,0));
    texcoord.push_back(glm::vec2(1,1));
    texcoord.push_back(glm::vec2(0,1));

    normal.push_back(glm::vec3(0,1,0));
    normal.push_back(glm::vec3(0,1,0));
    normal.push_back(glm::vec3(0,1,0));
    normal.push_back(glm::vec3(0,1,0));

    indicies={0,1,2,0,3,2};
    model.push_back(Model(pos,texcoord,indicies,normal));
}
Model TileMesh::getModel(){
    return model[0];
}
Chunk::Chunk(){
    //printf("empty constructor nothin happened");
        //printf("%f,%f,%f\n",root_pos.x,root_pos.y,root_pos.z);
    this->root_pos=glm::vec3(0.0,0.0,0.0);
    this->makeMap(this->loadTiles("./maps/default.map"));
    this->tiles.reserve(chunkSize*chunkSize);
    this->setMeshes();
}
tileMap Chunk::loadTiles(std::string file){
    std::string map = loadFile(file);
    tileMap out;
    char lastChar = map[0];//stores last important charecter
    std::string currentNum;
    int temp_number;
    int num_pos=0;
    //std::vector<int> tileType;
    //std::vector<glm::vec3> tile_pos;
    //std::vector<int> bottom;
    int x=0,z=0;
    int tempTile=0;
    int temp_bottom=0;
    int temp_top=0;
    for(int i =0; i<map.length();i++){
        if(map[i]==','||map[i]==')'){
            temp_number=std::stoi(currentNum);
            printf("temp_number: %i num_pos: %i\n",temp_number,num_pos);
            if(num_pos==0){
                tempTile=temp_number;
            }
            if(num_pos==1){
                temp_bottom=temp_number;
            } 
            if(num_pos==2){
                temp_top=temp_number;
            }   
            num_pos++;
            //printf("number: %i\n",temp_number);
        }
        if(map[i]=='('||map[i]==','||map[i]==')'||map[i]=='\n'||map[i]==' '){
                
            if(map[i]==')'){
                out.tileMap.push_back((TileTypes)tempTile);
                int tileHeight=temp_number;
                out.tilePos.push_back(glm::vec3(x,temp_bottom,z));
                out.heights.push_back(temp_top-temp_bottom);
                z--;
                num_pos=0;
            }
            if(map[i]=='\n'){
                
                x++;
                z=0;
            }
            lastChar=map[i];
            currentNum="";

        }else{
            currentNum+=map[i];
        }
    }
    return out;
}
void Chunk::makeMap(tileMap in){
    for(int i=0;i<in.tileMap.size();i++){
        if(in.tileMap[i]==GRASS){
             this->tiles.push_back(Grass(in.tilePos[i],in.heights[i]));
        }
        if(in.tileMap[i]==ROCK){
             this->tiles.push_back(Rock(in.tilePos[i],in.heights[i]));
        }
    }
}
void Chunk::setMeshes(){
    this->mesh = Model(); 
    for(int i = 0; i<tiles.size();i++){
        //printf("texture num: %i\n",tiles[i].textureNum);
        printf("texture_num: %i\n",tiles[i].textureNum);
        this->mesh.add(tiles[i].getModel(),tiles[i].pos,tiles[i].textureNum);
    }
    std::vector<Model> temp = {this->mesh};
    runModel = initMesh(temp);
}
void Chunk::draw(){
    drawMesh(runModel[0],glm::vec3(0.0,0.0,0.0));
}
Tile Chunk::getTile(int x, int z){
    return this->tiles[x*chunkSize+z];
}
void Chunk::setTile(int x, int z, Tile tile_in){
    //this->tiles.assign(x*chunkSize+z,tile);
    this->tiles[x*chunkSize+z]=tile_in;
}
Chunk::~Chunk(){
    this->tiles.clear();
    std::cout<<"chunk deleted\n";
}
World::World(glm::vec3 pos_in){
    printf("hello world");
    std::vector<Tile*> tiles;
    //this->loadedChunk=Chunk();
}
void World::draw(){
    //printf("drawn!!\n");
    bindTexture(0);
    this->loadedChunk.draw();    
}
glm::vec3 World::tick(glm::vec3 input_move, float delta_time){
    //player_pos = physics::runFrame(player_pos,input_move,this,delta_time); 
    return cam_pos;
}
void World::setCamPos(glm::vec3 pos){
    this->cam_pos=pos;
}
Tile World::getTile(int x, int z){
    return this->loadedChunk.getTile(x,z);
}
void World::setTile(int x, int z, Tile tile){
    this->loadedChunk.setTile(x,z,tile);
}