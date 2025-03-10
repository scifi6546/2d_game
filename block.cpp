#include "block.hpp"
#include "texture.h"
#include "physics.h"
//#include "tile.hpp"
#include "loadfile.h"
#include <stdlib.h> 
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

std::vector<RunTimeModel>models;
TileMesh tileMesh;
void printTileMap(TileMap in,std::vector<int> number){
    printf("tile map:\n\n");
    printf("tilemap.width: %i, tilemap.height: %i\n",in.width,in.height);
    printf("tileMap.size(): %i\n",(int) in.map.size());
    for(int i =0;i<in.map.size();i++){
        printf("(%i,%i,%i) ",(int) in.map[i],in.heights[i],number[i]);
        //std::cout<<in.tileMap[i];
        if(((i+1)%(in.width))==0&&i>0){
            printf("\n");
            //printf("new line added\n");
        }
    }
    std::cout<<"\n\n\n";
}
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

    this->root_pos=glm::vec3(0.0,0.0,0.0);
    TileMap temp = this->loadTiles("./maps/default.map");
    
    std::vector<int> height = this->genHeights(temp);
    printTileMap(temp,height);
    this->makeMap(temp,height);
    
    this->tiles.reserve(chunkSize*chunkSize);
    this->setMeshes();
    
}
//still needs to be tested almost garuenteed to crash
std::vector<int> Chunk::genHeights(TileMap in){
    std::vector<int> out;
    int tempH;
    for(int i =0;i<in.map.size();i++){
        int temp=0;
        if(i-in.width>=0){
            if(in.heights[i-in.width]==in.heights[i]){
                temp+=1;
            }
        }else{
            temp+=1;
        }
        if(i-1>=0){
            if(in.heights[i-1]==in.map[i]){
                temp+=10;
            }
        }else{
            temp+=10;
        }
        if(i+1<in.heights.size()){
            if(in.heights[i+1]==in.heights[i]){
                temp+=100;
            }
        }else{
            temp+=100;
        }
        if(i+in.width<in.heights.size()){
            if(in.heights[i+in.width]==in.heights[i]){
                temp+=1000;
            }

        }else{
            temp+=1000;
        }
        //printf("height: %0.4i\n",temp);
        out.push_back(temp);
    }
    return out;
}
TileMap Chunk::loadTiles(std::string file){
  
    std::string map = loadFile(file);
    TileMap out;
    char lastChar = map[0];//stores last important charecter
    std::string currentNum;
    int temp_number;
    int num_pos=0;
    int x=0,z=0,tempWidth=0;
    int tempTile=0;
    int temp_bottom=0;
    int temp_top=0;
    for(int i =0; i<map.length();i++){
        if(map[i]==','||map[i]==')'){
            temp_number=std::stoi(currentNum);
            //printf("temp_number: %i num_pos: %i\n",temp_number,num_pos);
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
        }
        if(map[i]=='('||map[i]==','||map[i]==')'||map[i]=='\n'||map[i]==' '){
                
            if(map[i]==')'){
                out.map.push_back((TileTypes)tempTile);
                int tileHeight=temp_number;
                out.tilePos.push_back(glm::vec3(x,temp_bottom,z));
                out.heights.push_back(temp_top-temp_bottom);
                z--;
                num_pos=0;
            }
            if(map[i]=='\n'){
                
                x++;
                tempWidth=-1*z;
                z=0;
            }
            lastChar=map[i];
            currentNum="";

        }else{
            currentNum+=map[i];
        }
    }
    out.width=tempWidth;
    out.height=x+1;
    return out;

}

void Chunk::makeMap(TileMap in,std::vector<int> number){
    for(int i=0;i<in.map.size();i++){
        if(in.map[i]==GRASS){
             this->tiles.push_back(Grass(in.tilePos[i],in.heights[i],number[i]));
        }
        if(in.map[i]==ROCK){
             this->tiles.push_back(Rock(in.tilePos[i],in.heights[i],number[i]));
        }
    }
}
void Chunk::setMeshes(){
    mesh = Model(); 
    for(int i = 0; i<tiles.size();i++){
        //printf("texture_num: %i\n",tiles[i].textureNum);
        mesh.add(tiles[i].getModel(),tiles[i].pos,tiles[i].textureNum);
    }
    std::vector<Model> temp = {mesh};
    runModel = initMesh(temp);
}
void Chunk::draw(){
    drawMesh(runModel[0],glm::vec3(0.0,0.0,0.0));
}
Tile Chunk::getTile(int x, int z){
    int index = x*chunkSize+z;
    if(index<0||index>=this->tiles.size()){
        //todo implelemt better error handeling
        printf("wrong tile accessed need to fix\n");
        return this->tiles[0];
    }
    return this->tiles[index];
}
void Chunk::setTile(int x, int z, Tile tile_in){
    this->tiles[x*chunkSize+z]=tile_in;
}
Chunk::~Chunk(){
    this->tiles.clear();
    std::cout<<"chunk deleted\n";
}
World::World(glm::vec3 pos_in){
    player = Entity(glm::vec3(1.0,0.0,0.0));
    printf("hello world");
    std::vector<Tile*> tiles;
}
void World::draw(){
    //printf("drawn!!\n");
    player.draw();
    bindTexture(0);
    this->loadedChunk.draw();    
}
glm::vec3 World::tick(glm::vec3 input_move, float delta_time){
    float temp_deltaT = -1*delta_time;
    glm::vec3 temp_player_pos = player.pos;

    glm::vec3 player_v = glm::vec3(0.0,0.0,0.0);
    player_v.x=input_move.z*(-1);
    player_v.z=input_move.x*(-1);

    player.pos=physics::runFrame(player.pos,player_v,this,delta_time);
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