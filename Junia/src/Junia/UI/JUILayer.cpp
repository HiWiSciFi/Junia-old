#include "JUILayer.hpp"
#include "JUI.hpp"

namespace Junia
{
	void JUILayer::OnEnable() { JUI::Init(); }

	void JUILayer::OnUpdate()
	{
		JUI::Begin();
		JUI::Text("Hello World");
		JUI::End();
	}

	void JUILayer::OnDisable() { JUI::Shutdown(); }
}
