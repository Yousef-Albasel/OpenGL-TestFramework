#pragma once
#include "Test.h"
#include "../Window.h"
#include "GL/glew.h"
#include "imgui.h"
namespace test {
	class TestClearColor : public Test {
	public:
		TestClearColor();
		~TestClearColor();

		void onUpdate(float deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;
	private:
		float m_ClearColor[4];
	};

}