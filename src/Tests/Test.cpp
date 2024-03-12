#include "test.h"

namespace test {
	
	
	TestMenu::TestMenu(Test*& currentTestPointer) : m_CurrentTest(currentTestPointer) {};
	
	void TestMenu::onImGuiRender() {
		for (auto& test : m_Tests) {
			if (ImGui::Button(test.first.c_str())) // if pressed
			{
				m_CurrentTest = test.second();
			}
		}
	};
}