#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Window.h"
#include "stb_image.h"
#include "shader.h"
#include "VertexArray.h"
#include "ElementBuffer.h"
#include "Camera.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Tests/TestClearColor.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "AlbaselStudios", NULL, NULL);

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    float deltaTime = 0.0f;	// Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame
    // ============= Creating VAO,VBO ==============//

    GLfloat vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f


    };

    unsigned int indices[]{
    0,1,3,1,2,3
    };

    VertexArray VAO;
    VertexBuffer VBO(vertices, sizeof(vertices));
    
    VertexBufferLayout layout;
    layout.Push<float>(3); // Pushing Postition
    layout.Push<float>(2); // Pushing TexCoord
    
    VAO.AddBuffer(VBO, layout);

    ElementBuffer EBO(indices, sizeof(indices));
    

    // Link shaders into a program
    Shader shader("res/shader/basic.shader");
    shader.Bind();
    // Loading Texture

    Texture texture("res/textures/diamond.png");
    texture.Bind();

   // setup Camera
    Camera camera;

    // Setup ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window,true);
    ImGui_ImplOpenGL3_Init("#version 330");

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    glm::vec3 translation = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 rotation = glm::vec3(1.0f, 0.0f, 0.0f);
    static int counter = 0;

    /* =========== Main Loop ============= */
   glEnable(GL_DEPTH_TEST);
   while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Delta Time setup
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Model Matrix Setup  (float)glfwGetTime() * 
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(glm::mat4(1.0f), translation);
        model = glm::rotate(model,glm::radians(50.0f), rotation);
        shader.setUniformMatrix4fv("model", 1, GL_FALSE, model);

        // View Matrix Setup
        glm::mat4 view = glm::mat4(1.0f);
        view = camera.setViewMat();
        shader.setUniformMatrix4fv("view", 1, GL_FALSE, view);

        // Projection Matrix setup
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(80.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        shader.setUniformMatrix4fv("projection", 1, GL_FALSE, projection);



        camera.ProcessInputs(window,2.5f,deltaTime);

        shader.Bind(); // Move the shader binding here
        GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
       
        
        // Drawing Stuff in imgui
        {
            ImGui::Begin("AlbaselStudios");
            ImGui::SliderFloat3("Translate", &translation.x, -10.0f, 10.0f);
            ImGui::SliderFloat3("rotate", &rotation.x, -10.0f, 10.0f);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }


        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();

    }
   ImGui_ImplGlfw_Shutdown();
   ImGui_ImplOpenGL3_Shutdown();
   ImGui::DestroyContext();
   glfwTerminate();

    return 0;
}