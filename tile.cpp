#include "tile.h"
#include "OBJ_Loader.h"
#include <string>
Tile::Tile(){
    this->makeModel();
}
Tile::Tile(glm::vec3 pos){
    this->pos=pos;
    this->makeModel();   
}
void Tile::makeModel(){
    printf("OBJ_NAME: %s\n",objName.c_str());
    
    if(objName!=""){
       
        this->loadModel();
        return;
    }else{
        this->genSquare();
    }
}
void Tile::genSquare(){
    std::vector<glm::vec3> pos_model;
    pos_model.reserve(4);
    std::vector<glm::vec2> texcoord;
    texcoord.reserve(4);
    std::vector<unsigned int> indicies;
    indicies.reserve(6);
    std::vector<glm::vec3> normal;
    normal.reserve(6);
//face 0
    pos_model.push_back(glm::vec3(0,0,0));
    pos_model.push_back(glm::vec3(1,0,0));
    pos_model.push_back(glm::vec3(1,0,1));
    pos_model.push_back(glm::vec3(0,0,1));

    texcoord.push_back(glm::vec2(0,0));
    texcoord.push_back(glm::vec2(1,0));
    texcoord.push_back(glm::vec2(1,1));
    texcoord.push_back(glm::vec2(0,1));

    normal.push_back(glm::vec3(0,1,0));
    normal.push_back(glm::vec3(0,1,0));
    normal.push_back(glm::vec3(0,1,0));
    normal.push_back(glm::vec3(0,1,0));

    indicies={0,1,2,0,3,2};
    meshModel = Model(pos_model,texcoord,indicies,normal);
}
void Tile::loadModel(){
    printf("rock loaded\n");
    objl::Loader Loader;
    printf("objName: %s\n",objName.c_str());
    bool loaded = Loader.LoadFile(objName);
    if(!loaded){
        printf("MODEL NOT LOADED!!!!\n\n\n\n");
        return;
    }
    std::vector<glm::vec3> pos;
    std::vector<glm::vec3> normal;
    std::vector<glm::vec2> texCoord;
    std::vector<unsigned int> indices;
    pos.reserve(Loader.LoadedVertices.size());
    normal.reserve(Loader.LoadedVertices.size());
    texCoord.reserve(Loader.LoadedVertices.size());
    for(int i =0;i<Loader.LoadedVertices.size();i++){
        //printf("i: %i\n",i);
        float x,y,z;
        objl::Vector3 temp = Loader.LoadedVertices.at(i).Position;
        //objl::Vector3 temp = Loader.LoadedVertices[i].Position; 
        pos.push_back(glm::vec3(temp.X,temp.Y,temp.Z));
        
        temp = Loader.LoadedVertices.at(i).Normal;
        //temp = Loader.LoadedVertices[i].Normal;
        normal.push_back(glm::vec3(temp.X,temp.Y,temp.Z));

        objl::Vector2 temps = Loader.LoadedVertices.at(i).TextureCoordinate;
        texCoord.push_back(glm::vec2(temps.X,temps.Y));
    }
    for(int i =0; i<Loader.LoadedIndices.size();i++){
        indices.push_back(Loader.LoadedIndices[i]);
    }
    //printf("normal len: %i, pos")
    
    meshModel=Model(pos,texCoord,indices,normal);
}
Grass::Grass(glm::vec3 pos_in){
    this->pos=pos_in;
    this->makeModel();
    this->textureNum=0;
}
Rock::Rock(glm::vec3 pos_in){
    objName="./Models/Rock2.obj";
    this->pos=pos_in;
    this->makeModel();
    this->textureNum=1;
}
