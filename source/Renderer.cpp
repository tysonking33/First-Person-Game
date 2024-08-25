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

std::vector<float> Renderer::GenerateCube(float size, const glm::vec3& position) {
    float halfSize = size / 2.0f;
    std::vector<float> vertices = {
        // Positions                      // Normals           // Texture Coords
        // Front face
        position.x - halfSize, position.y - halfSize, position.z + halfSize,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        position.x + halfSize, position.y - halfSize, position.z + halfSize,  0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        position.x + halfSize, position.y + halfSize, position.z + halfSize,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        position.x + halfSize, position.y + halfSize, position.z + halfSize,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        position.x - halfSize, position.y + halfSize, position.z + halfSize,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        position.x - halfSize, position.y - halfSize, position.z + halfSize,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        // Back face
        position.x - halfSize, position.y - halfSize, position.z - halfSize,  0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        position.x + halfSize, position.y - halfSize, position.z - halfSize,  0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        position.x + halfSize, position.y + halfSize, position.z - halfSize,  0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        position.x + halfSize, position.y + halfSize, position.z - halfSize,  0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        position.x - halfSize, position.y + halfSize, position.z - halfSize,  0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
        position.x - halfSize, position.y - halfSize, position.z - halfSize,  0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        // Left face
        position.x - halfSize, position.y - halfSize, position.z - halfSize,  -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        position.x - halfSize, position.y - halfSize, position.z + halfSize,  -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        position.x - halfSize, position.y + halfSize, position.z + halfSize,  -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        position.x - halfSize, position.y + halfSize, position.z + halfSize,  -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        position.x - halfSize, position.y + halfSize, position.z - halfSize,  -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        position.x - halfSize, position.y - halfSize, position.z - halfSize,  -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        // Right face
        position.x + halfSize, position.y - halfSize, position.z - halfSize,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        position.x + halfSize, position.y - halfSize, position.z + halfSize,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        position.x + halfSize, position.y + halfSize, position.z + halfSize,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        position.x + halfSize, position.y + halfSize, position.z + halfSize,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        position.x + halfSize, position.y + halfSize, position.z - halfSize,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        position.x + halfSize, position.y - halfSize, position.z - halfSize,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        // Top face
        position.x - halfSize, position.y + halfSize, position.z - halfSize,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        position.x + halfSize, position.y + halfSize, position.z - halfSize,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        position.x + halfSize, position.y + halfSize, position.z + halfSize,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        position.x + halfSize, position.y + halfSize, position.z + halfSize,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        position.x - halfSize, position.y + halfSize, position.z + halfSize,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        position.x - halfSize, position.y + halfSize, position.z - halfSize,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        // Bottom face
        position.x - halfSize, position.y - halfSize, position.z - halfSize,  0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        position.x + halfSize, position.y - halfSize, position.z - halfSize,  0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        position.x + halfSize, position.y - halfSize, position.z + halfSize,  0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        position.x + halfSize, position.y - halfSize, position.z + halfSize,  0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        position.x - halfSize, position.y - halfSize, position.z + halfSize,  0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        position.x - halfSize, position.y - halfSize, position.z - halfSize,  0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    };

    return vertices;
}

