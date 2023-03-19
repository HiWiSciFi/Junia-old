#pragma once

#include <Junia/Core/Scene.hpp>
#include <string>

class Scene1 : public Junia::Scene
{
	private:
		std::string name;

	public:
		Scene1(const std::string& name);
		~Scene1();
};
