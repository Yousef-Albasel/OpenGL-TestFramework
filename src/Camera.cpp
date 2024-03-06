#include "Camera.h"

void Camera::setCameraPos(glm::vec3 cp)  {
	cameraPos = cp;
};
void Camera::setCameraFront(glm::vec3 cf)  {
	cameraFront = cf;
};
void Camera::setCameraUp(glm::vec3 cu)  {
	cameraUp = cu;
};

glm::mat4 Camera::setViewMat() {
	return (glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp));
};

glm::mat4 Camera::setViewMat(glm::vec3 cp , glm::vec3 cf, glm::vec3 cu) {
	return (glm::lookAt(cp, cp + cf, cu));
};


void Camera::ProcessInputs(GLFWwindow *window,float cameraSpeed, float deltaTime){
    cameraSpeed *= deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) // UP
        cameraPos -= cameraUp * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) // DOWN
        cameraPos += cameraUp * cameraSpeed;

};
