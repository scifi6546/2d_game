#include "tile.h"
#include "OBJ_Loader.h"
#include <string>
Tile::Tile(){
    //this->makeModel();
}
void Tile::makeModel(int bottom,int height,int number){
    printf("OBJ_NAME: %s\n",objName.c_str());
    if(useMultiModels){
        //to implement properly
        this->meshModel=this->loadMultiModel(bottom,height+bottom,number);
        return;
    }
    if(objName!=""){
       
        this->meshModel=this->loadModel(objName);
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
Model Tile::loadMultiModel(int bottom,int top, int number){//to finish
    printf("used multi models!\n");
    Model temp;
    char tempStr[4];
    sprintf(tempStr,"%0.4i",number);
    std::string numStr = tempStr;
    for(int i =bottom;i<top;i++){
        if(i==bottom){
            temp.add(loadModel(multiBasePath+numStr+"_bot.obj"),glm::vec3(0.0,i,0.0),textureNum);
        }else if(i==top){
            temp.add(loadModel(multiBasePath+numStr+"_top.obj"),glm::vec3(0.0,i,0.0),textureNum);
        }else{
            
            temp.add(loadModel(multiBasePath+numStr+"_mid.obj"),glm::vec3(0.0,i,0.0),textureNum);
        }
    }
    return temp;
}
Model Tile::loadModel(std::string in){
    //printf("rock loaded\n");
    objl::Loader Loader;
    printf("objName: %s\n",in.c_str());
    bool loaded = Loader.LoadFile(in);
    if(!loaded){
        printf("MODEL NOT LOADED!!!!\n\n\n\n");
        return Model();
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
    
    return Model(pos,texCoord,indices,normal);
}
Grass::Grass(glm::vec3 pos_in,int height,int number){
    this->pos=pos_in;
    this->makeModel(round(pos_in.y),height,number);
    this->textureNum=0;
}
Rock::Rock(glm::vec3 pos_in,int height,int number){
    //objName="./Models/Rock.obj";
    objName="./Models/rock/bottom.obj";
    this->pos=pos_in;
    this->useMultiModels=true;
    this->makeModel(round(pos_in.y),height,number);
    this->textureNum=1;
}
