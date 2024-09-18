#include "../includes/Renderer.h"

void Renderer::setPlaneColor(const glm::vec3 &color)
{
    planeColor = color;
}

void Renderer::DrawPlane(Shader &shader, Camera &camera)
{

    float vertices[] = {
        // positions          // normals           // texture coords
        -10.0f, 0.0f, -10.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,  // top left
        10.0f, 0.0f, -10.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // top right corner
        10.0f, 0.0f, 10.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,    // bottom right corner
        10.0f, 0.0f, 10.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,    // bottom right corner
        -10.0f, 0.0f, 10.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,   // bottom-left corner
        -10.0f, 0.0f, -10.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f}; // top left corner
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

    float vertices[] = {
        // positions          // normals           // texture coords
        -10.0f, -10.0f, 10.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,  // top left
        10.0f, -10.0f, 10.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // top right corner
        10.0f, 10.0f, 10.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,    // bottom right corner
        10.0f, 10.0f, 10.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,    // bottom right corner
        -10.0f, 10.0f, 10.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,   // bottom-left corner
        -10.0f, -10.0f, 10.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f}; // top left corner
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

void Renderer::DrawStreak(Shader &shader, Camera &camera)
{

    float x_start = camera.getPosition().x;
    float y_start = camera.getPosition().y;
    float z_start = camera.getPosition().z;

    float t = 10.f;

    float x_end = camera.getPosition().x + t * camera.getFront().x;
    float y_end = camera.getPosition().y + t * camera.getFront().y;
    float z_end = camera.getPosition().z + t * camera.getFront().z;

    GLfloat vertices[] = {
        x_start, y_start, z_start, // Vertex 1
        x_end, y_end, z_end        // Vertex 2
    };

    // Set up VAO and VBO
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
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
