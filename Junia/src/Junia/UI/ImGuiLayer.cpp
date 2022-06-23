#include "ImGuiLayer.hpp"
#include "JUI.hpp"

namespace Junia
{
	void ImGuiLayer::OnEnable()
	{
		JUI::Init();
	}

	void ImGuiLayer::OnUpdate()
	{
		JUI::Begin();
		JUI::Text("Hello World");
		JUI::End();
	}

	void ImGuiLayer::OnDisable()
	{

	}
}
