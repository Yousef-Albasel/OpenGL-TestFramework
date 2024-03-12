#include"SimpleCube.h"

namespace test {
	SimpleCube::SimpleCube() : m_Translation(1.0f, 0.0f, 0.0f), m_Rotation(1.0f, 0.0f, 0.0f)  {
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

        m_VAO = std::make_unique<VertexArray>();
        m_VBO = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
        VertexBufferLayout layout;
        layout.Push<float>(3); // Pushing Postition
        layout.Push<float>(2); // Pushing TexCoord
        m_VAO->AddBuffer(*m_VBO, layout);
        m_Camera = std::make_unique<Camera>();

        m_shader = std::make_unique<Shader>("res/shader/basic.shader");
        m_Texture = std::make_unique<Texture>("res/textures/diamond.png");

        // Model Matrix Setup  (float)glfwGetTime() * 
        


    };

	SimpleCube::~SimpleCube() {};

	void SimpleCube::onUpdate(float deltaTime)  {};
	void SimpleCube::onRender()  {
		GLCall(glClearColor(0.07f,0.07f,0.07f,1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));


        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(glm::mat4(1.0f), m_Translation);
        model = glm::rotate(model, glm::radians(50.0f), m_Rotation);
        m_shader->setUniformMatrix4fv("model", 1, GL_FALSE, model);

        // View Matrix Setup
        glm::mat4 view = glm::mat4(1.0f);
        view = m_Camera->setViewMat();
        m_shader->setUniformMatrix4fv("view", 1, GL_FALSE, view);

        // Projection Matrix setup
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(80.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        m_shader->setUniformMatrix4fv("projection", 1, GL_FALSE, projection);
        m_VBO->Bind();
        m_shader->Bind(); 
        m_Texture->Bind();
        GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));

	};
	void SimpleCube::onImGuiRender() {
        ImGui::SliderFloat3("Translate", &m_Translation.x, -10.0f, 10.0f);
        ImGui::SliderFloat3("rotate", &m_Rotation.x, -10.0f, 10.0f);
	};

}