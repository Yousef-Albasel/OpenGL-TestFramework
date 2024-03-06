#pragma once
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <GLFW/glfw3.h>

class Camera {
    glm::vec3         cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
    glm::vec3         cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3         cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
public:
    Camera() {
    };

    void setCameraPos( glm::vec3 cp);
    void setCameraFront(glm::vec3 cf);
    void setCameraUp(glm::vec3 cu);

    glm::mat4 setViewMat();
    glm::mat4 setViewMat(glm::vec3 cp, glm::vec3 cf, glm::vec3 cu);

    void ProcessInputs(GLFWwindow *window,float cameraSpeed,float deltaTime);

};