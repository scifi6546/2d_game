#ifndef ENTITY_H
#define ENTITY_H
#include "mesh.h"
#include <glm/glm.hpp>
    class Entity{
        public:
            Entity(){Entity(glm::vec3(0.0,0.0,0.0)
            );};
            Entity(glm::vec3 in);
            void draw();
            glm::vec3 pos=glm::vec3(0.0,0.0,0.0);
        private:
            Model model;
            RunTimeModel runModel;
            void initModel();
            Model getModel();
            

    };
#endif