void Renderer::DrawCube(Shader &shader, Camera &camera, std::vector<float> vertices)
{
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
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

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


void Renderer::UpdateCube(float size, const glm::vec3& position, std::vector<float>& vertices) {
    float halfSize = size / 2.0f;

    // Update the vertex positions
    for (size_t i = 0; i < vertices.size(); i += 8) {
        // Calculate the relative positions based on the original vertices
        float relativeX = (vertices[i] < position.x) ? -halfSize : halfSize;
        float relativeY = (vertices[i + 1] < position.y) ? -halfSize : halfSize;
        float relativeZ = (vertices[i + 2] < position.z) ? -halfSize : halfSize;

        // Update the vertex position based on the new size and position
        vertices[i]     = position.x + relativeX;
        vertices[i + 1] = position.y + relativeY;
        vertices[i + 2] = position.z + relativeZ;
    }
}



void Renderer::ChangeHitStatus(bool hit)
{
    cubeHitStatus = hit;
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
bool Renderer::RayCast(Camera *camera, std::vector<Vertex> DataPoints)
{
    glm::vec3 rayPosition = camera->getPosition();
    glm::vec3 rayViewDirection = camera->getFront();
    float cameraYaw = camera->getYaw();
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

        /*-------------------------calculating if the plane is in the viewport of the camera--------*/
        glm::vec3 planeCentriod = 0.25f*(p1+p2+p3+p4);


        glm::vec3 rayOToCentroidVec = planeCentriod - rayPosition;

        glm::vec3 normalisedDir = glm::normalize(rayViewDirection);

        glm::vec3 normalisedRayToCentroid = glm::normalize(rayOToCentroidVec);

        float pointToPlaneAngle = acos(cos(glm::dot(normalisedDir, normalisedRayToCentroid)));

        //assume there is a  10 degrees angles to each side for the viewport, idk later, i.e. if yaw is 30 the viewport angle is 75 and -5
        float leftRightAngle = 180.f;
        float clockwiseAngle = cameraYaw - leftRightAngle;
        if (clockwiseAngle <= -359)
        {
            clockwiseAngle += 360;
        }

        float antiClockwiseAngle = cameraYaw + leftRightAngle;
        if (antiClockwiseAngle >= 359)
        {
            antiClockwiseAngle -= 360;
        }


        if (pointToPlaneAngle < clockwiseAngle  || pointToPlaneAngle >  antiClockwiseAngle)
        {
            //out of  viewport
            return false;
        }

        /*---------------------------------calculate collision------------------------------------*/
        glm::vec3 v1 = p2 - p1;
        glm::vec3 v2 = p3 - p1;

        glm::vec3 normalVector = glm::cross(v1, v2);
        glm::vec3 normalisedNormalVector = glm::normalize(normalVector);

        float normDotDir = glm::dot(normalisedNormalVector, rayViewDirection);

        std::cout << "Normal Vector: " << glm::to_string(normalisedNormalVector) << std::endl;
        std::cout << "Ray Direction: " << glm::to_string(normalisedDir) << std::endl;
        std::cout << "Dot Product: " << normDotDir << std::endl;

        const float epsilon = 1e-6f;
        if (fabs(normDotDir) < epsilon)
        {
            //no intersection, parallel
            std::cout << "no intersection, parallel\n";
            //return false;
        }

        //plane's distance from the origin along the normal vector
        float d = glm::dot(normalisedNormalVector, p1);
        float t = (d - glm::dot(normalisedNormalVector, rayPosition))/ (normDotDir);

        if (t < 0)
        {
            //behind ray origin, no collison
            std::cout << "behind ray origin, no collison\n";

            //return false;
        }
        else
        {
            glm::vec3 point_of_intersection = rayPosition + t * rayViewDirection;
            std::vector<glm::vec3> planeCoordinates;

            planeCoordinates.push_back(p1);
            planeCoordinates.push_back(p2);
            planeCoordinates.push_back(p3);
            planeCoordinates.push_back(p4);
            //collison occurs where t is positive, i.e. in front of camera
            if (CheckDotOnBoundedPlane(point_of_intersection, planeCoordinates, normalisedNormalVector) == true)
            {
                return true;
            }
        }
        

    }
    std::cout << "everything failed\n";
    return false;
}

std::vector<Vertex> Renderer::convertPlainArrayToCubeFormat(std::vector<float> originalArray)
{
    std::vector<Vertex> final_vector;
    for (int i = 0; i < 8*36; i += 8)
    {
        Vertex current_Vertex = Vertex(originalArray[i], originalArray[i+1], originalArray[i+2], originalArray[i+3], originalArray[i+4], originalArray[i+5], originalArray[i+6], originalArray[i+7]);
        final_vector.push_back(current_Vertex);
    }
    return final_vector;

}

//checking if the point of interscetion in within the vertexs of the bounded plane not just the infinite plane
bool Renderer::CheckDotOnBoundedPlane(glm::vec3 point_of_intersection, std::vector<glm::vec3> planeCoordinates, glm::vec3 planeNormal)
{
    //p0,p1,p2, p3 are in clockwise order starting from top left, top right, bottom right, bottom left
    glm::vec3 p0 = planeCoordinates[0];
    glm::vec3 p1= planeCoordinates[1];
    glm::vec3 p2 = planeCoordinates[2];
    glm::vec3 p3 = planeCoordinates[3];


    /* ---------------------------triangle 1 = p0, p1, p2------------------------*/
    
    //find vectors
    glm::vec3 v0 = p1- p0;
    glm::vec3 v1 = p2- p0;
    glm::vec3 v2 = point_of_intersection - p0;

    //find dot products
    float dot00 = glm::dot(v0,v0);
    float dot01 = glm::dot(v0,v1);
    float dot02 = glm::dot(v0,v2);
    float dot11 = glm::dot(v1,v1);
    float dot12 = glm::dot(v1,v2);

    //float Calculate Barycentric Coordinates
    float invDenom = 1/(glm::dot(dot00, dot11) - glm::dot(dot01, dot01));

    float alpha = glm::dot((dot11 * dot02) - (dot01 * dot12), invDenom);
    float beta = glm::dot((dot00 * dot12) - (dot01 * dot02), invDenom);

    float yThing = 1 - alpha - beta;

    if ((alpha >= 0 && alpha <= 1)
        && (beta >= 0 && beta <= 1)
        && (alpha + beta <= 1))
        {
            return true;
        }


    /*----------------------------------------------triangle 2 = p2, p3, p0---------------------------------*/

        //find vectors
    v0 = p3 - p2;
    v1 = p0 - p2;
    v2 = point_of_intersection - p2;

    //find dot products
    dot00 = glm::dot(v0,v0);
    dot01 = glm::dot(v0,v1);
    dot02 = glm::dot(v0,v2);
    dot11 = glm::dot(v1,v1);
    dot12 = glm::dot(v1,v2);

    //float Calculate Barycentric Coordinates
    invDenom = 1/(glm::dot(dot00, dot11) - glm::dot(dot01, dot01));

    alpha = glm::dot((dot11 * dot02) - (dot01 * dot12), invDenom);
    beta = glm::dot((dot00 * dot12) - (dot01 * dot02), invDenom);

    yThing = 1 - alpha - beta;

    if ((alpha >= 0 && alpha <= 1)
        && (beta >= 0 && beta <= 1)
        && (alpha + beta <= 1))
        {
            return true;
        }
    std::cout << "point of intersection not in plane\n";
    return false;
}


void Renderer::DrawWall(Shader &shader, Camera &camera)
{

    float vertices[] = {
        // positions          // normals           // texture coords
        -10.0f, -10.0f,10.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,     //top left
        10.0f, -10.0f, 10.0f,0.0f, 1.0f, 0.0f, 1.0f, 0.0f,      //top right corner
        10.0f, 10.0f,10.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,       //bottom right corner
        10.0f,10.0f,10.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,       //bottom right corner
        -10.0f, 10.0f,10.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,      //bottom-left corner
        -10.0f,  -10.0f,10.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f};    //top left corner
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

    planeColor = Gray;

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

bool Renderer::detectWallLeft(Camera *camera)
{
    if (camera->getPosition().z == 10.f)
    {
        return true;
    }
    return false;
}


void Renderer::DrawStreak(Shader &shader, Camera &camera){
    
    float x_start = camera.getPosition().x;
    float y_start = camera.getPosition().y;
    float z_start = camera.getPosition().z;

    float t = 10.f;

    float x_end = camera.getPosition().x + t * camera.getFront().x;
    float y_end = camera.getPosition().y + t * camera.getFront().y;
    float z_end = camera.getPosition().z + t * camera.getFront().z;

    GLfloat vertices[] = {
        x_start, y_start, z_start, // Vertex 1
         x_end,  y_end, z_end // Vertex 2
    };

    // Set up VAO and VBO
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    planeColor = White;

    shader.use();
    shader.setVec3("planeColor", planeColor); // Set the plane color
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)800 / (float)600, 0.1f, 100.0f);
    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 2); // Draw a single line with 2 verticesa

    glBindVertexArray(0);
}
