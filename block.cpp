#include "block.h"
#include "texture.h"
#include "physics.h"
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
    printf("empty constructor nothin happened");
}
Chunk::Chunk(std::vector<Tile*> tiles,glm::vec3 root_pos){
    //printf("%f,%f,%f\n",root_pos.x,root_pos.y,root_pos.z);
    this->root_pos=root_pos;

    this->tiles.reserve(tiles.size());
    for(int i=0;i<tiles.size();i++){
        this->tiles.push_back(*tiles[i]);
    }
    //models = initMesh(tileMesh.getModel());
    this->setMeshes();
}

void Chunk::setMeshes(){
    this->mesh = Model(); 
    this->mesh.add(tileMesh.getModel(),glm::vec3(-10.0,0.0,-10.0),0);//needs to be done IDK why
    for(int i =0;i<chunkSize;i++){
        for(int j=0;j<chunkSize;j++){
            this->mesh.add(tileMesh.getModel(),glm::vec3((float)i,0.0,(float) j),0);
        }
    } 
    std::vector<Model> temp = {this->mesh};
    runModel = initMesh(temp);
}
void Chunk::draw(){
    drawMesh(runModel[0],glm::vec3(0.0,0.0,0.0));
}
TILE_TYPES Chunk::getTile(int x, int z){
    return this->tiles[x*chunkSize+z].tileType;
}
void Chunk::setTile(int x, int z, TILE_TYPES tile){
    this->tiles[x*chunkSize+z].setTile(tile);
}
Chunk::~Chunk(){
    this->tiles.clear();
    std::cout<<"chunk deleted\n";
}
World::World(glm::vec3 pos_in){
    printf("hello world");
    std::vector<Tile*> tiles;
    this->loadedChunk=Chunk(tiles,glm::vec3(0.0,0.0,0.0));
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
TILE_TYPES World::getTile(int x, int z){
    return this->loadedChunk.getTile(x,z);
}
void World::setTile(int x, int z, TILE_TYPES tile){
    this->loadedChunk.setTile(x,z,tile);
}