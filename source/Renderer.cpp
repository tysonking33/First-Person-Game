#include "../includes/Renderer.h"

void Renderer::setPlaneColor(const glm::vec3 &color)
{
    planeColor = color;
}

void Renderer::DrawPlane(Shader &shader, Camera &camera)
{
    // Updated vertices for a 20x20 plane, only in positive coordinates
    float vertices[] = {
        // positions          // normals           // texture coords
        0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,    // bottom-left corner (0, 0)
        20.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // bottom-right corner (20, 0)
        20.0f, 0.0f, 20.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,   // top-right corner (20, 20)
        
        20.0f, 0.0f, 20.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,   // top-right corner (20, 20)
        0.0f, 0.0f, 20.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,    // top-left corner (0, 20)
        0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f     // bottom-left corner (0, 0)
    };

    // Set up the VAO and VBO
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture coordinates attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Set plane color
    planeColor = Blue;

    shader.use();
    shader.setVec3("planeColor", planeColor); // Set the plane color
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)800 / (float)600, 0.1f, 100.0f);
    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);

    // Draw the plane
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Clean up
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}


void Renderer::DrawCubeBasic(Shader &shader, Camera &camera, std::vector<float> vertices, glm::vec3 cubeColor)
{

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
    shader.setVec3("planeColor", cubeColor); // Set the plane color
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

    // std::cout << "successfully drawCube\n";
}

std::vector<Vertex> Renderer::convertPlainArrayToCubeFormat(std::vector<float> originalArray)
{
    std::vector<Vertex> final_vector;
    for (int i = 0; i < 8 * 36; i += 8)
    {
        Vertex current_Vertex = Vertex(originalArray[i], originalArray[i + 1], originalArray[i + 2], originalArray[i + 3], originalArray[i + 4], originalArray[i + 5], originalArray[i + 6], originalArray[i + 7]);
        final_vector.push_back(current_Vertex);
    }
    return final_vector;
}

void Renderer::DrawWall(Shader &shader, Camera &camera)
{
    // Updated vertices for a wall that spans in positive coordinates and has a height of 20
    float vertices[] = {
        // positions          // normals           // texture coords
        0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,     // bottom-left corner (0, 0)
        20.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,    // bottom-right corner (20, 0)
        20.0f, 20.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,    // top-right corner (20, 20)
        
        20.0f, 20.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,    // top-right corner (20, 20)
        0.0f, 20.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,     // top-left corner (0, 20)
        0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f      // bottom-left corner (0, 0)
    };

    // Set up the VAO and VBO
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture coordinates attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Set wall color
    planeColor = Gray;

    shader.use();
    shader.setVec3("planeColor", planeColor); // Set the wall color
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)800 / (float)600, 0.1f, 100.0f);
    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);

    // Draw the wall
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Clean up
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

void Renderer::DrawCuboid(Shader &shader, Camera &camera, glm::vec3 position, float orientation, glm::vec3 dimensions)
{
    // Define the cuboid vertices
    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f,  // front-bottom-left
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  1.0f, 0.0f,  // front-bottom-right
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  1.0f, 1.0f,  // front-top-right

         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  1.0f, 1.0f,  // front-top-right
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  0.0f, 1.0f,  // front-top-left
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f,  // front-bottom-left

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f,  0.0f, 0.0f,  // back-bottom-left
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f,  1.0f, 0.0f,  // back-bottom-right
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  1.0f,  1.0f, 1.0f,  // back-top-right

         0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  1.0f,  1.0f, 1.0f,  // back-top-right
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  1.0f,  0.0f, 1.0f,  // back-top-left
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f,  0.0f, 0.0f,  // back-bottom-left

        -0.5f,  0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  0.0f, 1.0f,  // left-top-front
        -0.5f,  0.5f,  0.5f, -1.0f, 0.0f,  0.0f,  0.0f, 0.0f,  // left-top-back
        -0.5f, -0.5f,  0.5f, -1.0f, 0.0f,  0.0f,  1.0f, 0.0f,  // left-bottom-back

        -0.5f, -0.5f,  0.5f, -1.0f, 0.0f,  0.0f,  1.0f, 0.0f,  // left-bottom-back
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  0.0f, 0.0f,  // left-bottom-front
        -0.5f,  0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  0.0f, 1.0f,  // left-top-front

         0.5f,  0.5f, -0.5f,  1.0f, 0.0f,  0.0f,  0.0f, 1.0f,  // right-top-front
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f,  0.0f, 0.0f,  // right-top-back
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f,  1.0f, 0.0f,  // right-bottom-back

         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f,  1.0f, 0.0f,  // right-bottom-back
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  0.0f,  0.0f, 0.0f,  // right-bottom-front
         0.5f,  0.5f, -0.5f,  1.0f, 0.0f,  0.0f,  0.0f, 1.0f   // right-top-front
    };

    // Scale the cuboid to the given width, height, and depth
    for (int i = 0; i < sizeof(vertices) / sizeof(vertices[0]); i += 8)
    {
        vertices[i] *= dimensions.x;  // Scale x
        vertices[i + 1] *= dimensions.y;  // Scale y
        vertices[i + 2] *= dimensions.z;  // Scale z
    }

    // Set up the VAO and VBO
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture coordinates attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Set cuboid color (can customize or pass as parameter)
    glm::vec3 cuboidColor = glm::vec3(1.0f, 0.0f, 0.0f); // Red

    shader.use();
    shader.setVec3("planeColor", cuboidColor);

    // Create the model matrix for translation and rotation
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);  // Translate to position
    model = glm::rotate(model, glm::radians(orientation), glm::vec3(0.0f, 1.0f, 0.0f));  // Rotate around the Y-axis

    // Set up view and projection matrices
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)800 / (float)600, 0.1f, 100.0f);

    // Set shader uniforms
    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);

    // Draw the cuboid
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36); // 36 vertices for 12 triangles in a cuboid

    // Clean up
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}


