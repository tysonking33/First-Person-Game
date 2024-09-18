#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include "Shader.h"
#include <GLFW/glfw3.h>
#include "Camera.h"

#include <array>
#include <vector>
#include "Color.h"
#include "Renderer.h"
#include "Cube.h"

class Physics_Engine{
public:
    /*-------------------------------------------------checking ray to cube collison---------------------------------------------*/
    bool RayCast(Camera *camera, std::vector<Vertex> DataPoints);       
    bool CheckDotOnBoundedPlane(glm::vec3 point_of_intersection, std::vector<glm::vec3> planeCoordinates, glm::vec3 planeNormal);
    /*---------------------------------------------------------------------------------------------------------------------------*/

    /*-------------------------------------------------checking cube to cube collison---------------------------------------------*/
    bool cubeCollision(Cube *cubeA, Cube *cubeB);

};

#endif