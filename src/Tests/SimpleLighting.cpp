#include"SimpleLighting.h"

namespace test {
	SimpleLighting::SimpleLighting(): m_Translation(0.0f, 0.0f, 0.0f), m_Rotation(1.0f, 0.0f, 0.0f), lightPos(3.0f,0.0f,1.0f) {
        float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
        };
        unsigned int indices[]{
            0,1,3,1,2,3
        };

        m_VAO = std::make_unique<VertexArray>();
        m_VBO = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
        VertexBufferLayout layout;
        layout.Push<float>(3); // Pushing Postition
        layout.Push<float>(3); // Pushing light unit
        m_VAO->AddBuffer(*m_VBO, layout);
        m_Camera = std::make_unique<Camera>();

        m_shader = std::make_unique<Shader>("res/shader/light.shader");
        m_shader->Bind();
        m_shader->SetUniform3f("objectColor", 1.0f, 0.5f, 0.31f);
        m_shader->SetUniform3f("lightColor", 1.0f, 1.0f, 1.0f); 
        
        m_LightSourceShader = std::make_unique<Shader>("res/shader/LightSource.shader");
    };

	SimpleLighting::~SimpleLighting() {};

	void SimpleLighting::onUpdate(float deltaTime)  {};



	void SimpleLighting::onRender()  {
		GLCall(glClearColor(0.07f,0.07f,0.07f,1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        m_VBO->Bind();
        m_shader->Bind(); 
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(glm::mat4(1.0f), m_Translation);
        model = glm::rotate(model, glm::radians(50.0f), m_Rotation);
        m_shader->setUniformMatrix4fv("model", 1, GL_FALSE, model);

        // View Matrix Setup
        glm::mat4 view = glm::mat4(1.0f);
        view = m_Camera->setViewMat();
        m_shader->setUniformMatrix4fv("view", 1, GL_FALSE, view);
        glm::vec3 CameraPos = m_Camera->getCameraPos();
        m_shader->SetUniform3f("viewPos", CameraPos.x,CameraPos.y,CameraPos.z );
        // Projection Matrix setup
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(80.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        m_shader->setUniformMatrix4fv("projection", 1, GL_FALSE, projection);
        
        // Lighted Cube Call
        m_shader->setUniformMatrix4fv("model", 1, GL_FALSE, model);
        m_shader->SetUniform3f("lightPos", lightPos.x, lightPos.y, lightPos.z);
        GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));

        // Light source Call
        lightPos.x = 2.0f * cos(glfwGetTime() * glm::radians(60.0f));
        lightPos.z = 2.0f * sin(glfwGetTime() * glm::radians(60.0f));

        m_LightSourceShader->Bind();
        glm::mat4 lightModel = glm::mat4(1.0f);
        lightModel = glm::translate(glm::mat4(1.0f), lightPos);
        lightModel = glm::scale(lightModel, glm::vec3(0.2f));
        lightModel = glm::rotate(lightModel, glm::radians(60.0f), glm::vec3(1.0f, 0.0f, 1.0f));

        // View Matrix Setup
        m_LightSourceShader->setUniformMatrix4fv("view", 1, GL_FALSE, view);

        // Projection Matrix setup
        m_LightSourceShader->setUniformMatrix4fv("projection", 1, GL_FALSE, projection);


        m_LightSourceShader->setUniformMatrix4fv("model", 1, GL_FALSE, lightModel);
        GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));

	};
	void SimpleLighting::onImGuiRender() {
        ImGui::SliderFloat3("Translate", &m_Translation.x, -10.0f, 10.0f);
        ImGui::SliderFloat3("rotate", &m_Rotation.x, -10.0f, 10.0f);
        ImGui::SliderFloat3("Translate Light Souce", &lightPos.x, -10.0f, 10.0f);
	};

}