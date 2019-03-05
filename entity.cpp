#include "entity.h"
#include "mesh.h"

Entity::Entity(glm::vec3 in){
    this->pos=in;
    
    this->initModel();
}
void Entity::initModel(){
    this->model=getModel();
    //std::vector<Model> temp = {this->model};
    std::vector<RunTimeModel> tempRun = initMesh({this->model});
    this->runModel=tempRun[0];
}
void Entity::draw(){
    drawMesh(runModel,pos);
}
Model Entity::getModel(){
    Model temp;
    std::vector<glm::vec3> pos_model;
    pos_model.reserve(4);
    std::vector<glm::vec2> texcoord;
    texcoord.reserve(4);
    std::vector<unsigned int> indicies;
    indicies.reserve(6);
    std::vector<glm::vec3> normal;
    normal.reserve(6);
//face 0
    pos_model.push_back(glm::vec3(0.0,0.0,0.0));
    pos_model.push_back(glm::vec3(0.0,0.0,1.0));
    pos_model.push_back(glm::vec3(0.0,1.0,1.0));
    pos_model.push_back(glm::vec3(0.0,1.0,0.0));

    texcoord.push_back(glm::vec2(0.0,1.0));
    texcoord.push_back(glm::vec2(1.0,1.0));
    texcoord.push_back(glm::vec2(1.0,0.0));
    texcoord.push_back(glm::vec2(0.0,0.0));

    normal.push_back(glm::vec3(1.0,0,0));
    normal.push_back(glm::vec3(1.0,0,0));
    normal.push_back(glm::vec3(1.0,0,0));
    normal.push_back(glm::vec3(1.0,0,0));

    indicies={0,1,2,0,3,2};
    temp.add(Model(pos_model,texcoord,indicies,normal),glm::vec3(0.0,0.0,0.0),2);
    return temp;
}