#pragma once
#include <functional>
#include <vector>
#include <string>
#include <imgui.h>
namespace test {
	class Test {
	public:
		Test() {};
		virtual ~Test() {};
		virtual void onUpdate(float deltaTime) {};
		virtual void onRender() {};
		virtual void onImGuiRender() {};
	};


	class TestMenu : public Test{
	public:
		TestMenu(Test*& currentTestPointer);
		virtual ~TestMenu() {};
		virtual void onImGuiRender();
	
		template<typename T>
		void RegisterTest(const std::string& name) {
			m_Tests.push_back(std::make_pair(name, []() {return new T();}));
		}
	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_Tests;
	
	};
}