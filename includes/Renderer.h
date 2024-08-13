#ifndef RENDERER_H
#define RENDERER_H

#include "Shader.h"
#include <GLFW/glfw3.h>
#include "Camera.h"

class Renderer {
public:
    Renderer() {}

    void DrawPlane(Shader &shader, Camera &camera);
    void setPlaneColor(const glm::vec3 &color);  // Method to set the plane color


    void DrawCube(Shader &shader, Camera &camera);
private:
        glm::vec3 planeColor;  // Color variable

};
#endif
