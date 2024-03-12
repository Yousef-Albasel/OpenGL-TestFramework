#pragma once
#include "Test.h"
#include "../Window.h"
#include "GL/glew.h"
#include "imgui.h"
#include "../VertexArray.h"
#include "../VertexBuffer.h"
#include "../VertexBufferLayout.h"
#include "../ElementBuffer.h"
#include "../Shader.h"
#include "../Texture.h"
#include "../Camera.h"
#include <glm/gtc/type_ptr.hpp>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <memory>
#include <GLFW/glfw3.h>


namespace test {
	class SimpleCube : public Test {
	public:
		SimpleCube();
		~SimpleCube();

		void onUpdate(float deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<Shader> m_shader;
		std::unique_ptr<Camera> m_Camera;
		std::unique_ptr<Texture> m_Texture;

	
		glm::vec3 m_Translation;
		glm::vec3 m_Rotation;

	};

}