#include "physics.h"
glm::vec3 stored_velocity=glm::vec3(0.0f,0.0f,0.0f);
glm::vec3 physics::runFrame(glm::vec3 player_pos, glm::vec3 player_v, World * gameWorld, float deltaT){
    glm::vec3 temp_pos = player_pos+player_v*deltaT;
    int x = floor(temp_pos.x);
    int y = floor(temp_pos.x);
    int z = floor(temp_pos.z);
    Tile temp = gameWorld->getTile(x,z);
    
    return temp_pos;
}