void Renderer::DrawSquare(Shader &shader, glm::vec2 position, float size)
{
    // Define the square vertices in 2D space
    std::vector<float> vertices = {
        // Positions       // Normals         // TexCoords
        position.x - size, position.y - size, 0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom-left corner
        position.x + size, position.y - size, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // Bottom-right corner
        position.x + size, position.y + size, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Top-right corner

        position.x - size, position.y - size, 0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom-left corner
        position.x + size, position.y + size, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Top-right corner
        position.x - size, position.y + size, 0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f  // Top-left corner
    };

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // TexCoord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    shader.use();
    
    // Set model matrix for translation
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f)); // Adjust position of square
    shader.setMat4("model", model);

    // Set orthogonal projection for the minimap
    glm::mat4 projection = glm::ortho(0.0f, 1.0f, 0.0f, 1.0f);  // Mapping the minimap to normalized screen coordinates
    shader.setMat4("projection", projection);

    // Set a default color (e.g., white) for the square
    shader.setVec3("planeColor", glm::vec3(0.0f, 1.0f, 0.0f));  // Green for square

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Renderer::DrawCircle(Shader &shader, glm::vec2 position, float radius)
{
    const int numSegments = 36; // Number of segments (triangles) to approximate the circle
    std::vector<float> vertices;
    
    for (int i = 0; i < numSegments; ++i)
    {
        float theta = 2.0f * 3.14159265359f * float(i) / float(numSegments);  // Angle for each vertex
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        
        // Add the vertices for each segment
        vertices.push_back(position.x + x);
        vertices.push_back(position.y + y);
        vertices.push_back(0.0f); // z-coordinate (2D, so z is 0)
        vertices.push_back(0.0f); // Normals (not used for circles)
        vertices.push_back(0.0f); // Normals (not used for circles)
        vertices.push_back(1.0f); // Normals (not used for circles)
        vertices.push_back(0.0f); // Texture coord (not used)
        vertices.push_back(0.0f); // Texture coord (not used)
    }

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Normal attribute (not used for circle, but required by shader)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // TexCoord attribute (not used, but required)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    shader.use();
    
    // Set model matrix for translation
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f)); // Adjust position of circle
    shader.setMat4("model", model);

    // Set orthogonal projection for the minimap
    glm::mat4 projection = glm::ortho(0.0f, 1.0f, 0.0f, 1.0f);  // Mapping the minimap to normalized screen coordinates
    shader.setMat4("projection", projection);

    // Set a default color (e.g., white) for the circle
    shader.setVec3("planeColor", glm::vec3(1.0f, 0.0f, 0.0f));  // Red for circle

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, numSegments);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Renderer::renderMinimap(Shader &shader, Camera &camera, glm::vec3 playerPosition, glm::vec3 enemyPosition, std::vector<Obstacle*> obstacles, float mapWidth, float mapHeight)
{
    // Set the orthogonal projection for the minimap (no perspective)
    glm::mat4 projection = glm::ortho(0.0f, 1.0f, 0.0f, 1.0f);  // Mapping the minimap to normalized screen coordinates
    shader.setMat4("projection", projection);

    // Render Player (as a circle)
    shader.use();
    glm::vec2 playerMinimapPos = glm::vec2(playerPosition.x / mapWidth, playerPosition.z / mapHeight);  // Normalize to minimap space
    shader.setVec3("planeColor", glm::vec3(1.0f, 1.0f, 1.0f));  // White color for player
    DrawCircle(shader, playerMinimapPos, 0.02f);  // Draw player with a radius of 0.02f

    // Render Enemy (as a circle)
    glm::vec2 enemyMinimapPos = glm::vec2(enemyPosition.x / mapWidth, enemyPosition.z / mapHeight);  // Normalize to minimap space
    shader.setVec3("planeColor", glm::vec3(1.0f, 0.0f, 0.0f));  // Red color for enemy
    DrawCircle(shader, enemyMinimapPos, 0.02f);  // Draw enemy with a radius of 0.02f

    // Render Obstacles (as squares)
    for (const auto& obstacle : obstacles) {
        glm::vec2 obstacleMinimapPos = glm::vec2(obstacle->position.x / mapWidth, obstacle->position.z / mapHeight);  // Normalize to minimap space
        shader.setVec3("planeColor", glm::vec3(0.0f, 1.0f, 0.0f));  // Green color for obstacles
        DrawSquare(shader, obstacleMinimapPos, 0.03f);  // Draw obstacle with size 0.03f
    }
}
