#include "../includes/Renderer.h"

void Renderer::setPlaneColor(const glm::vec3 &color)
{
    planeColor = color;
}

void Renderer::DrawPlane(Shader &shader, Camera &camera)
{

    float vertices[] = {
        // positions          // normals           // texture coords
        -10.0f, 0.0f, -10.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,     //top left
        10.0f, 0.0f, -10.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,      //top right corner
        10.0f, 0.0f, 10.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,       //bottom right corner
        10.0f, 0.0f, 10.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,       //bottom right corner
        -10.0f, 0.0f, 10.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,      //bottom-left corner
        -10.0f, 0.0f, -10.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f};    //top left corner
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    planeColor = Blue;

    shader.use();
    shader.setVec3("planeColor", planeColor); // Set the plane color
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)800 / (float)600, 0.1f, 100.0f);
    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Renderer::DrawStick(Shader &shader, Camera &camera, glm::vec3 start, glm::vec3 end)
{

    float vertices[] = {
        // positions          // normals           // texture coords
        start.x, 0.0f, start.z, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,     //top left
        end.x, 0.0f, start.z, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,      //top right corner
        end.x, 0.0f, end.z, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,       //bottom right corner
        end.x, 0.0f, end.z, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,       //bottom right corner
        start.x, 0.0f, end.z, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,      //bottom-left corner
        start.x, 0.0f, start.z, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f    //top left corner
    };    
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    planeColor = Green;

    shader.use();
    shader.setVec3("planeColor", planeColor); // Set the plane color
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)800 / (float)600, 0.1f, 100.0f);
    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Renderer::DrawCube(Shader &shader, Camera &camera, glm::vec3 start, glm::vec3 end)
{
    float vertices[] = {
        // Top face
        // positions          // normals           // texture coords
        -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, // Top-Left                   //a
        1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // Top-Right                  //b
        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,   // Bottom-Right               //c
        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,   // Bottom-Right               //c
        -1.0f, 1.0f, 10.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,  // Bottom-Left               //d
        -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, // Top-Left                   //a

        // Bottom face
        -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, // Top-Left
        1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,  // Top-Right
        1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,   // Bottom-Right
        1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,   // Bottom-Right
        -1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,  // Bottom-Left
        -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, // Top-Left

        // Front face
        -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // Top-Left
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,   // Top-Right
        1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,  // Bottom-Right
        1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,  // Bottom-Right
        -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // Bottom-Left
        -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // Top-Left

        // Back face
        -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // Top-Left
        1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,  // Top-Right
        1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, // Bottom-Right
        1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, // Bottom-Right
        -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, // Bottom-Left
        -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,  // Top-Left

        // Left face
        -1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-Left
        -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  // Top-Right
        -1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // Bottom-Right
        -1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // Bottom-Right
        -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // Bottom-Left
        -1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-Left

        // Right face
        1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // Top-Left
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,   // Top-Right
        1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // Bottom-Right
        1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // Bottom-Right
        1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // Bottom-Left
        1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f   // Top-Left
    };

    planeColor = Green;

    if (cubeHitStatus == true)
    {
        planeColor = Red;
    }


    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    shader.use();
    shader.setVec3("planeColor", planeColor); // Set the plane color
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)800 / (float)600, 0.1f, 100.0f);
    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    //std::cout << "successfully drawCube\n";
}

void Renderer::ChangeHitStatus()
{
    cubeHitStatus = !cubeHitStatus;
}


//abccda
/*pseudo code
    calculate ray equation

    for loop (0 < 6)
    {
        calculate equation of plane

        if (ray intercept with plane):
            return true 
    }
    return false
*/
bool Renderer::RayCast(glm::vec3 rayPosition, glm::vec3 rayViewDirection, std::vector<Vertex> DataPoints)
{
    /*-------------------------finding equation of ray-------------------------------------------*/
    //t is number of iterations
    //ray(x) = rayPosition.x + t * rayViewDirection.x
    //ray(y) = rayPosition.y + t * rayViewDirection.y
    //ray(z) = rayPosition.z + t * rayViewDirection.z

    for (int i= 0; i < 36; i += 6)
    {
        /*-------------------------find equation of a plane for every face--------------------------*/
        //chose 3 points
        glm::vec3 p1 = glm::vec3{DataPoints[i].position[0], DataPoints[i].position[1], DataPoints[i].position[2]};
        glm::vec3 p2 = glm::vec3{DataPoints[i+1].position[0], DataPoints[i+1].position[1], DataPoints[i+1].position[2]};
        glm::vec3 p3 = glm::vec3{DataPoints[i+2].position[0], DataPoints[i+2].position[1], DataPoints[i+2].position[2]};
        glm::vec3 p4 = glm::vec3{DataPoints[i+4].position[0], DataPoints[i+4].position[1], DataPoints[i+4].position[2]};

        //find 2 vectors in the plane v1 = P2 - P1, v2 = P3 - P1
        glm::vec3 v1 = p2 - p1;
        glm::vec3 v2 = p3 - p1;

        //find normal vector cross_product(v1, v2)
        glm::vec3 normal = glm::cross(v1, v2);

        //normalize the normal vector
        glm::vec3 normalised_normal = glm::normalize(normal);

        /*PLane equation 
        dot_product(n, (x - p)) = 0
        n = normal vector
        p = point on plane
        x is generic point on plane
        */

       /* Line equation
       L(t) = Point + t*Direction_vector
       */

        //compare the same ray to every face to see if the equations will intercept
        if (glm::dot(normalised_normal, rayViewDirection) != 0)
        {
            //plane and line intersect
            float t = glm::dot(normalised_normal, p1 - rayPosition)/ glm::dot(normalised_normal, rayViewDirection);
            
            glm::vec3 point_of_intersection = glm::vec3(rayPosition.x + t * rayViewDirection.x, rayPosition.y + t * rayViewDirection.y, rayPosition.z + t * rayViewDirection.z);

            std::vector<glm::vec3> planeCoordinates;
            planeCoordinates.push_back(p1);
            planeCoordinates.push_back(p2);
            planeCoordinates.push_back(p3);
            planeCoordinates.push_back(p4);

            return CheckDotOnBoundedPlane(point_of_intersection, planeCoordinates);

        }
        else
        {
        
            if (glm::dot(normalised_normal, p1 - rayPosition) == 0)
            {
                //line is a subset of the plane, plane and line intersect
                return true;
            }
        }
    }

    return false;
}

std::vector<Vertex> Renderer::convertPlainArrayToCubeFormat(float originalArray[])
{
    std::vector<Vertex> final_vector;
    for (int i = 0; i < 8*36; i += 8)
    {
        Vertex current_Vertex = Vertex(originalArray[i], originalArray[i+1], originalArray[i+2], originalArray[i+3], originalArray[i+4], originalArray[i+5], originalArray[i+6], originalArray[i+7]);
        final_vector.push_back(current_Vertex);
    }
    return final_vector;

}


bool Renderer::CheckDotOnBoundedPlane(glm::vec3 point_of_intersection, std::vector<glm::vec3> planeCoordinates)
{
    //p1,p2,p3, p4 are in clockwise order starting from top left, top right, bottom right, bottom left
    glm::vec3 p1 = planeCoordinates[0];
    glm::vec3 p2 = planeCoordinates[1];
    glm::vec3 p3 = planeCoordinates[2];
    glm::vec3 p4 = planeCoordinates[3];


    //triangle 1 = p1, p2, p3
    //triangle 2 = p3, p4, p1

}